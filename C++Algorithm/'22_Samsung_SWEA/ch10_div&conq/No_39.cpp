
#include<iostream>
#include <stdio.h>
#include <malloc.h>

using namespace std;

int arr[1000001];
int tmp[1000001];
int N;
long long ans;

void merge(int start, int mid, int end) { 
    int p1 = start, p2 = mid, index = 0;
   
    while (p1 < mid && p2 < end) {
        if (arr[p1] < arr[p2]) {
            tmp[index++] = arr[p1++];
        }
        else if (arr[p1] > arr[p2]) {
            ans += mid - p1;
            tmp[index++] = arr[p2++];
        }
        else {
            tmp[index++] = arr[p2++];
        }
    }
    while (p1 < mid) {
        tmp[index++] = arr[p1++];
    }
    while (p2 < end) {
        tmp[index++] = arr[p2++];
    }
    for (int i = 0; i < end - start; ++i) {
        arr[start + i] = tmp[i];
    }
}

void merge_sort(int start, int end) { 
    int mid = (start + end) / 2;
    if (start < mid) {
        merge_sort(start, mid);
        merge_sort(mid, end);
        merge(start, mid, end);
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
        cin >> N;
        for(int i = 0; i < N; i++)
            cin >> arr[i];
		merge_sort(0, N);
        cout << '#' << test_case << ' ' << ans << endl;
        ans = 0;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}