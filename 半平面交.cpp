
double eps = 1e-9;
struct pt{
    double x,y;
    pt (double _x,double _y) : x(_x),y(_y){};
};
pt operator+(pt a,pt b){
    return {a.x+b.x,a.y+b.y};
}
pt operator-(pt a, pt b){
    return {a.x-b.x,a.y-b.y};
}

pt operator*(pt a, double v){
    return {a.x*v,a.y*v};
}
double operator^(pt a, pt b){
    return a.x*b.y-a.y*b.x; 
}
// ba cross ca
double cross(pt a, pt b, pt c){
    return (b-a)^(c-a);
}

struct li{
    pt s,e;
    bool up(){
        if(abs(e.y-s.y)<eps&&e.x-s.x<0) return 1;
        return e.y-s.y > 0;
    }
};
double cross(li a,li b){
    pt g=b.e-b.s;
    g=a.s+g;
    return cross(a.s,g,a.e);
}

li operator-(li a,li b){
    return {b.s-a.s,b.e-a.e};
}

pt intersect(li a,li b){
    double g1,g2;
    g1=(cross(a.s,b.e,b.s));
    g2=(cross(a.e,b.s,b.e));
    return a.s+(a.e-a.s)*(g1/(g1+g2));
}

bool right(li a,li b,li c){
    pt p = intersect(b,c);
    return cross(a.s,a.e,p)<0;
}

bool sa(li a,li b){
    pt g=b.e-b.s;
    g=a.s+g;
    // cout<<cross(a.s,a.e,g)<<" "<<eps<<"\n";
    return abs(cross(a.s,a.e,g))<eps;
}

bool cmpankle(li t1,li t2){
    if(t1.up()!=t2.up()){
        return t1.up()<t2.up();
    }
    if(abs(cross(t1,t2))<eps){
        return ((t1.e-t1.s)^(t2.e-t1.s))<0;
    }
    return cross(t1,t2)<0;
}

deque<li>halfintersect(vector<li>all){
    deque<li>now;
    sort(all.begin(),all.end(),cmpankle);

    now.pb(all[0]);

    for(int i=1;i<all.size();i++){
        if(sa(all[i],all[i-1])) continue;
        while(now.size()>1&&right(all[i],now.back(),now[now.size()-2])) now.pop_back();
        while(now.size()>1&&right(all[i],now[0],now[1])) now.pop_front();
        now.pb(all[i]);
    }
    while(now.size()>2&&right(now[0],now.back(),now[now.size()-2])) now.pop_back();
    return now;
}