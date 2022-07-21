#define MAX_NODE 10000

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
    num = num - 1;
    while(num--)
    {
        ptr = ptr->next;
    }
    Node* _node = getNode(data);
    _node->next = ptr->next;
    ptr->next = _node;
}

void removeNode(int data) 
{
    Node* rNode = head;
    while(rNode->next != nullptr && rNode->next->data != data)
    {
        rNode = rNode->next;
    }
    if(rNode->next != nullptr){
        rNode->next = rNode->next->next;
    }
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