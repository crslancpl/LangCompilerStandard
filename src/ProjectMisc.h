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

static vector< shared_ptr<Reader> > Readers;

void AddReader(shared_ptr<Reader> &reader);

void SetInputFileDir(const string &Dir);
string GetInputFileDir();
void SetEntryFile(const string& FilePath);
string GetEntryFile();
void SetEntryFunc(const string &FuncName);
string GetEntryFuncName();

void PrintReaders();

#endif
