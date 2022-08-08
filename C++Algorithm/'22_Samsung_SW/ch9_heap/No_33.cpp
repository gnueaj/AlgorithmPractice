#include<algorithm>
#include<string>
#include<iostream>
#include<queue>
#include<cstring>
#include<utility>

using namespace std;

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

int map[101][101];
int dist[101][101];
int N;

bool valid(int x, int y)
{
    return x >= 1 && x <= N && y >= 1 && y <= N;
}

int bfs()
{
    queue<pair<int, int>> q;
    q.push({1, 1});
    dist[1][1] = 0;

    while(!q.empty())
    {
        pair<int, int> from = q.front(); q.pop();
        for(int i = 0; i < 4; i++)
        {
            int tox = from.first + dx[i];
            int toy = from.second + dy[i];
            if(valid(tox, toy) && 
                dist[from.first][from.second] + map[tox][toy] < dist[tox][toy])
                {
                    q.push({tox, toy});
                    dist[tox][toy] = dist[from.first][from.second] + map[tox][toy];
                }
        }
    }

    return dist[N][N];
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	//freopen("input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
        memset(map, 0, sizeof(int) * 101 * 101);
        for(int i = 0; i <= 100; i++)
        {
            for(int j = 0; j <= 100; j++)
                dist[i][j] = 99999;
        }

    
        cin >> N;
        for(int i = 1; i <= N; i++)
            for(int j = 1; j <= N; j++)
                scanf("%1d", &map[i][j]);
        
        cout << '#' << test_case << ' ' << bfs() << endl;
        
	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}