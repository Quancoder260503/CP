#include<bits/stdc++.h>
#include<iostream>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> info; 
const int N = 5e5 + 5;
int timer = 0;
int n,m,ans,q; 
struct node{
     bool rev = false; 
     int val,mx;
     int id = ++timer;
     node *c[2] = {NULL,NULL}, *pa = NULL; 
     node(int v){
          val = mx = v; 
     }    
     void push(){
          if(rev){
               swap(c[0],c[1]);
               if(c[0]) c[0] -> rev = c[0] -> rev xor true; 
               if(c[1]) c[1] -> rev = c[1] -> rev xor true; 
               rev = false; 
          }
     }
     void pull(){
           mx = val;
           if(c[0]) mx = max(mx, c[0] -> mx);
           if(c[1]) mx = max(mx, c[1] -> mx); 
     }
}* lct[N + 1];
bool isRoot(node *t){
      return (!t -> pa || (t -> pa -> c[0] != t && t -> pa -> c[1] != t)); 
}
void rotate(node *t){
            node *p = t -> pa;
            bool b = (p -> c[0] == t); 
            while((t -> pa = p -> pa) && !isRoot(p)){
                 t -> pa -> c[(t -> pa -> c[1] == p)] = t;
            }
            if(p -> c[!b] = t -> c[b]) p -> c[!b] -> pa = p; 
            t -> c[b] = p; 
            p -> pa = t; 
            p -> pull(); 
}
void splay(node *t){
       while(!isRoot(t)){
            node *p = t -> pa; 
            p -> push(); 
            t -> push();
            rotate(t); 
       }
       t -> push();
       t -> pull(); 
}
node *access(node *t){
      node *last = NULL;
      for(node *u = t; u; u = u -> pa){
           splay(u);
           u -> c[1] = last; 
           last = u; 
      }
      splay(t);
      return last; 
}
void evert(node *t){
      access(t);
      t -> rev = true;
}
void link(node *a, node *b){
     evert(a);
     a -> pa = b; 
}
void cut(node *a,node *b){
     evert(a);
     access(b); 
     if(b -> c[0]) b -> c[0] -> pa = NULL; 
     b -> c[0] = 0;
     b -> pull(); 
}
node *path(node *a,node *b){
      evert(a);
      access(b); 
      return b; 
}
node *lca(node *a, node *b){
      evert(lct[1]);
      access(a); 
      return access(b); 
}
bool connected(node *a, node *b){
      path(a,b);
      while(b -> c[0]) b = b -> c[0]; 
      return a == b;
}
int main(){
     scanf("%d%d%d",&n,&m,&q);
     for(int i = 1; i <= n; i++) lct[i] = new node(0);
     for(int i = 1; i <= m; i++){
            int a,b; scanf("%d%d",&a,&b); 
            lct[n + i] = new node(i);
            if(!connected(lct[a],lct[b])){
                 link(lct[a],lct[n + i]);
                 link(lct[b],lct[n + i]); 
            }            
     }
     for(int i = 1; i <= q; i++){
           int u,v; scanf("%d%d",&u,&v);
           if(!connected(lct[u],lct[v])){
                printf("%d\n",-1); 
           }
           else{
                node *x = path(lct[u],lct[v]);
                printf("%d\n",x -> mx);
           }
     }
     return 0;
}
