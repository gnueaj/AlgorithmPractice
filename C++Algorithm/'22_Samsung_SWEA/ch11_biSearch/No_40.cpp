#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;

long long N, P;
long long ans;
bool visited[2000001];
long long day[200001];

void bs(long long left, long long right)
{ 
    ans = P + 1;
    for(int i = 0; i < N; i++)
    {
        visited[day[i]] = true;
    }
    
	long long cnt = 0; 
	while(right < 1000000) 
    {
		if(visited[right]) 
        { 
			cnt += 1;
			right += 1;
			ans = max(ans, cnt);
		}
		else 
        { 
			if(P == 0) 
            {
	    	    ans = max(ans, cnt);
				if(!visited[left]) P += 1; 
				left += 1; 
				cnt -= 1; 
			}
			else 
            {
				P--;
				cnt += 1;
				right += 1;
			}
		}
	}
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
        cin >> N >> P;
        for(int i = 0; i < N; i++) cin >> day[i];
        bs(1, 1);
        cout << '#' << test_case << ' ' << ans << '\n';
        memset(visited, 0, sizeof(bool) * 1000001);
        memset(day, 0, sizeof(long long) * 200001);
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}