//
// Created by 杨忠诚 on 18/1/15.
//

#ifndef _GESTURE_H
#define _GESTURE_H

#include <vector>
#include "common_type.h"

namespace ns_recognizer {
    class Gesture {
    private:
        //原始点
        std::vector<TPoint*> points;
        //长度
        std::vector<double> lengths;
        //关键点
        std::vector<TPoint*> keyPoints;
        //维度
        int dimensionalNum;
        //初始化长度
        void initLengths();
    public:
        /**
         * 添加点
         * @param point
         */
        void addPoint(TPoint* point);

        /**
         * 获得所有点
         * @return
         */
        std::vector<TPoint*> getPoints();

        /**
         * 设置原始点
         */
        void setPoints(std::vector<TPoint*>);

        /**
         * 获取索引
         * @param point
         * @return
         */
        int indexOf(TPoint point);

        /**
         * 通过索引获得点
         * @param index
         * @return
         */
        TPoint* getPoint(int index);

        /**
         * 获得手势范围
         * @return
         */
        RectF getRectF();

        /**
         * 添加手势
         * @param gesture
         */
        void addGesture(Gesture gesture);

        /**
         * 设置关键点
         * @param keyPoints
         */
        void setKeyPoints(std::vector<TPoint*> keyPoints);

        /**
         * 获得关键点
         * @return
         */
        std::vector<TPoint*> getKeyPoints();

        /**
         * 设置维度
         * @param dimensionalNum
         */
        void setDimensionalNum(int dimensionalNum);

        /**
         * 获得维度
         * @return
         */
        int getDimensionalNum();

        /**
         * 添加长度
         * @param index
         * @return
         */
        double getLength(int index);

        /**
         * 获得总长度
         * @return
         */
        double getTotalLength();

        /**
         * 克隆手势
         * @return
         */
        Gesture* clone();

    };
}

#endif //_GESTURE_H
