/*
* This will store other informations about the project, primarily
* properties for building the app or transpiling.
*/


#ifndef PROJECTMISC_H_
#define PROJECTMISC_H_
#include <utility>
#pragma once

#include <memory>
#include <map>
#include <vector>
#include <string>

#include "FileReader.h"

using namespace std;

enum class TypeCode{
    OTHERS = 0,
    VAR = 1,
    FUNC = 2,
    CLASS = 3,
    ADD = 4,
    DASH = 5,
    STAR = 6,
    SLASH = 7,
    EQUAL = 8,
    COMMA = 9,
    DOT = 10,
    BRACKL = 11,
    BRACKR = 12,
    ANGBRACKL = 13,
    ANGBRACKR = 14,
    BLOCBRACKL = 15,
    BLOCBRACKR = 16,
    BRACEL = 17,
    BRACER = 18
};

void AddKeywordCode(const string &Keyword, unsigned short Code);
void AddKeyword(const string &Code , const string &Keyword);

void AddReader(shared_ptr<Reader> &reader);

void SetInputFileDir(const string &Dir);
string GetInputFileDir();
void SetEntryFile(const string& FilePath);
string GetEntryFile();
void SetEntryFunc(const string &FuncName);
string GetEntryFuncName();

void AddProcessedFile(pair<string,bool> *p);
bool CheckIfFileProcessedBefore(const string &FileName);
//If no than it will be pushed to `map<string,bool> AssociateFiles` in ProjectMisc.cpp

void PrintReaders();

#endif
