struct chinese_remainder{
    int n;
    void init(int y){
        n=y;
    }
    int extgcd(int t1,int t2, int &x, int &y){
        if(t2==0) {
            x=1, y=0;return t1;
        }
        int g, h;
        int d=extgcd(t2, t1%t2, g, h);
        x=h, y = g-t1/t2*h;
        return d;
    }
    int gogo(vector<int>mm, vector<int>re){//mol , remain
        int M=1;
        for(int i=0;i<n;i++) M*=mm[i];
        int ans=0;
        for(int i=0;i<n;i++){
            int c=M/mm[i], x, y;
            extgcd(c, mm[i], x, y);
            ans=(ans+c*x%M*re[i]%M)%M;
        }
        return (ans%M+M)%M;
    }
};