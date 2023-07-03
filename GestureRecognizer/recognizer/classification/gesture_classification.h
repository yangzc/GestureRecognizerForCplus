//
// Created by 杨忠诚 on 18/3/13.
//

#ifndef _GESTURE_CLASSIFICATION_H
#define _GESTURE_CLASSIFICATION_H

#include "reducer.h"
#include "matcher.h"
#include "template_manager.h"
#include "classification.h"

using namespace std;
namespace ns_recognizer {

    class GestureClassification : public Classification {

    private:
        Reducer * reducer;
        Matcher * matcher;
        TemplateManager * templateManager;
        std::map<std::string, std::vector<Polyline*> > templateMap;
    public:

        GestureClassification(string templatePath, PairRule *pairRule);

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
    };
}

#endif //_GESTURE_CLASSIFICATION_H
