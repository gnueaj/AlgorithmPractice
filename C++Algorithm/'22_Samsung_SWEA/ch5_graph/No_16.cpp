#include<iostream>
#include<vector>
#include<utility>
#include<queue>
#include<algorithm>
#include<iostream>
using namespace std;

int map[13][13];
bool wire[13][13];
int dist[13];
bool visited[13][13];
int N;
vector<pair<int,int>> core;

bool edge(int x1, int y1)
{
    return x1 == 1 || y1 == 1 || x1 == N || y1 == N;
}
bool possible(int x1, int y1, int x2, int y2) 
{
    if(x1 == x2)
    {
        for(int i = y1; i <= y2; i++)
            if(wire[x1][i]) return false; //가로
    }
    else
    {
        for(int i = x1; i <= x2; i++)
            if(wire[i][y1]) return false; //세로
    }
    return true;
}
void set_wire(int x1, int y1, int x2, int y2)
{
    if(x1 == x2)
    {
        for(int i = y1; i <= y2; i++)
            wire[x1][i]= true; //가로
    }
    else
    {
        for(int i = x1; i <= x2; i++)
            wire[i][y1] = true; //세로
    }
}

void rm_wire(int x1, int y1, int x2, int y2) 
{
    if(x1 == x2)
    {
        for(int i = y1; i <= y2; i++)
            wire[x1][i]= false; //가로
    }
    else
    {
        for(int i = x1; i <= x2; i++)
            wire[i][y1] = false; //세로
    }
}

void init()
{
    core.clear();
    for(int i = 0; i < 13; i++)
    {
        dist[i] = 0;
        for(int j = 0; j < 13; j++)
        {
            visited[i][j] = false;
            map[i][j] = false;
            wire[i][j] = false;
        }
    }
}

void dfs_rec(int nth, int prev, int connected)
{
    if(nth >= N) return;
    if(dist[N] && prev > dist[N]) return;

    int x = core[nth].first;
    int y = core[nth].second;
    
    if(!visited[x][y] && !edge(x, y))   
    {
        if(possible(x, y + 1, x, N))
        {
            set_wire(x, y + 1, x, N); //전선 설치
            if(!dist[connected]) dist[connected] = prev + N - y;
            else dist[connected] = min(dist[connected], prev + N - y); //구간합 계산 
            visited[x][y] = true; // 방문 표시
            dfs_rec(nth + 1, prev + N - y, connected + 1); //다음 전선 설치
            
            rm_wire(x, y + 1, x, N); //전선 제거
            visited[x][y] = false;
        }
        if(possible(x, 1, x, y - 1))
        {
            set_wire(x, 1, x, y - 1);
            if(!dist[connected]) dist[connected] = prev + y - 1;
            else dist[connected] = min(dist[connected], prev + y - 1);
            visited[x][y] = true;
            dfs_rec(nth + 1, prev + y - 1, connected + 1);

            rm_wire(x, 1, x, y - 1);
            visited[x][y] = false;
        }
        if(possible(1, y, x - 1, y))
        {
            set_wire(1, y, x - 1, y);
            if(!dist[connected]) dist[connected] = prev + x - 1;
            else dist[connected] = min(dist[connected], prev + x - 1);
            visited[x][y] = true;
            dfs_rec(nth + 1, prev + x - 1, connected + 1);
            
            rm_wire(1, y, x - 1, y);
            visited[x][y] = false;
        }
        if(possible(x + 1, y, N, y))
        {
            set_wire(x + 1, y, N, y);
            if(!dist[connected]) dist[connected] = prev + N - x;
            else dist[connected] = min(dist[connected], prev + N - x);
            visited[x][y] = true;
            dfs_rec(nth + 1, prev + N - x, connected + 1);
            
            rm_wire(x + 1, y, N, y);
            visited[x][y] = false;
        }
    }

    if(!visited[x][y])
    {   
        visited[x][y] = true;
        dfs_rec(nth+1, prev, connected);
        visited[x][y] = false;
    }
        
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	//freopen("input.txt", "r", stdin);
	cin >> T;
	
	for(test_case = 1; test_case <= T; ++test_case)
	{
        init();
        cin >> N;
        for(int i = 1; i <= N; i++)
        {
            for(int j = 1; j <= N; j++)
            {
                cin >> map[i][j];
                if(map[i][j]) 
                {
                    wire[i][j] = 1;
                    core.push_back({i, j});
                }
            }
        }
        dfs_rec(0,0,0);
        int ans;
        for(int i = N; i >= 1; i--)
            if(dist[i])
            {
                ans = dist[i];
                break;
            } 
        cout << "#" << test_case << ' ' << ans << endl;
	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}