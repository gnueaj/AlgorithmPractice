#include <iostream>
#include <utility>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>

using namespace std;


list<int> tsDB[6][6]; //[mTeam][mScore] = mID
list<int>::iterator it[100001];
int findTeam[100001];

void init()
{
    for(int i = 1; i <= 5; i++)
    {
        for(int j = 1; j <= 5; j++)
        {
            tsDB[i][j].clear();
        }
    }
}

void hire(int mID, int mTeam, int mScore)
{
    tsDB[mTeam][mScore].push_front(mID);
    it[mID] = tsDB[mTeam][mScore].begin();
    findTeam[mID] = mTeam;
}

void fire(int mID)
{
    tsDB[0][0].erase(it[mID]);
}

void updateSoldier(int mID, int mScore)
{
    tsDB[0][0].erase(it[mID]); //원래 점수 삭제
    tsDB[findTeam[mID]][mScore].push_front(mID); //새 점수 입력
    it[mID] = tsDB[findTeam[mID]][mScore].begin();
}

void updateTeam(int mTeam, int mChangeScore)
{
    list<int> tmp[6];
    for(int prevScore = 1; prevScore <= 5; prevScore++)
    {
        int nextScore;
        if(prevScore + mChangeScore > 5) nextScore = 5;
        else if(prevScore + mChangeScore < 1) nextScore = 1;
        else nextScore = prevScore + mChangeScore;

        tmp[nextScore].splice(tmp[nextScore].begin(), tsDB[mTeam][prevScore]);
    }

    for(int i = 1; i <= 5; i++)
    {
        tsDB[mTeam][i].splice(tsDB[mTeam][i].begin(), tmp[i]);
    }
}

int bestSoldier(int mTeam)
{
    int ans = 0;
    for(int i = 5; i >= 1; i--)
    {
        for(auto iter = tsDB[mTeam][i].begin(); iter != tsDB[mTeam][i].end(); iter++)
        {
            ans = max(ans, *iter);
        }
        if(ans) 
        {
            return ans;
        }
    }
}