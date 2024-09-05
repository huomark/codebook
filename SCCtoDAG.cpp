const int N = 1005;
struct scc{
    vector<int>node[N],nnode[N], scc[N];

    int low[N],dfn[N],vis[N],id[N], pol[N]={0};
    int iu=0,cnt=0;
    stack<int>now;

    void init(int n){
        for(int i=1;i<=n;i++) vis[i]=0, node[i].clear(), nnode[i].clear(), scc[i].clear(), id[i]=0;
        cnt=0, iu=0;
    }

    void dfs(int v){
        vis[v]=1,low[v]=dfn[v]=++iu;
        now.push(v);
    
        for(int k:node[v]){
            if(!vis[k]){
                dfs(k);
                low[v]=min(low[v],low[k]);
            }
            else if(!id[k]){
                low[v]=min(low[v],dfn[k]);
            }
        }
    
        if(low[v]==dfn[v]){
            cnt++;
            while(1){
                int t=now.top();now.pop();
                id[t]=cnt;
                scc[cnt].pb(t);
                if(t==v) break;
            }
        }
    }

    void add(int g,int h){
        node[g].pb(h);
    }

    void work(int n){
        for(int i=1;i<=n;i++){
            if(!vis[i]) dfs(i);
        }
        for(int i=1;i<=cnt;i++){
            for(int ii:scc[i]){
                for(int j:node[ii]){
                    if(id[j]!=i){
                        nnode[i].pb(id[j]);
                        pol[id[j]]++;
                    }
                }
            }
        }
    }
}iu;