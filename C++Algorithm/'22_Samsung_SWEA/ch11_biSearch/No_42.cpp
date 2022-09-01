#include<iostream>
#include<algorithm>

using namespace std;

long long ans;
long long N, M;
long long A[200];

void bs()
{
    long long left = 1, right = (long long)2e18;

    while(left <= right)
    {
        long long sum = 0;
        long long mid = left + (right - left) / 2; // mid는 가방 수
        for(int i = 0; i < N; i++)
        {
            sum += A[i] / mid;
        }
        
        if(sum == M)
        {
            ans = max(ans, mid);
            left = mid + 1;
        }
        else if(sum > M)
        {
            left = mid + 1;
        }
        else if(sum < M)
        {
            right = mid - 1;
        }
    }
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	//freopen("input.txt", "r", stdin);
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> N >> M;
		for(int i = 0; i < N; i++)
        {
            cin >> A[i];
        }
        bs();
        cout << '#' << test_case << ' ' << ans << endl;
        ans = 0;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}