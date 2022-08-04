#define MAX_N 1000
#include<iostream>
struct xy{
    int x, y;
    xy(int x, int y):x(x), y(y){}
    xy(){};
};

int front;
int rear;
xy queue[MAX_N];
int graph[11][11];

void queueInit(void)
{
	front = 0;
	rear = 0;
}

int queueIsEmpty(void)
{
	return (front == rear);
}

int queueIsFull(void)
{
	if ((rear + 1) % MAX_N == front)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void queueEnqueue(xy x)
{
	queue[rear] = x;
	rear++;
	if (rear == MAX_N)
	{
		rear = 0;
	}

	//return 1;
}

xy queueDequeue()
{
	xy ret = queue[front];
	front++;
	if (front == MAX_N)
	{
		front = 0;
	}
	return ret;
}


bool check[11][11];
int dist[11][11];
int dx[] = {-1,0, 0, 1};
int dy[] = {0, 1, -1, 0};
int size;
void bfs_init(int map_size, int map[10][10]) 
{
    size = map_size;
    queueInit();
    for(int i = 0; i < map_size; i++)
    {
        for(int j = 0; j < map_size; j++)
        {
            graph[i+1][j+1] = map[i][j];
            check[i+1][j+1] = false;
            dist[i+1][j+1] = 0;
        }
    }
}


bool valid(int x, int y)
{
    return x >= 1 && y >= 1 && x <= size && y <= size;
}

int bfs(int y1, int x1, int y2, int x2) {
    queueInit();
    for(int i = 1; i<=10; i++)
    for(int j = 1; j<=10; j++) 
        check[i][j] = dist[i][j]= 0;
    queueEnqueue(xy(x1,y1));
    dist[x1][y1] = 0;
    check[x1][y1] = true;

    dist[x2][y2] = -1;
    while(!queueIsEmpty())
    {
       
        xy from = queueDequeue();
        
        for(int i = 0; i < 4; i++)
        {
            int tox = from.x +dx[i];
            int toy = from.y +dy[i];
        
            if(valid(tox, toy) && !check[tox][toy] && !graph[tox][toy])
            {
                check[tox][toy] = true;
                queueEnqueue(xy(tox,toy));
                dist[tox][toy] = dist[from.x][from.y] + 1;
            }
            if(dist[x2][y2] != -1) return dist[x2][y2];
        }

    }

    return dist[x2][y2];
}