#include<iostream>
#include<algorithm>
#include<functional>

using namespace std;

long long ans;
long long A, B, K;

long long power(long long x, long long p, long long mod) {
	long long res = 1;
	while (p) {
		if (p & 1) res *= x;
		x *= x;
        if(x % mod) x %= mod;
        if(res % mod) res %= mod; 
		p >>= 1;
	}
	return res;
}

void solve()
{
    long long n = (A * power(2, K, A + B)) % (A + B);
    ans = min(n, A + B - n);

}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> A >> B >> K;
        solve();
        cout << '#' << test_case << ' ' << ans << endl;
        ans = 0;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}