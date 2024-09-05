const int N = 3e5+5;
struct Seg{
    int seg[N*4]={0},la[N*4]={0};

    void init(int n){
        for(int i=1;i<=n*4;i++) seg[i]=0, la[i]=-1;
    }
    void push(int ind){
        int t=la[ind];la[ind]=0;
        la[ind*2]+=t,la[ind*2+1]+=t,seg[ind*2]+=t,seg[ind*2+1]+=t;
    }
    void upd(int l,int r,int l1,int r1,int val,int ind){
        if(l1<=l&&r<=r1) {
            seg[ind]+=val;
            la[ind]+=val;
            return;
        }
        int mid=l+r>>1;
        if(la[ind]!=-1) push(ind);
        if(r1<=mid) upd(l,mid,l1,r1,val,ind*2);
        else if(l1>mid) upd(mid+1,r,l1,r1,val,ind*2+1);
        else{
            upd(l,mid,l1,r1,val,ind*2);upd(mid+1,r,l1,r1,val,ind*2+1);
        }
        seg[ind]=seg[ind*2]+seg[ind*2+1];
    }

    int val(int l,int r,int l1,int r1,int ind){
        if(l1<=l&&r<=r1) return seg[ind];
        int mid=l+r>>1;
        if(la[ind]!=-1) push(ind);
        if(r1<=mid) return val(l,mid,l1,r1,ind*2);
        else if(l1>mid) return val(mid+1,r,l1,r1,ind*2+1);
        else return (val(l,mid,l1,r1,ind*2)+val(mid+1,r,l1,r1,ind*2+1));
        seg[ind]=seg[ind*2]+seg[ind*2+1];
    }
};