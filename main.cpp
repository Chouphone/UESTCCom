//#include "token.h"
#include "phaser.h"

#include<string>
#include<iostream>
#include<fstream>

using namespace std;

int main()
{
	string filename = "code.txt";
	ifstream fin(filename);
	std::istreambuf_iterator<char> beg(fin), end;
	string src(beg, end);
	src += '\0';
	microsyntax srca(src);

	//cout << src << endl;

	if (srca.Analysis())
	{
		srca.PrintAns();
	}
	else
	{
		cout << "Error, failed\n";
	}

	Phaser ph(srca.GetWords());
	if (ph.Analysis())
	{
		;
	}
	else
	{
		cout << "Error, failed\n";
	}
//	system("PAUSE");
	return 0;
}
