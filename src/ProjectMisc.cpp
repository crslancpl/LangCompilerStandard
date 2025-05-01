#include <algorithm>
#include <memory>
#include <map>
#include <string>

#include "ProjectMisc.h"

#include "FileReader.h"
#include "FileDatas.h"
#include "GlobalTools.h"


map<string,bool> AssociateFiles;

vector< shared_ptr<Reader> > Readers;

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

void AddProcessedFile(pair<string,bool> *p){
    AssociateFiles.insert(AssociateFiles.end(),*p);
}

bool CheckIfFileProcessedBefore(const string &FileName){
    map<string, bool>::iterator iterator = AssociateFiles.find(FileName);
    if(iterator == AssociateFiles.end()){
        //not found in list
        return false;
    }else{
        return true;
    }
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
