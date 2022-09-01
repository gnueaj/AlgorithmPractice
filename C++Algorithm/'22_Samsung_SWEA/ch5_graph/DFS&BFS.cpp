#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<utility>

using namespace std;

vector<int> map[1001];

bool visited[1001];//FALSE
int parent[1001];//NIL
int dist[1001];//0
int s_time[1001];//0
int f_time[1001];//0

int dfs_time = 0;

void dfs(int u)
{
	dfs_time++;
	s_time[u] = dfs_time;
	visited[u] = true;
	cout << u << ' ';
	for (int i = 0; i < map[u].size(); i++)
	{
		int v = map[u][i];
		if (visited[v] == false)
		{
			parent[v] = u;
			dfs(v);
		}
	}
	f_time[u] = dfs_time;
}
void dfs_stack(int from)
{
	stack<int> s;
	s.push(from);
	visited[from] = true;
	printf("%d ", from);

	while (!s.empty())
	{
		int from = s.top(); s.pop();
		for (int i = 0; i<map[from].size(); i++)
		{
			int to = map[from][i];
			if (visited[to] == false)
			{
				printf("%d ", to);
				visited[to] = true;
				s.push(from);
				s.push(to);
				break;
			}
		}
	}
}
void bfs(int start)
{
	queue<int> q;

	cout << start << ' ';
	visited[start] = true;
	parent[start] = 0;
	dist[start] = 0;
	q.push(start);

	while (!q.empty())
	{
		int u = q.front(); q.pop();
		for (int i = 0; i < map[u].size(); i++)
		{
			int v = map[u][i];
			if (visited[v] == false)
			{
				cout << v << ' ';
				visited[v] = true;
				dist[v] = dist[u] + 1;
				parent[v] = u;
				q.push(v);
			}
		}
	}
	cout << '\n';
}

int main()
{
	int v, e;
	cin >> v >> e;
	int start;
	cin >> start;

	while (e--)
	{
		int from, to;
		cin >> from >> to;
		map[from].push_back(to);
		map[to].push_back(from);
	}
	for (int i = 1; i <= v; i++)
		sort(map[i].begin(), map[i].end());

	dfs(start);
	cout << '\n';
	memset(parent, 0, sizeof(parent));
	memset(visited, false, sizeof(visited));
	bfs(start);
}