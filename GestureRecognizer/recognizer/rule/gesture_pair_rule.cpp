//
// Created by 杨忠诚 on 18/3/20.
//

#include <algorithm>
#include "gesture_pair_rule.h"

using namespace ns_recognizer;

const std::string GesturePairRule::ZERO("0");
const std::string GesturePairRule::TWO("2");
const std::string GesturePairRule::THREE("3");
const std::string GesturePairRule::SIX("6");
const std::string GesturePairRule::SEVEN("7");
const std::string GesturePairRule::EIGHT("8");
const std::string GesturePairRule::NINE("9");

const std::string GesturePairRule::ONE("1");
const std::string GesturePairRule::HENG("-");
const std::string GesturePairRule::LEFT_PIE("/");
const std::string GesturePairRule::RIGHT_NA("\\");
const std::string GesturePairRule::XIAO_YU("<");
const std::string GesturePairRule::SHU_WAN_GOU("竖弯钩");


GesturePairRule::GesturePairRule() {
    SINGLE_GESTURE.push_back(ZERO);
    SINGLE_GESTURE.push_back(TWO);
    SINGLE_GESTURE.push_back(THREE);
    SINGLE_GESTURE.push_back(SIX);
    SINGLE_GESTURE.push_back(SEVEN);
    SINGLE_GESTURE.push_back(EIGHT);
    SINGLE_GESTURE.push_back(NINE);

    GESTURES.push_back(DOT);
    GESTURES.push_back(ONE);
    GESTURES.push_back(XIAO_YU);
    GESTURES.push_back(HENG);
    GESTURES.push_back(RIGHT_NA);//那
    GESTURES.push_back(LEFT_PIE);//右撇
    GESTURES.push_back(SHU_WAN_GOU);
}

std::vector<std::string> GesturePairRule::getAllGestures() {
    std::vector<std::string> list;
    list.insert(list.end(), SINGLE_GESTURE.begin(), SINGLE_GESTURE.end());
    list.insert(list.end(), GESTURES.begin(), GESTURES.end());
    return list;
}

std::string GesturePairRule::getAlias(std::string name) {
    if (strcmp(name.c_str(), SEVEN.c_str()) == 0) {
        return std::string("(7|>)");
    } else if (strcmp(name.c_str(), TWO.c_str()) == 0) {
        return std::string("(2|z)");
    } else {
        return name;
    }
}

//获得所有符号映射
std::map<std::string, std::string> GesturePairRule::getCombinationLabels() {
    std::map<std::string, std::string> labels;
    labels.insert(std::pair<std::string, std::string>(std::string(RIGHT_NA + LEFT_PIE), std::string("x")));
    labels.insert(std::pair<std::string, std::string>(std::string(LEFT_PIE + RIGHT_NA), std::string("x")));

    labels.insert(std::pair<std::string, std::string>(std::string(XIAO_YU + ONE), std::string("4")));
    labels.insert(std::pair<std::string, std::string>(std::string(XIAO_YU + LEFT_PIE), std::string("4")));
    labels.insert(std::pair<std::string, std::string>(std::string(SHU_WAN_GOU + HENG), std::string("5")));
    labels.insert(std::pair<std::string, std::string>(std::string(SHU_WAN_GOU + getShortLabel(HENG)), std::string("5")));
    labels.insert(std::pair<std::string, std::string>(std::string(SHU_WAN_GOU + RIGHT_NA), std::string("5")));

    labels.insert(std::pair<std::string, std::string>(std::string(HENG + SHU_WAN_GOU), std::string("5")));
    labels.insert(std::pair<std::string, std::string>(std::string(getShortLabel(HENG) + SHU_WAN_GOU), std::string("5")));
    labels.insert(std::pair<std::string, std::string>(std::string(RIGHT_NA + SHU_WAN_GOU), std::string("5")));

    labels.insert(std::pair<std::string, std::string>(std::string(getShortLabel(RIGHT_NA) + LEFT_PIE), std::string("y")));
    labels.insert(std::pair<std::string, std::string>(std::string(getShortLabel(RIGHT_NA) + ONE), std::string("y")));

    labels.insert(std::pair<std::string, std::string>(std::string(HENG + HENG), std::string("=")));
    labels.insert(std::pair<std::string, std::string>(std::string(HENG + ONE), std::string("+")));

//    labels.insert(std::pair<std::string, std::string>(std::string(ONE + HENG + ONE), std::string("÷")));
//    labels.insert(std::pair<std::string, std::string>(std::string(RIGHT_NA + HENG + RIGHT_NA), std::string("÷")));
//    labels.insert(std::pair<std::string, std::string>(std::string(getShortLabel(RIGHT_NA) + HENG + getShortLabel(RIGHT_NA)), std::string("÷")));
//    labels.insert(std::pair<std::string, std::string>(std::string(getShortLabel(RIGHT_NA) + HENG + RIGHT_NA), std::string("÷")));
//    labels.insert(std::pair<std::string, std::string>(std::string(RIGHT_NA + HENG + getShortLabel(RIGHT_NA)), std::string("÷")));
//    labels.insert(std::pair<std::string, std::string>(std::string(ONE + HENG + RIGHT_NA), std::string("÷")));
    labels.insert(std::pair<std::string, std::string>(std::string(DOT + HENG + DOT), std::string("÷")));

//    labels.insert(std::pair<std::string, std::string>(std::string(HENG + ONE + ONE), std::string("÷")));
//    labels.insert(std::pair<std::string, std::string>(std::string(HENG + RIGHT_NA + RIGHT_NA), std::string("÷")));
//    labels.insert(std::pair<std::string, std::string>(std::string(HENG + getShortLabel(RIGHT_NA) + getShortLabel(RIGHT_NA)), std::string("÷")));
//    labels.insert(std::pair<std::string, std::string>(std::string(HENG + getShortLabel(RIGHT_NA) + RIGHT_NA), std::string("÷")));
//    labels.insert(std::pair<std::string, std::string>(std::string(HENG + RIGHT_NA + getShortLabel(RIGHT_NA)), std::string("÷")));
//    labels.insert(std::pair<std::string, std::string>(std::string(HENG + ONE + RIGHT_NA), std::string("÷")));
    labels.insert(std::pair<std::string, std::string>(std::string(HENG + DOT + DOT), std::string("÷")));

    labels.insert(std::pair<std::string, std::string>(std::string(ONE), std::string(ONE)));
    labels.insert(std::pair<std::string, std::string>(std::string(XIAO_YU), std::string(XIAO_YU)));
    labels.insert(std::pair<std::string, std::string>(std::string(HENG), std::string(HENG)));
    labels.insert(std::pair<std::string, std::string>(std::string(RIGHT_NA), std::string("\\")));
    labels.insert(std::pair<std::string, std::string>(std::string(LEFT_PIE), std::string("/")));
    labels.insert(std::pair<std::string, std::string>(std::string(SHU_WAN_GOU), std::string("?")));
    labels.insert(std::pair<std::string, std::string>(std::string(DOT), std::string(".")));
    return labels;
}


std::string GesturePairRule::getShortLabel(std::string label) {
//    if (strcmp(label.c_str(), RIGHT_NA.c_str()) == 0) {
//        return label + "_S";
    return DOT;
//    }
//    return label;
}


bool GesturePairRule::isSingleGesture(std::string tag) {
    return std::find(SINGLE_GESTURE.begin(), SINGLE_GESTURE.end(), tag) != SINGLE_GESTURE.end();
}