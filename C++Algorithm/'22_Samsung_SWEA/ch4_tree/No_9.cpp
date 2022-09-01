#include<iostream>
#include<string>

using namespace std;

struct Node{
	char value;
	int left, right;
	Node(char value, int left, int right) : value(value), left(left), right(right){};
	Node(){};
};

Node tree[101];

void ans(int n)
{
	if(tree[n].left) ans(tree[n].left);
	if(tree[n].value) cout << tree[n].value;
	if(tree[n].right) ans(tree[n].right);
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	//setbuf(stdout, NULL);
	freopen("input.txt", "r", stdin);

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
		cout << endl;
	}
	return 0;
}