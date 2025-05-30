#ifndef GLOBALTOOLS_H_
#define GLOBALTOOLS_H_
#pragma once

#include <string>
#include <vector>

#include "FileDatas.h"

using namespace std;

vector<string> TrimText(const string &Text, const vector<char> &Saperator);
vector<string> TrimText(const string &Text, const string &Saperator);

bool IsNumberChar(char c);
bool IsAlphabetChar(char c);

bool Contains(const vector<string> &list, const string &item);
bool Contains(const string &list, char character);
void RemoveLeadingInvisibleChar(string &Text);

class Log{
    public:
    FileDatas *ParentFileDatas;

    static void Write(const string &Message);
    static void WriteLine(const string &Message);

    bool HideError = false;
    void Err(const string &Message, const string &Details);
    bool HideWarning = false;
    void Warn(const string &Message, const string &Details);
    bool HideSuggest = false;
    void Suggest(const string &Message, const string &Details);
    bool HideInfo = false;
    void Info(const string &Message, const string &Details);
};

#endif
