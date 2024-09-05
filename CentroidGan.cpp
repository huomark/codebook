int n, k1, k2;
int bit[200005], sz[200005], dep[200005], cnt[200005], tot[200005];
vector<int> node[200005];
bool vis[200005];
ll ans = 0;
int mx = 0;
int ap = 0;
 
void upd(int now, int val){
    while(now <= k2) bit[now] += val, now += now & -now;
}
 
int val(int now){
    int ans = 0;
    while(now >= 1) ans += bit[now], now -= now & -now;
    return ans;
}
 
int range(int l, int r){
    return val(r) - val(l - 1);
}
 
void dfs(int v, int pre){
    dep[v] = dep[pre] + 1;
    if(dep[v] > k2) return;
    cnt[dep[v]]++;
    mx = max(mx, dep[v]);
 
    ans += range(max(k1 - dep[v], 1), k2 - dep[v]);
    
    if(dep[v] >= k1) ans++;
    for(int k1: node[v]){
        if(k1 == pre || vis[k1]) continue;
        dfs(k1, v);
    }
}
 
void szz(int v,int pre){
    sz[v] = 1;
    for(int k: node[v]){
        if(vis[k] || k == pre) continue;
        szz(k, v);
        sz[v] += sz[k];
    }
}
 
int get_centroid(int v, int pre, int tot){
    for(int k: node[v]){
        if(vis[k] || k == pre) continue;
        if(sz[k] > tot / 2) return get_centroid(k, v, tot);
    }
    return v;
}
 
 
void cd(int v, int pre){
    szz(v, v);
    int c = get_centroid(v, v, sz[v]);
    vis[c] = 1;
 
    ap = 0;
    for(int k1: node[c]){
        if(vis[k1]) continue;
        dep[k1] = 0, mx = 0;
        dfs(k1, k1);
        ap = max(ap, mx);
        for(int i = 1; i <= mx; i++) upd(i, cnt[i]), tot[i] += cnt[i], cnt[i] = 0;
    }
    for(int i = 1; i <= ap; i++) upd(i, -tot[i]), tot[i] = 0;

    for(int k: node[c]){
        if(vis[k] || sz[k] <= k1) continue;
        cd(k, c);
    }
}