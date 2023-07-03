//
// Created by 杨忠诚 on 18/1/15.
//

#ifndef _DOUGLASPEUKCER_REDUCER_H
#define _DOUGLASPEUKCER_REDUCER_H

#include "reducer.h"

namespace ns_recognizer {

    class DouglasPeukcerReducer : public Reducer {

    public:
        virtual Polyline* reduce(Gesture* gesture);
    };

}

#endif //_DOUGLASPEUKCER_REDUCER_H
