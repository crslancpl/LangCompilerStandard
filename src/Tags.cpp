
#include <string>
#include <vector>

#include "Tags.h"

#include "GlobalTools.h"
#include "ProjectMisc.h"
#include "FileReader.h"

using namespace std;


void TagProcessor::IdentifyTag(const string &TagContent, int Line){
    vector<string> Contents = TrimText(TagContent, " ");

    if(Contents[0] == "use"){
        if(Contents.size() == 2){
            Reader::ReadFile(GetInputFileDir() + Contents[1]);
        }else{
            ParentLogger->Err("No file name to include", "", Line);
        }
    }
}
