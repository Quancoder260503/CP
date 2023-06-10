#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=1e5+1;
vector<pair<ll,pair<int,int>>>edge;
vector<pair<ll,pair<int,int>>>query;
int n,m;
ll res[sz];
struct DSU{
    vector<int>e;
    DSU(int n) {e=vector<int>(n+1,-1);}
    int get(int x){
        if (e[x]<0) return x;
        else return get(e[x]);
    }
    bool sameset(int a,int b){
        if (get(a)==get(b)) return true;
        else return false;
    }
    int size(int x){
        return -e[get(x)];
    }
    bool unite(int a,int b){
        a=get(a); b=get(b);
        if (a==b) return false;
        if(e[a]>e[b]) swap(a,b);
        e[a]+=e[b]; e[b]=a;
        return true;
     }
};
int main(){
   cin>>n>>m;
   DSU dsu(n);
   for(int i=0;i<n-1;i++){
       int u,v;ll d;
       cin>>u>>v>>d;
       edge.push_back({d,{u,v}});
   } 
    sort(edge.begin(), edge.end()); 
    reverse(edge.begin(),edge.end());
    for(int i=0;i<m;i++){
       ll u ;int v;
       cin>>u>>v;
       query.push_back({u,{v,i}});
    }
     sort(query.begin(),query.end());
     reverse(query.begin(),query.end());
     int t=0;
     for(auto q:query){
         int indx=q.second.second;
         int v=q.second.first;
         ll k=q.first;
         while (t<n-1 and k<=edge[t].first){
             dsu.unite(edge[t].second.first,edge[t].second.second);
             t++;
         } 
         res[indx]=dsu.size(v)-1;
    } for (int i=0;i<m;i++){
         cout <<res[i]<<endl;
     }
}