#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
int n,m;
bool visited[8][8];
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
ll d[8][8];
char c[8][8];
vector<pair<int,int>>path;
pair<int,int>par[8][8];
int xd,yd;
void bfs(int sx,int sy){
    visited[sx][sy]=1;
    d[sx][sy]=0;
    queue<pair<int,int>>q;
    q.push({sx,sy});
    while (!q.empty()){
        int x1=q.front().first;
        int y1=q.front().second;
        q.pop();
        for (int i=0;i<4;i++){
            int x=x1+dx[i];
            int y=y1+dy[i];
            if (x<0 or x>=8) continue;
            if (y<0 or y>=8) continue;
            if (c[x][y]=='C' or visited[x][y]) continue;
            visited[x][y]=true;
            d[x][y]=d[x1][y1]+1;
            par[x][y]={x1,y1};
            q.push({x,y});
         }
     }
}
void trace(){
    int i,j;
    i=xd;j=yd;
    while (i!=7 or j!=0){
        path.push_back({i,j});
        int k=i;
        i=par[i][j].first;
        j=par[k][j].second;
    }
    while (i!=7){
        path.push_back({i,j});
        i=par[i][j].first;
    } while (j!=0){
        path.push_back({i,j});
        j=par[i][j].second;
    }
}
void print(){
    int prevx=path[0].first;
    int prevy=path[0].second;
    int predirx=path[0].first-7;
    int prediry=path[0].second;
    if (predirx==-1 and prediry==0){
       if (c[prevx][prevy]=='I') cout <<"LXF";
       else cout <<"LF";
    } else{
       if (c[prevx][prevy]=='I') cout <<"XF";
        else cout <<"F";
    }
    for (int i=1;i<path.size();i++){
         int curx=path[i].first;
         int cury=path[i].second;
         int curdirx=curx-prevx;
         int curdiry=cury-prevy;
         if (curdirx==predirx and curdirx==predirx){
             if (c[curx][cury]=='I') cout <<"XF";
             else cout<<"F";
         }
         if (prediry==0 and predirx==1){
            if (curdiry==prediry-1){
               if (c[curx][cury]=='I') cout <<"RXF";
               else cout <<"RF";
           } if (curdiry==prediry+1){
               if (c[curx][cury]=='I') cout <<"LXF";
               else cout<<"LF";
            }
         }    
         if (predirx==0 and prediry==1){
             if (curdirx==predirx+1){
                 if (c[curx][cury]=='I') cout <<"RXF";
                 else cout <<"RF";
             } if (curdirx==predirx-1){
                 if( c[curx][cury]=='I') cout <<"LXF";
                 else cout<<"LF";
             }
         }
         if (predirx==0 and prediry==-1){
             if (curdirx==predirx-1){
                 if (c[curx][cury]=='I') cout <<"RXF";
                 else cout <<"RF";
             } if (curdirx==predirx+1){
                 if( c[curx][cury]=='I') cout <<"LXF";
                 else cout<<"LF";
             }
         } if (predirx==-1 and prediry==0){
             if (curdiry==prediry+1){
               if (c[curx][cury]=='I') cout <<"RXF";
               else cout <<"RF";
           } if (curdiry==prediry-1){
               if (c[curx][cury]=='I') cout <<"LXF";
               else cout<<"LF";
            }
         }
             predirx=curdirx;
             prediry=curdiry;
             prevx=curx;
             prevy=cury;
        }
}       
int main(){
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            cin>>c[i][j];
            if (c[i][j]=='D'){
                xd=i;
                yd=j;
            }
        }
    } bfs(7,0);
      if (d[xd][yd]==0) cout <<"no solution";
      else{
          trace();
          reverse(path.begin(),path.end());
          print();
      }
}
