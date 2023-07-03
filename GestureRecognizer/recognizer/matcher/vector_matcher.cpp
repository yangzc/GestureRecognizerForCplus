//
// Created by 杨忠诚 on 18/1/19.
//

#include "gesture_utils.h"
#include "vector_matcher.h"

using namespace ns_recognizer;

float VectorMatcher::getSimilar(Polyline *polylineThis, Polyline *polylineOther) {
    std::vector<Vector*> vectorThis = polylineThis->getVectors();
    std::vector<Vector*> vectorOther = polylineOther->getVectors();

    int count = std::min(vectorThis.size(), vectorOther.size());
    double score = 0;
    for (int i = 0; i < count; ++i) {
        Vector *v1 = vectorThis[i];
        Vector *v2 = vectorOther[i];

        double v1Distance = GestureUtils::distance(v1->start, v1->end);
        double x1 = (v1->end->x - v1->start->x)/v1Distance;
        double y1 = (v1->end->y - v1->start->y)/v1Distance;

        double v2Distance = GestureUtils::distance(v2->start, v2->end);
        double x2 = (v2->end->x - v2->start->x)/v2Distance;
        double y2 = (v2->end->y - v2->start->y)/v2Distance;

        score += x1 * x2 + y1 * y2;
    }
    return score;
}
