#ifndef TABLEREADER_H_
#define TABLEREADER_H_
#pragma once

#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

class TableReader{
    public:
    static map<string,unsigned int> Code;

    fstream file;

    bool LoadTables(vector<string> TablePaths);
    void Read(const string &FilePath);
};

#endif
