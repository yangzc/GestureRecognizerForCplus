//
// Created by 杨忠诚 on 18/1/15.
//

#include <algorithm>
#include "template_parser_json.h"
#include "template_manager.h"

using namespace ns_recognizer;

TemplateManager::TemplateManager(std::string filePath, PairRule *pairRule) {
    //保存文件路径
    this->pFilePath = filePath;
    //初始化解析器
    this->parser = new JsonParser(filePath);
    //匹配规则
    this->pairRule = pairRule;
    reload();
}

void TemplateManager::insertTemplate(std::map<std::string, std::string> labels, int count, ...) {
}

std::map<std::string, std::vector<Gesture*> > TemplateManager::getTemplateMap() {
    return this->templateMap;
}

void TemplateManager::reload() {
    std::vector<std::string> gs = pairRule->getAllGestures();
    std::map<std::string, std::vector<Gesture*> > gestureMap = parser->parser();
    std::map<std::string, std::vector<Gesture*> >::iterator iterator;
    for (iterator = gestureMap.begin(); iterator != gestureMap.end(); iterator ++) {
        std::string key = iterator->first;
        if (std::find(gs.begin(), gs.end(), key) == gs.end())
            continue;
        this->templateMap.insert(std::pair<std::string, std::vector<Gesture*> >(key, iterator->second));
    }
}

void TemplateManager::save() {
    parser->save(this->templateMap);
}

void TemplateManager::addTemplate(std::string tag, Gesture *gesture, bool isPersist) {
    std::vector<Gesture*> gestures = this->templateMap.at(tag);
    std::map<std::string, std::vector<Gesture*> >::iterator it = this->templateMap.find(tag);
    if (it == templateMap.end()) {
        this->templateMap.insert(std::pair<std::string, std::vector<Gesture*> >(tag, gestures));
    }
    gestures.push_back(gesture);
    if (isPersist)
        save();
}

void TemplateManager::clearTemplate() {
    this->templateMap.clear();
}

void TemplateManager::removeTemplate(std::string tag) {
    this->templateMap.erase(tag);
}







