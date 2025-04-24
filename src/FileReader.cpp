#include "FileReader.h"
#include "FileDatas.h"
#include <string>

Reader::Reader(string FilePath){
    Path = FilePath;
    CurrentFile.InputFilePath = FilePath;

}
