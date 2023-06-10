#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=1e5+1;
int n,m;
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
      } int count(){
        int cnt=0;
        for(int i=1;i<=n;i++){
            if (e[i]<0) cnt++;
        } return cnt;
    } int getmax(){
        int ans=0;
        for (int i=1;i<n;i++){
            ans=max(ans,-e[i]);
        } return ans;
    }
};
int main(){
    cin>>n>>m;
    DSU dsu(n);
    for (int i=0;i<m;i++){
        int type,u,v;
        cin>>type>>u>>v;
        if (!type) dsu.unite(u,v);
        else cout <<dsu.samset(u,v)<<endl;
    }
}