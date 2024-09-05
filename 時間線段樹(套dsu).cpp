#include<bits/stdc++.h>
using namespace std;

#define pb push_back

const int N=3e5+5;

int dsu[N],sz[N];
int cc=0;
vector<tuple<int,int,int>>go;
vector<tuple<int,int,int,int>>all;
int ans[N];

int find(int g){
    while(dsu[g]!=g) g=dsu[g];
    return g;
}

bool un(int g,int h){
    g=find(g),h=find(h);
    if(g==h) return 0;
    cc--;
    if(sz[g]>sz[h]) swap(g,h);
    go.pb({g,dsu[g],sz[g]});
    go.pb({h,dsu[h],sz[h]});
    dsu[g]=h,sz[h]+=sz[g];
    return 1;
}

void undo(){
    auto [t1,t2,t3]=go.back();go.pop_back();
    dsu[t1]=t2,sz[t1]=t3;
}

vector<pair<int,int>>segt[N*4];

void upd(int l,int r,int l1,int r1,int ind,pair<int,int>tt){
    if(l1<=l&&r<=r1){
        segt[ind].pb(tt);
        return;
    }
    int mid=l+r>>1;
    if(r1<=mid) upd(l,mid,l1,r1,ind*2,tt);
    else if(l1>mid) upd(mid+1,r,l1,r1,ind*2+1,tt);
    else{
        upd(mid+1,r,l1,r1,ind*2+1,tt);upd(l,mid,l1,r1,ind*2,tt);
    }
}

void tra(int l,int r,int ind){
    int iu=0;
    while(segt[ind].size()){
        auto [g,h]=segt[ind].back();segt[ind].pop_back();
        if(un(g,h))
        iu++;
    }
    if(l==r){
        ans[l]=cc;
        while(iu--){
            undo();
            undo();
            cc++;
        }
        return;
    }
    int mid=l+r>>1;
    tra(l,mid,ind*2);tra(mid+1,r,ind*2+1);

    while(iu--){
        undo();
        undo();
        cc++;
    }
}