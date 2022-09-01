#include<algorithm>
#include<string>
#include<iostream>
#include<unordered_set>

using namespace std;

unordered_set<string> _hash;

int main(int argc, char** argv)
{
	int test_case;
	int T;

	//freopen("input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		int N, M;
		cin >> N >> M;
		while (N--)
		{
			string s;
			cin >> s;
			_hash.insert(s);
		}
		int ans = 0;
		while (M--)
		{
			string s;
			cin >> s;
			if (_hash.find(s) != _hash.end()) ans++;
		}
		cout << '#' << test_case << ' ' << ans << endl;
		_hash.clear();
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}