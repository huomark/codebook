vector<int>node[100005];
int df[100005],low[100005],vis[100005]={0};
stack<int>now;
vector<pair<int,int>>ans;
 
void dfs(int v,int pre){
    now.push(v);
    if(v==1) df[v]=1;
    else df[v]=df[pre]+1;
    low[v]=df[v];
    vis[v]=1;
    for(int g:node[v]){
        if(g==pre) continue;
        if(!vis[g]) {
            dfs(g,v);
            low[v]=min(low[v],low[g]);
        }
        else low[v]=min(low[v],df[g]);   
    }
    if(v!=1&&df[v]==low[v]){
        ans.pb({pre,v});
    }
}
