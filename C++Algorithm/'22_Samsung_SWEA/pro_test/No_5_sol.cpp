#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

int N;
int A[22][22], B[22][22];
int TABLE[48889];

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};


bool valid1(int x, int y) 
{
    return x >= 1 && y >= 1 && x <= N && y <= N;
}

bool valid2(int x, int y) 
{
    return x >= 0 && y >= 0 && x <= N + 1 && y <= N + 1;
}

bool palindrome(int x) 
{
    int tmp = x;
    int n = 0;
    while(x) 
    {
        n = n * 10 + x % 10;
        x /= 10;
    }
    return tmp == n;
}


int bfs(int level) 
{
    queue<pair<int, int>> q;
    bool visited[22][22] = {false, };
    q.push({0, 0});
    visited[0][0] = true;

    int ans = (N + 2) * (N + 2);

    while(!q.empty()) 
    {
        pair<int, int> from = q.front(); q.pop();
        ans -= 1;

        for(int i=0; i<4; i++) 
        {
            int tox = from.first + dx[i];
            int toy = from.second + dy[i];
            if(valid2(tox, toy) && !visited[tox][toy] && B[tox][toy] < level) 
            {
                visited[tox][toy] = true;
                q.push({tox, toy});
            }
        }
    }
    return ans;
}

void init(int n, int _A[20][20]) 
{
    memset(TABLE, 0, sizeof(TABLE));
    memset(B, 0, sizeof(B));
    

    int idx = 0;
    N = n;

    for(int i = 1; i <= N; i++) 
    {
        for(int j = 1; j <= N; j++) 
        {
            A[i][j] = B[i][j] = _A[i-1][j-1];
        }
    }

    for(int i = 1; i <= N; i++) 
    {
        for(int j = 1; j <= N; j++) 
        {
            int from = A[i][j];
            for(int k=0; k<4; k++) 
            {
                int tox = i + dx[k];
                int toy = j + dy[k];
                int num = 4;
                for(int m = 1; m <= 4; m++) 
                {
                    if(!valid1(tox, toy)) 
                        break;

                    num = num * 10 + A[tox][toy] - from + 4;
                    TABLE[num] += 1;

                    tox += dx[k];
                    toy += dy[k];
                }
            }
        }
    }
}

int numberOfCandidate(int M, int block[5]) 
{
    if(M == 1) 
    {
        return N * N;
    }

    int num = 4;
    for(int i = 1; i < M; i++) 
        num = num * 10 + block[0] - block[i] + 4;

    return palindrome(num) ? TABLE[num] >> 1 : TABLE[num];
}

int maxArea(int M, int block[5], int lev)
{
    int ans = -1;
    for(int i = 1; i <= N; i++) 
    {
        for(int j = 1; j <= N; j++) 
        {
            int base = A[i][j];
            int t = base + block[0];

            for(int k = 0; k < 4; k++) 
            {
                int tox = i + dx[k];
                int toy = j + dy[k];

                bool flag = true;

                for(int m = 1; m < M; m++) 
                {
                    if(!valid1(tox, toy)) 
                    {
                        flag = false;
                        break;
                    }
                    if(A[tox][toy] + block[m] != t) 
                    {
                        flag = false;
                        break;
                    }
                    tox += dx[k];
                    toy += dy[k];
                }

                if(flag) 
                {
                    tox = i;
                    toy = j;

                    for(int m = 0; m < M; m++) 
                    {
                        B[tox][toy] = t;
                        tox += dx[k];
                        toy += dy[k];
                    }
                    ans = max(ans, bfs(lev));

                    tox = i;
                    toy = j;
                    for(int m = 0; m < M; m++) 
                    {
                        B[tox][toy] = A[tox][toy];
                        tox += dx[k];
                        toy += dy[k];
                    }
                }
            }
        }
    }

    return ans;
}