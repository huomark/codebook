int seg[800005],a[200005],la[800005]={0};
void build(int l,int r,int ind){
    if(l==r){
        seg[ind]=a[l];
        return;
    }
    int mid=l+r>>1;
    build(l,mid,ind*2),build(mid+1,r,ind*2+1);
    seg[ind]=seg[ind*2]+seg[ind*2+1];
}

void push(int l,int r,int ind){
    int p=la[ind];la[ind]=0;
    int mid=l+r>>1;
    la[ind*2]+=p,la[ind*2+1]+=p,seg[ind*2]+=(mid-l+1)*p,seg[ind*2+1]+=(r-l)*p;
}

void upd(int l,int r,int l1,int r1,int val,int ind){
    if(l1<=l&&r<=r1){
        seg[ind]+=val*(r-l+1);
        la[ind]+=val;
        return;
    }
    int mid=l+r>>1;
    if(la[ind]) push(l,r,ind);
    if(r1<=mid) upd(l,mid,l1,r1,val,ind*2);
    else if(l1>mid) upd(mid+1,r,l1,r1,val,ind*2+1);
    else{
        upd(l,mid,l1,r1,val,ind*2);
        upd(mid+1,r,l1,r1,val,ind*2+1);    
    }
    seg[ind]=seg[ind*2]+seg[ind*2+1];
}

int val(int l,int r,int l1,int r1,int ind){
    if(l1<=l&&r<=r1) return seg[ind];
    int mid=l+r>>1;
    if(la[ind]) push(l,r,ind);
    if(r1<=mid) return val(l,mid,l1,r1,ind*2);
    else if(l1>mid) return val(mid+1,r,l1,r1,ind*2+1);
    else return val(l,mid,l1,r1,ind*2)+val(mid+1,r,l1,r1,ind*2+1);
    
}