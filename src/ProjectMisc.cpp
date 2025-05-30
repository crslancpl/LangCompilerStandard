/*
*
*
*/

#include "ProjectMisc.h"

#include <algorithm>
#include <memory>
#include <map>
#include <string>
#include <utility>

#include "Enums.h"
#include "FileReader.h"
#include "FileDatas.h"
#include "GlobalTools.h"



map< string, TypeCode> KeywordsTypes;
map< string, TypeCode> Keywords;
void AddKeywordCode(const string &Keyword, unsigned short Code){
    pair<string, TypeCode> P;
    P.first = Keyword;
    P.second = static_cast<TypeCode>(Code);
    KeywordsTypes.insert(KeywordsTypes.end(), P);
}

void AddKeyword(const string &Type, const string &Keyword){
    // Type can be either name or code of the keyword
    pair<string, TypeCode> P;
    P.first = Keyword;
    if(IsNumberChar(Type[0])){
        // The mapping is mapped by code instead of the name of keyword
        P.second = static_cast<TypeCode>(stoi(Type));
    }else{
        map<string, TypeCode>::iterator i = KeywordsTypes.find(Type);
        if(i != KeywordsTypes.end()){
            P.second = i ->second;
        }else{
            return;
        }
    }
    Keywords.insert(Keywords.end(), P);
}

TypeCode GetCodeFromKeyword(const string &Keyword){
    map<string, TypeCode>::iterator i = Keywords.find(Keyword);
    if(i != Keywords.end()){
        //It is a keyword
        return i->second;
    }
    else return TypeCode::OTHERS;
}




vector< shared_ptr<Reader> > Readers;
map<string,bool> AssociateFiles;

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
