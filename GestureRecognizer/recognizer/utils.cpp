//
// Created by 杨忠诚 on 18/3/8.
//
#include <float.h>
#include <sys/time.h>
#include "utils.h"

using namespace ns_recognizer;

static struct timeval tv_begin;
static struct timeval tv_end;
static double elasped;

void Utils::bench_start() {
    gettimeofday(&tv_begin, NULL);
}

void Utils::bench_end(const char *comment) {
    gettimeofday(&tv_end, NULL);
    elasped = ((tv_end.tv_sec - tv_begin.tv_sec) * 1000000.0f + tv_end.tv_usec - tv_begin.tv_usec) / 1000.0f;
    printf("%.2fms   %s\n", elasped, comment);
}

std::vector<std::string> Utils::split_string(const std::string &str,
                                             const std::string &delimiter) {
    std::vector<std::string> strings;

    std::string::size_type pos = 0;
    std::string::size_type prev = 0;
    while ((pos = str.find(delimiter, prev)) != std::string::npos) {
        strings.push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
    }

    // To get the last substring (or only, if delimiter is not found)
    strings.push_back(str.substr(prev));

    return strings;
}

RectF Utils::getBoundBox(std::vector<TPoint*> points) {
    float minX = FLT_MAX;
    float maxX = -FLT_MAX;
    float minY = FLT_MAX;
    float maxY = -FLT_MAX;
    for(int i = 0; i < points.size(); i++) {
        minX = std::min(points[i]->x, minX);
        maxX = std::max(points[i]->x, maxX);
        minY = std::min(points[i]->y, minY);
        maxY = std::max(points[i]->y, maxY);
    }
    RectF result;
    result.left = minX;
    result.top = minY;
    result.right = maxX;
    result.bottom = maxY;
    return result;
}
