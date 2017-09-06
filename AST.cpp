#include "AST.h"
#include <map>
#include <string>
#include <iostream>
#include <stack>
#include <list>
#include <string.h>

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

void AddExpr::generateCode(retData* data) {
    retData *data1 = new retData();
    retData *data2 = new retData();
    expr1->generateCode(data1);
    expr2->generateCode(data2);

    releaseTemp(data1->place);
    releaseTemp(data2->place);

    string instruction = "add ", place = getTemp();

    if(this->expr1->isA(NUM_EXPR)) {
        instruction = "addi ";
    }
    string newCode = strdup(data->code.c_str());
    newCode += instruction + place + ", " + data1->place + ", " + data2->place + "\n";
    data->code = newCode;
    data->place = place;

    cout<< "dentro de genCode weon " << data->code;
}

void SubExpr::generateCode(retData* data) {
    data->code = "subExpr";
    data->place = "$t0";
}

void MultExpr::generateCode(retData* data) {
    data->code = "multExpr";
    data->place = "$t0";
}

void NumExpr::generateCode(retData* data) {
    string place = getTemp();

    cout<< "dentro de NumExpr" << endl;

    data->code = "numExpr";
    data->place = place;
}

void IdExpr::generateCode(retData* data) {

    string place = getTemp();

    data->code = "idExpr";
    data->place = this->id;
}