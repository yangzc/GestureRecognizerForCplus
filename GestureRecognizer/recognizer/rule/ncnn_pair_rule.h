//
// Created by 杨忠诚 on 18/3/20.
//

#ifndef _NCNN_PAIR_RULE_H
#define _NCNN_PAIR_RULE_H


#include "pair_rule.h"

namespace ns_recognizer {

#define MAKE_KEY(s) PairRule::SPLIT + s + PairRule::SPLIT
#define MAKE_KEY_2(s1, s2) PairRule::SPLIT + s1 + PairRule::SPLIT + PairRule::SPLIT + s2 + PairRule::SPLIT
#define MAKE_KEY_3(s1, s2, s3) \
    PairRule::SPLIT + s1 + PairRule::SPLIT + \
    PairRule::SPLIT + s2 + PairRule::SPLIT + \
    PairRule::SPLIT + s3 + PairRule::SPLIT

    class NcnnPairRule : public PairRule {

    public:
        NcnnPairRule();

        virtual std::vector<std::string> getAllGestures();
        virtual std::string getAlias(std::string);
        virtual std::map<std::string, std::string> getCombinationLabels();
        virtual std::string getShortLabel(std::string);
        virtual bool isSingleGesture(std::string);

        static const std::string ZERO;
        static const std::string ONE;
        static const std::string TWO;
        static const std::string THREE;
        static const std::string FOUR;
        static const std::string FIVE;
        static const std::string SIX;
        static const std::string SEVEN;
        static const std::string EIGHT;
        static const std::string NINE;
        static const std::string NA;
        static const std::string PIE;
        static const std::string DAYU;
        static const std::string XIAOYU;
        static const std::string Y;
        static const std::string Z;
        static const std::string HENG;

    private:
        std::vector<std::string> NCNN_GESTURES;
        std::vector<std::string> NCNN_SINGLE_GESTURE;
    };
}

#endif //_NCNN_PAIR_RULE_H
