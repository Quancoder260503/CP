#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
vector<ll>g[100005];
ll parent[100005];
int main(){
    int n,m;
    cin>>n>>m;
    for (int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<ll>dis(n+1,1e9);
    queue<int>q;
    q.push(1);
    dis[1]=1;
    while (!q.empty()){
        int node=q.front();
        q.pop();
        for (int neighbor: g[node]){
            if (dis[neighbor]==1e9){
                dis[neighbor]=dis[node]+1;
                parent[neighbor]=node;
                q.push(neighbor);
            }
        }
    }if (dis[n]!=1e9){
    cout << dis[n]<<endl;
    vector<int>res;
    res.push_back(n);
    while (res.back()!=1){
        res.push_back(parent[res.back()]);
    } for (int j=res.size()-1;j>=0;j--){
        cout << res[j]<< " ";
    }
  }else{
        cout<< "IMPOSSIBLE";
    }
}
