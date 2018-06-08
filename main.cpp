#include <iostream>
#include <fstream>
#include "token.h"

using namespace std;

int main()
{
    ifstream fin("code.txt");
    std::istreambuf_iterator<char> beg(fin), end;
    string src(beg, end);
    src+='\0';
    microsyntax srca(src);
    cout<<src<<endl;
    if(srca.Analysis())
    {
        srca.PrintAns();
    }
    else
    {
        cout<<"Error, failed\n";
    }
    return 0;
}
