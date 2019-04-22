#include<fstream>
#include<string>
using namespace std;
void ignoreLineIfstream(ifstream& fs, int lineCount)
{
	string s;
	for (int i = 0; i < lineCount; i++)
	{
		std::getline(fs, s);
	}
}
