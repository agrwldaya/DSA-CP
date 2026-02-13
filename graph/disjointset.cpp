#include<bits/stdc++.h>
using namespace std;

class DSU{
    vector<int>parent,size;

    DSU(int n){
        parent.resize(n);
        size.resize(n,1);

        for(int i=0;i<n;i++){
            parent[i]=i;
        }
    }

    int findUltimateparent(int x){
        if(x==parent[x]) return x;

        return parent[x] = findUltimateparent(parent[x]);
    };

    void unionbySize(int a,int b){
         int up_a = findUltimateparent(a);
         int up_b = findUltimateparent(b);

          if(up_a==up_b) return;

          if(size[up_a]>size[up_b]){
             parent[up_b] = up_a;
             size[up_a]+=size[up_b]; 
          }else{
             parent[up_a] = up_b;
             size[up_b]+=size[up_a];
          }
    }
};