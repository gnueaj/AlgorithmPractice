#include <iostream>
#include <utility>
#include <cstring>
#include <map>
#include <set>
#include <cstdlib>
#include <ctime>
#include <list>

using namespace std;


int main()
{
    list<int> lst[6][6];
    list<int>::iterator it[100001];
    lst[4][5].push_front(999);
    lst[4][5].push_front(888);
    it[888] = lst[4][5].begin();
    lst[4][5].push_front(777);
    it[777] = lst[4][5].begin();
    for(auto it = lst[4][5].begin(); it !=lst[4][5].end(); it++)
        cout << *it << ' ';
    lst[0][0].erase(it[888]);
    for(auto it = lst[4][5].begin(); it !=lst[4][5].end(); it++)
        cout << *it << ' ';
    lst[2][3].erase(it[777]);
     for(auto it = lst[4][5].begin(); it !=lst[4][5].end(); it++)
        cout << *it << ' ';
}