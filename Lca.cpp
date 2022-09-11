#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
const int trsz=8e5+1;
ll tin[sz];
ll euler_tour[sz];
ll segtree[trsz];
vector<ll>adj[sz];
ll n,q;
ll timer=0;
void dfs(int node=0 , int parent=-1) {
	tin[node] = timer;
	euler_tour[timer++] = node;
	for (int i : adj[node]) {
		if (i != parent) {
			dfs(i, node);
			euler_tour[timer++] = node;
		}
	}
}
int mn_tin(int x, int y) {
	if (x == -1) return y;
	if (y == -1) return x;
	return (tin[x] <= tin[y] ? x : y);
}
void build(int node = 1, int l = 0, int r = timer - 1) {
	if (l == r) segtree[node] = euler_tour[l];
	else {
		int mid = (l + r) / 2;
		build(node * 2, l, mid);
		build(node * 2 + 1, mid + 1, r);
		segtree[node] = mn_tin(segtree[node * 2], segtree[node * 2 + 1]);
	}
}
 
int query(int a, int b, int node = 1, int l = 0, int r = timer - 1) {
	if (l > b || r < a) return -1;
	if (l >= a && r <= b) return segtree[node];
	int mid = (l + r) / 2;
	return mn_tin(query(a, b, node * 2, l, mid), query(a, b, node * 2 + 1, mid + 1, r));
}
int lca(int a, int b) {
	if (tin[a] > tin[b]) swap(a, b);
	return query(tin[a], tin[b]);
}
int main(){
    cin>>n>>q;
    for (int i=1;i<n;i++){
        int a;cin>>a;--a;
        adj[a].push_back(i);
    } dfs();
      build();
      for (int i=1;i<=q;i++){
          int u,v;cin>>u>>v;
          --u,--v; 
          ll k=lca(u,v)+1;
          cout<<k<<endl;
      }
}