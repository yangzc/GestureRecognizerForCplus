//
// Created by 杨忠诚 on 18/3/13.
//

#ifndef _CMB_RULE_H
#define _CMB_RULE_H

#include <string>
#include <vector>
#include <map>

using namespace std;
namespace ns_recognizer {
    class PairRule {

    public:
        virtual std::vector<std::string> getAllGestures() = 0;
        virtual std::string getAlias(std::string) = 0;
        virtual std::map<std::string, std::string> getCombinationLabels() = 0;
        virtual std::string getShortLabel(std::string) = 0;
        virtual bool isSingleGesture(std::string) = 0;
    public:
        static const std::string DOT;
        static const std::string SPLIT;
    };
}

#endif //_CMB_RULE_H
