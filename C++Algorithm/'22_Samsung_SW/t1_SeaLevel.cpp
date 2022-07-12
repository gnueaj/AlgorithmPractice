#include <iostream>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;

int map[101][101];
bool visited[101][101];

int dx[] = {-1, 0, 0, 1};
int dy[] = {0, -1, 1, 0};
int N;

bool valid(int x, int y, int height)
{
    return x >= 1 && x <= N && y >= 1 && y <= N && 
            map[x][y] > height && !visited[x][y];
}

void init()
{
    for(int i = 0; i <= 100; i++)
        for(int j = 0; j <=100; j++)
            map[i][j] = visited[i][j] = 0;
}

void solve(int tc, int maxHeight)
{
    int maxPartition = 0;
    queue<pair<int, int>> q;
    for(int height = 0; height < maxHeight; height++)
    {
        int partition = 0;
        for(int i = 1; i <= N; i++)
        {
            for(int j = 1; j <= N; j++)
            {
                if(valid(i, j, height))
                {
                    q.push({i, j});
                    visited[i][j] = true;
                    partition += 1;
                    while(!q.empty())
                    {
                        pair<int, int> from = q.front(); q.pop();
                        for(int k = 0; k < 4; k++)
                        {
                            int tox = from.first + dx[k];
                            int toy = from.second + dy[k];
                            if(valid(tox, toy, height))
                            {
                                q.push({tox, toy});
                                visited[tox][toy] = true;
                            }
                        }
                    }
                }
            }
        }
        maxPartition = max(maxPartition, partition);
        for(int i = 0; i <= 100; i++)
            for(int j = 0; j <=100; j++)
                visited[i][j] = false;
    }
    
    cout << '#' << tc << ' '<< maxPartition << '\n';
}

int main()
{
    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++)
    {
        int maxHeight = 0;
        cin >> N;
        for(int i = 1; i <= N; i++)
        {
            for(int j = 1; j <= N; j++)
            {
                cin >> map[i][j];
                maxHeight = max(map[i][j], maxHeight);
            }
        }
        solve(tc, maxHeight);

        init();
    }
}