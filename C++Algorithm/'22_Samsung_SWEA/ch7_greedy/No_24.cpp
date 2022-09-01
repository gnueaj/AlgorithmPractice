#include<algorithm>
#include<string>
#include<iostream>

using namespace std;

int ans, n;
string s;
bool visited[1000000][11];

void greedy(int cnt, int cur)
{
    if(visited[stoi(s)][cnt]) return;

    visited[stoi(s)][cnt] = true;

    if(cnt == n)
    {
        ans = max(ans, stoi(s));
        return;
    }

    for(int i = cur; i < s.size(); i++)
    {
        for(int j = i + 1; j < s.size(); j++)
        {
            
                swap(s[i], s[j]);
                greedy(cnt + 1, i);
                swap(s[i], s[j]);
            
        }
    }
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
        cin >> s >> n;
        greedy(0,0);
        cout << '#' << test_case << ' ' << ans << endl;
        ans = 0;
        memset(visited, false, sizeof(bool)*1000000*11);
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}