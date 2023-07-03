//
// Created by 杨忠诚 on 18/1/15.
//

#include <cmath>
#include "distance_matcher.h"
#include "../gesture_utils.h"

using namespace ns_recognizer;
static float Phi = (float) (0.5 * (-1.0 + sqrt(5.0)));

/**
 * 欧式距离
 * @param point1
 * @param point2
 * @return
 */
float getDistance(std::vector<TPoint*> point1, std::vector<TPoint*> point2) {
    float distance = 0;
    int count = std::min(point1.size(), point2.size());
    for (int i = 0; i < count; i++) {
        TPoint *p1 = point1[i];
        TPoint *p2 = point2[i];
        distance += pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2);
    }
    return (float) (sqrt(distance) / point1.size());
}

float getDistanceAtAngle(std::vector<TPoint*> point1, std::vector<TPoint*> point2, float theta) {
    TPoint centerPoint = GestureUtils::getCenterPoint(point1);
    std::vector<TPoint*> newPoints = GestureUtils::rotate(point1, centerPoint, theta);
//        return GestureUtils.hausdorffDistance(newPoints, point2);
    return getDistance(newPoints, point2);
}

float distanceAtBestAngle(std::vector<TPoint*> p1, std::vector<TPoint*> p2, float a, float b, float threshold) {
    float x1 = (float) (Phi * a + (1.0 - Phi) * b);
    float f1 = getDistanceAtAngle(p1, p2, x1);
    float x2 = (float) ((1.0 - Phi) * a + Phi * b);
    float f2 = getDistanceAtAngle(p1, p2, x2);
    while(fabs( b - a ) > threshold) {
        if( f1 < f2 ) {
            b = x2;
            x2 = x1;
            f2 = f1;
            x1 = (float) (Phi * a + (1.0 - Phi) * b);
            f1 = getDistanceAtAngle(p1, p2, x1);
        } else {
            a = x1;
            x1 = x2;
            f1 = f2;
            x2 = (float) ((1.0 - Phi) * a + Phi * b);
            f2 = getDistanceAtAngle(p1, p2, x2);
        }
    }
    return fmin(f1, f2);
}

float getSimilar1(Polyline* thisPolyline, Polyline* otherPolyline) {
    float d = distanceAtBestAngle(thisPolyline->getPoints(), otherPolyline->getPoints(), -45, 45, 2);
//        float d = getDistanceAtAngle(thisPolyline.getPoints(), otherPolyline.getPoints(), 0);
    return (float) (1.0 - (d / (0.5 * sqrt(SQUARE * SQUARE + SQUARE * SQUARE))));
}

float getSimilar2(Polyline* thisPolyline, Polyline* otherPolyline) {
    double v1 = 0, v2 = 0;
    for (int i = 0; i < thisPolyline->getPoints().size(); i++) {
        float x1 = thisPolyline->getPoints()[i]->x;
        float y1 = thisPolyline->getPoints()[i]->y;
        float x2 = otherPolyline->getPoints()[i]->x;
        float y2 = otherPolyline->getPoints()[i]->y;

        v1 += x1 * x2 + y1 * y2;
        v2 += hypot(x1, y1) * hypot(x2, y2);
    }
    //向量的cos=1 方向完全相同 cos=-1方向完全相反 0垂直
    return (float) fabs(v1 / v2);
}

float DistanceMatcher::getSimilar(Polyline *polylineThis, Polyline *polylineOther) {
    float balance = 0.4f;
    float score1 = getSimilar1(polylineThis, polylineOther);
    float score2 = getSimilar2(polylineThis, polylineOther);
    float score = balance * score1 + (1- balance) * score2;
    if (std::isinf(score) || std::isnan(score))
        return 0;

    double result;
    char s[20];
    sprintf(s, "%.2lf", score);
    sscanf(s, "%lf", &result);
    return result;
}