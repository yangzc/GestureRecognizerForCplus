//
//  main.cpp
//  GestureRecognizer
//
//  Created by yangzc on 2018/6/4.
//  Copyright © 2018年 yangzc. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <vector>
#include "gesture.h"
#include "recognizer.h"
#include "lenet.mem.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace ns_recognizer;

void printValue(std::string label, std::vector<float> value) {
    std::vector<Gesture *> gsVector;
    Gesture * g = new Gesture();
    
    for (int i = 0; i < value.size(); i += 2) {
        float x = value[i];
        float y = value[i + 1];
        //获取数据点
        g->addPoint(new TPoint(x, y));
    }
    gsVector.push_back(g);
    vector<TResult*> result = ns_recognizer::Recognizer::getInstance()->recognizer(gsVector);
//   PRINTF("result %s = %s", label.c_str(), result.c_str());
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "start init engine !" << endl;
    
    std::string str;
    ifstream myfile("/Users/yangzc/devsoft/project/android/GestureRecognizer/library/src/main/assets/synset_words.txt");
    string temp;
    while (getline(myfile, temp)) {
        str.append(temp + "\n");
    }
    myfile.close();
    
    Recognizer::getInstance()->useNcnnClassif(lenet_param_bin, lenet_bin, str);
    
    float value1[] = {351,160,351,173,350,183,349,194,348,204,347,219,346,230,345,243,344,253,344,264,344,275,343,287,342,301,341,314,340,329,339,344,338,359,338,370,338,381,337,391};
    float value2[] = {261,152,273,145,283,141,295,137,307,135,319,135,331,137,340,148,346,159,350,171,354,182,357,193,359,207,359,220,359,232,358,246,352,261,347,270,340,279,328,295,314,308,299,318,284,328,269,337,259,342,251,352,246,362,262,365,281,365,294,365,307,365,319,365,331,365,348,365,360,365,375,365,386,365,400,365,414,364,429,363,439,362};
    float value3[] = {290,167,302,163,314,159,327,155,337,153,350,153,361,154,369,163,372,173,373,184,373,201,372,212,366,222,358,232,349,240,333,249,323,253,306,259,294,263,306,261,320,259,331,258,342,257,358,257,370,259,380,266,385,279,386,291,387,306,384,327,379,340,375,351,370,363,363,374,353,385,340,398,329,408,317,415,308,421,293,424,281,428};
    float value6[] = {365,187,353,197,346,205,341,217,335,232,330,247,325,263,321,279,318,295,317,313,316,331,318,343,322,356,328,373,334,382,348,391,363,395,379,398,390,398,406,398,421,393,432,380,439,371,442,361,445,351,448,337,444,323,433,316,422,312,410,309,397,307,383,305,371,304,359,306,349,309,339,315};
    float value7[] = {279,164,291,164,306,163,323,162,334,162,353,162,368,162,383,162,395,162,405,163,405,178,405,194,405,211,403,227,400,256,396,283,392,309,387,339,385,359,380,392,378,409,376,431,374,447,373,459,373,472};
    float value8[] = {363,190,352,190,340,190,330,195,321,205,314,216,310,232,313,250,323,263,342,279,358,287,380,300,398,310,418,323,435,334,448,343,458,351,470,367,474,378,478,394,480,411,480,429,478,446,468,466,454,480,436,492,413,498,388,499,360,498,341,491,320,480,307,470,299,461,292,444,292,425,292,402,295,377,301,353,307,330,312,313,317,294,323,279,328,268,337,249,342,239,347,226,350,215,352,205,357,192};
    float value9[] = {414,209,401,219,394,234,390,245,389,256,389,269,396,280,408,286,420,289,433,286,440,273,445,255,447,245,449,232,449,221,447,245,444,267,441,297,437,349,435,388,434,433,433,474,431,505,430,524,429,536,429,547};
    
    {
        printValue("1", vector<float>(begin(value1), end(value1)));
        printValue("2", vector<float>(begin(value2), end(value2)));
        printValue("3", vector<float>(begin(value3), end(value3)));
        printValue("6", vector<float>(begin(value6), end(value6)));
        printValue("7", vector<float>(begin(value7), end(value7)));
        printValue("8", vector<float>(begin(value8), end(value8)));
        printValue("9", vector<float>(begin(value9), end(value9)));
    }
    
    return 0;
}
