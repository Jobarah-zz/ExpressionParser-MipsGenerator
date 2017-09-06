#include "AST.h"
#include<map>
#include<string>
#include <iostream>
#include <stack>
#include <list>

using namespace std;

map<string, bool> tempsMap = {
    {"$t0", false}, 
    {"$t1", false}, 
    {"$t2", false}, 
    {"$t3", false},
    {"$t4", false},
    {"$t5", false},
    {"$t6", false},
    {"$t7", false},
    {"$t8", false},
    {"$t9", false},
};

string getTemp() {
    for (std::map<string, bool>::iterator it=tempsMap.begin(); it!=tempsMap.end(); ++it)
        if(!it->second) {
            tempsMap[it->first] = true;
            return it->first;
        }
}

void releaseTemp(string _temp) {
    if(tempsMap[_temp])
        tempsMap[_temp] = false;
}

retData * AddExpr::generateCode() {
    retData *data = new retData();
    retData *expr1Data = expr1->generateCode();
    retData *expr2Data = expr2->generateCode();

    releaseTemp(expr1Data->place);
    releaseTemp(expr2Data->place);

    string instruction = "add", place = getTemp();

    if(this->expr1->isA(NUM_EXPR)) {
        instruction = "addi";
    }
    
    data->code = instruction + place + "," + expr1Data->place + "," + expr2Data->place + "\n";
    data->place = place;

    cout<<data->code;

    return data;
}

retData * SubExpr::generateCode()  {
    retData *data = new retData();
    data->code = "subExpr";
    data->place = "$t0";

    return data;
}

retData * MultExpr::generateCode() {
    retData *data = new retData();
    data->code = "multExpr";
    data->place = "$t0";

    return data;
}

retData * NumExpr::generateCode() {
    retData *data = new retData();

    string place = getTemp();

    data->code = "numExpr";
    data->place = place;

    return data;
}

retData * IdExpr::generateCode() {
    retData *data = new retData();

    string place = getTemp();

    data->code = "idExpr";
    data->place = place;

    return data;
}