#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
    vector<string> elements;
    float num; float num1; float num2;

    {
        int i;
        for (i = 1; i < argc; i = i + 1)
            elements.push_back(argv[i]);
    }
    int i;
    i = 0;
    while (elements.size() > 1)
    {
        if (elements[i] == "x")
            {
                num1 = stof(elements[i - 2]) ; num2 = stof(elements[i - 1]);
                num = num1 * num2;
                elements[i] = to_string(num);
                elements.erase(elements.begin() + i - 2, elements.begin() + i);
                i = i - 2;
            }
        else if (elements[i] == "/")
            {
                num1 = stof(elements[i - 2]) ; num2 = stof(elements[i - 1]);
                num = num1 / num2;
                elements[i] = to_string(num);
                elements.erase(elements.begin() + i - 2, elements.begin() + i);
                i=i-2;
            }
        else if (elements[i] == "-")
            {
                num1 = stof(elements[i - 2]) ; num2 = stof(elements[i - 1]);
                num = num1 - num2;
                elements[i] = to_string(num);
                elements.erase(elements.begin() + i - 2, elements.begin() + i);
                i=i-2;
            }
        else if (elements[i] == "+")
            {
                num1 = stof(elements[i - 2]) ; num2 = stof(elements[i - 1]);
                num = num1 + num2;
                elements[i] = to_string(num);
                elements.erase(elements.begin() + i - 2, elements.begin() + i);
                i = i-2;
            }
        else
            {
                i = i+1;
            }
    }
    if (elements.size() == 1)
        {
        cout << elements[0];
        }
    else
        {
            cout << "Error";
        }
    return 0;
}