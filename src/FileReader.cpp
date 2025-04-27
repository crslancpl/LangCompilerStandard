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
    FindTag();
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
            cout << LineNo << "." << TagContent << endl;//輸出格式2(沒#)
            p.IdentifyTag(TagContent, LineNo);
        }
    }
    InputFile.close();
    TotalLine = LineNo - 1;
    Log::Write("Close file:"+ FileName);
    cout <<" Total Line number: " << LineNo<< endl;
}

void Reader::GetFileNameAndDir(const string &FilePath){
    vector<string> SaperatedFilePath = TrimText(FilePath, "/\\");
    FileName = SaperatedFilePath[SaperatedFilePath.size() - 1];
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

void Reader::ReadFile(const string &FilePath){
    Log::WriteLine(FilePath);
    shared_ptr<Reader> R = make_shared<Reader>(FilePath);
    cout << "new reader for file: " << R->FileName <<" ptr: " << R.get() << endl;
    AddReader(R);
}
