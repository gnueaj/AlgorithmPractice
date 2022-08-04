/////////////////////////////////////////////////////////////////////////////////////////////
// 기본 제공코드는 임의 수정해도 관계 없습니다. 단, 입출력 포맷 주의
// 아래 표준 입출력 예제 필요시 참고하세요.
// 표준 입력 예제
// int a;
// float b, c;
// double d, e, f;
// char g;
// char var[256];
// long long AB;
// cin >> a;                            // int 변수 1개 입력받는 예제
// cin >> b >> c;                       // float 변수 2개 입력받는 예제 
// cin >> d >> e >> f;                  // double 변수 3개 입력받는 예제
// cin >> g;                            // char 변수 1개 입력받는 예제
// cin >> var;                          // 문자열 1개 입력받는 예제
// cin >> AB;                           // long long 변수 1개 입력받는 예제
/////////////////////////////////////////////////////////////////////////////////////////////
// 표준 출력 예제
// int a = 0;                            
// float b = 1.0, c = 2.0;               
// double d = 3.0, e = 0.0; f = 1.0;
// char g = 'b';
// char var[256] = "ABCDEFG";
// long long AB = 12345678901234567L;
// cout << a;                           // int 변수 1개 출력하는 예제
// cout << b << " " << c;               // float 변수 2개 출력하는 예제
// cout << d << " " << e << " " << f;   // double 변수 3개 출력하는 예제
// cout << g;                           // char 변수 1개 출력하는 예제
// cout << var;                         // 문자열 1개 출력하는 예제
// cout << AB;                          // long long 변수 1개 출력하는 예제
/////////////////////////////////////////////////////////////////////////////////////////////

#include<iostream>
#include<vector>
#include <queue>
#include<algorithm>
#include<cmath>

using namespace std;


struct Node{
    long long parent = 0;
    long long level = 0;
    vector<long long> child;
};

Node tree[100001];
long long N;
bool visited[100001];
long long parent[100001][18];

void init()
{
    for(int i = 0; i <= N; i++)
    {
        tree[i] = Node();
        visited[i] = false;
        for(int j = 0; j < 18; j++)
            parent[i][j] = 0;
    }
}

long long LCA(long long n1, long long n2)
{
    long long ret = 0;
    if(tree[n1].level < tree[n2].level)
    {
        long long tmp = n1;
        n1 = n2;
        n2 = tmp;
    }

    long long diff = tree[n1].level - tree[n2].level;
    ret += diff;
    
    for(int i = 0; diff != 0; i++)
    {
        if(diff % 2)
            n1 = parent[n1][i];
        diff = diff >> 1;
    }

    long long cmp = tree[n1].level;
    if(n1 != n2)
    {
        for(int i = 17; i >= 0; i--)
        {
            if(parent[n1][i] && parent[n1][i] != parent[n2][i])
            {
                n1 = parent[n1][i];
                n2 = parent[n2][i];
            }
        }
        ret += (cmp - tree[parent[n1][0]].level) * 2;
    }

    return ret;
}


long long ans()
{
    for(int i = 0; i <= N; i++)
    {
        for(int j = 0; j < 17; j++)
        {
            if(tree[i].parent)
            {
                parent[i][j + 1] = parent[parent[i][j]][j];
            }
        }
    }

    long long ret = 0;
    queue<long long> q;
    q.push(1);
    visited[1] = true;

    long long cmp = 1;
    while(!q.empty())
    {
        long long from = q.front(); q.pop();
        for(int i = 0; i < tree[from].child.size(); i++)
        {
            long long to = tree[from].child[i];
            if(!visited[to])
            {
                q.push(to);
                visited[to] = true;
                ret += LCA(to, cmp);
                cmp = to;
            }
        }
    }
    return ret;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        init();
        cin >> N;
       
        for(int i = 2; i <= N; i++)
        {
            long long node;
            cin >> node;
            tree[i].parent = node;
            tree[i].level = tree[node].level + 1;
            parent[i][0] = node;
            tree[node].child.push_back(i);
        }
        
        cout << "#" << test_case << ' ' << ans() << ' ' << endl;
	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}