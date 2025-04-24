#ifndef FILEDATAS_H_
#define FILEDATAS_H_

#pragma once

#include <string>
#include <vector>
#include <map>


using namespace std;


class FileDatas{
    public:
    string InputFilePath;
    vector<string> AssociatedFiles;
    map<string, string> Variables; //<variable name, variable type>
};

#endif
