#include <cstdlib>
#include <string>
#include <memory>
#include <fstream>
#include <utility>

#include "FileReader.h"

#include "FileDatas.h"
#include "GlobalTools.h"
#include "ProjectMisc.h"
#include "TextProcessor.h"


void Reader::ReadFile(const string &FilePath){
    if(CheckIfFileProcessedBefore(FilePath)){

    }
    shared_ptr<Reader> R = make_shared<Reader>(FilePath);

    pair<string, bool> F;//<file name, is file exist>, this will be given to ProjectMisc.cpp
    F.first = FilePath;
    F.second = R->IsFileExist;
    cout << R->IsFileExist << endl;
    if(R->IsFileExist){
        AddReader(R);
    }else{
        Log::WriteLine(FilePath + " is not existing");
    }

    //AddProcessedFile(&F);
}

Reader::Reader(string FilePath){
    InputFile.open(FilePath);
    Log::WriteLine("Openning " + FilePath);

    if(InputFile.is_open()){
        Log::WriteLine("File openned");
        InitializeReader(FilePath);
    }else{
        Log::WriteLine("Cannot open file" + Datas.Path);
        IsFileExist = false;
    }
}

void Reader::InitializeReader(const string &FilePath){
    Datas.Path = FilePath;
    Datas.InputFilePath = FilePath;
    GetFileNameAndDir(FilePath);
    Logger.ParentFileDatas = &Datas;

    Log::WriteLine("FileName: "+Datas.FileName);
    //Find the tag in the file first
    FindTag(); //Current progress
    //And then trim the whole file to symbols (skip Tags and comments)

}

void Reader::GetFileNameAndDir(const string &FilePath){
    vector<string> SaperatedFilePath = TrimText(FilePath, "/\\");
    Datas.FileName = SaperatedFilePath[SaperatedFilePath.size() - 1];
    if(GetInputFileDir().empty()){
        string Directory;
        for(string s: SaperatedFilePath){
            if(s != Datas.FileName){
                Directory = Directory + s + '/';
            }
        }
        if(!Directory.empty()){
            SetInputFileDir(Directory);
        }
    }
}

void Reader::FindTag(){
    string s;
    Datas.CurrentLine = 0; //This is only for finding Preprocessor

    bool IsNotEnd = true;
    while(true) {
        Datas.CurrentLine ++;
        getline(InputFile, s);
        if(s.empty()) break;
        if(s[0] == '#') {
            //cout << cnt << "." << s << endl;//輸出格式1(有#)
            string TagContent = s.substr(1);
            cout << Datas.FileName <<" "<<Datas.CurrentLine << "." << TagContent << endl;//輸出格式2(沒#)
            bool IsValidTag = IdentifyTag(TagContent);
            if(IsValidTag){
                Datas.TagLines.push_back(Datas.CurrentLine);
            }
        }
    }

    TotalLine = Datas.CurrentLine - 1;
}

bool Reader::IdentifyTag(const string &TagContent){
    //Return false if error encountered
    vector<string> Contents = TrimText(TagContent, " ");
    if(Contents.size() == 0){
        return false;
    }else if(Contents[0] == "Use"){
        // #use filename
        if(Contents.size() == 2){
            Reader::ReadFile(GetInputFileDir() + Contents[1]);
        }else{
            Logger.Err("No file name to include", "");
            return false;
        }
    }else if (Contents[0] == "NoCompile") {
        // copy and paste to the output file
    }else if (Contents[0] == "Lang"){
        // state that this file is only for certain language(api incompatible)
    }else if(Contents[0] == "Entry"){
        // specify the entry function of the program

        if(Datas.Path == GetEntryFile()){

            if(GetEntryFuncName().empty() && Contents.size() == 2){
                Log::WriteLine("Set entry function "+ Contents[1]);
                SetEntryFunc(Contents[1]);
            }else{
                Logger.Err("Entry function has already been set or there is no function after entry tag", "");
                return false;
            }

        }else{
            Logger.Err("Entry function have to be inside the entry file", "");
            return false;
        }

    }else if(Contents[0] == "SharedLib"){
        // output to .so or dll
    }

    return true;
}


void Reader::Read(){
    Datas.CurrentLine = 0;
    static string Symbol;

    char c;
    while(InputFile.get(c)){
        // The processor have to preload one char ahead so it can
        // determine is the next character associate with the current string
        ProcessText(c);
    }

    InputFile.close();
}

void Reader::ProcessText(char NextChar){
    static string CurrentText;
}
