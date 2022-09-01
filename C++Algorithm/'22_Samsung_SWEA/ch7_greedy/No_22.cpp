         
#include<iostream>

using namespace std;

int money[] = { 50000, 10000, 5000, 1000, 500, 100, 50, 10};

void greedy(int N)
{
    int ans[8] = {0, };
    for(int i = 0; i < 8; i++)
    {
        ans[i] = N / money[i];
        N %= money[i];
    } 
    for(int i = 0; i < 8; i++)
    {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	//freopen("input.txt", "r", stdin);
	cin>>T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for(test_case = 1; test_case <= T; ++test_case)
	{
        int N;
        cin >> N;
        cout << '#' << test_case << endl;
        greedy(N);

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}