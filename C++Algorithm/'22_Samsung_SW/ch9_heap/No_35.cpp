#include<iostream>
#include<unordered_set>
#include<algorithm>
#include<unordered_map>

using namespace std;

long long N, K;
long long ans;
long long num[11];

unordered_map<int, int> visited;

void DFS(long long X, long long D, long long nth)
{
    cout << nth << ' ' << D << ' '<< X << endl;
    if(X > K || D > K || nth >= ans)
        return;

    //cout << X << endl;
    if(visited.find(X) == visited.end())
    {
        //cout << 'f' << nth << ' ' << D << ' '<< X << endl;
        visited.insert({X, nth});
    }
    else if(nth < (visited.find(X)->second))
    {
        cout << 'n' << nth << ' ' << D << ' '<< X << endl;
        visited.find(X)->second = nth;
    }
    else
    {
        return;
    }

    if(X == K)
    {
        ans = min(ans, nth);
        return;
    }

    for(int i = 1; i <= N; i++)
    {
        //cout <<"dd" <<endl;
        DFS(X, D * num[i], nth + 1);   
    }

    DFS(X + D, D, nth + 1);
}

void solve()
{
    sort(num + 1, num + 1 + N);
    ans = 2147483647;
    
    long long X = 0;
    long long D = 1;
    DFS(X, D, 0);
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
            cin >> num[i];
        cin >> K;

		solve();
        cout << '#' << test_case << ' ' << ans << endl;
        
        for(int i = 1; i <= N; i++)
            num[i] = 0;
        visited.clear();
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}