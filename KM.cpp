
const int inf = 1e18;
// 0-base
struct KM {
    int n;
    vector<vector<int>> g;
    vector<int> lx, ly, slack;
    vector<int> match, visx, visy;
    KM(int n) : n(n), g(n, vector<int>(n)),
        lx(n), ly(n), slack(n), match(n), visx(n), visy(n) {}
    vector<int> & operator[](int i) { return g[i]; }
    bool dfs(int i, bool aug) {
        if(visx[i]) return false;
        visx[i] = true;
        for(int j = 0; j < n; j++) {
            if(visy[j]) continue;
            int d = lx[i] + ly[j] - g[i][j];
            if(d == 0) {
                visy[j] = true;
                if(match[j] == -1 || dfs(match[j], aug)) {
                    if(aug)
                        match[j] = i;
                    return true;
                }
            } else {
                slack[j] = min(slack[j], d);
            }
        }
        return false;
    }
    bool augment() {
        for(int j = 0; j < n; j++) if(!visy[j] && slack[j] == 0) {
            visy[j] = true;
            if(match[j] == -1 || dfs(match[j], false)) {
                return true;
            }
        }
        return false;
    }
    void relabel() {
        int delta = inf;
        for(int j = 0; j < n; j++) if(!visy[j]) delta = min(delta, slack[j]);
        for(int i = 0; i < n; i++) if(visx[i]) lx[i] -= delta;
        for(int j = 0; j < n; j++) {
            if(visy[j]) ly[j] += delta;
            else slack[j] -= delta;
        }
    }
    int solve() {
        for(int i = 0; i < n; i++) {
            lx[i] = 0;
            for(int j = 0; j < n; j++) lx[i] = max(lx[i], g[i][j]);
        }
        fill(ly.begin(), ly.end(), 0);
        fill(match.begin(), match.end(), -1);
        for(int i = 0; i < n; i++) {
            fill(slack.begin(), slack.end(), inf);
            fill(visx.begin(), visx.end(), false);
            fill(visy.begin(), visy.end(), false);
            if(dfs(i, true)) continue;
            while(!augment()) relabel();
            fill(visx.begin(), visx.end(), false);
            fill(visy.begin(), visy.end(), false);
            dfs(i, true);
        }
        int ans = 0;
        for(int j = 0; j < n; j++) if(match[j] != -1) ans += g[match[j]][j];
        return ans;
    }
};