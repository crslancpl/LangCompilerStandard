/*
* This is the entry of the compiler, where it will only do the
* job of reading every characters of the input file and pass it
* to the
*/
#include <fstream>
#include <iostream>
#include <memory>

#include "ProjectMisc.h"
#include "FileReader.h"
#include "GlobalTools.h"


using namespace std;

int main(){
    Log::WriteLine("Compiler started");
    Reader::ReadFile("/home/er/.mozilla/firefox/3a880qck.default-nightly-1/chrome/userChrome.css");


    return 0;
}
