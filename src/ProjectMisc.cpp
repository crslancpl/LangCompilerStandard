#include <algorithm>
#include <memory>

#include "ProjectMisc.h"

#include "FileReader.h"
#include "FileDatas.h"
#include "GlobalTools.h"


vector<string> AssociateFiles;

string InputFileDirectory = "";
string EntryFile = "";
string EntryFunction = "";

void SetInputFileDir(const string &Dir){
    InputFileDirectory = Dir;
    Log::WriteLine("Project Directory: " + InputFileDirectory);
}
string GetInputFileDir(){
    return InputFileDirectory;
}
void SetEntryFile(const string& FilePath){
    EntryFile = FilePath;
}
string GetEntryFile(){
    return EntryFile;
}
void SetEntryFunc(const string &FuncName){
    EntryFunction = FuncName;
}
string GetEntryFuncName(){
    return EntryFunction;
}


void AddReader(shared_ptr<Reader> &reader){
    Readers.push_back(reader);

}

void PrintReaders(){
    Log::WriteLine("All Readers: ");
    cout << "count: " << Readers.size() << endl;
    for(shared_ptr<Reader> r: Readers){
        cout<< r->Datas.FileName <<" ptr: "<< r.get() << endl;
    }
}
