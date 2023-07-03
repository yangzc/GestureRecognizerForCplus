//
// Created by 杨忠诚 on 18/1/15.
//

#ifndef _DISTANCE_REDUCER_H
#define _DISTANCE_REDUCER_H
#include "reducer.h"

namespace ns_recognizer {

    class DistanceReducer : public Reducer {

    public :

        virtual Polyline* reduce(Gesture* gesture);
    };
}

#endif //_DISTANCE_REDUCER_H
