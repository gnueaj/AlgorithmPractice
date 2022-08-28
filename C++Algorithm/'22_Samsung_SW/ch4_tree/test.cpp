#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int cow[500001];
int horse[500001];
int N, M;

int bs(int pos)
{
    int left = 0;
	int right = N - 1;
	
	if (pos < cow[left]) return 0;
	if (cow[right] < pos) return N - 1;
	
    int ans;
	while (left <= right) 
    {
		int mid = left + (right - left) / 2;
		
		if (cow[mid] <= pos) 
        {
			ans = mid;
            left = mid + 1;
		} 
        else 
        {
			right = mid - 1;
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
    cin >> T;

    for(test_case = 1; test_case <= T; ++test_case)
    {
        cin >> N >> M;
        memset(cow, 0, sizeof(cow));
        memset(horse, 0, sizeof(horse));
        int c1, c2;
        cin >> c1 >> c2;
        int dx = abs(c2 - c1);
        for(int i = 0; i < N; i++) cin >> cow[i];
        for(int i = 0; i < M; i++) cin >> horse[i];
        sort(cow, cow + N);
        int ans = 2147483647;
        int cnt = 0;

        for(int i = 0; i < M; i++)
        {
            int idx = bs(horse[i]);
            if(0 <= idx && idx < N) // cidx == idx, cpos == cow[idx], hpos = horse[i]
            {
                int dz = abs(cow[idx] - horse[i]);
                if(dz < ans)
                {
                    ans = dz;
                    cnt = 1;
                }
                else if(ans == dz)
                {
                    cnt += 1;
                }
            }
            if(0 < idx && idx < N && cow[idx] != horse[i])
            {
                int dz = abs(cow[idx - 1] - horse[i]);
                if(dz < ans)
                {
                    ans = dz;
                    cnt = 1;
                }
                else if(ans == dz)
                {
                    cnt += 1;
                }
            }
        }
        cout << '#' << test_case << ' ' << dx + ans << ' ' << cnt << '\n';
        
    }
    return 0;
}