const int N = 1005;
struct mat{
    int a[N][N];
    int vis[N],match[N]={0};

    int n;
    void init(int _n) {
        n=_n;
    }

    bool dfs(int now){
        for(int i=1;i<=n;i++) {
            
            if(a[now][i]&&!vis[i]){
                vis[i]=1;
                if(!match[i]||dfs(match[i])){
                    match[i]=now;
                    return 1;
                }
            }
        }
        return 0;
    }

    int solve(){

        int ans=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++) vis[j]=0;
            if(dfs(i)) ans++;
        }
        return ans;
    }
};
