/*
* This will first read all the tag, then read the input file character by character
*/

#ifndef FILEREADER_H_
#define FILEREADER_H_
#pragma once

#include <fstream>
#include <vector>
#include <memory>
#include <iostream>
#include <string>

#include "GlobalTools.h"
#include "Enums.h"
#include "FileDatas.h"

using namespace std;

class Reader{
    public:
    /* static */
    static void ReadFile(const string &FilePath);
    //this will automatically create an instance of reader

    /* constructor */
    Reader(string FilePath);

    /* none-static */
    bool IsFileExist = true;
    Log Logger;
    //this will store current file name
    map<TypeCode,string> Symbols;
    /* File Data*/
    FileDatas Datas;

    private:
    ifstream InputFile;

    int TotalLine; //this will be known when searching for tag

    bool IsTagLine(int line);

    void InitializeReader(const string &FilePath);

    void GetFileNameAndDir(const string &FilePath);

    void FindTag();

    bool IdentifyTag(const string &TagContent);

    void Read(); //read the file character by character and pass it to ProcessText()

    void ProcessText(char NewChar);

    TypeCode PushSymbol(string &Symbol);

};

#endif
