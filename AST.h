#ifndef _AST_H
#define _AST_H

#include <map>
#include <string>
#include <iostream>
#include <stack>
#include <list>

using namespace std;

enum ExprKind {
    ADD_EXPR,
    SUB_EXPR,
    MULT_EXPR,
    NUM_EXPR,
    ID_EXPR,
  };

class retData {
public:
    string code;
    string place;
};

class Expr {
public:
    Expr(){}
    virtual void generateCode(retData *data) = 0;
    virtual int getKind() = 0;
    bool isA(int kind) { return (getKind() == kind); }
};

class BinaryExpr: public Expr {
public:
    BinaryExpr(Expr *expr1, Expr *expr2) {
        this->expr1 = expr1;
        this->expr2 = expr2;
    }

    Expr *expr1;
    Expr *expr2;
};

class MultExpr: public BinaryExpr {
public:
    MultExpr(Expr *expr1, Expr *expr2) : BinaryExpr(expr1, expr2) {}

    void generateCode(retData *data);

    int getKind() { return MULT_EXPR; }
};

class AddExpr: public BinaryExpr {
public:
    AddExpr(Expr *expr1, Expr *expr2): BinaryExpr(expr1, expr2) {}

    void generateCode(retData *data);

    int getKind() { return ADD_EXPR; }
};

class SubExpr: public BinaryExpr {
public:
    SubExpr(Expr *expr1, Expr *expr2): BinaryExpr(expr1, expr2) {}

    void generateCode(retData *data);

    int getKind() { return SUB_EXPR; }
};

class NumExpr: public Expr {
public:
    NumExpr(char* value) { this->value = atoi(value); }

    void generateCode(retData *data);

    int getKind() { return NUM_EXPR; }

    int value;
};

class IdExpr: public Expr {
public:
    IdExpr(string id) { this->id = id; }
    
    void generateCode(retData *data);

    int getKind() { return ID_EXPR; }

    string id;
};

class AST {
public:
    list<Expr*> ExprList;
    retData *data = new retData();
    AST() {}

    void insertExpression(Expr* expr) {
        this->ExprList.push_front(expr);
    }

    void generateCode() {
        list<Expr*>::iterator it = ExprList.begin();
        
        while(it != ExprList.end()) {

            Expr *exp = *it;
            
            exp->generateCode(data);
            cout<< data->code << endl;

            it++;
        }
        cout<< endl;
    }
};

#endif