// we will learn how to build segment tree to find min/max val in a given range in O(log(n))


#include<bits/stdc++.h>
using namespace std;


// Why 4n in segment tree?
// Answer:

// Because the segment tree may expand to the next power of two, and in worst case the total number of nodes becomes less than 4n, so 4n is a safe upper bound for array allocation.


class Solution{
public:
    vector<int>stMin;
    vector<int>stMax;
    vector<int>lazyMin;
    vector<int>lazyMax;

    Solution(int n){
        stMin.resize(4*n);
        stMax.resize(4*n);
        lazyMin.resize(4*n,0);
        lazyMax.resize(4*n,0);
    }
    void BuiltSegmentTree(int i,int l,int r,vector<int>&nums){
        if(l==r){
            stMin[i] = nums[l];
            stMax[i] = nums[l];
            return;
        }
        int mid = l+(r-l)/2;
        BuiltSegmentTree(2*i+1,l,mid,nums);
        BuiltSegmentTree(2*i+2,mid+1,r,nums);

        stMin[i] = min(stMin[2*i+1],stMin[2*i+2]);
        stMax[i] = max(stMax[2*i+1],stMax[2*i+2]);
    }

    void UpdateSegmentTree(int i,int l,int r,vector<int>&nums,int idx){
        if(l==idx){
            stMin[i] = nums[idx];
            stMax[i] = nums[idx];
            return;
        }
        int mid = l+(r-l)/2;
        if(i<=mid){
            UpdateSegmentTree(2*i+1,l,mid,nums,idx);
        }else{
            UpdateSegmentTree(2*i+2,mid+1,r,nums,idx);
        }
        stMin[i] = min(stMin[2*i+1],stMin[2*i+2]);
        stMax[i] = max(stMax[2*i+1],stMax[2*i+2]);
    }

    int GetRangeMin(int i,int l,int r, int rl,int rr){
        if(r<rl || l>rr){
            return INT_MAX;
        }
        if(l>=rl && r<=rr) return stMin[i];

        int mid = l+(r-l)/2;
        return min(GetRangeMin(2*i+1,l,mid,rl,rr) ,GetRangeMin(2*i+2,mid+1,r,rl,rr));
    }
    
    int GetRangeMax(int i,int l,int r, int rl,int rr){
        if(r<rl || l>rr){
            return INT_MIN;
        }
        if(l>=rl && r<=rr) return stMax[i];

        int mid = l+(r-l)/2;
        return max(GetRangeMax(2*i+1,l,mid,rl,rr) ,GetRangeMax(2*i+2,mid+1,r,rl,rr));
    }   
    void updateInRange(int i,int l,int r,int rl,int rr,int val){
        // resolve pending lazy;
        if(lazyMin[i]!=0){
            stMin[i]+=lazyMin[i];
            stMax[i]+=lazyMax[i];
            if(l!=r){
                lazyMin[2*i+1] += lazyMin[i];
                lazyMin[2*i+2] += lazyMin[i];
                lazyMax[2*i+1] += lazyMax[i];
                lazyMax[2*i+2] += lazyMax[i];
            }
            lazyMin[i]=0;
            lazyMax[i]=0;
        }
        // non-overlap
        if(r<rl || l>rr){
            return;
        }
        // overlap
        if(l>=rl && r<=rr){
            stMin[i]+=val;
            stMax[i]+=val;

            if(l!=r){
                lazyMin[2*i+1] += val;
                lazyMin[2*i+2] += val;
                lazyMax[2*i+1] += val;
                lazyMax[2*i+2] += val;
            }
            return;
        }

        int mid  = l+(r-l)/2;
        updateInRange(2*i+1,l,mid,rl,rr,val);
        updateInRange(2*i+2,mid+1,r,rl,rr,val);
        stMin[i] = min(stMin[2*i+1],stMin[2*i+2]);
        stMax[i] = max(stMax[2*i+1],stMax[2*i+2]);
    }


    void PrintSegmentTree(){
        for(auto num:stMin){

            cout<<num<<" ";
        }
        cout<<endl;
        for(auto num:stMax){

            cout<<num<<" ";
        }
        cout<<endl;
    }

};

int main(){
    vector<int>arr = {3,2,4,1,7,5,9};

    Solution s(7);
    s.BuiltSegmentTree(0,0,6,arr);
    // s.PrintSegmentTree();

    int ans = s.GetRangeMin(0,0,6,2,5);
    cout<<ans<<endl;
    s.updateInRange(0,0,6,2,5,3);
    ans = s.GetRangeMin(0,0,6,2,5);
    cout<<ans<<endl;
    ans = s.GetRangeMax(0,0,6,2,5);
    cout<<ans<<endl;
}