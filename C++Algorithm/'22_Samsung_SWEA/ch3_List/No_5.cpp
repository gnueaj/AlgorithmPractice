#define MAX_NODE 10000

struct Node {
	int data;
	Node* prev;
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;

Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].prev = nullptr;
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
    _node->prev = head;
    head->next = _node;
    if(_node->next != nullptr)
    {
        _node->next->prev = _node;
    }
}

void addNode2Tail(int data) 
{
    Node* ptr = head;
    while(ptr->next!= nullptr)
    {
        ptr = ptr->next;
    }
    
    Node* _node = getNode(data);

    _node->prev = ptr;    
    ptr->next = _node;
}

void addNode2Num(int data, int num) 
{
    Node* ptr = head;
    if(num >= 1)
        num = num - 1;
    while(num--)
    {
        ptr = ptr->next;
    }
    Node* _node = getNode(data);
    _node->next = ptr->next;
    _node->prev = ptr;
    ptr->next = _node;
    if(_node->next != nullptr)
    {
        _node->next->prev = _node;
    }
    
}

int findNode(int data) 
{
    Node* rNode = head;
    int cnt = 1;
    while(rNode->next != nullptr && rNode->next->data != data)
    {
        cnt += 1;
        rNode = rNode->next;
    }
    if(rNode->next != nullptr)
    {
        return cnt;
    }
}

void removeNode(int data) 
{
    Node* rNode = head;
    while(rNode->next != nullptr && rNode->next->data != data)
    {
        rNode = rNode->next;
    }
    if(rNode->next != nullptr){
        if(rNode->next->next != nullptr)
        {
            rNode->next = rNode->next->next;
            rNode->next->prev = rNode;
        }
        else
            rNode->next = nullptr;
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

int getReversedList(int output[MAX_NODE]) 
{
    Node* ptr = head;
    while(ptr->next != nullptr)
    {
        ptr = ptr->next;
    }
    int cnt = 0;
    while(ptr != head)
    {
        output[cnt++] = ptr->data;
        ptr = ptr->prev;
    }
    return cnt;
}