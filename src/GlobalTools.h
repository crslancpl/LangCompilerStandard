#ifndef GLOBALTOOLS_H_
#define GLOBALTOOLS_H_
#pragma once

#include <string>
#include <vector>

using namespace std;

vector<string> TrimText(const string &Text, const vector<char> &Saperator);

class Log{
    public:
    string FileName;

    static void Write(string Message);
    static void WriteLine(string Message);

    bool HideError = false;
    void Err(string Message, string Details, unsigned int Line);
    bool HideWarning = false;
    void Warn(string Message, string Details, unsigned int Line);
    bool HideSuggest = false;
    void Suggest(string Message, string Details, unsigned int Line);
    bool HideInfo = false;
    void Info(string Message, string Details, unsigned int Line);
};

#endif
