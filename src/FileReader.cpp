/*
*
*
*/

#include "FileReader.h"

#include <cstdlib>
#include <string>
#include <memory>
#include <fstream>
#include <utility>

#include "FileDatas.h"
#include "GlobalTools.h"
#include "ProjectMisc.h"
#include "TextProcessor.h"


string ValidCharForName = "abcdefghijklmnopqrstubwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_";


void Reader::ReadFile(const string &FilePath){
    if(CheckIfFileProcessedBefore(FilePath)){
        Log::WriteLine(FilePath + " has been processed before");
        return;
    }
    shared_ptr<Reader> R = make_shared<Reader>(FilePath);

    pair<string, bool> F;//<file name, is file exist>, this will be given to ProjectMisc.cpp
    F.first = FilePath;
    F.second = R->IsFileExist;

    if(R->IsFileExist){
        AddReader(R);
    }else{
        Log::WriteLine(FilePath + " does not exist");
    }
    AddProcessedFile(&F);
}

Reader::Reader(string FilePath){
    InputFile.open(FilePath);
    Log::WriteLine("Reading " + FilePath);

    if(InputFile.is_open()){
        InitializeReader(FilePath);
    }else{
        IsFileExist = false;
    }
}

bool Reader::IsTagLine(int line){
    for(int i: Datas.TagLines){
        if(i == line){
            return true;
        }
    }
    return false;
}

void Reader::InitializeReader(const string &FilePath){
    Datas.Path = FilePath;
    Datas.InputFilePath = FilePath;
    GetFileNameAndDir(FilePath);
    Logger.ParentFileDatas = &Datas;

    //Find the tag in the file first
    FindTag(); //Current progress
    //And then trim the whole file to symbols (skip Tags and comments)
    Read();
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

    while(getline(InputFile, s)) {
        Datas.CurrentLine ++;
        RemoveLeadingInvisibleChar(s);
        if(s[0] == '#') {
            //cout << cnt << "." << s << endl;//輸出格式1(有#)
            string TagContent = s.substr(1);
            //cout <<"Preprocessor: "<<Datas.FileName <<" "<<Datas.CurrentLine << "." << TagContent << endl;//輸出格式2(沒#)
            bool IsValidTag = IdentifyTag(TagContent);
            Datas.TagLines.push_back(Datas.CurrentLine);
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
    Datas.CurrentLine = 1;
    static string Symbol;
    cout << "starts reading " << Datas.FileName<< endl;
    char c;
    InputFile.clear();
    InputFile.seekg(0);
    while(InputFile.get(c)){
        // The processor have to preload one char ahead so it can
        // determine is the next character associate with the current string
        ProcessText(c);
    }
    cout << "close file"<<endl;
    InputFile.close();
}

enum class ProcessType: short{
    Text, NumberAndByte, Comment, Char, None
};

void Reader::ProcessText(char NewChar){
    static string CurrentText;
    static ProcessType p = ProcessType::None;
    static string Note;

    if(p == ProcessType::Comment){
        if(NewChar == '\n'){
            p = ProcessType::None;
        }
        return;
    }

    if(p == ProcessType::Text){
        CurrentText += NewChar;
        if(NewChar == '\\'){
            //escape character
            Note = "escape";
        }else if(NewChar == CurrentText[0]){
            if(Note == "escape"){
                Note.clear();
            }else{
                PushSymbol(CurrentText);
            }
        }else{
            Note.clear();
        }
        return;
    }

    if(p == ProcessType::Char){
        if(AcceptSucceedingSpecialChar(CurrentText, NewChar)){
            CurrentText += NewChar;
            return;
        }else{
            PushSymbol(CurrentText);
            p = ProcessType::None;
        }
    }

    if(NewChar == '\n'){
        //New line
        Datas.CurrentLine ++;
        PushSymbol(CurrentText);
    }else if(IsTagLine(Datas.CurrentLine)){
        return;
    }else if(NewChar == ' ' || NewChar == '\t'){
        //Blank
        PushSymbol(CurrentText);
    }else if(IsNumberChar(NewChar)){
        //Number
        CurrentText += NewChar;
    }else if(IsAlphabetChar(NewChar)){
        //Alphabet
        CurrentText += NewChar;
    }else{
        //Special char
        if(p != ProcessType::Char){
            PushSymbol(CurrentText);
            p = ProcessType::Char;
            CurrentText += NewChar;
        }
    }
}

void Reader::PushSymbol(string &Symbol){
    if(! Symbol.empty()){
        TypeCode c = GetCodeFromKeyword(Symbol);
        cout << (int)c << Symbol <<endl;
        Symbols.insert(Symbols.end(),{c, Symbol});
        Symbol.clear();
    }

}

bool Reader::AcceptSucceedingSpecialChar(const string &Text ,char C){
    return false;
}
