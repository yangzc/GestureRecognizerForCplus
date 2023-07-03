//
// Created by 杨忠诚 on 18/1/15.
//

#ifndef _POLYLINE_H
#define _POLYLINE_H

#include <string>
#include "gesture.h"

namespace ns_recognizer {

    class Polyline {
    private:
        std::string tag;
        Gesture* gesture;
        std::vector<int> indexes;
        std::vector<double > lengths;
        std::vector<Vector*> vectors;
        double totalLength;

    public:
        Polyline(Gesture* gesture, std::vector<int> indexes);
        ~Polyline();
        std::vector<TPoint*> getPoints();
        void setTag(std::string tag);
        std::string getTag();
        std::vector<int> getIndexes();
        TPoint* getPoint(int index);
        Vector* getVector(int index);
        int getPointCount();
        double getLength(int index);
        double getTotalLength();
        Gesture* getGesture();
        std::vector<Vector*> getVectors();
    private:
        void initLengths();

    };
}

#endif //_POLYLINE_H
