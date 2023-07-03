//
// Created by 杨忠诚 on 18/1/16.
//

#ifndef _TEMPLATE_PARSER_H
#define _TEMPLATE_PARSER_H

#include <map>
#include <string>
#include <vector>
#include "gesture.h"

namespace ns_recognizer {

    class TemplateParser {
    public:

        /**
         * 解析
         * @return
         */
        virtual std::map<std::string, std::vector<Gesture*> > parser() = 0;

        /**
         * 保存
         */
        virtual void save(std::map<std::string, std::vector<Gesture*> >) = 0;
    };

}

#endif //_TEMPLATE_PARSER_H
