//
// Created by 杨忠诚 on 18/1/16.
//

#ifndef _TEMPLATE_PARSER_JSON_H
#define _TEMPLATE_PARSER_JSON_H

#include "template_parser.h"

namespace ns_recognizer {

    class JsonParser : public TemplateParser {

    public:

        JsonParser(std::string);

        /**
         * 解析
         * @return
         */
        virtual std::map<std::string, std::vector<Gesture*> > parser();

        /**
         * 保存
         */
        virtual void save(std::map<std::string, std::vector<Gesture*> >);

    private:
        std::string filePath;
    };

}

#endif //_TEMPLATE_PARSER_JSON_H
