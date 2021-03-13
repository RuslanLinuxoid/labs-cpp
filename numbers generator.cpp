#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ofstream out;
    out.open("data.txt");
    for (int i = 0; i < 1000000; ++i) out << rand() << endl;
    return 0;
}
