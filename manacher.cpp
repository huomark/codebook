
vector<int>manacher(string a){
    vector<int>d(a.size(),0);
    d[0]=1;
    for(int i=1,l=0,r=0;i<a.size();i++){
        if(i<=r) d[i]=min(d[r-i+l],r-i+1);
        while(i+d[i]<a.size()&&i-d[i]>=0&&a[i+d[i]]==a[i-d[i]]) d[i]++;
        if(d[i]+i-1>r) l=i-d[i]+1,r=d[i]+i-1;
    }
    return d;
}

void upd(string &t){
    string hh;
    for(int i=0;i<t.size();i++) hh+='#',hh+=t[i];
    hh+='#';hh+='$';
    t=hh;
}