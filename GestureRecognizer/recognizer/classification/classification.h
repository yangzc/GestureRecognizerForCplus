//
// Created by 杨忠诚 on 18/3/13.
//

#ifndef _CLASSIFICATION_H
#define _CLASSIFICATION_H

#include "common_type.h"
#include "gesture.h"
#include "polyline.h"
#include <map>

using namespace std;
namespace ns_recognizer {
    class Classification {
    public:

        /**
         * 根据手势识别分类
         * @param gesture 手势
         * @return 所有结果
         */
        virtual vector<TResult*> recognizer(Gesture *gesture) = 0;
        /**
         * 获得所有所有模板
         * @return
         */
        virtual std::map<std::string, std::vector<Polyline*> > getTemplate() = 0;
    };
}

#endif //_CLASSIFICATION_H
