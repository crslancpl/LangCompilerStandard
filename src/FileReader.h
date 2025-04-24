/*
* This will read the input file character by character
*/

#ifndef FILEREADER_H_
#define FILEREADER_H_
#pragma once

#include <iostream>
#include <string>

#include "FileDatas.h"

using namespace std;

class Reader{
    Reader(string FilePath);
    public:
    FileDatas CurrentFile;
    string Path;
    int CurrentLine;


    private:
};

#endif
