#include<bits/stdc++.h>
using namespace std;


// Why 4n in segment tree?
// Answer:

// Because the segment tree may expand to the next power of two, and in worst case the total number of nodes becomes less than 4n, so 4n is a safe upper bound for array allocation.


class Solution{
public:
    vector<int>st;
    vector<int>lazy;

    Solution(int n){
        st.resize(4*n);
        lazy.resize(4*n,0);
    }

    void BuiltSegmentTree(int i,int l,int r,vector<int>&nums){
        if(l==r){
            st[i] = nums[l];
            return;
        }
        int mid = l+(r-l)/2;
        BuiltSegmentTree(2*i+1,l,mid,nums);
        BuiltSegmentTree(2*i+2,mid+1,r,nums);

        st[i] = st[2*i+1]+st[2*i+2];
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
        st[i] = st[2*i+1]+st[2*i+2];
    }

    int GetRangeSum(int i,int l,int r, int rl,int rr){
        if(r<rl || l>rr){
            return 0;
        }
        if(l>=rl && r<=rr) return st[i];

        int mid = l+(r-l)/2;
        return GetRangeSum(2*i+1,l,mid,rl,rr) + GetRangeSum(2*i+2,mid+1,r,rl,rr);
    }
    
    void UpdateInRange(int i,int l,int r,int rl,int rr,int val){

        // STEP 1: Resolve pending lazy
        if(lazy[i] != 0){
            st[i] += (r-l+1) * lazy[i];

            if(l != r){
                lazy[2*i+1] += lazy[i];
                lazy[2*i+2] += lazy[i];
            }

            lazy[i] = 0;
        }

        // STEP 2: No overlap
        if(r < rl || l > rr){
            return;
        }

        // STEP 3: Complete overlap
        if(l >= rl && r <= rr){
            st[i] += (r-l+1) * val;

            if(l != r){
                lazy[2*i+1] += val;
                lazy[2*i+2] += val;
            }
            return;
        }

        // STEP 4: Partial overlap
        int mid = l + (r-l)/2;

        UpdateInRange(2*i+1,l,mid,rl,rr,val);
        UpdateInRange(2*i+2,mid+1,r,rl,rr,val);

        st[i] = st[2*i+1] + st[2*i+2];
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

    // arr[1] = 5;
    // s.UpdateSegmentTree(0,0,4,arr,1);
    // s.PrintSegmentTree();

    int ans = s.GetRangeSum(0,0,6,2,5);
    cout<<ans<<endl;
    s.UpdateInRange(0,0,6,2,5,2);
    // s.PrintSegmentTree();
    ans = s.GetRangeSum(0,0,6,2,5);
    cout<<ans<<endl;
}