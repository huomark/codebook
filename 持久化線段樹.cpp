const int N = 200005;
#define lc(ind) seg[ind].l 
#define rc(ind) seg[ind].r

int a[N];
struct node{
    int l,r,s;
}seg[N*25];

int root[N],id=0;

void build(int l,int r,int &ind){
    ind=++id;
    if(l==r){
        seg[ind].s=a[l];return;
    }
    int mid=l+r>>1;
    build(l,mid,lc(ind)),build(mid+1,r,rc(ind));
    seg[ind].s=seg[lc(ind)].s+seg[rc(ind)].s;
}

void upd(int l,int r,int xx,int val,int ind1,int &ind2){
    ind2=++id;seg[ind2]=seg[ind1];
    if(l==r) {
        seg[ind2].s=val;
        return;
    }
    int mid=l+r>>1;
    if(xx<=mid) upd(l,mid,xx,val,lc(ind1),lc(ind2));
    else upd(mid+1,r,xx,val,rc(ind1),rc(ind2));
    seg[ind2].s=seg[lc(ind2)].s+seg[rc(ind2)].s;
}

int val(int l,int r,int l1,int r1,int ind){
    if(l1<=l&&r<=r1) {
        return seg[ind].s;
    }
    int mid=l+r>>1;
    if(r1<=mid) return val(l,mid,l1,r1,lc(ind));
    else if(l1>mid) return val(mid+1,r,l1,r1,rc(ind));
    else return val(l,mid,l1,r1,lc(ind))+val(mid+1,r,l1,r1,rc(ind));
}