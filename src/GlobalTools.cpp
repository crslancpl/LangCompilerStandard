#include <vector>
#include <string>

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


void Log::Write(string Message){
    cout << Message;
}

void Log::WriteLine(string Message){
    cout << Message<< endl;
}

void Log::Err(string Message, string Details, unsigned int Line){
    if(HideError) return;
    cout << endl;
    cout << "error: " << FileName << " Line: " << Line << endl;
    cout << Message << endl;
    cout << Details << endl;
}

void Log::Warn(string Message, string Details, unsigned int Line){
    if(HideWarning) return;
    cout << endl;
    cout << "warning: " << FileName << " Line: " << Line << endl;
    cout << Message << endl;
    cout << Details << endl;
}

void Log::Suggest(string Message, string Details, unsigned int Line){
    if(HideSuggest) return;
    cout << endl;
    cout << "suggestion: " << FileName << " Line: " << Line << endl;
    cout << Message << endl;
    cout << Details << endl;
}

void Log::Info(string Message, string Details, unsigned int Line){
    if(HideInfo) return;
    cout << endl;
    cout << "info: " << FileName << " Line: " << Line << endl;
    cout << Message << endl;
    cout << Details << endl;
}
