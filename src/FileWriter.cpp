#include <string>
#include <iostream>
#include <fstream>

#include "FileWriter.h"

using namespace std;

void WriteToFile(string s,const string &OutputLocation){
   s = "12 3\n#123345\nqwdq\n#j asfd\n@";//@:停止字元
   ofstream fout(OutputLocation);//檔案位置
   fout << s;
   fout.close();
}//寫入資料
