#include <iostream>
#include <vector>
#include<string>
#include<sstream>

using namespace std;

void split(const string &chaine, char delimiteur, vector<string> &elements)
{
 stringstream ss(chaine);
 string sousChaine;
 while (getline(ss, sousChaine, delimiteur))
 {
 elements.push_back(sousChaine);
 }
}