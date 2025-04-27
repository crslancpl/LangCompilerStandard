#ifndef TAGS_H_
#define TAGS_H_
#pragma once

#include <string>

#include "GlobalTools.h"

using namespace std;

class TagProcessor{
    public:
    Log *ParentLogger;
    void IdentifyTag(const string &TagContent, int Line);
};


#endif
