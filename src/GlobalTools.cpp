#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#include "GlobalTools.h"

using namespace std;

vector<string> TrimText(const string &Text, const vector<char> &Saperator) {
	vector<string> v;
	string s;
	for (char c : Text) {
		bool IsSap = false;
		for (char Sape : Saperator) {
			if(Sape == c){
				IsSap = true;
			}
		}
		if(IsSap){
			if(!s.empty()){
				v.emplace(v.end(), s);
				s.clear();
			}
		}else{
			s += c;
		}
	}

	if(!s.empty()){
		v.emplace(v.end(), s);
		s.clear();
	}
	return v;
}

vector<string> TrimText(const string &Text, const string &Saperator) {
	vector<string> v;
	string s;
	for (char c : Text) {
		bool IsSap = false;
		for (char Sape : Saperator) {
			if(Sape == c){
				IsSap = true;
			}
		}
		if(IsSap){
			if(!s.empty()){
				v.emplace(v.end(), s);
				s.clear();
			}
		}else{
			s += c;
		}
	}

	if(!s.empty()){
		v.emplace(v.end(), s);
		s.clear();
	}
	return v;
}

bool IsNumberChar(char c){
    if(c >= 48 && c <= 57 ){
        return true;
    }
    return false;
}

bool IsAlphabetChar(char c){
    if(c >= 65 && c <= 90){
        return true;
    }

    if(c >= 97 && c <= 122){
        return true;
    }

    return false;
}

bool Contains(const vector<string> &list, const string &item) {
  if (find(list.begin(), list.end(), item) != list.end()) {
    return true;
  } else {
    return false;
  }
}

bool Contains(const string &list, char character){
    for(char c: list){
        if(c == character){
            return true;
        }
    }
    return false;
}

void RemoveLeadingInvisibleChar(string &Text){
    /*
    * This will remove whitespaces,tabs,and newline symbols before the Text.
    */
    int i = 0;
    for(char c: Text){
        if(c == ' ' || c == '\n' || c == '\t'){
            //invisible character
        }else{
            break;
        }
        i++;
    }

    Text = Text.substr(i);
}

// Class Log
// static
void Log::Write(const string &Message){
    cout << Message << " ";
}

void Log::WriteLine(const string &Message){
    cout << Message<< endl;
}
// none-static
void Log::Err(const string &Message, const string &Details){
    if(HideError) return;
    cout << endl;
    cout << "error: " << ParentFileDatas->FileName << " Line: " << ParentFileDatas->CurrentLine << endl;
    cout << Message << endl;
    if(Details.empty()) {
        cout << endl;
        return;
    }
    cout << Details << endl << endl;
}

void Log::Warn(const string &Message, const string &Details){
    if(HideWarning) return;
    cout << endl;
    cout << "warning: " << ParentFileDatas->FileName << " Line: " << ParentFileDatas->CurrentLine << endl;
    cout << Message << endl;
    if(Details.empty()) {
        cout << endl;
        return;
    }
    cout << Details << endl << endl;
}

void Log::Suggest(const string &Message, const string &Details){
    if(HideSuggest) return;
    cout << endl;
    cout << "suggestion: " << ParentFileDatas->FileName << " Line: " <<ParentFileDatas ->CurrentLine << endl;
    cout << Message << endl;
    if(Details.empty()) {
        cout << endl;
        return;
    }
    cout << Details << endl <<endl;
}

void Log::Info(const string &Message, const string &Details){
    if(HideInfo) return;
    cout << endl;
    cout << "info: " << ParentFileDatas->FileName << " Line: " << ParentFileDatas ->CurrentLine << endl;
    cout << Message << endl;
    if(Details.empty()) {
        cout << endl;
        return;
    }
    cout << Details << endl <<endl;
}
