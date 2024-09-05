const int N = 500005;
struct bcc_edge{
    vector<int>node[N+1], nnode[N+1], bcc[N+1];
    void add(int g,int h){
        node[g].pb(h);
        node[h].pb(g);
    }
    
    bool vis[N+1]={0};
    int id[N+1], dfn[N+1], low[N+1];
    stack<int>now;
    int iu=0;
    int num=0;

    void dfs(int v,int pre){
        dfn[v]=low[v]=++iu;
        now.push(v);
        vis[v]=1;
        int cc=0;
        for(int k:node[v]){
            if(k==pre&&cc==0) {
                cc++;
                continue;
            }
            if(!vis[k]) {
                dfs(k, v);
                low[v]=min(low[v],low[k]);
            }
            else low[v]=min(low[v],dfn[k]);
        }
        if(low[v]==dfn[v]){
            num++;
            while(1){
                int t = now.top();
                now.pop();
                bcc[num].pb(t);
                if(t==v) break;
            }
        }
    }

    void work(int n){
        for(int i=1;i<=n;i++){
            if(!vis[i]) dfs(i, i);
        }
    }
};