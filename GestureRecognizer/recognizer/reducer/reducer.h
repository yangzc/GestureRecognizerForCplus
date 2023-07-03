//
// Created by 杨忠诚 on 18/1/15.
//

#ifndef _REDUCER_H
#define _REDUCER_H

#include "../polyline.h"

namespace ns_recognizer {

    class Reducer {
    public:
        virtual Polyline* reduce(Gesture* gesture) = 0;
    };
}

#endif //_REDUCER_H
