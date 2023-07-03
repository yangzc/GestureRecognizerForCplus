//
// Created by 杨忠诚 on 18/1/15.
//

#ifndef _DISTANCE_MATCHER_H
#define _DISTANCE_MATCHER_H

#include "matcher.h"

namespace ns_recognizer {

    class DistanceMatcher : public Matcher {

    public:
        virtual float getSimilar(Polyline * polylineThis, Polyline * polylineOther);
    };

}

#endif //_DISTANCE_MATCHER_H
