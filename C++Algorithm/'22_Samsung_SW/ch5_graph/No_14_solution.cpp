int map[40][2];

void dfs_init(int N, int path[100][2])
{
    for(int i = 0; i < N; i++)
    {
        map[i][0] = path[i][0];
        map[i][1] = path[i][1];
    }
}

int rec_dfs(int root, int n)
{
    if(n > root) return n;

    int ans = -1;
    for(int i = 0; i < 40; i++)
    {
        if(map[i][0] == n)
        {
            ans = rec_dfs(root, map[i][1]); 
            if(ans != -1) return ans;
        } 
    }
    return ans;
}

int dfs(int n)
{
    int ans = rec_dfs(n, n);
	return ans;
}
