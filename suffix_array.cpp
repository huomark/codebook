string s; // need to push_back ' '
bool cmp(int x, int y){
    return s[x] < s[y];
}
void counting_sort(vector<int> rk, vector<int>& suffix){
    vector<vector<int> > cnt(s.size());
    for(int i = 0; i < s.size(); i++){
        cnt[rk[suffix[i]]].push_back(suffix[i]);
    }
    suffix.clear();
    for(int i = 0; i < s.size(); i++){
        for(auto j : cnt[i]){
            suffix.push_back(j);
        }
    }
}
void suffix_array(vector<int>& suffix){
    vector<int> rk;
    rk.resize(s.size());
    suffix.resize(s.size());
    int n = s.size();
    for(int i = 0; i < n; i++){
        suffix[i] = i;
    }
    sort(suffix.begin(), suffix.end(), cmp);
    rk[suffix[0]] = 0;
    for(int i = 1; i < n; i++){
        rk[suffix[i]] = rk[suffix[i - 1]] + (s[suffix[i]] != s[suffix[i  - 1]]);
    }
    for(int i = 0; (1 << i) < n; i++){
        for(int j = 0; j < n; j++){
            suffix[j] = (suffix[j] - (1 << i) + n) % n;
        }
        counting_sort(rk, suffix);
        vector<int> new_rk(n);
        new_rk[suffix[0]] = 0;
        for(int j = 1; j < n; j++){
            pair<int, int> pre = {rk[suffix[j - 1]], rk[(suffix[j - 1] + (1 << i)) % n]};
            pair<int, int> now = {rk[suffix[j]], rk[(suffix[j] + (1 << i)) % n]};
            new_rk[suffix[j]] = new_rk[suffix[j - 1]] + (pre != now);
        }
        rk = new_rk;
    }
}
void get_lcp(vector<int> suffix, vector<int>& lcp){
    lcp.resize(s.size());
    int k = 0;
    vector<int> id(suffix.size());
    for(int i = 0; i < suffix.size(); i++){
        id[suffix[i]] = i;
    }
    for(int i = 0; i < (int)s.size() - 1; i++){
        if(k){
            k = k - 1;
        }
        while(k < min((int)s.size() - i, (int)s.size() - suffix[id[i] - 1])
            && s[i + k] == s[suffix[id[i] - 1] + k])
                k++;
        lcp[id[i]] = k;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> s;
    int n = s.size();
    s.push_back(' ');
    vector<int> suffix;
    suffix_array(suffix);
    vector<int> lcp;
    get_lcp(suffix, lcp);
}
