// we will learn how to build segment tree to find minimum val in a given range in O(log(n))


#include<bits/stdc++.h>
using namespace std;


// Why 4n in segment tree?
// Answer:

// Because the segment tree may expand to the next power of two, and in worst case the total number of nodes becomes less than 4n, so 4n is a safe upper bound for array allocation.


class Solution{
public:
    vector<int>st;

    Solution(int n){
        st.resize(4*n);
    }
    void BuiltSegmentTree(int i,int l,int r,vector<int>&nums){
        if(l==r){
            st[i] = nums[l];
            return;
        }
        int mid = l+(r-l)/2;
        BuiltSegmentTree(2*i+1,l,mid,nums);
        BuiltSegmentTree(2*i+2,mid+1,r,nums);

        st[i] = min(st[2*i+1],st[2*i+2]);
    }

    void UpdateSegmentTree(int i,int l,int r,vector<int>&nums,int idx){
        if(l==idx){
            st[i] = nums[idx];
            return;
        }
        int mid = l+(r-l)/2;
        if(i<=mid){
            UpdateSegmentTree(2*i+1,l,mid,nums,idx);
        }else{
            UpdateSegmentTree(2*i+2,mid+1,r,nums,idx);
        }
        st[i] = min(st[2*i+1],st[2*i+2]);
    }

    int GetRangeMin(int i,int l,int r, int rl,int rr){
        if(r<rl || l>rr){
            return INT_MAX;
        }
        if(l>=rl && r<=rr) return st[i];

        int mid = l+(r-l)/2;
        return min(GetRangeMin(2*i+1,l,mid,rl,rr) ,GetRangeMin(2*i+2,mid+1,r,rl,rr));
    }
  
    void PrintSegmentTree(){
        for(auto num:st){
            cout<<num<<" ";
        }
        cout<<endl;
    }
};

int main(){
    vector<int>arr = {3,1,4,2,7,5,9};

    Solution s(7);
    s.BuiltSegmentTree(0,0,6,arr);
    // s.PrintSegmentTree();

    int ans = s.GetRangeMin(0,0,6,0,5);
    cout<<ans<<endl;
}