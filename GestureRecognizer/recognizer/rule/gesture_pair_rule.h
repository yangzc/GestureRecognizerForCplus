//
// Created by 杨忠诚 on 18/3/20.
//

#ifndef _GESTURE_PAIR_RULE_H
#define _GESTURE_PAIR_RULE_H

#include "pair_rule.h"

namespace ns_recognizer {

    class GesturePairRule : public PairRule {

    public:
        GesturePairRule();

        virtual std::vector<std::string> getAllGestures();
        virtual std::string getAlias(std::string);
        virtual std::map<std::string, std::string> getCombinationLabels();
        virtual std::string getShortLabel(std::string);
        virtual bool isSingleGesture(std::string);

    private:
        std::vector<std::string> GESTURES;
        std::vector<std::string> SINGLE_GESTURE;

        static const std::string ZERO;
        static const std::string TWO;
        static const std::string THREE;
        static const std::string SIX;
        static const std::string SEVEN;
        static const std::string EIGHT;
        static const std::string NINE;

        static const std::string ONE;
        static const std::string HENG;
        static const std::string LEFT_PIE;
        static const std::string RIGHT_NA;
        static const std::string XIAO_YU;
        static const std::string SHU_WAN_GOU;
    };
}

#endif //_GESTURE_PAIR_RULE_H
