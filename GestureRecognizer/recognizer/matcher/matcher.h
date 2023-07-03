//
// Created by 杨忠诚 on 18/1/15.
//

#ifndef _MATCHER_H
#define _MATCHER_H

#include "../polyline.h"

namespace ns_recognizer {

    class Matcher {
    public:
        /**
         * 获得匹配结果
         * @param polylineThis
         * @param polylineOther
         * @return
         */
        virtual float getSimilar(Polyline * polylineThis, Polyline * polylineOther) = 0;
    };
}

#endif //_MATCHER_H
