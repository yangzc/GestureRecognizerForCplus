//
// Created by 杨忠诚 on 18/3/13.
//

#ifndef _NCNN_CLASSIFICATION_H
#define _NCNN_CLASSIFICATION_H

#include "classification.h"
#include <ncnn/net.h>
#include "bitmap_image.hpp"

using namespace std;
namespace ns_recognizer {

    class NcnnClassification : public Classification {

    private:
        ncnn::Net *reg_net;
        std::vector<std::string> words;
    public:

        /**
         * 初始化Ncnn分类器
         * @param _paraMem
         * @param _binMem
         * @param _wordTxt
         */
        NcnnClassification(const unsigned char* _paraMem, const unsigned char* _binMem, string _wordTxt);

        /**
         * 根据手势识别分类
         * @param gesture 手势
         * @return 所有结果
         */
        virtual vector<TResult*> recognizer(Gesture *gesture);

        /**
         * 获得所有所有模板
         * @return
         */
        virtual std::map<std::string, std::vector<Polyline*> > getTemplate();

    private:
        bitmap_image buildBitmap(vector<Gesture*> gestures);
        void printValue(std::string label, float value[], int size);

        /**
         * 手势切割
         * @param gestures 切割手势
         * @return 返回切割后的手势
         */
        vector<vector<Gesture*> > cutGesture(vector<Gesture*> gestures);
    };
}
#endif //_NCNN_CLASSIFICATION_H
