#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

int N;
string s[20001];

bool cmp(string& a, string& b)
{
    if(a.length() != b.length()) return a.length() < b.length();
    else return a < b; 
}

void solve()
{
    sort(s, s + N, cmp);
    for(int i = 0; i < N; i++)
    {
        if(s[i] == s[i + 1]) continue;
        else cout << s[i] << '\n';
    } 
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	//freopen("input.txt", "r", stdin);
	cin>>T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> N;
        for(int i = 0; i < N; i++)
        {
            cin >> s[i];
        }
        cout << '#' << test_case << '\n';
        solve();
        for(int i = 0; i < N; i++)
        {
            s[i] = "";
        }
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}