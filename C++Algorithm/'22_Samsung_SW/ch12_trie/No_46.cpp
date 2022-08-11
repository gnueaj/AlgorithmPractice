#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

string s[400];
string str;
string ans;

int K;
void solve()
{
    ans = "";
    for(int i = 0; i < str.length(); i++)
        s[i] = "";
    for(int i = 0; i < str.length(); i++)
    {
        for(int j = i; j < str.length(); j++)
        {
            s[i] += str[j];
        }
    }
    sort(s, s + str.length());


    int lcp[401] = {0, };
    for(int i = 1; i < str.length(); i++)
    {
        for(int j = 0; j < s[i].length(); j++)
        {
            if(s[i][j] == s[i - 1][j])
                lcp[i] += 1;
            else
                break;
        }
    }
    int sum = 0;
   
    for(int i = 0; i < str.length(); i++)
    {
        if(sum + s[i].length() - lcp[i] < K)
        {
            sum += s[i].length() - lcp[i];
        }
        else
        {
            for(int j = 0; j < K - sum + lcp[i]; j++)
                ans += s[i][j];
            break;
        }
    }
    if(ans == "") ans = "none";
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	//freopen("input.txt", "r", stdin);
	cin>>T;
	
	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> K >> str;
        solve();
        cout << '#' << test_case << ' ' << ans << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}