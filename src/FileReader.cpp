#include <string>
#include <memory>

#include "FileReader.h"
#include "FileDatas.h"


Reader::Reader(string FilePath){
    Path = FilePath;
    CurrentFile.InputFilePath = FilePath;

}

void Reader::ReadFile(const string &FilePath){
    unique_ptr<Reader>R = make_unique<Reader>(FilePath);
}
