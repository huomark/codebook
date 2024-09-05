
const int N=1000005;

int trie[N][26];
struct AC_automaton{

    // bool end[N]={0};
    int nxt[N]={0};
    int cnt[N]={0};
    int iu=0;
    void init(){
        for(int i=0;i<N;i++) for(int j=0;j<26;j++) trie[i][j]=0;
    }
    void tbuild(string g){
        int now=0;
        for(int i=0;i<g.size();i++){
            if(!trie[now][g[i]-'a']){
                trie[now][g[i]-'a']=++iu;
            }
            now=trie[now][g[i]-'a'];
        }
        // end[now]=1;
        cnt[now]++;
    }

    void build(){
        queue<int>now;
        for(int i=0;i<26;i++) {
            if(trie[0][i]) now.push(trie[0][i]);
        }
        // now.push(0);
        while(now.size()){
            int tt=now.front();now.pop();
            for(int i=0;i<26;i++){
                int ch=trie[tt][i];
                if(ch) nxt[ch]=trie[nxt[tt]][i],now.push(ch);
                else trie[tt][i]=trie[nxt[tt]][i];
            }
        }
    }

    int gogo(string g){
        int ans=0;
        int now=0;
        for(int i=0;i<g.size();i++){
            now=trie[now][g[i]-'a'];
            for(int j=now;j&&~cnt[j];j=nxt[j]){
                ans+=cnt[j];
                cnt[j]=-1;
            }
        }
        return ans;
    }

};