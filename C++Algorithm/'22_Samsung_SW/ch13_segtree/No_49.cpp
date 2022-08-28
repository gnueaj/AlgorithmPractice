#include<iostream>
#include<algorithm>

using namespace std;

int n, q;
int mintree[200001]; //1번 노드가 루트, 노드 개수는 N + N - 1 = 2 * N - 1 개
int maxtree[200001];
int a[100001];

void init() {
	for (int i = 0; i < n; i++) {
		mintree[i + n] = maxtree[i + n] = a[i];  // 리프노드 index [n ~ 2n)
	}
   
	for (int i = n - 1; i > 0; i--) { // 부모노드 index[1 ~ N)
		mintree[i] = min(mintree[i << 1], mintree[i << 1 | 1]);
        maxtree[i] = max(maxtree[i << 1], maxtree[i << 1 | 1]);
	}   
}

void update(int i, int x) {
    i = i + n; // i번째 리프노드의 인덱스
	mintree[i] = maxtree[i] = x;
	while (i >>= 1) {
		mintree[i] = min(mintree[i << 1], mintree[i << 1 | 1]);
        maxtree[i] = max(maxtree[i << 1], maxtree[i << 1 | 1]);
	}//조상의 값 모두 바꾸기
}

int query(int l, int r) {
	int maxVal = -1;
    int minVal = 2147483647;
	for (l += n, r += n; l != r; l >>= 1, r >>= 1) 
    {//리프노드부터 탐색
		if (l & 1)
        {
            minVal = min(minVal, mintree[l]);
            maxVal = max(maxVal, maxtree[l++]);
        } // l이 오른쪽 자식일 때는 더해야 함
		if (r & 1) 
        {
            minVal = min(minVal, mintree[--r]);
            maxVal = max(maxVal, maxtree[r]);
        } // r이 오른쪽 자식일 때는 더할필요 없음
	}

    return maxVal - minVal;
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
        cin >> n >> q;
        for(int i = 0; i < n; i++)
            cin >> a[i];
        
        init();
        cout << "#" << test_case << ' ';
        while(q--)
        {
            int op;
            cin >> op;
            if(op == 0)
            {   
                int i, x;
                cin >> i >> x;
                update(i, x);
            }
            if(op == 1)
            {
                int l, r;
                cin >> l >> r;
                cout << query(l, r) << ' ';
            }
        }
        cout << '\n';
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}