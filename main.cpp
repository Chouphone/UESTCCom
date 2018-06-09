//#include "token.h"
#include "phaser.h"

#include<string>
#include<iostream>
#include<fstream>

using namespace std;

int main()
{
	string filename = "code";
	string fileco1 = ".txt";
	string fe1 = ".dyd",fe2 = ".var", fe3 = ".pro";
	ifstream fin(filename + fileco1);
	std::istreambuf_iterator<char> beg(fin), end;
	string src(beg, end);
	src += '\0';
	microsyntax srca(src);

	//cout << src << endl;
	cout<<"microsyntax begin\n";

	if (srca.Analysis())
	{
		cout<<"microsyntax succeccd!\n, Begin syntax analysis.\n";
		freopen((filename + fe1).c_str(), "w", stdout);
		srca.PrintAns();
		fclose(stdout);
		freopen("/dev/tty","w",stdout);
	}
	else
	{
		cout << "Error, failed\n";
	}

	Phaser ph(srca.GetWords());
	if (ph.Analysis())
	{
		cout<<"No syntax error, OK!\n";
		//make out put files;
		freopen((filename + fe2).c_str(), "w", stdout);
		ph.PrintVar();
		fclose(stdout);

		freopen((filename + fe3).c_str(), "w", stdout);
		ph.PrintProc();
		fclose(stdout);	
	}	
	else
	{
		cout << "Syntax Error, failed\n";
	}
//	system("PAUSE");
	return 0;
}
