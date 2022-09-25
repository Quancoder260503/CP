#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//count the number of distinc_value in range
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=2e5+1;
const ld inf=1e7+1;
string t,s;
int n,m,q;
int timer=0;
bool use[sz];
vector<int>adj[sz];
int a[sz];
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
int h[sz];
string name[sz];
vector<array<int,2>>dp[sz];
int st[sz],en[sz];
vector<array<int,3>>queries;
map<string,int>mp;
int ord[sz];
int ans[sz];
int max_h;
int to[sz];
struct compare {
 bool operator()(const array<int,2>& value,
        const int& key)
 {
  return (value[0] < key);
 }
 bool operator()(const int& key,
     const array<int,2>& value)
 {
  return (key < value[0]);
 }
};
template<class T> struct Seg {
	const T ID = 0; T comb(T a, T b) { return a+b; }
	int n; vector<T> seg;
	void init(int _n) { n = _n; seg.assign(2*n,ID); }
	void pull(int p) { seg[p] = comb(seg[2*p],seg[2*p+1]); }
	void upd(int p, T val) {
		seg[p += n] +=val; for (p /= 2; p; p /= 2) pull(p); }
	T query(int l, int r) {	
		T ra = ID, rb = ID;
		for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
			if (l&1) ra = comb(ra,seg[l++]);
			if (r&1) rb = comb(seg[--r],rb);
		}
		return comb(ra,rb);
	}
};
void dfs(int u,int p){
    dp[h[u]].push_back({timer,u});
    max_h=max(max_h,h[u]);
    st[u]=timer++;
    for(auto v:adj[u]){
        if(v==p) continue;
        h[v]=h[u]+1;
        dfs(v,u);
    }
    en[u]=timer++;
}
Seg<int>tree;
int main(){   
    cin>>n;
    for(int i=1;i<=n;i++){
        string t;cin>>t;
        int x;cin>>x;
        name[i]=t;
        adj[x].push_back(i);
    }
    dfs(0,-1); 
    tree.init(n+1);
    cin>>q;
    int cnt=0;
    for(int i=0;i<=max_h;i++){
        for(auto v:dp[i]){
            to[cnt]=v[1];
            ord[v[1]]=cnt++;
        }
    }
    for(int i=0;i<q;i++){
        int u,hi;cin>>u>>hi;
        const auto &v=dp[hi+h[u]];
        int lb=lower_bound(v.begin(),v.end(),st[u],compare())-v.begin();
        int rb=lower_bound(v.begin(),v.end(),en[u],compare())-v.begin()-1;
        if(lb==v.size()) continue;
        if(en[u]<v[0][0]) continue;
        int lpos=v[lb][1]; int rpos=v[rb][1];
        lpos=ord[lpos]; rpos=ord[rpos];
        queries.push_back({lpos,rpos,i});
    }
     sort(queries.rbegin(),queries.rend());
     int cur=n;
     for(auto e:queries){
          while(cur>=e[0]){
                  if(mp.count(name[to[cur]])) tree.upd(mp[name[to[cur]]],-1);
                    mp[name[to[cur]]]=cur;
                    tree.upd(cur,1);
                    cur--;
        }
        ans[e[2]]=tree.query(e[0],e[1]);
    }
    for(int i=0;i<q;i++) cout<<ans[i]<<endl;
}
