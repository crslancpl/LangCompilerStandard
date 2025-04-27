#include <string>
#include <memory>
#include <fstream>

#include "FileReader.h"

#include "FileDatas.h"
#include "GlobalTools.h"
#include "ProjectMisc.h"
#include "Tags.h"


Reader::Reader(string FilePath){
    Path = FilePath;
    CurrentFile.InputFilePath = FilePath;
    GetFileNameAndDir(FilePath);
    DedicatedLog.FileName = FileName;
    p.ParentLogger = &DedicatedLog;
    Log::WriteLine("FileName: "+FileName);
    FindTag(); //Current progress
}

void Reader::FindTag(){
    string s;
    int LineNo = 0; //This is only for finding Preprocessor
    ifstream InputFile(Path);
    bool IsNotEnd = true;
    while(true) {
        LineNo ++;
        getline(InputFile, s);
        if(s.empty()) break;
        if(s[0] == '#') {
            //cout << cnt << "." << s << endl;//輸出格式1(有#)
            string TagContent = s.substr(1);
            cout << FileName <<" "<<LineNo << "." << TagContent << endl;//輸出格式2(沒#)
            bool IsValidTag = p.IdentifyTag(TagContent, LineNo);
            if(IsValidTag){
                TagLines.push_back(LineNo);
            }
        }
    }
    InputFile.close();
    TotalLine = LineNo - 1;
}

void Reader::GetFileNameAndDir(const string &FilePath){
    vector<string> SaperatedFilePath = TrimText(FilePath, "/\\");
    FileName = SaperatedFilePath[SaperatedFilePath.size() - 1];
    if(GetInputFileDir().empty()){
        string Directory;
        for(string s: SaperatedFilePath){
            if(s != FileName){
                Directory = Directory + s + '/';
            }
        }
        if(!Directory.empty()){
            SetInputFileDir(Directory);
        }
    }
}

void Reader::ReadFile(const string &FilePath){
    shared_ptr<Reader> R = make_shared<Reader>(FilePath);
    AddReader(R);
}
