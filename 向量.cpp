
typedef pair<double,double> pdd;
typedef pair<int,int> pii;
double eps = 1e-9;

pdd operator+(pdd a,pdd b){
    return pdd(a.F+b.F,a.S+b.S);
}
pdd operator-(pdd a,pdd b){
    return pdd(a.F-b.F,a.S-b.S);
}
pdd operator*(pdd a,double b){
    return pdd(a.F*b,a.S*b);
}
pdd operator/(pdd a,double b){
    return pdd(a.F/b,a.S/b);
}

double dot(pdd a,pdd b){
    return a.F*b.F+a.S*b.S;
}
double cross(pdd a,pdd b){
    return a.F*b.S-a.S*b.F;
}
double abs2(pdd a){
    return dot(a,a);
}
double abs(pdd a){
    return sqrt(dot(a,a));
}

int sign(double a){
    return fabs(a) < eps ? 0: a>0 ? 1 : -1;
}
double ori(pdd a,pdd b,pdd c){
    return sign(cross(b-a,c-a));
}

bool collinearity(pdd p1,pdd p2,pdd p3){
    return sign(cross(p1-p3,p2-p3))==0;// in the same line
}

bool btw(pdd p1,pdd p2,pdd p3){
    if(!collinearity(p1,p2,p3)) return 0;
    return sign(dot(p1-p3,p2-p3))<=0;//in the same line and p1,p3 on the p2's both sides
}

bool ifintersect(pdd p1,pdd p2,pdd p3,pdd p4){
    int a123=ori(p1,p2,p3);
    int a124=ori(p1,p2,p4);
    int a341=ori(p3,p4,p1);
    int a342=ori(p3,p4,p2);
    if(btw(p1,p2,p3)||btw(p1,p2,p4)||btw(p3,p4,p1)||btw(p3,p4,p2)) return true;
    return a123*a124<0&&a341*a342<0;
}

pdd intersect(pdd p1,pdd p2,pdd p3,pdd p4){
    double a123=cross(p2-p1,p3-p1);
    double a124=cross(p4-p1,p2-p1);
    return (p4*a123+p3*a124)/(a123+a124);
}

pdd touin(pdd p1,pdd p2,pdd p3){
    return (p2-p1)*dot(p3-p1,p2-p1)/abs2(p2-p1);
}

vector<pii> convex_hull (vector<pii>dots){
    sort(dots.begin(),dots.end());
    vector<pii>hull;
    for(int i=0;i<2;i++){
        int g=hull.size();
        for(int j=0;j<(int)(dots.size());j++){
            while(hull.size()-g>=2&&ori(hull[hull.size()-2],hull.back(),dots[j])<0) hull.pop_back();
            hull.pb(dots[j]);
            // dbg(dots[j].F,dots[j].S,hull.size())
        }
        hull.pop_back();
        // for(auto gg:hull) cout<<gg.F<<" "<<gg.S<<"a\n";
        reverse(dots.begin(),dots.end());
    }
    return hull;
}

int area(pair<int,int>r1,pair<int,int>r2){
    return r2.F*r1.S-r1.F*r2.S;
}

bool cmpankle(pdd a,pdd b){
    #define is_neg(k) (sign(k.S)<0||(sign(k.S)==0&&sign(k.F)<0))

    int t1=is_neg(a),t2=is_neg(b);
    if(t1!=t2) return t1<t2;
    if(sign(cross(a,b))==0) return abs2(a)<abs2(b);
    return sign(cross(a,b))>0;
}