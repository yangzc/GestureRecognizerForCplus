//
// Created by 杨忠诚 on 18/1/15.
//

#include <cmath>
#include "distance_reducer.h"
#include "../gesture_utils.h"
#include "douglaspeukcer_reducer.h"

using namespace ns_recognizer;

static const int SAMPLES_SIZE = 16;
static const int MIN_ANGLE = 26;
static const float DIMENSIONAL_THRESHOLD = 0.2f;


std::vector<TPoint*> translateToOrigin(std::vector<TPoint*> keyPoints, std::vector<TPoint*> points) {
    std::vector<TPoint*> result;
    RectF rectF = GestureUtils::getBoundBox(points);
    for (int i = 0; i < points.size(); i++) {
        float x = points[i]->x - rectF.left;
        float y = points[i]->y - rectF.top;
        TPoint *p = new TPoint(x, y);
        result.push_back(p);
    }
    return result;
}

std::vector<TPoint*> scaleToSquare(std::vector<TPoint*> points, float size) {
    std::vector<TPoint*> result;
    RectF rectF = GestureUtils::getBoundBox(points);
    float width = rectF.right - rectF.left;
    float height = rectF.bottom - rectF.top;
    if (width == 0)
        width = 10;
    if (height == 0)
        height = 10;
    for (int i = 0; i < points.size(); i++) {
        float x = (points[i]->x - rectF.left) * size / width;
        float y = (points[i]->y - rectF.top) * size/ height;
        result.push_back(new TPoint(x, y));
    }
    return result;
}

std::vector<TPoint*> rotateBy(std::vector<TPoint*> points, float theta) {
    TPoint centerPoint = GestureUtils::getCenterPoint(points);
    return GestureUtils::rotate(points, centerPoint, theta);
}

/**
 * 旋转
 * @param points
 * @return
 */
std::vector<TPoint*> rotateToZero(std::vector<TPoint*> points, bool isOneDimensional) {
    RectF rectF = GestureUtils::getBoundBox(points);
    float width = rectF.right - rectF.left;
    float height = rectF.bottom - rectF.top;

    //判断是否属于一维坐标
    if (isOneDimensional || width == 0 || height == 0
        || width/height < DIMENSIONAL_THRESHOLD
        || height/width < DIMENSIONAL_THRESHOLD) {
        return points;
    }

    TPoint centerPoint = GestureUtils::getCenterPoint(points);
    TPoint *firstPoint = points[0];
    double angle = atan2(centerPoint.y - firstPoint->y, centerPoint.x- firstPoint->x);
    printf("angle: %lf, first.x: %lf, first.y: %lf, center.x: %lf, center.y: %lf\n",
           angle, firstPoint->x, firstPoint->y, centerPoint.x, centerPoint.y);
    return rotateBy(points, (float) -angle);
}


Polyline* DistanceReducer::reduce(Gesture *gesture) {
//    std::vector<TPoint*> regular = GestureUtils::beRegular(gesture->getPoints(), 16);
//    gesture->setPoints(regular);

    DouglasPeukcerReducer *reducer = new DouglasPeukcerReducer();
    Polyline* polyline = reducer->reduce(gesture);

    std::vector<TPoint*> keyPoints = polyline->getPoints();
    bool isOneDimensional = false;
    if (keyPoints.size() <= 2) {
        //一维&二维
        isOneDimensional = true;
    }
    delete(polyline);

    //设置维度数
    gesture->setDimensionalNum(keyPoints.size());
    gesture->setKeyPoints(keyPoints);
    //重新采样
    std::vector<TPoint*> reSampleList = GestureUtils::reSample(keyPoints, SAMPLES_SIZE);
    //旋转
    std::vector<TPoint*> rotatedList = rotateToZero(reSampleList, isOneDimensional);
    //scale转换
    std::vector<TPoint*> scaledList = scaleToSquare(rotatedList, SQUARE);
    //转换到坐标原点
    std::vector<TPoint*> result = translateToOrigin(keyPoints, scaledList);
    //重置原始点
    gesture->setPoints(result);
    std::vector<int> indexes;
    for (int i = 0; i < result.size(); i++) {
        indexes.push_back(i);
    }
    return new Polyline(gesture, indexes);
}
