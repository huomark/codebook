vector<int>ans;
string t1,t2;

int nxt[1000005];

void init(){
    nxt[0]=-1;int iu=-1;
    for(int i=1;i<t2.size();i++){
        while(iu!=-1&&t2[iu+1]!=t2[i]) iu=nxt[iu];
        if(t2[iu+1]==t2[i]) iu++;
        nxt[i]=iu;
    }
}

void go(){
    int iu=-1;
    for(int i=0;i<t1.size();i++){
        while(iu!=-1 && t2[iu+1]!=t1[i]) iu=nxt[iu];
        if(t2[iu+1]==t1[i]) iu++;
        if(iu==t2.size()-1) ans.pb(i+2-t2.size()), iu=nxt[iu];
    }
}