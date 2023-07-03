//
// Created by 杨忠诚 on 18/1/15.
//

#include <cmath>
#include "polyline.h"
#include "gesture_utils.h"

using namespace ns_recognizer;

Polyline::Polyline(Gesture *gesture, std::vector<int> indexes) {
    this->gesture = gesture;
    this->indexes = indexes;
    initLengths();
    getVectors();
}

Polyline::~Polyline() {
    indexes.clear();
    lengths.clear();
    vectors.clear();
}

void Polyline::initLengths() {
    double distance = 0;
    lengths.push_back(0);
    for (int i = 1; i < indexes.size(); i++) {
        TPoint *start = gesture->getPoint(indexes[i - 1]);
        TPoint *next = gesture->getPoint(indexes[i]);
        distance += GestureUtils::distance(start, next);
        lengths.push_back(distance);
    }
}

std::vector<TPoint*> Polyline::getPoints() {
    std::vector<TPoint*> points;
    for (int i = 0; i < indexes.size(); i++) {
        points.push_back(gesture->getPoint(indexes[i]));
    }
    return points;
}

void Polyline::setTag(std::string tag) {
    this->tag = tag;
}

std::string Polyline::getTag() {
    if (tag.empty())
        return "unknown";
    return tag;
}

std::vector<int> Polyline::getIndexes() {
    return this->indexes;
}

TPoint* Polyline::getPoint(int index) {
    return gesture->getPoint(indexes[index]);
}

Vector* Polyline::getVector(int index) {
    return vectors[index];
}

int Polyline::getPointCount() {
    return indexes.size();
}

double Polyline::getLength(int index) {
    return lengths[index];
}

double Polyline::getTotalLength() {
    return lengths[lengths.size() - 1];
}

Gesture* Polyline::getGesture() {
    return this->gesture;
}

std::vector<Vector*> Polyline::getVectors() {
    if (vectors.empty()) {
        double totalLength = lengths[lengths.size() - 1];
        for (int i = 0; i < indexes.size() - 1; i++) {
            TPoint *start = gesture->getPoint(indexes[i]);
            TPoint *next = gesture->getPoint(indexes[i + 1]);

            double angle = atan2(next->y - start->y, next->x - start->x);
            angle = angle > 0 ? angle : (2 * M_PI + angle);
            double len = (lengths[i + 1] - lengths[i]) / totalLength;

            Vector *v = new Vector();
            v->start = start;
            v->end = next;
            v->distance = len;
            v->angle = angle;
            //长度和角度
            vectors.push_back(v);
        }
    }
    return vectors;
}