#include <fstream>
#include <string>
#include <iostream>
#include <cpr/cpr.h>
#include <Windows.h>
using namespace std;

int main(int argc,char* argv[]) {

	if (argc < 3)
	{
		cout << "Error! Usage: WebFuzzer.exe {host} {wordlist}";
		return -1;
	}

	fstream wordlist;

	wordlist.open(argv[2], ios::in);
	
	if (!wordlist.is_open())
	{
		cout << "Error! File not found!";
		return -1;
	}
	else
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		string content;
		while (getline(wordlist,content))
		{
			SetConsoleTextAttribute(hConsole, 15);
			string host = argv[1] + content;

			cpr::Response response = cpr::Get(cpr::Url{ host });
			if (response.status_code == 200)
			{
				SetConsoleTextAttribute(hConsole, 2);
				cout << "[" << response.status_code << "] " << response.url << endl;
				continue;
			}
			cout << "[" << response.status_code << "] " << response.url << endl;

		}
				
		wordlist.close();
	}

	return 0;
}