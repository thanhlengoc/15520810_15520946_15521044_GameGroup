#pragma once
#include<fstream>
using namespace std;
/* bỏ qua dòng chữ khi đọc file */
extern void ignoreLineIfstream(ifstream& fs, int lineCount);
