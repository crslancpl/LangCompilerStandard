#include <string>
#include <memory>

#include "FileReader.h"
#include "FileDatas.h"
#include "GlobalTools.h"


Reader::Reader(string FilePath){
    Path = FilePath;
    CurrentFile.InputFilePath = FilePath;
    string FileName = GetFileName(FilePath);
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
    unique_ptr<Reader> R = make_unique<Reader>(FilePath);

}
