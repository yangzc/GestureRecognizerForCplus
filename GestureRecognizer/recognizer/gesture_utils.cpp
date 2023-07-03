//
// Created by 杨忠诚 on 18/1/15.
//

#include <cmath>
#include <cfloat>
#include <algorithm>
#include "gesture_utils.h"

using namespace ns_recognizer;

double GestureUtils::distance(TPoint* point1, TPoint* point2) {
    float diffX = point1->x - point2->x;
    float diffY = point1->y - point2->y;
    return sqrt(diffX * diffX + diffY * diffY);
}

TPoint GestureUtils::getSmallestAngle(std::vector<TPoint*> points, int thresholdAngle) {
    if (points.size() <= 2)
        return TPoint(-1, -1);

    TPoint point(-1, -1);
    TPoint *first = points[0];
    TPoint *middle = points[1];
    double smallestAngle = 360;
    for (int i = 2; i < points.size(); i++) {
        TPoint *last = points[i];
        double angle = fabs(180 - getAngle(first, last, middle));
        if (angle < smallestAngle) {
            smallestAngle = angle;
            point.x = middle->x;
            point.y = middle->y;
        }
        first = middle;
        middle = last;
    }
    return smallestAngle < thresholdAngle ? point : TPoint(-1, -1);
}

double GestureUtils::getAngle(TPoint *p0, TPoint *p1, TPoint *c) {
    double p0c = sqrt(pow(c->x - p0->x, 2) + pow(c->y - p0->y, 2));
    double p1c = sqrt(pow(c->x - p1->x, 2) + pow(c->y - p1->y, 2));
    double p0p1 = sqrt(pow(p1->x - p0->x, 2) + pow(p1->y - p0->y, 2));
    double angle = acos((p1c * p1c + p0c * p0c - p0p1 * p0p1) / (2 * p1c * p0c));
    return angle * 180.0 / M_PI;
}

RectF GestureUtils::getBoundBox(std::vector<TPoint*> points) {
    float minX = FLT_MAX;
    float maxX = -FLT_MAX;
    float minY = FLT_MAX;
    float maxY = -FLT_MAX;
    for(int i = 0; i < points.size(); i++) {
        minX = std::min(points[i]->x, minX);
        maxX = std::max(points[i]->x, maxX);
        minY = std::min(points[i]->y, minY);
        maxY = std::max(points[i]->y, maxY);
    }
    RectF result;
    result.left = minX;
    result.top = minY;
    result.right = maxX;
    result.bottom = maxY;
    return result;
}

RectF GestureUtils::getBoundBox(std::vector<TResult *> results) {
    float minX = FLT_MAX;
    float maxX = -FLT_MAX;
    float minY = FLT_MAX;
    float maxY = -FLT_MAX;
    for(int i = 0; i < results.size(); i++) {
        minX = std::min(results[i]->left, minX);
        maxX = std::max(results[i]->right, maxX);
        minY = std::min(results[i]->top, minY);
        maxY = std::max(results[i]->bottom, maxY);
    }
    RectF result;
    result.left = minX;
    result.top = minY;
    result.right = maxX;
    result.bottom = maxY;
    return result;
}

std::vector<TPoint*> GestureUtils::reSample(std::vector<TPoint*> points, int sampleSize) {
    std::vector<TPoint*> result;
    //每段长度
    float distance = (float) (getPathLength(points) / (sampleSize * 1.0f - 1));
    float lastLeft = 0;
    //添加首节点
    result.push_back(points[0]);
    for (int i = 1; i < points.size(); i++) {
        TPoint *last = points[i - 1];
        TPoint *current = points[i];
        double between = GestureUtils::distance(last, current);
        float thisUsed = 0;
        while (between - thisUsed + lastLeft >= distance) {
            //重构点
            float x = last->x + (thisUsed + distance - lastLeft) * (current->x - last->x) / between;
            float y = last->y + (thisUsed + distance - lastLeft) * (current->y - last->y) / between;
            result.push_back(new TPoint(x, y));
            thisUsed += distance;
        }
        lastLeft = between - thisUsed + lastLeft;
    }
    if (result.size() == sampleSize -1) {
        result.push_back(points[points.size() -1]);
    }
//   PRINTF("resamples: %d", result.size());

    if (result.size() != 1 && result.size() != sampleSize) {
        throw NULL;
    }
    return result;
}

