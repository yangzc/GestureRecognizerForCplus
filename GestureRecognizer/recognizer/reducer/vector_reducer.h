//
// Created by 杨忠诚 on 18/1/19.
//

#ifndef _VECTOR_REDUCER_H
#define _VECTOR_REDUCER_H

#include "reducer.h"

namespace ns_recognizer {

    class VectorReducer : public Reducer {

    public:

        virtual Polyline* reduce(Gesture* gesture);

    };

}

#endif //_VECTOR_REDUCER_H
