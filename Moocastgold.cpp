#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=1001;
ll corx[sz];ll cory[sz];
bool visited[sz];
ld dp[sz][sz];
int n;
void dfs(int node,double x){
    visited[node]=true;
    for (int i=1;i<=n;i++){
        if (visited[i]) continue;
        if (dp[node][i] <= x) dfs(i,x);
    }
}
bool compute(double x){
    int k=0;
    for (int i=1;i<=n;i++){
        visited[i]=0;
    }
    for (int i=1;i<=n;i++){
        if (!visited[i]){
            k++;
            dfs(i,x);
        }
    } if (k==1) return 1;
      else return 0;   
}
int main(){
    cin>>n;
    for (int i=1;i<=n;i++){
        int u,v;
        cin>>u>>v;
        corx[i]=u;
        cory[i]=v;
    } ld k=0;
    for(int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            dp[i][j]=hypot(corx[i]-corx[j],cory[i]-cory[j]);
            k=max(k,dp[i][j]);
        }
    }  ll high=(ll) k*k; ll low=1; 
       while (high>low){
        int mid=(high+low)/2;
        if (compute(sqrt(mid))){
            high=mid;
        }else{
            low=mid+1;
        }
   } cout <<low;
}