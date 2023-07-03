//
// Created by 杨忠诚 on 18/1/15.
//

#include "gesture.h"
#include "gesture_utils.h"

using namespace ns_recognizer;

void Gesture::addPoint(TPoint* point) {
    this->points.push_back(point);
}

std::vector<TPoint*> Gesture::getPoints() {
    return this->points;
}

void Gesture::setPoints(std::vector<TPoint*> points) {
    this->points = points;
    this->lengths.clear();
}

int Gesture::indexOf(TPoint point) {
    if (points.empty())
        return -1;
    for (int i = 0; i < points.size(); ++i) {
        TPoint *p = points[i];
        if (p->x == point.x && p->y == point.y) {
            return i;
        }
    }
    return -1;
}

TPoint* Gesture::getPoint(int index) {
    return this->points[index];
}

RectF Gesture::getRectF() {
    return GestureUtils::getBoundBox(points);
}

void Gesture::addGesture(Gesture gesture) {
    std::vector<TPoint*> ps = gesture.getPoints();
    for (int i = 0; i < ps.size(); i++) {
        this->points.push_back(ps[i]);
    }
}

void Gesture::setKeyPoints(std::vector<TPoint*> keyPoints) {
    this->keyPoints = keyPoints;
}

std::vector<TPoint*> Gesture::getKeyPoints() {
    return this->keyPoints;
}

void Gesture::setDimensionalNum(int dimensionalNum) {
    this->dimensionalNum = dimensionalNum;
}

int Gesture::getDimensionalNum() {
    return dimensionalNum;
}

double Gesture::getLength(int index) {
    if (lengths.size() == 0) {
        initLengths();
    }
    return lengths[index];
}

double Gesture::getTotalLength() {
    if (lengths.size() == 0) {
        initLengths();
    }
    return lengths[lengths.size() -1];
}

void Gesture::initLengths() {
    lengths.push_back(0);
    TPoint *lastPoint = points[0];
    double distance = 0;
    for (int i = 1; i < points.size(); i++) {
        TPoint *point = points[i];
        distance += GestureUtils::distance(lastPoint, point);
        lengths.push_back(distance);
        lastPoint = point;
    }
}

Gesture* Gesture::clone() {
    Gesture* gesture = new Gesture();
    for (int i = 0; i < points.size(); i++) {
        gesture->points.push_back(new TPoint(points[i]->x, points[i]->y));
    }
    return gesture;
}

