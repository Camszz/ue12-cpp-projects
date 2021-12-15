#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
    vector<string> elements;
    {
        int i;
        for (i=1; i<argc; i=i+1)
            elements.push_back(argv[i]);
    }
    cout << elements[0];
}