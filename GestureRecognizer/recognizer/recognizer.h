//
// Created by 杨忠诚 on 18/1/12.
//

#ifndef _RECOGNIZER_H
#define _RECOGNIZER_H

#include <vector>
#include "reducer.h"
#include "matcher.h"
#include "template_manager.h"
#include "classification.h"
#include <ncnn/net.h>
#include "pair_rule.h"
#include "common_type.h"

using namespace std;
namespace ns_recognizer {

    class Recognizer {
    private:
        //合并规则
        PairRule *pairRule;
        //分类器
        Classification *classification;

        ncnn::Net *net;
        float density;
    public:

        static Recognizer* getInstance();

        /**
         * 使用基于手势的识别方法
         * @param filePath
         * @param density
         */
        void useGestureClassif(std::string filePath, float density);

        /**
         * 使用基于Ncnn的识别方法
         * @param _paraMem
         * @param _binMem
         * @param _wordTxt
         */
        void useNcnnClassif(const unsigned char *_paraMem, const unsigned char *_binMem,
                            string _wordTxt);

        /**
         * 多笔画识别
         * @param gs
         * @return
         */
        vector<TResult*> recognizer(vector<Gesture*> gs);

        /**
         * 获得模板
         * @return
         */
        std::map<std::string, std::vector<Polyline*> > getTemplate();

    private:
        /**
         * 构造方法
         */
        Recognizer();

        /**
         * 析构方法
         */
        virtual ~Recognizer();

        /**
         * 获得合并标签
         * @param list
         * @param start
         * @param end
         * @return
         */
        std::string getCombinationString(std::vector<TResult*> list, int start, int end);

        /**
         * 合并结果
         * @param list
         * @param maxDistance
         * @return
         */
        std::vector<TResult*> getCombinationResult(std::vector<TResult*> list, float maxDistance);

        /**
         * 获得最大可合并索引
         * @param list
         * @param start
         * @param end
         * @return
         */
        int getMaxCombinationIndex(std::vector<TResult*> list, int start, int end);

        /**
         * 单笔画识别
         * @param points
         * @return
         */
        vector<TResult*> recognizer(Gesture * gesture);
    };
}

#endif //_RECOGNIZER_H
