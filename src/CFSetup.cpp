#include "CFSetup.h"

#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <thread>
#include <mutex>

#include "FileReader.h"
#include "ProjectMisc.h"
#include "GlobalTools.h"

using namespace std;

vector<string> ProjectSetup::CFTokenTables;
vector<string> ProjectSetup::CustTokenTable;

void ProjectSetup::ReadProject(const string &Path){
    GetDir(Path);
    cout << "Reading project"<<endl;
    ProjectProp p;
    fstream f;

    f.open(Path);
    if(f.fail()){
        cout << "Failed to read project"<<endl;
    }
    string s;
    bool IsComment = false;
    TableReader r;
    while(getline(f,s)){
        RmSurroundingInvisibleChar(s);

        if(s.empty()){
            continue;
        }

        if(s == "/Comment"){
            IsComment = !IsComment;
            continue;
        }
        if(IsComment){
            continue;
        }

        if(s == "#CFTokenTable"){
            p = CFTOKENTABLE;
            continue;
        }else if(s == "#CustomTokenTable"){
            p = CUSTOMTOKENTABLE;
            continue;
        }else if(s == "#EntryFile"){
            p = ENTRY;
            continue;
        }

        switch (p) {
            case CFTOKENTABLE:
                CFTokenTables.push_back(s);
                break;
            case CUSTOMTOKENTABLE:
                CustTokenTable.push_back(s);
                break;
            case ENTRY:
                SetEntryFile(GetInputFileDir() + s);
                break;
            default:
                break;
        }
    }

    LoadTables();

}

mutex ThreadLock;

void ProjectSetup::LoadTables(){
    vector<thread> threads;
    for(string Path : CFTokenTables){
        thread NewThread(TableReader::ReadCFTokenTable, Path);
        threads.push_back(move(NewThread));
    }

    for(thread &t : threads){
        t.join();
    }

    ThreadLock.unlock();
    threads.clear();
    for(string Path : CustTokenTable){
        thread NewThread(TableReader::ReadCustTokenTable, Path);
        threads.push_back(move(NewThread));
        /*
         * it is now written in concurrency since we don't know how
         * much CustomTokenTables will be used in the future
         */
    }

    for(thread &t : threads){
        t.join();
    }

}

void ProjectSetup::GetDir(const string &FilePath){
    /*
     * The directory for the project setup file is not the same with
     * the directory of code
     */
    vector<string> SaperatedFilePath = TrimText(FilePath, "/\\");
    string FileName = SaperatedFilePath[SaperatedFilePath.size() - 1];
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




void TableReader::ReadCFTokenTable(const string &FilePath){
    fstream file;
    file.open(GetInputFileDir() + FilePath);
    if(file.fail()){
        cout << "\nFailed to open file \"" << FilePath <<"\"\n";
        return;
    }else{
        cout << "\nReading "<< FilePath << "\n";
    }
    bool IsComment = false;
    string Line;
    vector<string> LineContent;
    while (getline(file,Line)){

        if(Line == "/Comment"){
            IsComment = !IsComment;
            continue;
        }
        if(IsComment){
            continue;
        }
        LineContent =TrimText(Line," \t");
        if(LineContent.size() == 3){
            if(LineContent[1] == "="){
                ThreadLock.lock();
                AddCFCode(LineContent[0], stoi(LineContent[2]));
                ThreadLock.unlock();
            }
        }
    }
}

void TableReader::ReadCustTokenTable(const string &FilePath){
    fstream file;
    file.open(GetInputFileDir() + FilePath);
    if(file.fail()){
        cout << "\nFailed to open file \"" << FilePath <<"\"\n";
        return;
    }else{
        cout << "\nReading "<< FilePath << "\n";
    }

    bool IsComment = false;
    string Line;
    vector<string> LineContent;
    while (getline(file,Line)){
        if(Line == "/Comment"){
            IsComment = !IsComment;
            continue;
        }
        if(IsComment){
            continue;
        }

        LineContent =TrimText(Line," \t");
        if(LineContent.size() == 3){
            if(LineContent[1] == ":"){
                ThreadLock.lock();
                AddCustKeyword(LineContent[0], LineContent[2]);
                ThreadLock.unlock();
            }
        }

    }
}
