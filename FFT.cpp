using cd = complex<double>;
const double PI = acos(-1);
struct poly{
    vector<cd>a;

    void FFT(vector<cd>&a, int n, int op){
        int r[n+1]={0};
        for(int i=0;i<n;i++) r[i]=r[i/2]/2+((i&1)?n/2:0);
        for(int i=0;i<n;i++){
            if(i<r[i]) swap(a[i],a[r[i]]);
        }
        for(int i=2;i<=n;i<<=1){
            cd w1({cos(PI*2/i),sin(PI*2/i)*op});
            for(int j=0;j<n;j+=i){
                cd wk({1,0});
                for(int k=j;k<j+i/2;k++){
                    cd x=a[k],y=a[k+i/2]*wk;
                    a[k]=x+y,a[k+i/2]=x-y;wk*=w1;
                }
            }
        }
    }

    vector<int>mul(poly g1, poly g2){// n是領導次方(0-base)
        auto t1 = g1.a, t2 = g2.a;
        int n=1;int m=t1.size()+t2.size()-2;
        while(n<=m) n<<=1;
        t1.resize(n), t2.resize(n);
        FFT(t1, n, 1), FFT(t2, n, 1);
        for(int i=0;i<n;i++) t1[i]*=t2[i];
        FFT(t1, n, -1);
        vector<int>ans;
        for(int i=0;i<=m;i++) ans.pb(t1[i].real()/n+0.5);
        return ans;
    }
};