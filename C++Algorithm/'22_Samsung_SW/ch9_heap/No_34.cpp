#include<algorithm>
#include<string>
#include<iostream>
#include<queue>
#include<cstring>
#include<utility>
#include<functional>

using namespace std;

int N;
int median;

int solve(int st)
{
    int ans = 0;

    priority_queue<int, vector<int>, greater<int>> min_heap;
    priority_queue<int> max_heap;    
    
    int X, Y;
    cin >> X >> Y;
    if(X < Y) swap(X, Y); // X >= Y
    
    N -= 1;
    if(X >= st && st >= Y)
    {
        median = st;
        min_heap.push(X);
        max_heap.push(Y);
    }
    else if(X >= Y && Y >= st)
    {
        median = Y;
        min_heap.push(X);
        max_heap.push(st);
    }
    else if(st >= X && X >= Y)
    {
        median = X;
        min_heap.push(st);
        max_heap.push(Y);
    }
    ans += median;

    while(N--)
    {
        cin >> X >> Y;
        if(X < Y) swap(X, Y);
        if(X >= median && median >= Y)
        {
            min_heap.push(X);
            max_heap.push(Y);

            ans += median;
            ans %= 20171109;
        }
        else if(X >= Y && Y >= median)
        {
            min_heap.push(X);
            min_heap.push(Y);
            max_heap.push(median);
            median = min_heap.top(); min_heap.pop();

            ans += median;
            ans %= 20171109;
        }
        else if(median >= X && X >= Y)
        {
            max_heap.push(X);
            max_heap.push(Y);
            min_heap.push(median);
            median = max_heap.top(); max_heap.pop();

            ans += median;
            ans %= 20171109;
        }
    }
    return ans;
}

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	int test_case;
	int T;

	//freopen("input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
        int st;
        cin >> N >> st;
        int ans = solve(st);
        cout << '#' << test_case << ' ' << ans << endl;
	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}