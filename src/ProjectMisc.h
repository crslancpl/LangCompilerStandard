/*
* This will store other informations about the project, primarily
* properties for building the app or transpiling.
*/


#ifndef PROJECTMISC_H_
#define PROJECTMISC_H_
#pragma once

#include <memory>
#include <vector>
#include <string>

#include "FileReader.h"

using namespace std;

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