double GestureUtils::getPathLength(std::vector<TPoint*> points) {
    double distance = 0;
    for (int i = 1; i < points.size(); i++) {
        distance += GestureUtils::distance(points[i - 1], points[i]);
    }
    return distance;
}

double GestureUtils::getDiagonal(std::vector<TPoint*> points) {
    //获得边框
    RectF bound = getBoundBox(points);
    float height = bound.bottom - bound.top;
    float width = bound.right - bound.left;
    return sqrt(height * height + width * width);
}

TPoint GestureUtils::getCenterPoint(std::vector<TPoint*> points) {
    RectF boundRectF = getBoundBox(points);
    return TPoint((boundRectF.right + boundRectF.left)/2, (boundRectF.bottom + boundRectF.top)/2);
}

std::vector<TPoint*> GestureUtils::removePointByThresholdAngle(std::vector<TPoint*> points,
                                                              int thresholdAngle) {
    TPoint point = getSmallestAngle(points, thresholdAngle);
    while (point.x != -1 && point.y != -1) {
        for (int i = 0; i < points.size(); ++i) {
            if (points[i]->x == point.x && points[i]->y == point.y){
                points.erase(points.begin()+i);
                break;
            }
        }
        point = getSmallestAngle(points, thresholdAngle);
    }
    return points;
}

std::vector<TPoint*> GestureUtils::rotate(std::vector<TPoint*> points, TPoint centerPoint, float theta) {
    return rotate(points, centerPoint, theta, false);
}

std::vector<TPoint*> GestureUtils::rotate(std::vector<TPoint*> points, TPoint centerPoint,
                                         float theta, bool optSelf) {
    std::vector<TPoint*> result;
    double sin = std::sin(theta);
    double cos = std::cos(theta);
    //坐标变换
    for (int i = 0; i < points.size(); i++) {
        TPoint *point = points[i];
        float x = (float) ((point->x - centerPoint.x) * cos - (point->y - centerPoint.y) * sin + centerPoint.x);
        float y = (float) ((point->x - centerPoint.x) * sin + (point->y - centerPoint.y) * cos + centerPoint.y);
        if (optSelf) {
            point->x = x;
            point->y = y;
        } else {
            result.push_back(new TPoint(x, y));
        }
    }
    if (optSelf)
        return points;
    return result;
}

std::vector<int> GestureUtils::douglasPeukcerReducer(std::vector<TPoint*> points,
                                                     double tolerance) {
    bool marked[points.size()];
    for (int i = 0; i < points.size() - 1; i++) {
        marked[i] =  false;
    }
    marked[0] = true;
    marked[points.size() - 1] = true;

    douglasPeukcerReducerImpl(points, marked, tolerance, 0, points.size() - 1);

    std::vector<int> result;
    for (int i = 0; i < points.size(); i++) {
        if (marked[i]) {
            result.push_back(i);
        }
    }
    return result;
}

void GestureUtils::douglasPeukcerReducerImpl(std::vector<TPoint*> points, bool *marked,
                                             double tolerance, int firstIdx, int lastIndex) {
    if (firstIdx + 1 >= lastIndex)
        return;

    TPoint *firstPoint = points[firstIdx];
    TPoint *lastPoint = points[lastIndex];

    double fastest = 0;
    int fastestIdx = 0;
    for (int i = firstIdx + 1; i < lastIndex; i++) {
        TPoint *point = points[i];
        double distance = getDouglasPeukcerDistance(point, firstPoint, lastPoint);
        if (distance > fastest) {
            fastest = distance;
            fastestIdx = i;
        }
    }

    if (fastest > tolerance) {
        marked[fastestIdx] = true;
        douglasPeukcerReducerImpl(points, marked, tolerance, firstIdx, fastestIdx);
        douglasPeukcerReducerImpl(points, marked, tolerance, fastestIdx, lastIndex);
    }

}

