//
// Created by 杨忠诚 on 18/1/12.
//

#include "recognizer.h"
#include "gesture_utils.h"
#ifdef ANDROID
#include <pthread.h>
#else
#include <pthread/pthread.h>
#endif
#include "distance_reducer.h"
#include "distance_matcher.h"
#include <algorithm>
#include <cstring>
#include <cmath>
#include "vector_reducer.h"
#include "vector_matcher.h"
#include "gesture_classification.h"
#include "ncnn_classification.h"
#include "gesture_pair_rule.h"
#include "ncnn_pair_rule.h"

using namespace ns_recognizer;

static Recognizer *_instance = 0;
pthread_mutex_t mutex_1;

Recognizer::Recognizer() {
}

Recognizer::~Recognizer() {

}

void Recognizer::useGestureClassif(std::string filePath, float density) {
    this->density = density;
    this->pairRule = new GesturePairRule();
    this->classification = new GestureClassification(filePath, pairRule);
}

void Recognizer::useNcnnClassif(const unsigned char *_paraMem, const unsigned char *_binMem,
                                string _wordTxt) {
    this->pairRule = new NcnnPairRule();
    this->classification = new NcnnClassification(_paraMem, _binMem, _wordTxt);
}

Recognizer* Recognizer::getInstance() {
    pthread_mutex_lock(&mutex_1);
    if (_instance == 0) {
        _instance = new Recognizer();
    }
    pthread_mutex_unlock(&mutex_1);
    return _instance;
}

vector<TResult*> Recognizer::recognizer(Gesture* gesture) {
    return this->classification->recognizer(gesture);
}

std::vector<Gesture*> mergeGesture(std::vector<Gesture*> g) {
    return g;
}

TResult* getBestResult(std::vector<TResult*> results, Gesture * gesture) {
//    std::sort(results.begin(), results.end(), compare);
    TResult *bestResult = NULL;
    if (!results.empty()) {
        int dimensNum = gesture->getDimensionalNum();
        int smallDimensDiff = 100;
        float maxScore = -1;
        for (int i = 0; i < results.size(); i++) {
            TResult *item = results[i];
            if (abs(dimensNum - item->dimensional) <= smallDimensDiff && item->score > maxScore) {
                bestResult = item;
                maxScore = item->score;
            }
        }
    }
    return bestResult;
}

std::string Recognizer::getCombinationString(std::vector<TResult*> list, int start, int end) {
    std::string result;
    for (int i = start; i < end; i++) {
        TResult *r = list[i];
        if (r->isShort == 1) {
            result.append(MAKE_KEY(pairRule->getShortLabel(r->tag)));
        } else {
            result.append(MAKE_KEY(r->tag));
        }
    }
    std::map<std::string, std::string>::iterator it;
    std::map<std::string, std::string> combination = this->pairRule->getCombinationLabels();
    it = combination.find(result);
    return it->second;
}

int Recognizer::getMaxCombinationIndex(std::vector<TResult*> list, int start, int end) {
    std::string tempLabel;
    int maxIndex = -1;
    std::map<std::string, std::string> map = this->pairRule->getCombinationLabels();
    for (int i = start; i < end; i++) {
        if (list[i]->isShort == 1) {
            tempLabel.append(MAKE_KEY(pairRule->getShortLabel(list[i]->tag)));
        } else {
            tempLabel.append(MAKE_KEY(list[i]->tag));
        }
        printf("getMaxCombinationIndex tempLabel: %s, isShort: %s\n", tempLabel.c_str(), list[i]->isShort ? "short" : "normal");
        if (map.find(tempLabel.c_str()) != map.end()) {
            maxIndex = i + 1;
        }
    }
    return maxIndex;
}

