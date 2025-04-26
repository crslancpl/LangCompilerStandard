/*
* This will read the input file character by character
*/

#ifndef FILEREADER_H_
#define FILEREADER_H_

#pragma once

#include <memory>
#include <iostream>
#include <string>

#include "GlobalTools.h"
#include "FileDatas.h"

using namespace std;

class Reader{
    public:
    //static

    //this will automatically create an instance of reader
    static void ReadFile(const string &FilePath);

    /*none-static*/
    Reader(string FilePath);

    //this will store current file name
    Log DedicatedLog;
    FileDatas CurrentFile;
    string Path;
    string FileName;
    int CurrentLine;

    private:
    string GetFileName(const string &FilePath);
};

#endif
