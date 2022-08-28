#include<iostream>
#include<algorithm>

using namespace std;

long long n, q;
long long segtree[200001]; //1번 노드가 루트, 노드 개수는 N + N - 1 = 2 * N - 1 개
long long a[100001];

void init() {
	for (int i = 0; i < n; i++) {
		segtree[i + n] = a[i];  // 리프노드 index [n ~ 2n)
	}
   
	for (int i = n - 1; i > 0; i--) { // 부모노드 index[1 ~ N)
		segtree[i] = segtree[i << 1] + segtree[i << 1 | 1];
	}
}

void update(int i, int x) {
    if(i & 1) x = -x; 
    i = i + n; // i번째 리프노드의 인덱스
	segtree[i] = x;
	while (i >>= 1) {
		segtree[i] = segtree[i << 1] + segtree[i << 1 | 1];
	}
}

long long query(int l, int r) {
	long long sum = 0;
    bool isOdd = l & 1;
	for (l += n, r += n; l != r; l >>= 1, r >>= 1) 
    {//리프노드부터 탐색
		if (l & 1)
        {
            sum += segtree[l++];
        } // l이 오른쪽 자식일 때는 더해야 함
		if (r & 1) 
        {
            sum += segtree[--r];
        } // r이 오른쪽 자식일 때는 더할필요 없음
	}
    if(isOdd) sum = -sum;
    return sum;
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
        cin >> n >> q;
        for(int i = 0; i < n; i++)
        {
            cin >> a[i];
            if(i & 1) a[i] = -a[i];
        }
        
        init();
        cout << "#" << test_case << ' ';
        while(q--)
        {
            int op;
            cin >> op;
            if(op == 0)
            {   
                long long i, x;
                cin >> i >> x;
                update(i, x);
            }
            if(op == 1)
            {
                long long l, r;
                cin >> l >> r;
                cout << query(l, r) << ' ';
            }
        }
        cout << '\n';
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}