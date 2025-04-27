#include <algorithm>
#include <memory>

#include "ProjectMisc.h"

#include "FileReader.h"
#include "FileDatas.h"
#include "GlobalTools.h"

vector< shared_ptr<Reader> > Readers;
vector<string> AssociateFiles;

string InputFileDirectory;
string Entry;

void SetInputFileDir(const string &Dir){
    InputFileDirectory = Dir;
    Log::WriteLine("Project Directory: " + InputFileDirectory);
}
string GetInputFileDir(){
    return InputFileDirectory;
};

void AddReader(shared_ptr<Reader> &reader){
    cout << "add reader "<< endl;

    Readers.push_back(reader);

    Log::Write("(Path: ");
    Log::WriteLine( reader->Path);

}
