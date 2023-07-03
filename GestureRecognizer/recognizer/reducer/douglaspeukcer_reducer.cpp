//
// Created by 杨忠诚 on 18/1/15.
//

#include <cmath>
#include "douglaspeukcer_reducer.h"
#include "../gesture_utils.h"

using namespace ns_recognizer;

Polyline* DouglasPeukcerReducer::reduce(Gesture *gesture) {
    double diagonal = GestureUtils::getDiagonal(gesture->getPoints());
    std::vector<int> reducerList = GestureUtils::douglasPeukcerReducer(gesture->getPoints(), diagonal/ 22.0);
    std::vector<TPoint*> points;
    for (int i = 0; i < reducerList.size(); i++) {
        TPoint *p = gesture->getPoint(reducerList[i]);
        points.push_back(p);
    }

    std::vector<TPoint*> result = GestureUtils::removePointByThresholdAngle(points, 26);
    //特殊处理一维坐标
    if (result.size() == 2) {
        TPoint *pointStart = result[0];
        TPoint *pointEnd = result[1];

        double degrees = (atan2(fabs(pointEnd->y - pointStart->y), fabs(pointEnd->x - pointStart->x))) * 180.0 / M_PI;
        if (degrees < ANGLE_THRESHOLD) {
            pointEnd->y = pointStart->y;
        } else if (degrees > 90 - ANGLE_THRESHOLD) {
            pointEnd->x = pointStart->x;
        }
    }

    std::vector<int> indexes;
    for (int i = 0; i < result.size(); i++) {
        TPoint point = *result[i];
        indexes.push_back(gesture->indexOf(point));
    }
    return new Polyline(gesture, indexes);
}