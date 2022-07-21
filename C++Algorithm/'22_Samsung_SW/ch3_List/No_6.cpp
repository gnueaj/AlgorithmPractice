
#include<iostream>

using namespace std;
#define MAX_NODE 50000

struct Node {
	int data;
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;


Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void init()
{
    nodeCnt = 0;
    head = getNode(-1);
}

void addNode2Head(int data) 
{
    Node* _node = getNode(data);
    _node->next = head->next;

    head->next = _node;
}

void addNode2Tail(int data) 
{
    Node* ptr = head;
    while(ptr->next!= nullptr)
    {
        ptr = ptr->next;
    }
    
    Node* _node = getNode(data);
    ptr->next = _node;

}

void addNode2Num(int data, int num) 
{
    Node* ptr = head;
    while(num--)
    {
        ptr = ptr->next;
    }
    Node* _node = getNode(data);
    _node->next = ptr->next;
    ptr->next = _node;
}

void removeNode(int num) 
{
    Node* rNode = head;
    while(num--)
    {
        rNode = rNode->next;
    }
    rNode->next = rNode->next->next;
    // Node* rNode = head;
    // while(rNode->next != nullptr && rNode->next->data != data)
    // {
    //     rNode = rNode->next;
    // }
    // if(rNode->next != nullptr){
    //     rNode->next = rNode->next->next;
    // }
}

int getList(int output[MAX_NODE]) 
{
    Node* ptr = head;
    int cnt = 0;
    while(ptr->next != nullptr)
    {
        ptr = ptr->next;
        output[cnt++] = ptr->data;
    }
    return cnt;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	freopen("input.txt", "r", stdin);
	T = 10; 
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for(test_case = 1; test_case <= T; ++test_case)
	{
        init();
        int len;
        cin >> len;
        while(len--)
        {
            int data;
            cin >> data;
            //cout << "d";5

            addNode2Tail(data);
        }

        int num;
        cin >> num;
        while(num--)
        {
            char cmd;
            cin >> cmd;
            int x, y, data;;
            switch(cmd)
            {
                case 'I':
                    cin >> x >> y;
                    for(int i = 0, rep = y; i < rep; i++, y++)
                    {
                        cin >> data;
                        addNode2Num(data, y);
                    }
                break;

                case 'D':
                    cin >> x >> y;
                    while(y--)
                    {
                        removeNode(x);
                    }
                break;

                case 'A':
                    cin >> y;
                    while(y--)
                    {
                        cin >> data;
                        addNode2Tail(data);
                    }
                break;
            }
        }
        int rep = 0;
        cout << "#" << test_case << " ";
        for(Node* ptr = head; rep < 10 && ptr-> next != nullptr; ptr = ptr->next, rep++)
        {
            cout << ptr->next->data << ' ';
        }
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}