struct Big{
    vector<int>num;
    void init(int n){
        num.resize(n,0);
    }

    void upd(int x){
        int sz=0;
        int t=x;
        while(x) sz++,x/=10;
        if(sz==0){
            num.resize(1),num[0]=0;
            return;
        }
        num.resize(sz);sz=0;
        while(t) num[sz]=t%10,t/=10,sz++;
    }
};
Big operator+(Big bb,Big t2){
    vector<int>b=bb.num;
    vector<int>num=t2.num;
    int tot=0;
    vector<int>ans=num;
    int mx=max(ans.size(),b.size());
    ans.resize(mx+5);
    for(int i=0;i<b.size();i++){
        ans[i]+=b[i]+tot;
        tot=ans[i]/10,ans[i]%=10;
    }
    for(int i=b.size();i<ans.size();i++){
        ans[i]+=tot;
        tot=ans[i]/10,ans[i]%=10;
    }
    for(int i=ans.size()-1;i>=0;i--){
        if(i==0) ans.resize(1);
        if(ans[i]!=0){
            ans.resize(i+1);
            break;
        }
    }
    t2.num=ans;
    return t2;
}
Big operator*(Big bb,Big t2){
    vector<int>b=bb.num;
    vector<int>num=t2.num;
    vector<int>ans(b.size()+num.size()+50,0);
    for(int i=0;i<b.size();i++){
        for(int j=0;j<num.size();j++){
            ans[i+j]+=num[j]*b[i];
        }
    }

    int tot=0;
    for(int i=0;i<ans.size();i++){
        ans[i]+=tot;
        tot=ans[i]/10,ans[i]%=10;
    }
    int p;
    for(int i=ans.size()-1;i>=0;i--){
        if(i==0) p=1;
        if(ans[i]!=0) p=i+1;
        if(ans[i]!=0) break;
    }
    ans.resize(p);
    t2.num=ans;
    return t2;
}
Big max1(Big t1,Big t2){
    vector<int>g1=t1.num,g2=t2.num;
    if(g1.size()>g2.size()) return t1;
    if(g1.size()<g2.size()) return t2;
    for(int i=g1.size()-1;i>=0;i--){
        if(g1[i]!=g2[i]){
            if(g1[i]>g2[i]) return t1;
            else return t2;
        }
    }
    return t1;
}