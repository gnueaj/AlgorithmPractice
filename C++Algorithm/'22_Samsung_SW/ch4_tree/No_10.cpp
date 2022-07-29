#include<iostream>
#include<string>
#include<vector>
#include<cstring>

using namespace std;

struct Node{
	char value;
	int left, right;
	Node(char value, int left, int right) : value(value), left(left), right(right){};
	Node(){};
};

Node tree[1001];

bool valid = true;
bool pre = false;

bool isop(char s){return (s == '+') || (s == '-') || 
                        (s == '*') || (s == '/');}

void ans(int n) // 숫자인가?
{
    if(tree[n].left) ans(tree[n].left);
    bool cur = isop(tree[n].value);
    if(pre == cur) valid = false;
    pre = cur;
    if(tree[n].right) ans(tree[n].right);
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	//setbuf(stdout, NULL);
	//freopen("input.txt", "r", stdin);
	int c = 10;
	while(c--)
	{
		cin >> T;
		for(test_case = 1; test_case <= T; ++test_case)
		{
			int num;
			char value;
			cin >> num >> value;
			
			string s;
			getline(cin, s);
			int left = 0, right = 0;
			for(int i = 0, v = 0; ;i++)
			{
				if(s[i] != ' ' && s[i] != '\0')
				{
					v *= 10;
					v += (s[i] - '0');
				}
				else if(left == 0 && v != 0)
				{
					left = v;
					v = 0;
					if(s[i] == '\0') break;
				}
				else if(s[i] == '\0')
				{
					right = v;
					break;
				}
			}
			
			Node node = Node(value, left, right);
			tree[num] = node;
			
		}
		cout << "#" << 10 - c << " "; 
		ans(1); 
		cout << valid << endl;
        valid = true;
        pre = false;
	}
	return 0;
}