#include <iostream>
#include <cstring>
#include <vector>
#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999
#define MAX_NODE 50000

using namespace std;

struct Node
{
    char name[NAME_MAXLEN + 1]; // 디렉토리 이름
    Node* parent = nullptr;
    vector<Node*> child;
    int child_cnt = 0;
};

Node tree[MAX_NODE];
int node_cnt = 0;
Node *root;

Node* make_node(char name[NAME_MAXLEN + 1], Node* parent)
{
    strcpy(tree[node_cnt].name, name);
    tree[node_cnt].parent = parent;
    return &tree[node_cnt++];
}

void update_parent(Node* node, int cnt)
{
    Node* cur = node->parent;
    while(cur != nullptr)
    {
        cur->child_cnt += cnt;
        cur = cur->parent;
    }
}//node의 조상들을 업데이트

void init(int n) 
{
    for(int i = 0; i < node_cnt; i++)
    {
        tree[i] = Node();
    }
    node_cnt = 0;
    root = make_node("/", nullptr);
}

Node* find_node(char path[PATH_MAXLEN + 1])
{
    if(!strcmp(path, "/"))
    {
        return &tree[0];
    }

    Node* cur = root;

    int i = 1;
    while(true)
    {
        char tmp[NAME_MAXLEN + 1];
        int c = 0;
        for(; path[i] != '/'; i++)
        {
            tmp[c++] = path[i];
        }
        tmp[c] = '\0';
        for(auto it = cur->child.begin(); it != cur->child.end(); it++)
        {
            if(!strcmp((*it)->name, tmp))
            {
                cur = *it;
                break;
            }
        }
        if(path[++i] == '\0')
            break;
    }

    return cur;
}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) //하위에 만들기
{
    Node* parent = find_node(path); // /aa/bb/이면 "bb"디렉터리 찾기
    Node* node = make_node(name, parent); // sname으로 노드 만들고 parent에 붙이기

    parent->child.push_back(node);
    update_parent(node, 1);
}

void cmd_rm(char path[PATH_MAXLEN + 1]) 
{
    Node* cur = find_node(path);
    cur->parent->child_cnt = cur->parent->child_cnt - cur->child_cnt - 1;

    for(auto it = cur->parent->child.begin(); it != cur->parent->child.end(); it++)
    {
        if(!strcmp((*it)->name, cur->name))
        {
            cur->parent->child.erase(it);
            break;
        }
    }
    update_parent(cur->parent, - cur->child_cnt - 1);
}

void cp_traverse(Node* srcDir, Node* node) //srcDir의 하위를 node의 하위로
{
    for(auto it = srcDir->child.begin(); it != srcDir->child.end(); it++)
    {
        Node* copy = make_node((*it)->name, node);
        copy->child_cnt = (*it)->child_cnt;
        node->child.push_back(copy);
        cp_traverse(*it, copy);
    }
}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) 
{
    Node* srcDir = find_node(srcPath); 
    Node* dstDir = find_node(dstPath); // dstDir의 하위에 srcDir과 그 하위 디렉토리 복사

    Node* node = make_node(srcDir->name, dstDir);
    node->child_cnt = srcDir->child_cnt;
    dstDir->child.push_back(node); // dstDir 하위에 srcDir 복사
    cp_traverse(srcDir, node); // node->child = srcDir->child , deep copy
    update_parent(node, node->child_cnt + 1);
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) 
{
    Node* srcDir = find_node(srcPath); 
    Node* dstDir = find_node(dstPath);

    for(auto it = srcDir->parent->child.begin(); it != srcDir->parent->child.end(); it++)
    {
        if(!strcmp((*it)->name, srcDir->name))
        {
            srcDir->parent->child.erase(it);
            break;
        }
    }
    update_parent(srcDir, - srcDir->child_cnt - 1);//srcDir->parent의 연결 끊기

    dstDir->child.push_back(srcDir);
    srcDir->parent = dstDir;
    update_parent(srcDir, srcDir->child_cnt + 1);
}

int cmd_find(char path[PATH_MAXLEN + 1]) 
{
	return find_node(path)->child_cnt;
}