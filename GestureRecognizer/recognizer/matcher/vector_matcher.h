//
// Created by 杨忠诚 on 18/1/19.
//

#ifndef _VECTOR_MATCHER_H
#define _VECTOR_MATCHER_H

#include "matcher.h"

namespace ns_recognizer {

    class VectorMatcher : public Matcher {

        virtual float getSimilar(Polyline * polylineThis, Polyline * polylineOther);
    };

}

#endif //_VECTOR_MATCHER_H
