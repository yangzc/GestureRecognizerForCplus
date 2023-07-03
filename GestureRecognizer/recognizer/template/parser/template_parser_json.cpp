//
// Created by 杨忠诚 on 18/1/16.
//

#include "json.h"
#include <fstream>
#include "gesture.h"
#include "gesture_utils.h"
#include "template_parser_json.h"

using namespace ns_recognizer;


JsonParser::JsonParser(std::string filePath) {
    this->filePath = filePath;
}

std::map<std::string, std::vector<Gesture*> > JsonParser::parser() {
    std::map<std::string, std::vector<Gesture*> > result;
    Json::Reader reader;
    std::ifstream is(this->filePath.c_str());
    Json::Value root;
    if (reader.parse(is, root)) {
        for (int i = 0; i < root.size(); ++i) {
            std::string tag = root[i]["t"].asCString();
            std::vector<Gesture*> gesture;
            Json::Value pointsArr = root[i]["p"];
            for (int j = 0; j < pointsArr.size(); ++j) {
                Json::Value points = pointsArr[j];
                Gesture *g = new Gesture();
                for (int k = 0; k < points.size(); k += 2) {
                    g->addPoint(new TPoint(points[k].asDouble(), points[k + 1].asDouble()));
                }
                gesture.push_back(g);
            }
            result.insert(std::pair<std::string, std::vector<Gesture*> >(tag, gesture));
        }
    }
    return result;
}

void JsonParser::save(std::map<std::string, std::vector<Gesture *> > map) {
    Json::Value root;

    std::map<std::string, std::vector<Gesture *> >::iterator iterator;
    for (iterator = map.begin(); iterator != map.end(); iterator ++) {
        std::string tag = iterator->first;
        std::vector<Gesture*> gestures = iterator->second;

        Json::Value jsonItem;
        Json::Value gestureArr;
        jsonItem["t"] = tag;
        jsonItem["p"] = gestureArr;

        for (int j = 0; j < gestures.size(); ++j) {
            Gesture *gesture = gestures[j];
            std::vector<TPoint*> points = gesture->getPoints();

            Json::Value pointArr;
            for (int k = 0; k < points.size(); ++k) {
                pointArr.append(points[k]->x);
                pointArr.append(points[k]->y);
            }
            gestureArr.append(pointArr);
        }

        root.append(jsonItem);
    }

    Json::FastWriter write;
    std::string content = write.write(root);
    std::ofstream ofs;
    ofs.open(this->filePath.c_str());
    ofs << content;
    ofs.close();
}
