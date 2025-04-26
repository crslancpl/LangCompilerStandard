#ifndef GLOBALTOOLS_H_
#define GLOBALTOOLS_H_
#pragma once

#include <string>
#include <vector>

using namespace std;

vector<string> TrimText(const string &Text, const vector<char> &Saperator);

bool Contains(vector<string> &list, const string &item);

class Log{
    public:
    string FileName;

    static void Write(const string &Message);
    static void WriteLine(const string &Message);

    bool HideError = false;
    void Err(const string &Message, const string &Details, unsigned int Line);
    bool HideWarning = false;
    void Warn(const string &Message, const string &Details, unsigned int Line);
    bool HideSuggest = false;
    void Suggest(const string &Message, const string &Details, unsigned int Line);
    bool HideInfo = false;
    void Info(const string &Message, const string &Details, unsigned int Line);
};

#endif
