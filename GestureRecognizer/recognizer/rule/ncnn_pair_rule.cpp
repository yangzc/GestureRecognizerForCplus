//
// Created by 杨忠诚 on 18/3/20.
//

#include <algorithm>
#include "ncnn_pair_rule.h"

using namespace ns_recognizer;

const std::string NcnnPairRule::ZERO("0");
const std::string NcnnPairRule::ONE("1");
const std::string NcnnPairRule::TWO("2");
const std::string NcnnPairRule::THREE("3");
const std::string NcnnPairRule::FOUR("4");
const std::string NcnnPairRule::FIVE("5");
const std::string NcnnPairRule::SIX("6");
const std::string NcnnPairRule::SEVEN("7");
const std::string NcnnPairRule::EIGHT("8");
const std::string NcnnPairRule::NINE("9");
const std::string NcnnPairRule::NA("10");
const std::string NcnnPairRule::PIE("11");
const std::string NcnnPairRule::Y("12");
const std::string NcnnPairRule::DAYU("13");
const std::string NcnnPairRule::XIAOYU("14");
const std::string NcnnPairRule::Z("15");
const std::string NcnnPairRule::HENG("16");

NcnnPairRule::NcnnPairRule() {
    NCNN_SINGLE_GESTURE.push_back(ZERO);
    NCNN_SINGLE_GESTURE.push_back(TWO);
    NCNN_SINGLE_GESTURE.push_back(THREE);
    NCNN_SINGLE_GESTURE.push_back(SIX);
    NCNN_SINGLE_GESTURE.push_back(SEVEN);
    NCNN_SINGLE_GESTURE.push_back(EIGHT);
    NCNN_SINGLE_GESTURE.push_back(NINE);
    NCNN_SINGLE_GESTURE.push_back(DAYU);
    NCNN_SINGLE_GESTURE.push_back(Y);
    NCNN_SINGLE_GESTURE.push_back(Z);

    NCNN_GESTURES.push_back(DOT);
    NCNN_GESTURES.push_back(ONE);
    NCNN_GESTURES.push_back(FOUR);
    NCNN_GESTURES.push_back(XIAOYU);
    NCNN_GESTURES.push_back(HENG);
    NCNN_GESTURES.push_back(NA);//那
    NCNN_GESTURES.push_back(PIE);//右撇
    NCNN_GESTURES.push_back(FIVE);
}

std::string NcnnPairRule::getShortLabel(std::string label) {
    return label + "_S";
//    return PairRule::DOT;
}

std::map<std::string, std::string> NcnnPairRule::getCombinationLabels() {
    std::map<std::string, std::string> labels;
    labels.insert(std::pair<std::string, std::string>(MAKE_KEY(ZERO), std::string("0")));
    labels.insert(std::pair<std::string, std::string>(MAKE_KEY(ONE), std::string("1")));
    labels.insert(std::pair<std::string, std::string>(MAKE_KEY(TWO), std::string("2")));
    labels.insert(std::pair<std::string, std::string>(MAKE_KEY(THREE), std::string("3")));
    labels.insert(std::pair<std::string, std::string>(MAKE_KEY_2(FOUR, ONE), std::string("4")));
    labels.insert(std::pair<std::string, std::string>(MAKE_KEY_2(XIAOYU, ONE), std::string("4")));
    labels.insert(std::pair<std::string, std::string>(MAKE_KEY_2(HENG, FIVE), std::string("5")));
    labels.insert(std::pair<std::string, std::string>(MAKE_KEY_2(FIVE, HENG), std::string("5")));
    labels.insert(std::pair<std::string, std::string>(MAKE_KEY_2(FIVE, getShortLabel(HENG)), std::string("5")));
    labels.insert(std::pair<std::string, std::string>(MAKE_KEY_2(getShortLabel(HENG), FIVE), std::string("5")));
    labels.insert(std::pair<std::string, std::string>(MAKE_KEY(SIX), std::string("6")));
    labels.insert(std::pair<std::string, std::string>(MAKE_KEY(SEVEN), std::string("7")));
    labels.insert(std::pair<std::string, std::string>(MAKE_KEY(EIGHT), std::string("8")));
    labels.insert(std::pair<std::string, std::string>(MAKE_KEY(NINE), std::string("9")));

    labels.insert(std::pair<std::string, std::string>(MAKE_KEY(DAYU), std::string(">")));
    labels.insert(std::pair<std::string, std::string>(MAKE_KEY(XIAOYU), std::string("<")));
    labels.insert(std::pair<std::string, std::string>(MAKE_KEY_2(HENG, HENG), std::string("=")));

    labels.insert(std::pair<std::string, std::string>(MAKE_KEY_2(NA, PIE), std::string("x")));
    labels.insert(std::pair<std::string, std::string>(MAKE_KEY_2(NA, ONE), std::string("x")));
    labels.insert(std::pair<std::string, std::string>(MAKE_KEY_2(getShortLabel(NA), PIE), std::string("y")));

    labels.insert(std::pair<std::string, std::string>(MAKE_KEY(Y), std::string("y")));
    labels.insert(std::pair<std::string, std::string>(MAKE_KEY(Z), std::string("z")));

    labels.insert(std::pair<std::string, std::string>(MAKE_KEY_2(HENG, ONE), std::string("+")));
    labels.insert(std::pair<std::string, std::string>(MAKE_KEY(HENG), std::string("-")));
    labels.insert(std::pair<std::string, std::string>(MAKE_KEY_3(DOT, HENG, DOT), std::string("÷")));
    labels.insert(std::pair<std::string, std::string>(MAKE_KEY_3(HENG, DOT, DOT), std::string("÷")));


    labels.insert(std::pair<std::string, std::string>(MAKE_KEY(FOUR), std::string("<")));
    labels.insert(std::pair<std::string, std::string>(MAKE_KEY(FIVE), std::string("?")));
    labels.insert(std::pair<std::string, std::string>(MAKE_KEY(NA), std::string("\\")));
    labels.insert(std::pair<std::string, std::string>(MAKE_KEY(PIE), std::string("/")));
    return labels;
}

std::vector<std::string> NcnnPairRule::getAllGestures() {
    std::vector<std::string> list;
    list.insert(list.end(), NCNN_SINGLE_GESTURE.begin(), NCNN_SINGLE_GESTURE.end());
    list.insert(list.end(), NCNN_GESTURES.begin(), NCNN_GESTURES.end());
    return list;
}

std::string NcnnPairRule::getAlias(std::string name) {
    if (strcmp(name.c_str(), SEVEN.c_str()) == 0 || strcmp(name.c_str(), DAYU.c_str()) == 0) {
        return std::string("(7|>)");
    } else if (strcmp(name.c_str(), TWO.c_str()) == 0 || strcmp(name.c_str(), Z.c_str()) == 0) {
        return std::string("(2|z)");
    } else if (strcmp(name.c_str(), Y.c_str()) == 0) {
        return std::string("y");
    } else {
        return name;
    }
}

bool NcnnPairRule::isSingleGesture(std::string tag) {
    return std::find(NCNN_SINGLE_GESTURE.begin(), NCNN_SINGLE_GESTURE.end(), tag) != NCNN_SINGLE_GESTURE.end();
}
