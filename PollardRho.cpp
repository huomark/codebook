#include<iostream>
#include<random>
#include<algorithm>
using namespace std;
#define ll long long

ll gcd(ll a, ll b){
    if(b == 0)
        return a;
    return gcd(b, a % b);
}

ll FastPow(ll a, ll u, ll n){
    ll ret = 1;
    while(u){
        if(u & 1)
            ret = (__int128)ret * a % n;
        a = (__int128)a * a % n;
        u >>= 1;
    }
    return ret;
}
// 模板開始 (MillerRabin + PollardRho)
bool Miller_Rabin(ll n){
    if(n < 3 || n % 2 == 0)
        return n == 2;
    ll u = n - 1, t = 0;
    while(u % 2 == 0)
        u /= 2, t++;
    for (int i = 0; i < 8; i++){
        ll a = rand() % (n - 2) + 2, v = FastPow(a, u, n);
        if(v == 1)
            continue;
        int s;
        for (s = 0; s < t; s++){
            if(v == n - 1)
                break;
            v = (__int128)v * v % n;
        }
        if(s == t)
            return 0;
    }
    return 1;
}

ll PollardRho(ll n){
    int step = 0, goal = 1;
    ll x = 0, y = 0;
    ll d = 1;
    ll c = (ll)rand() % (n - 1) + 1;    
    for(goal = 1;; goal <<= 1, x = y, d = 1){
        for(step = 0; step < goal; step++){
            y = ((__int128)y * y + c) % n;
            d = ((__int128)d * abs(x - y)) % n;
            if(step % 127 == 0){
                ll g = gcd(d, n);
                if(g > 1)
                    return g;
            }
        }
        ll g = gcd(d, n);
        if(g > 1)
            return g;
    }
    return 0;
}
// 模板結束
ll ans = 0;
void fac(ll n){
    if(n == 1)
        return;
    if(Miller_Rabin(n)){
        ans = max(n, ans);
        return;
    }
    if(n < ans)
        return;
    ll f = PollardRho(n);
    fac(f);
    fac(n / f);
    return;
}
signed main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        ll n;
        cin >> n;
        if(Miller_Rabin(n)){
            cout << "Prime\n";
            continue;
        }
        ans = 0;
        fac(n);
        cout << ans << "\n";
    }
    return 0;
}