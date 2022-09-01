#include<iostream>
#include<string>

using namespace std;

struct Node{
	string value;
	int left, right;
	Node(string value, int left, int right) : value(value), left(left), right(right){};
	Node(){};
};

Node tree[1001];

bool isop(char s){ return s == '+' || s == '-' || s == '*' || s == '/'; }

int inorder(int n) // 숫자인가?
{
    switch(tree[n].value[0])
    {
        case '+':
            return inorder(tree[n].left) + inorder(tree[n].right);
        case '-':
            return inorder(tree[n].left) - inorder(tree[n].right);
        case '*':
            return inorder(tree[n].left) * inorder(tree[n].right);
        case '/':
            return inorder(tree[n].left) / inorder(tree[n].right);
        default:
            return stoi(tree[n].value);
    }
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
			cin >> num;
			cin.ignore();

			string s;
			getline(cin, s);

            int left = 0, right = 0;
            string value = "";
            if(isop(s[0]))
            {
                value += s[0];
                for(int i = 1, v = 0; ;i++)
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
            }
            else
            {
                for(int i = 0; s[i]; i++)
                    value += s[i];
            }
			
			//cout << value << left << right << endl;
			Node node = Node(value, left, right);
			tree[num] = node;
			
		}
		cout << "#" << 10 - c << " "  << inorder(1) << endl;
	}
	return 0;
}