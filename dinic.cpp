const int N=505;
struct dinic{
    int s,t;
    int n;
    void init(int _n,int t1,int t2){
        s=t1,t=t2;n=_n;
    }
    struct Edge{
        int to,cap,flow;
    };
    vector<Edge>edge;
    vector<int>node[N+5];
    bool vis[N+5]={0};
    int cur[N+5],dep[N+5];

    void add(int g,int h,int c){
        // if(g==0){dbg(g,edge.size())}
        node[g].pb(edge.size());
        edge.pb({h,c,0});
        node[h].pb(edge.size());
        edge.pb({g,c,0});
    }
    bool bfs(){
        queue<int>now;
        for(int i=0;i<n;i++) cur[i]=0, dep[i]=0, vis[i]=0;
        now.push(s);
        vis[s]=1;dep[s]=1;
        while(now.size()){
            int tt=now.front();now.pop();
            for(int &i=cur[tt];i<node[tt].size();i++){
                auto [t1,t2,t3]=edge[node[tt][i]];
                if(!vis[t1]&&t2>t3){
                    dep[t1]=dep[tt]+1;
                    vis[t1]=1,now.push(t1);
                }
            }
        }
        return vis[t];
    }

    int dfs(int v,int tot){
        if(v==t||tot==0) return tot;
        int ff=0;
        for(int &i=cur[v];i<node[v].size();i++){
            auto [t1,t2,t3]=edge[node[v][i]];
            if(t2>t3&&dep[t1]==dep[v]+1){
                int g=dfs(t1,min(tot-ff,t2-t3));
                ff+=g;edge[node[v][i]].flow+=g,edge[node[v][i]^1].flow-=g;
                if(ff==tot) return ff;
            }
        }
        if(ff==0) dep[v]=0;
        return ff;
    }

    int flow(){
        int ans=0;
        while(bfs()){
            for(int i=0;i<n;i++) cur[i]=0;
            ans+=dfs(s,1e18);
        }
        return ans;
    }

    vector<int>ans(){
        for(int i=0;i<n;i++) cur[i]=0, vis[i]=0;
        che(s);
        vector<int>g;
        for(int i=0;i<n;i++){
            if(vis[i]) g.pb(i);
        }
        return g;
    }

    void dd(int u){
        for(int &i=cur[u];i<node[u].size();i++){
            auto [t1,t2,t3]=edge[node[u][i]];
            if(t1==s) continue;
            if(t2==t3){
                
            }
        }
    }

    void che(int v){
        vis[v]=1;
        for(int &i=cur[v];i<node[v].size();i++){
            auto [t1,t2,t3]=edge[node[v][i]];
            if(t2!=t3&&!vis[t1]) dd(t1);
        }
    }

};