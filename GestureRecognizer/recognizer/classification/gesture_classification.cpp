//
// Created by 杨忠诚 on 18/3/13.
//

#include "distance_reducer.h"
#include "distance_matcher.h"
#include "gesture_utils.h"
#include "gesture_classification.h"

using namespace ns_recognizer;

GestureClassification::GestureClassification(string filePath, PairRule *pairRule) {
    this->reducer = new DistanceReducer();
    this->matcher = new DistanceMatcher();

//    this->reducer = new VectorReducer();
//    this->matcher = new VectorMatcher();

    this->templateManager = new TemplateManager(filePath, pairRule);
    std::map<std::string, std::vector<Gesture*> > gestures = templateManager->getTemplateMap();
    std::map<std::string, std::vector<Gesture*> >::iterator iterator;
    for (iterator = gestures.begin(); iterator !=
                                      gestures.end(); iterator ++) {
        std::vector<Gesture*> gestures = iterator->second;
        std::vector<Polyline*> polyLines;
        for (int i = 0; i < gestures.size(); ++i) {
            if (gestures[i]->getPoints().empty()) {
                continue;
            }
            Polyline * polyline = reducer->reduce(gestures[i]->clone());
            polyline->setTag(iterator->first);
            polyLines.push_back(polyline);
        }
        this->templateMap.insert(std::pair<std::string, std::vector<Polyline*> >(iterator->first, polyLines));
    }
}

vector<TResult*> GestureClassification::recognizer(Gesture *gesture) {
    std::vector<TResult*> result;
    if (gesture->getPoints().size() <= 2) {
        TResult *r = new TResult();
        r->tag = PairRule::DOT;
        r->score = 100;
        r->dimensional = 0;
//        r->isShort = true;
        result.push_back(r);
        return result;
    }

    RectF rectF = GestureUtils::getBoundBox(gesture->getPoints());
//    float height = rectF.bottom - rectF.top;
//    float width = rectF.right - rectF.left;
//    double diagonal = sqrt(height * height + width * width);

    //数据对齐
    Polyline *polyline = reducer->reduce(gesture);
    polyline->setTag("this");
    std::vector<TPoint*> points = polyline->getPoints();
    int dimensionalNum = polyline->getGesture()->getDimensionalNum();

//    int isShort = 0;
//    printf("diagonal dis: %lf, distance: %lf", diagonal, DOT_POINTS_DISTANCE * this->density);
//    //判断是否是点
//    if (diagonal <= DOT_POINTS_DISTANCE * this->density) {
//        isShort = 1;
//    }

    //遍历匹配所有模板
    std::map<std::string, std::vector<Polyline*> >::iterator iterator;
    for (iterator = templateMap.begin(); iterator != templateMap.end(); iterator ++) {
        std::string tag = iterator->first;
        std::vector<Polyline*> polyLines = iterator->second;
        for (int j = 0; j < polyLines.size(); j++) {
            Polyline *polyline1 = polyLines[j];
            float score = matcher->getSimilar(polyline, polyline1);

            printf("p1: %s, p2: %s, score: %lf, p1_dimens: %d, p2_dimens: %d\n",
                   polyline->getTag().c_str(),
                   polyline1->getTag().c_str(),
                   score,
                   polyline->getGesture()->getDimensionalNum(),
                   polyline1->getGesture()->getDimensionalNum());

            if (dimensionalNum <= 3) {
                if (dimensionalNum == polyline1->getGesture()->getDimensionalNum()) {
                    TResult *r = new TResult();
                    r->tag = tag;
                    r->score = score;
                    r->dimensional = polyline1->getGesture()->getDimensionalNum();
                    r->left = rectF.left;
                    r->top = rectF.top;
                    r->right = rectF.right;
                    r->bottom = rectF.bottom;
                    result.push_back(r);
                }
            } else {
                TResult *r = new TResult();
                r->tag = tag;
                r->score = score;
                r->dimensional = polyline1->getGesture()->getDimensionalNum();
                r->left = rectF.left;
                r->top = rectF.top;
                r->right = rectF.right;
                r->bottom = rectF.bottom;
                result.push_back(r);
            }
        }
    }
    return result;
}

std::map<std::string, std::vector<Polyline*> > GestureClassification::getTemplate() {
    return this->templateMap;
}
