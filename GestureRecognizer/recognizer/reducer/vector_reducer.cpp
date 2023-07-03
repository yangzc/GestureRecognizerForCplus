//
// Created by 杨忠诚 on 18/1/19.
//

#include "gesture_utils.h"
#include "vector_reducer.h"
#include "douglaspeukcer_reducer.h"

using namespace ns_recognizer;

Polyline* VectorReducer::reduce(Gesture *gesture) {
    DouglasPeukcerReducer *reducer = new DouglasPeukcerReducer();
    Polyline* polyline = reducer->reduce(gesture);
    std::vector<TPoint*> keyPoints = polyline->getPoints();
//    bool isOneDimensional = false;
//    if (keyPoints.size() <= 2) {
//        //一维&二维
//        isOneDimensional = true;
//    }
    delete(polyline);

    //设置维度数
    gesture->setDimensionalNum(keyPoints.size());
    gesture->setKeyPoints(keyPoints);

    //重新采样
    std::vector<TPoint*> reSampleList = GestureUtils::reSample(gesture->getPoints(), 16);
//    for (int i = 1; i < reSampleList.size(); ++i) {
//        TPoint *lastPoint = reSampleList[i - 1];
//        TPoint * p = reSampleList[i];
//        double distance = GestureUtils::distance(lastPoint, p);
//        double x = (p->x - lastPoint->x)/distance;
//        double y = (p->y - lastPoint->y)/distance;
//
//    }
    //重置原始点
    gesture->setPoints(reSampleList);
    std::vector<int> indexes;
    for (int i = 0; i < reSampleList.size(); i++) {
        indexes.push_back(i);
    }
    return new Polyline(gesture, indexes);
}
