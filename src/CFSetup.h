#ifndef CFSETUP_H_
#define CFSETUP_H_
#pragma once

#include <string>
#include <vector>
#include <map>

using namespace std;

enum ProjectProp{
    CFTOKENTABLE,CUSTOMTOKENTABLE,ENTRY,NONE
};

class ProjectSetup{
    public:
    static void ReadProject(const string &Path);

    static vector<string> CFTokenTables;// For compiler, mapping string to int
    static vector<string> CustTokenTable;// For code, mapping string to user defined string

    static void LoadTables();
    static void GetDir(const string &FilePath);
};

class TableReader{
    public:
    static void ReadCFTokenTable(const string &FilePath);
    static void ReadCustTokenTable(const string &FilePath);
};

#endif
