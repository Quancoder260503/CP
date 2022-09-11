#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
int a[sz];
ll en[sz];
ll start[sz];
vector<ll>adj[sz];
vector<array<int,2>>query1;
ll n,q;
ll ans[sz];
int timer=0;
void dfs(int u,int p){
    start[u]=timer++;
    for(auto v:adj[u]){
        if (u==p) continue;
        dfs(v,u);
    } en[u]=timer++;
}
template<class T> struct Seg{
	const T ID = 0; T comb(T a, T b) { return a+b; }
	int n; vector<T> seg;
	void init(int _n) { n = _n; seg.assign(2*n,ID); }
	void pull(int p) { seg[p] = comb(seg[2*p],seg[2*p+1]); }
	void upd(int p, T val) { 
		seg[p += n] += val; for (p /= 2; p; p /= 2) pull(p); }
	T query(int l, int r) {
		T ra = ID, rb = ID;
		for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
			if (l&1) ra = comb(ra,seg[l++]);
			if (r&1) rb = comb(seg[--r],rb);
		}
		return comb(ra,rb);
	}
};
Seg<ll>st;
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
        query1.push_back({a[i],i});
    }
    for (int i=1;i<n;i++){
        int u;cin>>u;
        --u;
        adj[u].push_back(i);
    } dfs(0,-1);
      st.init(2*n+1);
      sort(query1.begin(),query1.end());
      reverse(query1.begin(),query1.end());
      for(auto e:query1){
           st.upd(start[e[1]],1);
           ll x=st.query(start[e[1]],en[e[1]])-1;
           ans[e[1]]=x;
      } for (int i=0;i<n;i++){
          cout <<ans[i]<<endl;
      }
}