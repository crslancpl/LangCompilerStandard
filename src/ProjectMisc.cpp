#include <algorithm>
#include <memory>

#include "FileReader.h"
#include "ProjectMisc.h"
#include "FileDatas.h"
#include "GlobalTools.h"

vector< shared_ptr<Reader> > Readers;

void AddReader(shared_ptr<Reader> &reader){
    cout << "add reader "<< endl;

    Readers.push_back(reader);

    Log::Write("(Path: ");
    Log::WriteLine( reader->Path);

}
