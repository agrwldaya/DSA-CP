int GetRangeSum(int i,int l,int r, int rl,int rr){
        if(r<rl || l>rr){
            return 0;
        }
        if(l>=rl && r<=rr) return st[i];

        int mid = l+(r-l)/2;
        return GetRangeSum(2*i+1,l,mid,rl,rr) + GetRangeSum(2*i+2,mid+1,r,rl,rr);
    }