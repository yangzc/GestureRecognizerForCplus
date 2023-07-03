//
// Created by 杨忠诚 on 18/1/15.
//

#ifndef _TEMPLATE_MANAGER_H
#define _TEMPLATE_MANAGER_H

#include <vector>
#include <string>
#include <map>
#include "pair_rule.h"
#include "gesture.h"
#include "parser/template_parser.h"

namespace ns_recognizer {

    class TemplateManager {
    public:
        TemplateManager(std::string, PairRule *pairRule);
        std::map<std::string, std::vector<Gesture*> > getTemplateMap();
        void addTemplate(std::string tag, Gesture * gesture, bool isPersist);
        void clearTemplate();
        void removeTemplate(std::string);
    private:
        void reload();
        void save();
        void insertTemplate(std::map<std::string, std::string> labels, int count, ...);
    private:
        std::string pFilePath;
        std::map<std::string, std::vector<Gesture*> > templateMap;
        TemplateParser *parser;
        PairRule *pairRule;

    };
}

#endif //_TEMPLATE_MANAGER_H
