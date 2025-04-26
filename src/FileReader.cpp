#include <string>
#include <memory>
#include <fstream>

#include "FileReader.h"

#include "FileDatas.h"
#include "GlobalTools.h"
#include "ProjectMisc.h"


Reader::Reader(string FilePath){
    Path = FilePath;
    CurrentFile.InputFilePath = FilePath;
    FileName = GetFileName(FilePath);
    DedicatedLog.FileName = FileName;
    Log::WriteLine(FileName);

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

            cout << LineNo << "." << s.substr(1) << endl;//輸出格式2(沒#)
        }
    }
    InputFile.close();
    TotalLine = LineNo - 1;
    Log::Write("Close file:"+ FileName);
    cout <<" Total Line number: " << LineNo<< endl;
}

string Reader::GetFileName(const string &FilePath){
    vector<string> SaperatedFilePath = TrimText(FilePath, "/\\");
    string FileName = SaperatedFilePath[SaperatedFilePath.size() - 1];
    return FileName;
}

void Reader::ReadFile(const string &FilePath){
    Log::WriteLine(FilePath);
    shared_ptr<Reader> R = make_shared<Reader>(FilePath);
    cout << "new reader for file: " << R->FileName <<" ptr: " << R.get() << endl;
    AddReader(R);
}
