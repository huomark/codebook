
const int N=8400005;
int a[N],b[N];
int r[N]={0};
int ans[6000005];
const int MOL = 998244353;//2281701377 2^27

int g=3;
int ff(int g1,int h){
    if(h==0) return 1;
    if(h==1) return g1;
    if(h%2) return g1*ff(g1,h-1)%MOL;
    else return ff(g1,h/2)*ff(g1,h/2)%MOL;
}

int gi=ff(g,MOL-2);

void butterfly(int a[],int n){
    for(int i=0;i<n;i++){
        r[i]=r[i/2]/2+(i&1?n/2:0);
    }
    for(int i=0;i<n;i++){
        if(i<r[i]) swap(a[i],a[r[i]]); 
    }
}

void NTT(int a[],int n){
    butterfly(a,n);
    for(int i=2;i<=n;i<<=1){// width
        int g1;
        g1=ff(3,(MOL-1)/i);
        for(int j=0;j<n;j+=i){//left
            int gk=1;
            for(int k=j;k<j+i/2;k++){
                int x=a[k],y=a[k+i/2]*gk-a[k+i/2]*gk/MOL*MOL;
                a[k]=(x+y)-(x+y)/MOL*MOL,a[k+i/2]=(x-y+MOL)%MOL;
                gk*=g1,gk-=gk/MOL*MOL;
            }
        }
    }
}