#include<bits/stdc++.h>
using namespace std;

// #define int long long
// 2e7 -> 884ms in luogu

int z[20000005],p[20000005];
void Z(string a){
    z[0]=a.size();
    for(int i=1,l,r=0;i<a.size();i++){
        if(i<=r) z[i]=min(z[i-l],r-i+1);
        while(a[z[i]]==a[i+z[i]]) z[i]++;
        if(z[i]+i-1>r) r=z[i]+i-1,l=i; 
    }
}

void Z2(string t1,string t2){
    for(int i=0,l,r=-1;i<t1.size();i++){
        if(i<=r) p[i]=min(r-i+1,z[i-l]);
        while(p[i]<t2.size()&&i+p[i]<t1.size()&&t1[i+p[i]]==t2[p[i]]) p[i]++;
        if(r<i+p[i]-1) r=i+p[i]-1,l=i;
    }
}

signed main(){
    string t1,a;
    cin>>t1>>a;
    Z(a);
    Z2(t1,a);
    
}