#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=1e5+1;
vector<int>g[sz];
vector<int>comp[sz];
int a[sz];
void dfs(int node,int c){
    if (a[node]>0) return;
    a[node]=c;
    for (auto u:g[node]){
        dfs(u,c);
    }
}
ll dist(int a,int b){
    int ans=1e5;
    for(int i:comp[b]){
        int k=lower_bound(comp[a].begin(),comp[a].end(),i)-comp[a].begin();
        if (k>0){
            ans=min(ans,abs(comp[a][k-1]-i));
        }   
        if (k<comp[a].size()){
             ans=min(ans,abs(comp[a][k]-i));
        }  
    } return (ll)ans*ans;
}
void solve(){
    int n,m;
    cin>>n>>m;
    for (int i=1;i<=n;i++){
        g[i].clear();
        a[i]=0;
        comp[i].clear();
    }
    for (int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }   
    int num=0;
    for (int i=1;i<=n;i++){
        if (a[i]==0){
            num++;
            dfs(i,num);
        }
    } for (int i=1;i<=n;i++){
        comp[a[i]].push_back(i);
    } ll val=dist(a[1],a[n]);
      for(int i=2;i<num;i++){
          val=min(val,dist(a[1],i)+dist(a[n],i));
      } cout <<val<<endl;
}
int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
}