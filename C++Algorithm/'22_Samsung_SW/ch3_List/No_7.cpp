#include<iostream>
#include<list>

using namespace std;

list<int> lst;

int main(int argc, char** argv)
{
    //setbuf(stdout, NULL);
    freopen("sample_input.txt", "r", stdin);
	int test_case;
	int T;
    cin >> T;
	
	

	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for(test_case = 1; test_case <= T; ++test_case)
	{
        lst.clear();
        int len, num, L;
        cin >> len >> num >> L;
        while(len--)
        {
            int data;
            cin >> data;
            lst.push_back(data);
        }

        while(num--)
        {
            char cmd;
            cin >> cmd;
            int x, data, idx;
            list<int>::iterator iter = lst.begin();
            switch(cmd)
            {
                case 'I':
                    cin >> x >> data;
                    idx = x;
                    while(idx--) iter++;
                    lst.insert(iter, data);
                break;

                case 'D':
                    cin >> x;
                    while(x--) iter++;
                    lst.erase(iter++);
                break;

                case 'C':
                    cin >> x >> data;
                    while(x--) iter++;
                    *iter = data;
                break;
            }
        }
        cout << "#" << test_case << ' ';
        list<int>::iterator itr = lst.begin();
        while(L-- && itr != lst.end()) itr++;
        if(itr != lst.end()) cout << *itr;
        else cout << -1;
        cout << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}