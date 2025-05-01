#ifndef FILEDATAS_H_
#define FILEDATAS_H_

#pragma once

#include <string>
#include <vector>

#include "Items.h"


using namespace std;


class FileDatas{
    public:
    string Path;
    string FileName;
    string InputFilePath;
    unsigned int CurrentLine;
    vector<int> TagLines;

    vector<string> AssociatedFiles;

    vector<EVariable> Variables;
    vector<EFunction> Functtios;
    vector<EClass> Classes;
};

#endif
