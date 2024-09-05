random_device rnd;
mt19937_64 rng(rnd());
struct treap{
    treap *l, *r;
    int pri, size,mn, mx, val, sum;
    bool tag;
    treap(int _val) : l(NULL), r(NULL), pri(rng()), size(1), mn(_val), mx(_val), sum(_val), val(_val), tag(false) {};
};

int sz(treap *t){
    return t? t->size: 0;
}

int sum(treap *t){
    return t? t->sum: 0;
}

int mx(treap *t){
    return t? t->mx : -1e18;
}
int mn(treap *t){
    return t? t->mn : 1e18;
}

void pull(treap *&t){
    t->size = sz(t->l)+sz(t->r)+1;
    t->mx = max({t->val, mx(t->l), mx(t->r)});
    t->mn = min({t->val, mn(t->l), mn(t->r)});
}

void push(treap *&t){
    if(!t->tag) return;
    if(t->l){
        swap(t->l->l,t->l->r);
        t->l->tag ^= 1;
    }
    if(t->r){
        swap(t->r->l,t->r->r);
        t->r->tag ^= 1;
    }
    t->tag = 0;
}

treap *merge(treap *a,treap *b){
    if(!a || !b) return a? a: b;
    if(a->pri > b->pri){
        push(a);
        a->r = merge(a->r,b);
        pull(a);
        return a;
    }
    else{
        push(b);
        b->l = merge(a,b->l);
        pull(b);
        return b;
    }
}

void split_size(treap *t, int k, treap *&a, treap *&b){ // 用size切
    if(!t) {a = b = NULL;return;}
    push(t);
    if(sz(t->l) + 1 <= k){
        a = t;
        split_size(t->r,k - sz(t->l) - 1,a->r,b);
        pull(a);
    }
    else{
        b = t;
        split_size(t->l,k,a,b->l);
        pull(b);
    }
}

void split_val(treap *t, int k, treap *&a, treap *&b){//用值切
    if(!t) {a = b = NULL;return;}
    push(t);
    if(t->val <= k){
        a = t;
        split_val(t->r, k, a->r, b);
        pull(a);
    }
    else{
        b = t;
        split_val(t->l,k,a,b->l);
        pull(b);
    }
}

void split_one(treap *t, int k, treap *&a, treap *&b){//切出恰一個值
    if(!t) {a = b = NULL;return;}
    push(t);
    if(t->val <= k && sz(t->l) + 1 == 1){
        a = t;
        split_one(t->r, -1e18, a->r, b);
        pull(a);
    }
    else{
        b = t;
        split_one(t->l,k,a,b->l);
        pull(b);
    }
}

treap *root;

void reverse(int l, int r){
    treap *tl = NULL, *tr = NULL;
    split_size(root, l - 1, tl, root);
    split_size(root, r - l + 1, root, tr);
    swap(root->l,root->r);
    root->tag ^= 1;
    root = merge(merge(tl, root), tr);
}

int val(int l,int r){
    treap *tl = NULL, *tr = NULL;
    split_size(root, l - 1, tl, root);
    split_size(root, r - l + 1, root, tr);
    int ans = sum(root);
    root = merge(merge(tl, root), tr);
    return ans;
}

void ins(int v){
    treap *tl, *tr;
    split_val(root, v - 1, tl, root);
    split_one(root, v, root, tr);

    root = merge(root, new treap(v));
    root = merge(merge(tl, root), tr);
}

void era(int v){
    treap *tl, *tr;
    split_val(root, v - 1, tl, root);
    split_one(root, v, root, tr);
    root = merge(tl, tr);
}

int v1(int t){
    treap *tl, *tr;
    split_val(root, t - 1, tl, root);
    int ans = sz(tl);
    root = merge(tl, root);
    return ans + 1;
}

int rank1(int x){
    treap *tl, *tr;
    split_size(root, x - 1, tl, root);
    int ans = mn(root);
    root = merge(tl, root);
    return ans;
}

int pre(int x){
    treap *tl, *tr;
    split_val(root, x - 1, tl, root);
    int ans = mx(tl);
    root = merge(tl, root);
    return ans;
}
int suf(int x){
    treap *tl, *tr;
    split_val(root, x, tl, root);
    int ans = mn(root);
    root = merge(tl, root);
    return ans;
}