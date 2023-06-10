#include <bits/stdc++.h>
#include <utility>
using namespace std;
typedef long long ll;
const int sz=1e5+5;
ll n,k,m,q,T,p,ans,start;
string s1,s2;
int par[sz];
int compsz[sz];
vector<array<char,2>>res;
void init(int n){
    for(int i=0;i<26;i++){
        par[i]=i;
        compsz[i]=1;
    }
}
int find(int x){
    if(x==par[x]) return x;
    else return find(par[x]);
}
void unite(int x,int y){
    x=find(x);y=find(y);
    if(x==y) return;
    if(compsz[x]<compsz[y]) swap(x,y);
    compsz[x]+=compsz[y];
    par[y]=x;
}
int main(){
    cin>>n;
    init(n);
    cin>>s1>>s2;
    for(int i=0;i<n;i++){
         int x1=s1[i]-'0'-48; 
         int x2=s2[i]-'0'-48;
         if(find(x1)==find(x2)) continue;
         unite(x1,x2);
         res.push_back({s1[i],s2[i]});
         ans++;
    } 
    cout<<ans<<endl;
    for(auto p:res) cout<<p[0]<<" "<<p[1]<<endl;
}