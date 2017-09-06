#include "AST.h"
#include <map>
#include <string>
#include <iostream>
#include <stack>
#include <list>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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
    string leftVal = data1->place;
    string rightVal = data2->place;

    string code = data1->code + "\n" + data2->code + "\n";    

    releaseTemp(data1->place);
    releaseTemp(data2->place);

    string instruction = "add ", place = getTemp();

    if(this->expr1->isA(NUM_EXPR)) {
        code = data2->code + "\n";
        code += "addi " + place + ", " + data2->place + ", " + std::to_string(((NumExpr*)expr1)->value);
	}else if(this->expr2->isA(NUM_EXPR))
	{
        code = data1->code + "\n";
		code += "addi " + place + ", " + data1->place + ", " + std::to_string(((NumExpr*)expr2)->value);
	}else{
		code += "add " + place + ", " + data1->place + ", " + data2->place;
	}

    data->code = code;
    data->place = place;

    delete data1;
    delete data2;
}

void SubExpr::generateCode(retData* data) {
    retData *data1 = new retData();
    retData *data2 = new retData();
    expr1->generateCode(data1);
    expr2->generateCode(data2);

    string code = data1->code + "\n" + data2->code + "\n";    

    releaseTemp(data1->place);
    releaseTemp(data2->place);

    string instruction = "sub ", place = getTemp();

    // if(this->expr1->isA(NUM_EXPR)) {
    //     instruction = "addi ";
    // }

    code += instruction + place + ", " + data1->place + ", " + data2->place;

    data->code = code;
    data->place = place;

    delete data1;
    delete data2;
}

void MultExpr::generateCode(retData* data) {
    retData *data1 = new retData();
    retData *data2 = new retData();
    expr1->generateCode(data1);
    expr2->generateCode(data2);

    string code = data1->code + "\n" + data2->code + "\n";    

    releaseTemp(data1->place);
    releaseTemp(data2->place);

    string instruction = "mult ", place = getTemp();

    code += instruction + place + ", " + data1->place + ", " + data2->place + "\n";
    code += "mflo " + place;

    data->code = code;
    data->place = place;

    delete data1;
    delete data2;
}

void NumExpr::generateCode(retData* data) {
    string place = getTemp();
    string sVal = std::to_string(this->value);
    data->code = "li " + place + ", " + sVal;
    data->place = place;
}

void IdExpr::generateCode(retData* data) {

    string place = getTemp();

    data->code = "lw " + place + ", " + this->id;
    data->place = place;
}