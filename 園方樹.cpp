const int N = 500005;
struct yftree{
    vector<int>node[N],nnode[N*2];
    int vis[N],low[N],dfn[N],dep[N*2];
    stack<int>st;
    int nn=0,iu=0;
    int n;
    void init(int _n){
        n=_n;
    }

    void add(int g,int h){
        node[g].pb(h);
        node[h].pb(g);
    }

    void dfs(int v,int pre){
        st.push(v);
        vis[v]=1;
        low[v]=dfn[v]=++iu;
        for(int k:node[v]){
            if(!vis[k]){
                dfs(k,v);
                low[v]=min(low[v],low[k]);
                if(low[k]>=dfn[v]){
                    nn++;
                    int tt;
                    while(1){
                        tt=st.top();st.pop();
                        nnode[nn+n].pb(tt);
                        nnode[tt].pb(nn+n);
                        if(tt==k) break;
                    }
                    tt=v;
                    nnode[nn+n].pb(tt);
                    nnode[tt].pb(nn+n);
                }
            }
            else{
                low[v]=min(low[v],dfn[k]);
            }
        }
    }

    void work(int n){
        for(int i=1;i<=n;i++){
            if(!vis[i]){
                int pre = iu;
                dfs(i, i);
                if(iu == pre + 1){
                    nn++;
                    nnode[nn+n].pb(i);
                    nnode[i].pb(nn+n);
                }
            }
        }
    }

};