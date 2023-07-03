//
// Created by 杨忠诚 on 18/1/12.
//

#ifndef _COMMON_TYPE_H
#define _COMMON_TYPE_H

#include <string>
namespace ns_recognizer {

    //点
    struct TPoint {

        TPoint(float x, float y) {
            this->x = x;
            this->y = y;
        }

        TPoint() {}

        float x = 0;
        float y = 0;
    };

    //结果
    struct TResult {

        TResult() {}

        TResult(std::string* tag, float score) {
            this->tag = *tag;
            this->score = score;
        }

        std::string tag;
        float score = 0;
        float left = 0;
        float top = 0;
        float right = 0;
        float bottom = 0;
        int dimensional = 0;
        int isShort = 0;
    };

    //范围
    struct RectF {
        float left = 0;
        float top = 0;
        float right = 0;
        float bottom = 0;
    };

    //向量
    struct Vector {
        double distance = 0;
        double angle = 0;
        TPoint *start = NULL;
        TPoint *end = NULL;
    };

    enum Direction {
        TOP_BOTTOM,//上下结构
        MIX,//混合结果
    };

    enum Word_size {
        NORMAL, SHORT, DOT
    };
}
#endif //_COMMON_TYPE_H
