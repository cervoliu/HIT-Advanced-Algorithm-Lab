#include "testlib.h"
using namespace std;
bool ok[10000000];
string getOutName(string s, int partition)
{
    int len = s.length();
    for (int i=len-1; i>=0; --i) 
        if (s[i] == '.')
        {
            s = s.substr(0, i);
            break;
        }
    s += "_" + to_string(partition) + ".txt";
    return s;
}
int main()
{
    ifstream infile;
    string filename = "data/kosarak.txt";
    infile.open(filename);
    int n = 0, x, y;
    while(!infile.eof())
    {
        infile >> x >> y;
        n = max(n, x);
    }
    infile.close();

    infile.open(filename);
    string outname = filename + "_"
    while(!infile.eof())
    {

    }
    return 0;
}