double GestureUtils::getDouglasPeukcerDistance(TPoint *point, TPoint *start, TPoint *end) {
    if (start->x == end->x && start->x == end->y) {
        return distance(start, point);
    }
    //http://www.ab126.com/geometric/3229.html
    double area = fabs((1.0 * start->y * end->x + 1.0 * end->y * point->x + 1.0 * point->y * start->x
                  - 1.0 * end->y * start->x - 1.0 * point->y * end->x - 1.0 * start->y * point->x)
                 / 2.0);
    double bottom = hypot(end->x - start->x, end->y - start->y);
    return area / bottom * 2;
}

float GestureUtils::hausdorffDistance(std::vector<TPoint*> points1, std::vector<TPoint*> points2) {
    /*
        Hausdorff Distance
        http://blog.csdn.net/lishuhuakai/article/details/53573241
        实现 Hausdorff 距离.该距离的定义如下:
        A = {a1, a2, ..., an}, B = {b1, b2, ..., bm}
        两者的 Hausdorff 距离为:
        H(A, B) = max{h(A, B), h(B, A)},
        其中
        h(A, B)的定义如下,无法用数学公式来展现,我这里用语言来描述一下得了.
        对于A中的每一个点a,首先在B中找到一个距离a最近的点b,得到a,b它们之间的距离dist(a, b),这里的dist定义如下:
        dist(a, b) = sqrt((xa - xb)^2, (ya - yb)^2),就是欧氏距离啦.
        通过计算得到n个这样的距离,找出其中最大的一个,作为h(A, B),h(B, A)同理.
         */
    double value1 = hausdorffDistanceBetween(points1, points2);
    double value2 = hausdorffDistanceBetween(points2, points1);
    return (float) fmax(value1, value2);
}

double GestureUtils::hausdorffDistanceBetween(std::vector<TPoint*> points1,
                                              std::vector<TPoint*> points2) {
    double distance = 0;
    for (int i = 0; i < points1.size(); i++) {
        double shortest = FLT_MAX;
        for (int j = 0; j < points2.size(); j++) {
            double dis = GestureUtils::distance(points1[i], points2[j]);
            if (dis < shortest) {
                shortest = dis;
            }
        }
        if (shortest > distance) {
            distance = shortest;
        }
    }
    return distance;

}

std::vector<TPoint*> GestureUtils::getValidCtrlPointCnt(std::vector<TPoint*> points,
                                                       double threshold) {
    std::vector<TPoint*> result;
    TPoint *first = points[0];
    result.push_back(first);

    for (int i = 1; i < points.size(); i++) {
        TPoint *point = points[i];
        double distance = GestureUtils::distance(point, first);
        if (distance > threshold * SQUARE) {

        }
    }
    return result;
}

std::vector<TPoint*> GestureUtils::beRegular(std::vector<TPoint*> points, int precision) {
    if (points.size() == 0 || points.size() < 3) {
        return points;
    }
    std::vector<TPoint*> result;
    result.push_back(points[0]);
    float angleUnit = 360.0 / precision;
    for (int i = 1; i < points.size() - 1; i++) {
        double angle = getAngle(points[i - 1], points[i + 1], points[i]);
        float angleRound = fmod(angle, angleUnit);
        if (angleRound > angleUnit/2) {
            angleRound = angleRound - angleUnit;
        }
        if (angleRound != 0) {
            std::vector<TPoint*> pointLeft(points.begin() + i + 1, points.begin() + i + 2);
            std::vector<TPoint*> rotated = rotate(pointLeft, *points[i], angleRound * 180.0 / M_PI);
            result.push_back(rotated[0]);
            if (i == points.size() - 2) {
                result.push_back(rotated[1]);
            }
        } else {
            result.push_back(points[i]);
            if (i == points.size() - 2) {
                result.push_back(points[i + 1]);
            }
        }
    }
    return result;
}

int GestureUtils::getAngle(TPoint *point1, TPoint *point2, float thresohld) {
    double angle = atan2(point2->y - point1->y, point2->x - point1->x) * 180.0 / M_PI;
    if (angle < 0) {
        angle = angle + 180.0f;
    }
    if (angle <= thresohld || angle >= 180 - thresohld) {
        //横
        return 0;
    } else if (angle > thresohld && angle <= 90 -thresohld) {
        //捺
        return 3;
    } else if (angle >= 90 - thresohld && angle <= 90 + thresohld) {
        //竖
        return 1;
    } else {
        //撇
        return 2;
    }

}
