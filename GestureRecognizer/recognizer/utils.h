//
// Created by 杨忠诚 on 18/3/8.
//

#ifndef _COMMONS_H
#define _COMMONS_H

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include "recognizer.h"

using namespace std;

namespace ns_recognizer {
    class Utils {
    public:

        static void bench_start();
        static void bench_end(const char* comment);
        static std::vector<std::string> split_string(const std::string& str, const std::string& delimiter);

        /**
         * 获得所有点的边界
         * @param points 所有坐标向量点
         * @return 边界
         */
        static RectF getBoundBox(std::vector<TPoint*> points);

    private:
    };
}
#endif //_COMMONS_H
