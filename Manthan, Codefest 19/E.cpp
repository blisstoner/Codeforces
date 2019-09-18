# pragma GCC optimize ("O3")
# pragma GCC optimize ("Ofast")
# pragma GCC optimize ("unroll-loops")
 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
 
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
 
typedef unsigned int ui;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef tuple<int, int, int> ti3;
typedef tuple<int, int, int, int> ti4;
typedef stack<int> si;
typedef queue<int> qi;
typedef priority_queue<int> pqi;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef tuple<ll, ll, ll> tl3;
typedef tuple<ll, ll, ll, ll> tl4;
typedef stack<ll> sl;
typedef queue<ll> ql;
typedef priority_queue<ll> pql;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>ordered_set;
 
const int dx[4] = { 1,0,-1,0 };
const int dy[4] = { 0,1,0,-1 };
const int ddx[8] = { 0,0,1,1,1,-1,-1,-1 }, ddy[8] = { 1,-1,1,0,-1,1,0,-1 };
ll POW(ll a, ll b, ll MMM) { ll ret = 1; for (; b; b >>= 1, a = (a*a) % MMM)if (b & 1)ret = (ret*a) % MMM; return ret; }
ll GCD(ll a, ll b) { return b ? GCD(b, a%b) : a; }
ll LCM(ll a, ll b) { if (a == 0 || b == 0)return a + b; return a / GCD(a, b) * b; }
ll INV(ll a, ll m) {
	ll m0 = m, y = 0, x = 1;
	if (m == 1)	return 0;
	while (a > 1) {
		ll q = a / m;
		ll t = m;
		m = a % m, a = t;
		t = y;
		y = x - q * y;
		x = t;
	}
	if (x < 0) x += m0;
	return x;
}
pll EXGCD(ll a, ll b) {
	if (b == 0) return { 1,0 };
	auto t = EXGCD(b, a%b);
	return { t.second,t.first - t.second*(a / b) };
}
bool OOB(ll x, ll y, ll N, ll M) { return 0 > x || x >= N || 0 > y || y >= M; }
#define X first
#define Y second
#define rep(i,a,b) for(int i = a; i < b; i++)
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(a) ((int)(a.size()))
#define sf1(a) cin >> a
#define sf2(a,b) cin >> a >> b
#define sf3(a,b,c) cin >> a >> b >> c
#define sf4(a,b,c,d) cin >> a >> b >> c >> d
#define sf5(a,b,c,d,e) cin >> a >> b >> c >> d >> e
#define sf6(a,b,c,d,e,f) cin >> a >> b >> c >> d >> e >> f
#define pf1(a) cout << (a) << ' '
#define pf2(a,b) cout << (a) << ' ' << (b) << ' '
#define pf3(a,b,c) cout << (a) << ' ' << (b) << ' '<< (c) << ' '
#define pf4(a,b,c,d) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << ' '
#define pf5(a,b,c,d,e) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << ' '<< (e) << ' '
#define pf6(a,b,c,d,e,f) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << ' '<< (e) << ' ' << (f) << ' '
#define pf0l() cout << '\n';
#define pf1l(a) cout << (a) << '\n'
#define pf2l(a,b) cout << (a) << ' ' << (b) << '\n'
#define pf3l(a,b,c) cout << (a) << ' ' << (b) << ' '<< (c) << '\n'
#define pf4l(a,b,c,d) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << '\n'
#define pf5l(a,b,c,d,e) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << ' '<< (e) << '\n'
#define pf6l(a,b,c,d,e,f) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << ' '<< (e) << ' ' << (f) << '\n'
#define pfvec(V) for(auto const &t : V) pf1(t)
#define pfvecl(V) for(auto const &t : V) pf1(t); pf0l()
 
class Seg { // 0-indexed
public:
  int n;
  vector<ll> a;
  Seg(int n) : n(n), a(2*n) {}
  void init() {
    for (int i = n - 1; i > 0; i--) a[i] = a[i << 1] + a[i << 1|1];
  }
  void update(int i, ll val) { // change i-th element to val(0-indexed)
    for (a[i += n] += val; i > 1; i >>= 1) a[i >> 1] = a[i] + a[i ^ 1];
  }
  // sum of l-th to r-th element(0-indexed)
  ll query(int l, int r) {
    ll ret = 0;
    for (l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ret += a[l++];
      if (r & 1) ret += a[--r];
    }
    return ret;
  }
  void pushval(int i, ll val){ // set i-th element to val
    a[i+n]=val;
  }
};
 
 
class SegMx { // 0-indexed
public:
  int n;
  vector<ll> a;
  SegMx(int n) : n(n), a(2*n) {}
  void init() {
    for (int i = n - 1; i > 0; i--) a[i] = max(a[i << 1], a[i << 1|1]);
  }
  // max of l-th to r-th element(0-indexed)
  ll query(int l, int r) {
    ll ret = -0x7f7f7f7f;
    for (l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ret = max(ret,a[l++]);
      if (r & 1) ret = max(ret,a[--r]);
    }
    return ret;
  }
  void pushval(int i, ll val){ // set i-th element to val
    a[i+n]=val;
  }
};
 
int n,w;
int a[1000005];
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
  sf2(n,w);
  Seg ans(w+1);
  rep(i,0,n){
    int len;
    sf1(len);
    a[0] = a[len+1] = 0;
    rep(j,1,len+1) sf1(a[j]);
    if(2*len <= w){
      int a_mx = *max_element(a,a+len+2);
      ans.update(len-1, a_mx);
      ans.update(w-len+1, -a_mx);      
      int curmx = 0;
      for(int i = 0; i < len-1; i++){
        curmx = max(curmx, a[i+1]);
        ans.update(i, curmx);
        ans.update(i+1,-curmx);      
      }
      curmx = 0;
      for(int i = w-1; i >= w-len+1; i--){
        curmx = max(curmx, a[i-(w-1)+len]);
        ans.update(i, curmx);
        ans.update(i+1,-curmx);
      }
    }
    else{
      SegMx SS(len+2);
      for(int i = 0; i < len+2; i++) SS.pushval(i, a[i]);
      SS.init();
      int margin = w-len+1;
      for(int i = 0; i < w; i++){
        int st = max(0, i+1-(margin-1));
        int en = min(len+1, i+1);
        int val = SS.query(st,en);
        //pf3l("st en ",st,en);
        //pf3l("ans upd", i, val);
        ans.update(i,val);
        ans.update(i+1,-val);
      }
    }    
  }
  rep(i,0,w) pf1(ans.query(0,i));
}
