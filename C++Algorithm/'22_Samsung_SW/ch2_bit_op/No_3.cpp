/////////////////////////////////////////////////////////////////////////////////////////////
// 기본 제공코드는 임의 수정해도 관계 없습니다. 단, 입출력 포맷 주의
// 아래 표준 입출력 예제 필요시 참고하세요.
// 표준 입력 예제
// int a;
// float b, c;
// double d, e, f;
// char g;
// char var[256];
// long long AB;
// cin >> a;                            // int 변수 1개 입력받는 예제
// cin >> b >> c;                       // float 변수 2개 입력받는 예제 
// cin >> d >> e >> f;                  // double 변수 3개 입력받는 예제
// cin >> g;                            // char 변수 1개 입력받는 예제
// cin >> var;                          // 문자열 1개 입력받는 예제
// cin >> AB;                           // long long 변수 1개 입력받는 예제
/////////////////////////////////////////////////////////////////////////////////////////////
// 표준 출력 예제
// int a = 0;                            
// float b = 1.0, c = 2.0;               
// double d = 3.0, e = 0.0; f = 1.0;
// char g = 'b';
// char var[256] = "ABCDEFG";
// long long AB = 12345678901234567L;
// cout << a;                           // int 변수 1개 출력하는 예제
// cout << b << " " << c;               // float 변수 2개 출력하는 예제
// cout << d << " " << e << " " << f;   // double 변수 3개 출력하는 예제
// cout << g;                           // char 변수 1개 출력하는 예제
// cout << var;                         // 문자열 1개 출력하는 예제
// cout << AB;                          // long long 변수 1개 출력하는 예제
/////////////////////////////////////////////////////////////////////////////////////////////

#include<iostream>
#include<cstring>

using namespace std;

long long dp[10001][16];
char str[10001];

void init()
{
    for(int i = 0; i < 10001; i++)
    {
        str[i] = 0;
        for(int j = 0; j < 16; j++)
        {
            dp[i][j] = 0;
        }
    }
}
long long ans()
{
    int len = strlen(str);
    for(int i = 0; i < 16; i++)
    {
        int shift = 3 - (str[0] - 'A'); 
        if((i & (1 << 3)) && (i & (1 << shift)))
        {
            dp[0][i] = 1;
        }
    } // 첫째 날

    int prevch = 1 << (3 - (str[0] - 'A')); 
    int curch = 1 << (3 - (str[1] - 'A')); 
    for(int prev = 0; prev < 16; prev++)
    {
        for(int cur = 0; cur < 16; cur++)
        {
            if((prev & prevch) && (cur & curch) && 
               (prev & (1 << 3)) && (prev & cur))
            {
                dp[1][cur] = dp[1][cur] + dp[0][prev];
            }
        }
    }// 둘째 날

    for(int day = 2; day < len; day++)
    {
        prevch = 1 << (3 - (str[day-1] - 'A')); 
        curch = 1 << (3 - (str[day] - 'A')); 
        for(int prev = 0; prev < 16; prev++)
        {
            for(int cur = 0; cur < 16; cur++)
            {
                if((prev & prevch) && (cur & curch) && (prev & cur))
                {
                    dp[day][cur] = (dp[day][cur] + dp[day-1][prev]) % 1000000007;
                }
            }
        }
    }// 셋째 날 부터

    long long ans = 0;
    for(int i = 0; i < 16; i++)
    {
        ans += dp[len-1][i];
        ans %= 1000000007;
    } // 답

    return ans;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	cin>>T;
	
	for(test_case = 1; test_case <= T; ++test_case)
	{	
        //init();
        memset(dp,0,sizeof(long long)*10001*16);
        memset(str,0,sizeof(char)*10001);

        cin >> str;
        cout << "#" << test_case << " " << ans() << endl;
    }
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}