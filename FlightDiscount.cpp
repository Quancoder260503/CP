#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
vector<pair<ll,ll>>g[200005];
ll d1[200005];
ll d0[200005];
void dijisktra(int n){
    using T=pair<ll,pair<int,bool>>;
    priority_queue<T,vector<T>,greater<T>>q;
    q.push({0,{n,0}});
    while (!q.empty()){
        ll value=q.top().first;
        int node=q.top().second.first;
        bool check=q.top().second.second;
        q.pop();
        if (d0[node]!=value and d1[node]!=value) continue;
        for (pair<int,ll> u:g[node]){
            int i=u.first;
            ll j=u.second;
            if (check){
               if (d1[i]>value+j){
                   d1[i]=value+j;
                   q.push({d1[i],{i,1}});
               }
            }   
            else{
                if (d0[i]>value+j){
                    d0[i]=value+j;
                    q.push({d0[i],{i,0}});
                } if (d1[i]>value+j/2){
                    d1[i]=value+j/2;
                    q.push({d1[i],{i,1}});
                }
            }    
        }
    }
}    
int main(){
    int n, m;
    cin>>n>>m;
    for (int i=0;i<m;i++){
        int u,v;
        ll k;
        cin>>u>>v>>k;
        g[u].push_back({v,k});
    } for (int i=2;i<=n;i++){
        d0[i]=LLONG_MAX;
        d1[i]=LLONG_MAX;
    } 
    dijisktra(1);  
    cout <<d1[n];
}
