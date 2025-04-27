/*
* This will first read all the tag, then read the input file character by character
*/

#ifndef FILEREADER_H_
#define FILEREADER_H_

#pragma once

#include <memory>
#include <iostream>
#include <string>

#include "GlobalTools.h"
#include "FileDatas.h"
#include "Tags.h"

using namespace std;

class Reader{
    public:
    /* static */

    static void ReadFile(const string &FilePath);
    //this will automatically create an instance of reader

    /* none-static */

    Reader(string FilePath);
    Log DedicatedLog;
    //this will store current file name
    FileDatas CurrentFile;
    string Path;
    string FileName;

    int CurrentLine;

    private:
    TagProcessor p;
    vector<int> TagLines;
    int TotalLine; //this will be known when searching for tag

    void GetFileNameAndDir(const string &FilePath);

    void FindTag();

};

#endif
