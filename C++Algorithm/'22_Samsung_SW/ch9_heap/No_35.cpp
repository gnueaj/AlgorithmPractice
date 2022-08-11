#include<iostream>
#include<unordered_set>
#include<algorithm>
#include<unordered_map>
#include<vector>
#include<queue>
#include<functional>
using namespace std;

long long N, K;
long long ans;
long long num[11];

unordered_map<int, int> visited;


void solve() {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push({0, K});

	while (pq.top().second) {
		pair<int, int> cur = pq.top(); pq.pop();
		for (int i = 1; i <= N; i++) {
			pq.push({cur.first + cur.second % num[i], cur.second / num[i]});
		}
	}
	ans = pq.top().first;
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