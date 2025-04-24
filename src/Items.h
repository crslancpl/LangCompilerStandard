/*
* Items are the things defined in the code, for example: variables,
* functions, classes. There is a 'E' at the end of class name to
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

class ItemE{
    public:
    vector<string> scopes;
    string Name;
    string Type;
};

class VariableE: public ItemE{
    public:
    bool IsInitialized;
};

class FunctionE: public ItemE{
    public:
    map<string, string> args; //<arg name, arg type>
};

class ClassConstructorE: public FunctionE{
    public:

};

class ClassE: public ItemE{
    public:
    //Constructor
    vector<ClassConstructorE> Constructors;
    //Non-static
    map<string, FunctionE> Methods; //<method name, method>
    map<string, VariableE> Variables; //variable name, variable>
    //Staitc
    map<string, FunctionE> StaticMethods; //<method name, method>
    map<string, VariableE> StaticVariables; //variable name, variable>
};


#endif
