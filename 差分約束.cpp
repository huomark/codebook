const int N = 5005;

vector<pair<int,int>> node[N];
vector<tuple<int,int,int>> all;
int dis[N];
int n, m;

bool spfa(){
    for(int i = 1; i <= n; i++) dis[i] = 1e9;
    dis[1] = 0;
    for(int i = 1; i <= n; i++){
        for(auto [t1, t2, t3]: all){
            if(dis[t1] > dis[t2] + t3) dis[t1] = dis[t2] + t3;
        }
    }

    for(auto [t1, t2, t3]: all){
        if(dis[t1] > dis[t2] + t3) return 1;
    }
    return 0;
}

void solve(){
    cin >> n >> m;


    for(int i = 1; i <= m; i++){
        int g, h, c;
        cin >> g >> h >> c;
        all.pb({g, h, c});
        node[h].pb({g, c});
    }
    if(spfa()){
        cout<<"NO\n";
        return;
    }
    for(int i = 1; i <= n; i++) dis[i] = 0;
    priority_queue<pair<int, int>,vector<pair<int, int>>,greater<>>now;
    for(int i = 1; i <= n; i++) now.push({dis[i], i});
    while(now.size()){
        auto t = now.top(); now.pop();
        if(t.F != dis[t.S]) continue;
        for(auto g: node[t.S]){
            if(dis[g.F]>t.F + g.S){
                dis[g.F] = t.F + g.S;
                now.push({dis[g.F], g.F});
            }
        }
    }

    for(int i = 1; i <= n; i++) cout<<dis[i] << " ";cout<< "\n";
}