#include <map>
#include <set>
#include <utility>
#include <iostream>

using namespace std;

set<pair<int, int>> emptySpaceSize;
set<pair<int, int>> emptySpaceIndex;

set<pair<int, int>> s;

int main()
{
    s.insert({15, 3});
    set<pair<int, int>>::iterator it = s.end();
    cout << (s.begin() == s.lower_bound({15,3})) << endl;
    
    
}