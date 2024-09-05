#include<iostream>
#include<algorithm>
#include<assert.h>
#include<vector>
using namespace std;
#define int long long
#define pii pair<int, int>
#define F first 
#define S second
#define pb push_back

// 模板開始
int exgcd(int a, int b, int &x, int &y){
    if(b == 0){
        x = 1, y = 0;
        return a;
    }
    int gcd = exgcd(b, a % b, y, x);
    y = y - a / b * x;
    return gcd;
}
int excrt(int n, int r[], int m[]){
    int ans = r[0], M = m[0], t, y;
    for (int i = 1; i < n; i++){
        int mod = m[i], res = ((r[i] - ans) % mod + mod) % mod;
        int gcd = exgcd(M, mod, t, y);
        if(res % gcd != 0){
            return -1;
        }
        t = (__int128)t * (res / gcd) % mod;
        ans += t * M;
        M = mod / gcd * M;
        ans = (ans % M + M) % M;
    }
    return ans;
}
// 模板結束
int m[100005], r[100005];
signed main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> m[i] >> r[i];

    cout << excrt(n, r, m) << "\n";
    return 0;
}