std::vector<TResult*> Recognizer::getCombinationResult(std::vector<TResult*> list, float maxDistance) {
    std::vector<TResult*> results;
    int i = 0;
    while (i < list.size()) {
        int index = getMaxCombinationIndex(list, i, list.size());
        printf("merge from i: %d to %d\n", i, index);
        if (index > 0) {
            std::string tag = getCombinationString(list, i, index);
            printf("getCombinationString string %s\n", tag.c_str());
            if (i == (index - 1)) {
                list[i]->tag = tag;
                results.push_back(list[i]);
            } else {
                std::vector<TResult*> combinationResults;
                combinationResults.insert(combinationResults.end(), list.begin() + i, list.begin() + index);
                RectF rectF = GestureUtils::getBoundBox(combinationResults);
                TResult *r = new TResult(&tag, 100);
                r->left = rectF.left;
                r->top = rectF.top;
                r->right = rectF.right;
                r->bottom = rectF.bottom;
                results.push_back(r);
            }
            i = index;
        } else {
            std::map<std::string, std::string> map = this->pairRule->getCombinationLabels();
            TResult *nextResult = list[i];
            if (nextResult->isShort == 1 && nextResult->dimensional <= 2) {
                std::string next = std::string(PairRule::DOT);
                results.push_back(new TResult(&next, 100));
            } else {
                std::map<std::string, std::string>::iterator it;
                it = map.find(MAKE_KEY(nextResult->tag));
                if (it != map.end()) {
                    results.push_back(new TResult(&(it->second), 100));
                } else {
                    std::string unknown("?");
                    results.push_back(new TResult(&unknown, 100));
                };
            }
            i ++;
        }
    }
    return results;
}

vector<TResult*> Recognizer::recognizer(vector<Gesture*> gs) {
    std::vector<TResult*> result;
    //合并手势
    std::vector<Gesture*> gestures = mergeGesture(gs);

    printf("====================");
    printf("input gesture size: %d\n", gs.size());

    std::string dd = MAKE_KEY_3("1", "2", "3");
    printf("data %s", dd.c_str());
//    printf("data %s", MAKE_KEY_2("1", "2").c_str());
//    printf("data %s", MAKE_KEY_3("1", "2", "3").c_str());

    std::vector<TResult*> bestResults;
    float maxDistance = 0;
    for (int i = 0; i < gestures.size(); ++i) {
        Gesture *gesture = gestures[i];
        //识别单个笔画
        std::vector<TResult*> itemResult = recognizer(gesture);
        TResult *bestResult = getBestResult(itemResult, gesture);
        if (bestResult == NULL) {
            continue;
        }
        bestResults.push_back(bestResult);

        float width = bestResult->right - bestResult->left;
        float height = bestResult->bottom - bestResult->top;
        double distance = sqrt(width * width + height * height);
        if (distance > maxDistance) {
            maxDistance = distance;
        }
    }

    std::vector<TResult*> labels;
    for (int i = 0; i < bestResults.size(); i++) {
        //识别单个笔画
        TResult *bestResult = bestResults[i];
        float width = bestResult->right - bestResult->left;
        float height = bestResult->bottom - bestResult->top;
        double distance = sqrt(width * width + height * height);
//        if (distance < maxDistance * DOT_GESTURE_THRESHOLD) {
//            //modify value
//            bestResult->tag = PairRule::DOT;
//        }else
        if (distance < maxDistance * SMALL_GESTURE_THRESHOLD && bestResult->dimensional <= 2) {
            bestResult->isShort = 1;
        } else {
            bestResult->isShort = 0;
        }

        printf("--> bestResult: %s, isShort: %s\n", bestResult->tag.c_str(), bestResult->isShort==1 ? "short" : "normal");
        if (!bestResult->tag.empty()) {
            bool isSingleGesture = pairRule->isSingleGesture(bestResult->tag);
            printf("--> bestResult: %s, isSingleGesture: %s\n", isSingleGesture ? "single" : "pair");
            if (isSingleGesture) {
                if (!labels.empty()) {
                    std::vector<TResult*> rs = getCombinationResult(labels, maxDistance);
                    result.insert(result.end(), rs.begin(), rs.end());
                    labels.clear();
                }
                result.push_back(bestResult);
            } else {
                labels.push_back(bestResult);
            }
        }
    }
    if (!labels.empty()) {
        std::vector<TResult*> rs = getCombinationResult(labels, maxDistance);
        result.insert(result.end(), rs.begin(), rs.end());
    }

    for (int i = 0; i < result.size(); i++) {
        TResult *r = result[i];
        float width = result[i]->right - result[i]->left;
        float height = result[i]->bottom - result[i]->top;
        double distance = sqrt(width * width + height * height);

        bool isShort = distance <= maxDistance * SMALL_GESTURE_THRESHOLD;
        r->tag = pairRule->getAlias(isShort && r->dimensional <= 2 ? PairRule::DOT : r->tag);
        printf("result: %s, left: %f, top: %f, right:%f, bottom:%f\n", r->tag.c_str(), r->left, r->top, r->right, r->bottom);
    }
    return result;
}

std::map<std::string, std::vector<Polyline*> > Recognizer::getTemplate() {
    return this->classification->getTemplate();
}

