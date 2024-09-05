for(int i=1;i<=n;i++){
    if(!a[i][i]){
        bool ok=0;
        int oo;
        for(int j=i+1;j<=n;j++){
            if(a[j][i]) {
                ok=1;
                oo=j;
                break;
            }
        }
        if(!ok) continue;
        for(int j=1;j<=n+1;j++) swap(a[oo][j],a[i][j]);
    }
    int y=a[i][i];
    for(int j=1;j<=n+1;j++){
        a[i][j]*=ff(y,m-2);
        a[i][j]%=m;
    }
    for(int j=1;j<=n;j++){
        if(j==i) continue;
        int pp=a[j][i];
        for(int k=1;k<=n+1;k++){
            a[j][k]=(a[j][k]-a[i][k]%m*pp%m+m)%m;
        }
    }
}