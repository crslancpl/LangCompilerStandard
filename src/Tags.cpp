
#include <string>
#include <vector>

#include "Tags.h"

#include "GlobalTools.h"
#include "ProjectMisc.h"
#include "FileReader.h"

using namespace std;


bool TagProcessor::IdentifyTag(const string &TagContent, int Line){
    //Return false if error encountered
    vector<string> Contents = TrimText(TagContent, " ");
    if(Contents.size() == 0){
        return false;
    }else if(Contents[0] == "Use"){
        // #use filename
        if(Contents.size() == 2){
            Reader::ReadFile(GetInputFileDir() + Contents[1]);
        }else{
            ParentLogger->Err("No file name to include", "", Line);
            return false;
        }
    }else if (Contents[0] == "NoCompile") {
        // copy and paste to the output file
    }else if (Contents[0] == "Lang"){
        // state that this file is only for certain language(api incompatible)
    }

    return true;
}
