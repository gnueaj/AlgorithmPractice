#include <iostream>
using namespace std;


char B[500001], S[100001];
int P[100001];

void CalcP() {
    P[0] = 0;
    for(int i = 1; S[i]; i++) {
        int j = P[i-1];
        while(j > 0) {
            if(S[i] == S[j]) break;
            j = P[j-1];
        }
        if(S[i] == S[j]) P[i] = j + 1;
        else P[i] = 0;
    }
}

int main() {
    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cin >> B >> S;
        CalcP();

        int piv = 0, cnt = 0, ans = 0;
        while(B[piv]) {
            if(B[piv] == S[cnt]) {
                if(!S[cnt+1]) {
                    // Find
                    ans++;
                    cnt = P[cnt];
                } else cnt++;
                piv++;
            } else if(cnt > 0) cnt = P[cnt-1];
            else piv++;
        }
        cout << '#' << tc << ' ' << ans << '\n';
    }
    return 0;
}