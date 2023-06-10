#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=1e5+1;
int n,m;
int ans=0;
int cnt;
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
        ans=max(ans,-e[a]);
        cnt--;
        return true;
     }
};
int main(){
    cin>>n>>m;
    cnt=n;
    DSU dsu(n);
    for (int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        dsu.unite(u,v);
        cout <<cnt<<" "<<ans<<endl;
    }
}
