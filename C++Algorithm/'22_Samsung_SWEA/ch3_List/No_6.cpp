#include<iostream>
#include<list>

using namespace std;

list<int> lst;

int main(int argc, char** argv)
{
	int test_case;
	int T = 10;
	//setbuf(stdout, NULL);
	freopen("input.txt", "r", stdin);

	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for(test_case = 1; test_case <= T; ++test_case)
	{
        lst.clear();
        int len;
        cin >> len;
        while(len--)
        {
            int data;
            cin >> data;
            lst.push_back(data);
        }

        int num;
        cin >> num;
        while(num--)
        {
            char cmd;
            cin >> cmd;
            int x, y, data, idx;
            list<int>::iterator iter = lst.begin();
            switch(cmd)
            {
                case 'I':
                    cin >> x >> y;
                    idx = x;
                    while(idx--) iter++;
                    for(int i = 0; i < y; i++)
                    {
                        cin >> data;
                        lst.insert(iter, data);
                    }
                break;

                case 'D':
                    cin >> x >> y;
                    while(x--) iter++;
                    while(y--)
                    {
                        lst.erase(iter++);
                    }
                break;

                case 'A':
                    cin >> y;
                    while(y--)
                    {
                        cin >> data;
                        lst.push_back(data);
                    }
                break;
            }
        }
        cout << "#" << test_case << ' ';
        int n = 0;
        for(auto it = lst.begin(); n < 10; it++, n++)
        {
            cout << *it << ' ';
        }
        cout << endl;
        //cout << "efe";
        lst.clear();
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}