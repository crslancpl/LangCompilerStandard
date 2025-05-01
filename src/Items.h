/*
* Items are the things defined in the code, for example: variables,
* functions, classes. There is a 'E' infront of class name to
* prevent ambiguous with other built-in items
*
*/

#ifndef ITEMS_H_
#define ITEMS_H_

#pragma once

#include <string>
#include <map>
#include <vector>

using namespace std;

class EItem{
    public:
    vector<string> scopes;
    string Name;
    string Type;
};

class EVariable: public EItem{
    public:
    bool Static;
    bool IsInitialized;
};

class EFunction: public EItem{
    public:
    map<string, string> args; //<arg name, arg type>
};

class EClassConstructor: public EFunction{
    public:

};

class EClass: public EItem{
    public:
    //Constructor
    vector<EClassConstructor> Constructors;
    //Non-static
    map<string, EFunction> Methods; //<method name, method>
    map<string, EVariable> Variables; //variable name, variable>
    //Staitc
    map<string, EFunction> StaticMethods; //<method name, method>
    map<string, EVariable> StaticVariables; //variable name, variable>
};


#endif
