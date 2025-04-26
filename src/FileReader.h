/*
* This will read the input file character by character
*/

#ifndef FILEREADER_H_
#define FILEREADER_H_
#include "GlobalTools.h"
#pragma once

#include <iostream>
#include <string>

#include "FileDatas.h"

using namespace std;

class Reader{
    public:
    Reader(string FilePath);

    static void ReadFile(const string &FilePath);

    Log DedicatedLog;
    FileDatas CurrentFile;
    string Path;
    int CurrentLine;


    private:
};

#endif
