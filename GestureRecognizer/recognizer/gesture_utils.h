//
// Created by 杨忠诚 on 18/1/15.
//

#ifndef _GESTURE_UTILS_H
#define _GESTURE_UTILS_H

#include "common_type.h"
#include <stdio.h>
#include <vector>

#define SQUARE 200
#define SMALL_GESTURE_THRESHOLD 0.4f
//#define DOT_GESTURE_THRESHOLD 0.3f
#define ANGLE_THRESHOLD 20

namespace ns_recognizer {


    class GestureUtils {

    public:

        /**
         * 获取两个点距离
         * @param point1
         * @param point2
         * @return
         */
        static double distance(TPoint* point1, TPoint* point2);

        /**
         * 获得夹角最小点
         * @param points 向量点
         * @param thresholdAngle 角度阈值
         * @return 最小角度点
         */
        static TPoint getSmallestAngle(std::vector<TPoint*>, int thresholdAngle);

        /**
         * 获得三个点之间的角度
         * @param p0 点2
         * @param p1 点1
         * @param c 夹角点
         * @return 监督
         */
        static double getAngle(TPoint *p0, TPoint *p1, TPoint *c);

        /**
         * 获得所有点的边界
         * @param points 所有坐标向量点
         * @return 边界
         */
        static RectF getBoundBox(std::vector<TPoint*> points);
        static RectF getBoundBox(std::vector<TResult*> results);

        /**
         * 重新采样
         * @param points 采样点
         * @param sampleSize 采样数
         * @return 重新采样数据
         */
        static std::vector<TPoint*> reSample(std::vector<TPoint*> points, int sampleSize);

        /**
         * 获取总路径长度
         * @param points 所有点
         * @return 总路径长度
         * */
        static double getPathLength(std::vector <TPoint*> points);

        /**
         * 获得斜线
         * @param points 所有向量点
         * @return 斜线长度
         **/
        static double getDiagonal(std::vector<TPoint*> points);

        /** 获得中心点坐标
         * @param points 所有向量点
         * @return 中心点
         **/
        static TPoint getCenterPoint(std::vector<TPoint*> points);

        /**
         * 清除所有角度小于threshold角度的点
         * @param points 所有向量点
         * @param thresholdAngle 角度阈值
         * @return 结果
         **/
        static std::vector<TPoint*> removePointByThresholdAngle(std::vector<TPoint*> points, int thresholdAngle);

        /**
         * 坐标旋转变换
         * @param points 所有向量点
         * @param centerPoint 旋转圆心
         * @param theta 旋转角度
         * @return 旋转结果
         **/
        static std::vector<TPoint*>rotate(std::vector<TPoint*> points, TPoint centerPoint, float theta);

        /**
         * 坐标旋转变换
         * @param points 所有向量点
         * @param centerPoint 旋转圆心
         * @param theta 旋转角度
         * @return 旋转结果
         **/
        static std::vector<TPoint*>rotate(std::vector<TPoint*> points, TPoint centerPoint, float theta,
                                         bool optSelf);
        /**
         * 道格拉斯—普克(Douglas一Peukcer)采样算法
         * @param points 待采样所有点
         * @param tolerance 距离阈值
         * @return 采样后的所有点
         **/
        static std::vector<int> douglasPeukcerReducer(std::vector<TPoint*> points, double tolerance);

        /**
         * 获取Hausdorff Distance
         * @param points1 第一个向量点集合
         * @param points2 第二个向量点集合
         * @return 距离
         **/
        static float hausdorffDistance(std::vector<TPoint*> points1, std::vector<TPoint*> points2);

        /**
         * 获得有效控制点数
         * @param points 所有采样点
         * @param threshold 阈值(%)
         * @return 有效控制点
         **/
        static std::vector<TPoint*> getValidCtrlPointCnt(std::vector<TPoint*> points, double threshold);

        /**
         * 点集所形成的折线规整夹角的角度
         * @param points 未规整的点集
         * @param precision 精确到多少个点 （建议：是4的倍数）
         * @return
         **/
        static std::vector<TPoint*> beRegular(std::vector<TPoint*> points, int precision);


        static int getAngle(TPoint* point1, TPoint* point2, float thresohld);

    private:

        static void douglasPeukcerReducerImpl(std::vector<TPoint*> points, bool marked[], double tolerance,
                                  int firstIdx, int lastIndex);

        /**
         * 获得点到线段距离
         * @param point 目标点
         * @param start 开始点
         * @param end 结束点
         * @return 距离
         **/
        static double getDouglasPeukcerDistance(TPoint *point, TPoint *start, TPoint *end);

        static double hausdorffDistanceBetween(std::vector<TPoint*> points1, std::vector<TPoint*> points2);
    };
}

#endif //_GESTURE_UTILS_H
