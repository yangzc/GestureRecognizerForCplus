//
// Created by 杨忠诚 on 18/3/13.
//

#include "utils.h"
#include "lenet.id.h"
#include "gesture_utils.h"
#include "ncnn_classification.h"
#include <iterator>
#include "ncnn_pair_rule.h"
#include "douglaspeukcer_reducer.h"

using namespace ns_recognizer;

void NcnnClassification::printValue(std::string label, float value1[], int size) {
    vector<float> value(value1, value1 + size);
    Gesture * g = new Gesture();
    for (int i = 0; i < value.size(); i += 2) {
        float x = value[i];
        float y = value[i + 1];
        //获取数据点
        g->addPoint(new TPoint(x, y));
    }
    std::vector<TResult*> ss = recognizer(g);
    delete g;
    printf("test result, %s == %s, g size: %d\n", label.c_str(), ss[0]->tag.c_str(), g->getPoints().size());
}

NcnnClassification::NcnnClassification(const unsigned char *_paraMem
        , const unsigned char *_binMem, string _wordTxt) {
    Utils::bench_start();
    this->reg_net = new ncnn::Net();
    int paramRtn = reg_net->load_param(_paraMem);
    int modelRtn = reg_net->load_model(_binMem);
    printf("paramRtn: %d, modelRtn: %d\n",  paramRtn, modelRtn);
    this->words = Utils::split_string(_wordTxt, "\n");
    Utils::bench_end("init finish\n");

//#define DEBUG_TEST_TEMPLATE
#ifdef DEBUG_TEST_TEMPLATE
    float value1[] = {351,160,351,173,350,183,349,194,348,204,347,219,346,230,345,243,344,253,344,264,344,275,343,287,342,301,341,314,340,329,339,344,338,359,338,370,338,381,337,391};
    float value2[] = {261,152,273,145,283,141,295,137,307,135,319,135,331,137,340,148,346,159,350,171,354,182,357,193,359,207,359,220,359,232,358,246,352,261,347,270,340,279,328,295,314,308,299,318,284,328,269,337,259,342,251,352,246,362,262,365,281,365,294,365,307,365,319,365,331,365,348,365,360,365,375,365,386,365,400,365,414,364,429,363,439,362};
    float value3[] = {290,167,302,163,314,159,327,155,337,153,350,153,361,154,369,163,372,173,373,184,373,201,372,212,366,222,358,232,349,240,333,249,323,253,306,259,294,263,306,261,320,259,331,258,342,257,358,257,370,259,380,266,385,279,386,291,387,306,384,327,379,340,375,351,370,363,363,374,353,385,340,398,329,408,317,415,308,421,293,424,281,428};
    float value6[] = {365,187,353,197,346,205,341,217,335,232,330,247,325,263,321,279,318,295,317,313,316,331,318,343,322,356,328,373,334,382,348,391,363,395,379,398,390,398,406,398,421,393,432,380,439,371,442,361,445,351,448,337,444,323,433,316,422,312,410,309,397,307,383,305,371,304,359,306,349,309,339,315};
    float value7[] = {279,164,291,164,306,163,323,162,334,162,353,162,368,162,383,162,395,162,405,163,405,178,405,194,405,211,403,227,400,256,396,283,392,309,387,339,385,359,380,392,378,409,376,431,374,447,373,459,373,472};
    float value8[] = {363,190,352,190,340,190,330,195,321,205,314,216,310,232,313,250,323,263,342,279,358,287,380,300,398,310,418,323,435,334,448,343,458,351,470,367,474,378,478,394,480,411,480,429,478,446,468,466,454,480,436,492,413,498,388,499,360,498,341,491,320,480,307,470,299,461,292,444,292,425,292,402,295,377,301,353,307,330,312,313,317,294,323,279,328,268,337,249,342,239,347,226,350,215,352,205,357,192};
    float value9[] = {414,209,401,219,394,234,390,245,389,256,389,269,396,280,408,286,420,289,433,286,440,273,445,255,447,245,449,232,449,221,447,245,444,267,441,297,437,349,435,388,434,433,433,474,431,505,430,524,429,536,429,547};

    {
        printValue("1", value1, sizeof(value1)/ sizeof(float));
        printValue("2", value2, sizeof(value2)/ sizeof(float));
        printValue("3", value3, sizeof(value3)/ sizeof(float));
        printValue("6", value6, sizeof(value6)/ sizeof(float));
        printValue("7", value7, sizeof(value7)/ sizeof(float));
        printValue("8", value8, sizeof(value8)/ sizeof(float));
        printValue("9", value9, sizeof(value9)/ sizeof(float));
    }
#endif
}

