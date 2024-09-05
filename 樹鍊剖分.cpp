
const int N = 500005;
struct TreeLan{
    int seg[N*4]={0};
    int la[N*4]={0};
    std::vector<int>node[N];
    int iu=0;
    int sz[N],mxson[N]={0},pre[N],top[N],id[N],dep[N];
    void dfs1(int v,int p){
        sz[v]=1,pre[v]=p;
        dep[v]=dep[p]+1;
        for(int k:node[v]){
            if(k==p) continue;
            dfs1(k,v);
            if(sz[mxson[v]]<sz[k]){
                mxson[v]=k;
            }
            sz[v]+=sz[k];
        }
    }
    void dfs2(int v,int tt){
        id[v]=++iu;
        top[v]=tt;
        if(mxson[v]==0) return;
        dfs2(mxson[v],tt);
        for(int k:node[v]){
            if(k==mxson[v]||k==pre[v]) continue;
            dfs2(k,k);
        }
    }

    void add(int g,int h){
        node[g].push_back(h),node[h].push_back(g);
    }
    int nn;
    void build(int n, int r){
        nn=n;
        dfs1(r,r);
        dfs2(r,r);
    }

    void push(int l,int r,int ind){
        int p=la[ind];la[ind]=0;
		int mid=l+r>>1;
        la[ind*2]+=p,la[ind*2+1]+=p;
        seg[ind*2]+=p*(mid-l+1),seg[ind*2+1]+=p*(r-mid);
    }

    void supd(int l,int r,int l1,int r1,int val,int ind){
        if(l1<=l&&r<=r1) {
            seg[ind]+=val*(r-l+1),la[ind]+=val;return;
        }   

        int mid=l+r>>1;
        if(la[ind]) push(l,r,ind);
        if(r1<=mid) supd(l,mid,l1,r1,val,ind*2);
        else if(l1>mid) supd(mid+1,r,l1,r1,val,ind*2+1);
        else{
            supd(l,mid,l1,r1,val,ind*2);supd(mid+1,r,l1,r1,val,ind*2+1);
        }
        seg[ind]=(seg[ind*2]+seg[ind*2+1])%p;
    }

    int sval(int l,int r,int l1,int r1,int ind){
        if(l1<=l&&r<=r1) return seg[ind]%p;
        int mid=l+r>>1;
        if(la[ind]) push(l,r,ind);
        if(r1<=mid) return sval(l,mid,l1,r1,ind*2);
        else if(l1>mid) return sval(mid+1,r,l1,r1,ind*2+1);
        else return (sval(l,mid,l1,r1,ind*2)+sval(mid+1,r,l1,r1,ind*2+1))%p;
    }
 
    void upd(int g,int h,int vv){
        int t1=top[g],t2=top[h];
        while(t1!=t2){
            if(dep[t1]<dep[t2])
                swap(t1,t2),swap(g,h);

            int i1=id[t1],i2=id[g];
            if(i1>i2) swap(i1,i2);
            supd(1,nn,i1,i2,vv,1);
            g=pre[t1],t1=top[g];
        }
        if(dep[g]<dep[h]){
            swap(g,h);
        }
        int i1=id[g],i2=id[h];
        if(i1>i2) swap(i1,i2);
        supd(1,nn,i1,i2,vv,1);
    }
    int query(int g,int h){
        int tot=0;
        int t1=top[g],t2=top[h];
        while(t1!=t2){
            if(dep[t1]<dep[t2])
                swap(t1,t2),swap(g,h);

            int i1=id[t1],i2=id[g];
            if(i1>i2) swap(i1,i2);
            tot+=(sval(1,nn,i1,i2,1));
            tot%=p;
            g=pre[t1],t1=top[g];
        }
        if(dep[g]<dep[h]){
            swap(g,h);
        }
        int i1=id[g],i2=id[h];
        if(i1>i2) swap(i1,i2);
        tot+=sval(1,nn,i1,i2,1);
        return tot%p;
    }

    void utree(int v, int val){
        supd(1, nn, id[v], id[v]+sz[v]-1, val, 1);
    }

    int qtree(int v){
        return sval(1, nn, id[v], id[v]+sz[v]-1, 1);
    }
}iu;