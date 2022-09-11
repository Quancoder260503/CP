#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<map>
#include<vector>
#include<utility>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz1=5e6+1;
const int sz=2e5+1;
ll n,y,z,dx,p,a,c,b,m,q;
int movex[4]={0,0,1,-1};
int movey[4]={-1,1,0,0};
vector<array<ll,4>>edge;
bool yes=0;
ll res=0;
ll deg[sz];
ll up[25][sz];
const int mod=998244353;
vector<ll>fac,finv,inv;
vector<ll>d1;
vector<array<ll,2>>ans;
vector<vector<ll>>d2;
vector<ll>anc[sz];
ll compsize[sz];
ll parent[sz];
void binom_init() {
    fac.resize(n+1);
    finv.resize(n+1);
    inv.resize(n+1);
    fac[0] = fac[1] = 1;
    inv[1] = 1;
    finv[0] = finv[1] = 1;
    for(int i=2; i<n+1; i++){
        fac[i] = fac[i-1]*i%mod;
        inv[i] = mod-mod/i*inv[mod%i]%mod;
        finv[i] = finv[i-1]*inv[i]%mod;
    }
}
ll binom(ll n, ll r){
    if(n<r || n<0 || r<0) return 0;
    return (fac[n]*finv[r]%mod*finv[n-r]%mod)%mod;
}
void init(int n){
	for (int i = 1; i <= n; i++){
		parent[i] = i;
		compsize[i] = 1;
	}
}
int find(int a){
	if (a == parent[a]) return a;
	return parent[a] = find(parent[a]);
}
void unite(int a, int b){
	int roota = find(a), rootb = find(b);
	if (roota == rootb) return ;
	if (compsize[roota] > compsize[rootb]) swap(roota, rootb);
	parent[roota] = rootb;
	compsize[rootb] += compsize[roota];
    res=max(res,compsize[rootb]);
}
ll jump(ll x, ll d){
    for(int i=0;i<20;i++){
        if((d>>i)&1) x=up[i][x];
    } return x?: -1;
}
int main(){   
      cin>>n>>q;
      for(int i=2;i<=n;i++){
          ll p;cin>>p;
          up[0][i]=p;
      }
     for(int i=1;i<=20;i++){
         for(int j=1;j<=n;j++) up[i][j]=up[i-1][up[i-1][j]];
     }
    for(int i=0;i<q;i++){
        ll u,v;cin>>u>>v;
        cout<<jump(u,v)<<endl;
    }
}    