vector<TResult*> NcnnClassification::recognizer(Gesture *gesture) {
    DouglasPeukcerReducer *reducer = new DouglasPeukcerReducer();
    Polyline* polyline = reducer->reduce(gesture);
    std::vector<TPoint*> keyPoints = polyline->getPoints();
    delete(polyline);
    //设置维度数
    RectF rectF = GestureUtils::getBoundBox(gesture->getPoints());
    TResult *r = new TResult();
    r->left = rectF.left;
    r->top = rectF.top;
    r->right = rectF.right;
    r->bottom = rectF.bottom;
    r->dimensional = keyPoints.size();
    gesture->setDimensionalNum(keyPoints.size());
    gesture->setKeyPoints(keyPoints);

    if (gesture->getDimensionalNum() == 2) {//线段
        TPoint *star = keyPoints[0];
        TPoint *end = keyPoints[1];
        int result = GestureUtils::getAngle(star, end, ANGLE_THRESHOLD);
        switch(result) {
            case 0: {
                r->tag = NcnnPairRule::HENG;
                break;
            }
            case 1: {
                r->tag = NcnnPairRule::ONE;
                break;
            }
            case 2: {
                r->tag = NcnnPairRule::PIE;
                break;
            }
            case 3: {
                r->tag = NcnnPairRule::NA;
                break;
            }
        }
        r->score = 100;
        printf("ncnn result d is: %s\n", r->tag.c_str());
    } else {
        Utils::bench_start();
        ncnn::Mat in;
        {
            //目前仅支持单笔识别
            vector<Gesture *> gs;
            gs.push_back(gesture);
            bitmap_image image = buildBitmap(gs);
            in = ncnn::Mat::from_pixels(image.data(), ncnn::Mat::PIXEL_BGR2GRAY, image.width(),
                                        image.height());
        }
        // net
        std::vector<float> cls_scores;
        {
            const float mean_vals[1] = {32.8816};
            const float norm_vals[1] = {0.00390625f};
            in.substract_mean_normalize(mean_vals, norm_vals);

            ncnn::Extractor ex = reg_net->create_extractor();
            ex.set_light_mode(true);
            ex.set_num_threads(4);

            ex.input(lenet_param_id::BLOB_data, in);

            ncnn::Mat out;
            ex.extract(lenet_param_id::BLOB_prob, out);

            ncnn::Mat out_flatterned = out.reshape(out.w * out.h * out.c);
            cls_scores.resize(out_flatterned.w);
            for (int j = 0; j < out_flatterned.w; j++) {
                cls_scores[j] = out_flatterned[j];
            }
        }

        // return top class
        int top_class = 0;
        float max_score = 0.f;
        for (size_t i = 0; i < cls_scores.size(); i++) {
            float s = cls_scores[i];
            printf("value: %d, score: %f", i, s);
            if (s > max_score) {
                top_class = i;
                max_score = s;
            }
        }
        const std::string &word = this->words[top_class];
        char tmp[32];
        sprintf(tmp, "%.3f", max_score);
        std::string result_str = "" + std::string(word.c_str() + 2) + ", score = " + tmp;
        printf("ncnn result is: %s\n", result_str.c_str());
        Utils::bench_end("detect!!!");
        r->tag = std::string(word.c_str() + 3);
        r->score = max_score;
    }
    vector<TResult*> result;
    result.push_back(r);
    return result;
}

std::map<std::string, std::vector<Polyline*> > NcnnClassification::getTemplate() {
    return std::map<std::string, std::vector<Polyline*> >();
}

bitmap_image NcnnClassification::buildBitmap(vector<Gesture*> gestures) {
    bitmap_image image(28,28);
    image.set_all_channels(0, 0, 0);
    image_drawer draw(image);
    draw.pen_width(2);
    draw.pen_color(255, 255, 255);

    float minX = 9999, maxX = 0;
    float minY = 9999, maxY = 0;
    for (int i = 0; i < gestures.size(); ++i) {
        vector<TPoint*> points = gestures[i]->getPoints();
        for (int j = 0; j < points.size(); j++) {
            float x = points[j]->x;
            float y = points[j]->y;
            minX = min(x, minX);
            maxX = max(x, maxX);

            minY = min(y, minY);
            maxY = max(y, maxY);
        }
    }
    float height = maxY - minY;
    float width = maxX - minX;
    float scale = 1.0f;
    if (width > height) {
        scale = 20.0f / width;
    } else {
        scale = 20.0f / height;
    }
    float offsetX = (28 - width * scale)/2;
    float offsetY = (28 - height * scale)/2;

    for (int i = 0; i < gestures.size(); ++i) {
        vector<TPoint*> points = gestures[i]->getPoints();
        if (points.size() > 1) {
            TPoint *last = points[0];
            for (int j = 1; j < points.size(); j++) {
                float x = points[j]->x;
                float y = points[j]->y;
                draw.line_segment((last->x - minX) * scale + offsetX,
                                  (last->y - minY) * scale + offsetY,
                                  (x - minX) * scale + offsetX,
                                  (y - minY) * scale + offsetY);
                last = points[j];
            }
        }
    }

//    string fileName = "/sdcard/recognizer_.png";
//    remove(fileName.c_str());
//    image.save_image(fileName);
    return image;
}

//数组排序
bool compareGesture(Gesture* g1, Gesture* g2) {
    RectF rectF1 = Utils::getBoundBox(g1->getPoints());
    RectF rectF2 = Utils::getBoundBox(g2->getPoints());
    if (rectF1.left > rectF2.left) {
        return true;
    }
    return false;
}

vector<vector<Gesture*> > NcnnClassification::cutGesture(vector<Gesture *> gestures) {
    if (gestures.size() > 0) {
        sort(gestures.begin(), gestures.end(), compareGesture);
        Gesture *last = gestures[0];

        vector<Gesture*> gsVector;
        RectF lastF = Utils::getBoundBox(last->getPoints());
        for (int i = 1; i < gestures.size(); ++i) {
            Gesture *gs = gestures[i];
            RectF rectF = Utils::getBoundBox(gs->getPoints());

        }
    }

    vector<vector<Gesture*> > result;
    for (int i = 0; i < gestures.size(); ++i) {
        Gesture *gs = gestures[i];
        RectF rectF = Utils::getBoundBox(gs->getPoints());
        float left = rectF.left;
        float top = rectF.top;

    }
    return result;
}
