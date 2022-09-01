#include<algorithm>
#include<string>
#include<iostream>
#include<queue>

using namespace std;



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
        priority_queue<int> pq;
		int N;
        cin >> N;
        cout << "#" <<test_case << ' ';
        while(N--)
        {
            int op;
            cin >> op;
            if(op == 1)
            {
                int n;
                cin >> n;
                pq.push(n);
            }
            else
            {
                if(pq.empty())
                    cout << -1 << ' ';
                else
                {
                    cout << pq.top() << ' ';
                    pq.pop();
                }
            }
        }
        cout << '\n';
       
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}