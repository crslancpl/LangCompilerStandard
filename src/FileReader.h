/*
* This will first read all the tag, then read the input file character by character
*/

#ifndef FILEREADER_H_
#define FILEREADER_H_

#include <fstream>
#pragma once

#include <memory>
#include <iostream>
#include <string>

#include "GlobalTools.h"
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

    /* File Data*/
    FileDatas Datas;

    private:
    ifstream InputFile;

    int TotalLine; //this will be known when searching for tag

    void InitializeReader(const string &FilePath);

    void GetFileNameAndDir(const string &FilePath);

    void FindTag();

    bool IdentifyTag(const string &TagContent);

    void Read(); //read the file character by character

    void ProcessText(char NextChar);

};

#endif
