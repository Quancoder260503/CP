#include<iostream>
#include<bits/stdc++.h>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
int n,m,k;
vector<ll>g[100005];
pair<int,int>cor[100005];
double dp[1001];
int s[1001];
void dijisktra(int src){
    vector<bool>visit(1005,false);
    using T=pair<double,int>;
    priority_queue<T,vector<T>,greater<T>>pq;
    pq.push({0,src});
    dp[src]=0;
    while (!pq.empty()){
        int node;double val;
        tie(val,node)=pq.top();
        pq.pop();
        if (dp[node]!=val) continue;
        visit[node]=true;
        int cnt=0;
        for (auto u:g[node]){
            if (cnt==s[node]) break;
            if (visit[u]) continue;
            int x=cor[node].first;
            int y=cor[node].second;
            int x1=cor[u].first;
            int y1=cor[u].second;
            double dist=sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
            cnt++;
            if (dp[u]>dp[node]+dist){
                pq.push({dp[u]=dp[node]+dist,u});
              }
          }
        }
    }
int main(){
    int n;
    cin>>n;
    for (int i=1;i<=n;i++){
        int x,y,t;
        cin>>x>>y>>t;
        cor[i].first=x;
        cor[i].second=y;
        s[i]=t;
        for (int j=0;j<n-1;j++){
            int v;
            cin>>v;
            g[i].push_back(v);
            }
        }
    const double inf =1e9;
    for(int i=1;i<=n;i++){
        dp[i]=inf;
    }    
    dijisktra(1);
    for (int i=1;i<=n;i++){
        cout <<dp[i]<<endl;
    }
}
