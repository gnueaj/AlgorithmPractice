#include<iostream>
#include<queue>
#include<algorithm>
#include <utility>

using namespace std;

char map[301][301];
bool visited[301][301];
int dist[301][301];

int N;
int ans;

int dx[] = {0, 0, -1, -1, -1, 1, 1, 1};
int dy[] = {-1, 1, 0, 1, -1, 0, 1, -1};

bool valid(int x, int y)
{
    return x >= 1 && x <= N && y >= 1 && y <= N;
}

void bfs(int x, int y)
{
    queue<pair<int, int>> q;
    q.push({x, y});
    visited[x][y] = true;

    while(!q.empty())
    {
        pair<int, int> from = q.front(); q.pop();
        for(int i = 0; i < 8; i++)
        {
            int tox = from.first + dx[i];
            int toy = from.second + dy[i];
            if(valid(tox, toy) && !visited[tox][toy])
            { 
                if(map[tox][toy] == '.')
                {
                    q.push({tox, toy});
                    visited[tox][toy] = true;
                }
                if(map[tox][toy] == '1')
                {
                    visited[tox][toy] = true;
                }
            }
        }
    }
}

int solve()
{
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            if(map[i][j] == '.')
            {
                for(int k = 0; k < 8; k++)
                {
                    int tox = i + dx[k];
                    int toy = j + dy[k];
                    if(valid(tox, toy) && map[tox][toy] == '*')
                    {
                        map[i][j] = '1';
                        break;
                    }
                }
            } 
        }
    }

    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            if(map[i][j] == '.' && !visited[i][j])
            {
                ans += 1;
                bfs(i, j);
            }
        }
    }
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            if(!visited[i][j] && map[i][j] == '1')
                ans += 1;
        }
    }
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	//freopen("input.txt", "r", stdin);
	cin>>T;
	
	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> N;
        for(int i = 1; i <= N; i++)
        {
            for(int j = 1; j <= N; j++)
            {
                cin >> map[i][j];
                if(map[i][j] == '*')
                {
                    visited[i][j] = true;
                }
            }
        }
        solve();
        cout << "#" << test_case << ' ' << ans << endl;
        ans = 0;
        for(int i = 0; i < 301; i++)
        {
            for(int j = 0; j < 301; j++)
            {
                dist[i][j] = 0;
                visited[i][j] = false;
                map[i][j] = 0;
            }
        }
	}

    
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}