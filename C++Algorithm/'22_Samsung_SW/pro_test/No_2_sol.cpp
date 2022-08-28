#include <iostream>
#include <set>
#include <algorithm>
#include <functional>

#define Y_MAX 1000000000

using namespace std;

set<int> x_up[101];
set<int> x_down[101];

void init()
{
    for(int i = 0; i < 101; i++)
    {
        x_up[i].clear();
        x_down[i].clear();
    }
}

void add(int mX, int mY)
{
    x_up[mX].insert(mY);
    x_down[mX + 1].insert(mY);
}

void remove(int mX, int mY)
{
    x_up[mX].erase(mY);
    x_down[mX + 1].erase(mY);
}

int numberOfCross(int mID)
{
    int x = mID, y = 0;
    int ans = 0;

    while(true)
    {
        int y1 = 0, y2 = 0; 
        if(x_up[x].upper_bound(y) != x_up[x].end())
        {
            y1 = *x_up[x].upper_bound(y);
        }

        if(x_down[x].upper_bound(y) != x_down[x].end())
        {
            y2 = *x_down[x].upper_bound(y);
        }

        if(!y1 && !y2) 
        {
            break;
        }
        else if(y1 && y2)
        {
            if(y1 < y2)
            {
                y = y1;
                x = x + 1;
            }
            else
            {
                y = y2;
                x = x - 1;
            }
            ans += 1;
        }
        else if(y1)
        {
            y = y1;
            x = x + 1;
            ans += 1;
        }
        else
        {
            y = y2;
            x = x - 1;
            ans += 1;
        }
    }

    
	return ans;
}

int participant(int mX, int mY)
{
    int x = mX, y = mY;

    while(true)
    {
        int y1 = 0, y2 = 0;
        auto it1 = x_up[x].lower_bound(y);
        if((it1 != x_up[x].end() && it1 != x_up[x].begin()) || 
            (it1 == x_up[x].end() && x_up[x].size() >= 1)) // 찾았고 이전원소 있음 || 못찾았지만 이전원소 있음
        {
            y1 = *(--it1);
        }

        auto it2 = x_down[x].lower_bound(y);
        if(it2 != x_down[x].end() && it2 != x_down[x].begin() || 
            (it2 == x_down[x].end() && x_down[x].size() >= 1))
        {
            //cout << "dd" << endl;
            y2 = *(--it2);
        }

        if(!y1 && !y2) 
        {
            break;
        }
        else if(y1 && y2)
        {
            if(y1 > y2)
            {
                y = y1;
                x = x + 1;
            }
            else
            {
                y = y2;
                x = x - 1;
            }
        }
        else if(y1)
        {
            y = y1;
            x = x + 1;
        }
        else
        {
            y = y2;
            x = x - 1;
        } 
    }

    //cout << x << endl;
	return x;
}