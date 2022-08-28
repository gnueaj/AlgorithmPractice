#include<iostream>
#include<cmath>

using namespace std;

long long N;
bool check(long long key)
{
    return key * (key + 1) / 2;
}

long long bs(long long left, long long right)
{
    long long ans = 0;
    while(left <= right)
    {
        long long mid = left + (right - left) / 2;
        
        if(mid * (mid + 1) / 2 <= N)
        {
            if(mid * (mid + 1) / 2 == N)
                ans = mid;
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    if(!ans) return -1;
    else return ans;
}

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	int test_case;
	int T;
	
	
	cin>>T;
	
	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> N;
        cout << '#' << test_case << ' ' << bs(1, 4 * sqrt(N)) << '\n';

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}