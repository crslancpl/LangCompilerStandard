#include "TableReader.h"

#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>
#include <fstream>

#include "ProjectMisc.h"
#include "GlobalTools.h"

using namespace std;

bool TableReader::LoadTables(vector<string> TablePaths){
    // return false if failed to read file

    return true;
}

void TableReader::Read(const string &FilePath){
    file.open(FilePath);
    if(file.fail()){
        cout << "\nFailed to open file \"" << FilePath <<"\n\"";
        return;
    }
    bool IsComment = false;
    string Line;
    vector<string> LineContent;
    while (getline(file,Line)){
        if(Line == "/Comment"){
            IsComment = !IsComment;
            return;
        }
        if(IsComment){
            return;
        }
        LineContent =TrimText(Line," \t");
        if(LineContent.size() == 3){
            if(LineContent[1] == "="){
                AddKeywordCode(LineContent[0], stoi(LineContent[2]));
            }
            if(LineContent[1] == ":"){
                AddKeyword(LineContent[0], LineContent[2]);
            }
        }
    }
}
