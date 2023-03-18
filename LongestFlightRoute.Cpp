#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
vector<int>g[100005];
int n;
ll dis[100005];
ll parent[100005];
void dijisktra(int n){
   using T=pair<int,ll>;
   priority_queue<T,vector<T>,greater<T>>q;
   dis[n]=0;
   q.push({n,0});
    while(!q.empty()){
        int node=q.top().first;
        int value=q.top().second;
        q.pop();
        if (dis[node]!=value) continue;
        for ( int u:g[node]){
            if (1+dis[node]>dis[u]){
                dis[u]=dis[node]+1;
                parent[u]=node;
                q.push({u,dis[u]});
            }
        }
    }
}    
int main() {
     int m;
    cin>>n>>m;
    for (int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        g[u-1].push_back(v-1);
    } for (int i=0;i<n;i++){
        dis[i]=-1e9;
    } 
    dijisktra(0);
    if (dis[n-1]==-1e9){
        cout <<"IMPOSSIBLE";
    } else{
        cout<< dis[n-1]+1<<endl;
        vector<ll>res;
        res.push_back(n-1);
        while (res.back()!=0){
            res.push_back(parent[res.back()]);
        } for (int i=res.size()-1;i>=0;i--){
            cout << res[i]+1 <<" ";
        }
    }
 }
 
