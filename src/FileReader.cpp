#include <string>
#include <memory>

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
}

string Reader::GetFileName(const string &FilePath){
    vector<string> SaperatedFilePath = TrimText(FilePath, "/\\");
    string FileName = SaperatedFilePath[SaperatedFilePath.size() - 1];
    return FileName;
}

void Reader::ReadFile(const string &FilePath){
    Log::WriteLine(FilePath);
    shared_ptr<Reader> R = make_shared<Reader>(FilePath);
    cout << "new reader ptr" << R.get() << endl;
    AddReader(R);
}
