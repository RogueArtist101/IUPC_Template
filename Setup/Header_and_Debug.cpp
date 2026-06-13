// Section: Setup
// Topic:   Header and Debug

//Bismillahir Rahmanir Raheem
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using cd = complex<double>;
#define rep(i,a,b) for(int i=int(a);i<int(b);i++)
#define pb push_back
#define vi vector<int>

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

template<typename T, typename cmp = less<T>>
using ordered_set = tree<T, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update>;

template<typename T, typename cmp = less_equal<T>>
using ordered_multiset = tree<T, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update>;

template<class K, class V> using hash_table = gp_hash_table<K, V, custom_hash>;
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

const int mod = 1e9+7;
const int mod2 = 998244353;

ll inv(ll a, ll m = mod) { return a <= 1 ? a : m - (ll)(m/a) * inv(m % a, m) % m; }
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a,b) * b; }
ll bigmod(ll a, ll b, ll m = mod) {
    if(b==0) return 1;
    ll x = bigmod(a,b/2,m);
    return (b&1) ? (x*x%m)*a%m : (x*x%m);
}

#ifndef ONLINE_JUDGE
void __print(int x){ cerr << x; }
void __print(ll x){ cerr << x; }
void __print(char x){ cerr << x; }
void __print(double x){ cerr << x; }
void __print(const string &x){ cerr << x; }
void __print(bool x){ cerr << (x ? "true" : "false"); }

template<typename T>
void _debug(T t){ __print(t); cerr << "]\n"; }

template<typename T, typename... V>
void _debug(T t, V... v){
    __print(t); cerr << ", "; _debug(v...);
}

#define debug(...) cerr<<"LINE("<<__LINE__<<") [" << #__VA_ARGS__ << "] = [", _debug(__VA_ARGS__)
#else
#define debug(...)  
#endif
