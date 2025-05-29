/*
* This is the entry of the compiler, where it will only do the
* job of reading every characters of the input file and pass it
* to the
*/

#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "ProjectMisc.h"
#include "FileReader.h"
#include "GlobalTools.h"
#include "TableReader.h"


using namespace std;

int main(int argnumber,char** InputFilePath){
    Log::WriteLine(">> Compiler started");
    if(argnumber == 1){
        Log::WriteLine("No input file");
        return 0;
    }
    SetEntryFile(InputFilePath[1]);

    TableReader TR;
    TR.Read("TestingInputFiles/ProcessorTokenList.txt");

    Reader::ReadFile(InputFilePath[1]);
    Log::WriteLine(">> Compiler ended");

    cout <<endl;
    return 0;
}
