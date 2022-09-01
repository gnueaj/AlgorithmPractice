#include<iostream>
#include<utility>
#include <algorithm>


using namespace std;

bool cmp(pair<int, int>& a, pair<int, int> b)
{
    return a.first < b.first;
}   


int greedy(int N)
{
    //pair<int, int> hall[401];
    pair<int, int> room[401];
    bool visited[401][401] = {false, };

    for(int i = 1; i <= N; i++)
    {
        int start, end;
        cin >> start >> end;
        if(start > end) swap(start, end);
        room[i] = {start, end};
        //hall[i] = {(start + 1) / 2, (end + 1) / 2};
    }
    sort(room + 1, room + N + 1, cmp);
    //sort(hall + 1, hall + N + 1, cmp);
    
    int ans = 0;
    int nodes = 0;
    for(int i = 1; i <= N; i++)
    {
        if(!visited[room[i].first][room[i].second])
            visited[room[i].first][room[i].second] = true;
        else 
            continue;

        int cmp = room[i].second;
        for(int j = i + 1; j <= N; j++)
        {
            if(cmp % 2) cmp += 1;
            if(!visited[room[j].first][room[j].second] &&
                room[j].first > cmp)
            {
                visited[room[j].first][room[j].second] = true;
                cmp = room[j].second;
            }    
        }
        ans += 1;
    }
    return ans;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	//freopen("input.txt", "r", stdin);
	cin>>T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for(test_case = 1; test_case <= T; ++test_case)
	{
        int N;
        cin >> N;
        int ans = greedy(N);
        cout << '#' << test_case << ' ' << ans << endl;

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}