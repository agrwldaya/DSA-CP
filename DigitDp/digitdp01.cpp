// code to find all digit d appearing betweeing the range l-r 


#include <bits/stdc++.h> 
using namespace std;

int dp[20][2][20][2]; // idx, bound, count, started

int solve(string &s, int idx, int bound, int cnt,int started,int D) {
    if (idx == s.size()) return cnt;

    if (dp[idx][bound][cnt][started] != -1) return dp[idx][bound][cnt][started];

    int limit = bound ? (s[idx] - '0') : 9;

    int ans = 0;

    for (int dig = 0; dig <= limit; dig++) {
        int newstarted = started || (dig!=0);

        int new_cnt = cnt;
        if(newstarted && dig==D) new_cnt++;

        int new_bound = (bound && (dig == limit));   
        ans += solve(s, idx + 1, new_bound, new_cnt,newstarted,D);
    }

    return dp[idx][bound][cnt][started] = ans;
}

// Pad with leading zeros so both strings have same length
string make_equal(string a, string b) {
    while (a.size() < b.size()) a = "0" + a;
    while (b.size() < a.size()) b = "0" + b;
    return a;
}

int main() {
    long long l, r,d;
    cout<<"enter the valuse of l,r and digit"<<endl;
    cin >> l >> r >> d;

    if (l > r) swap(l, r);
    if (l < 0) l = 0;

    string A = to_string(l - 1);
    string B = to_string(r);

    make_equal(A, B);

    memset(dp, -1, sizeof(dp));
    int leftAns = solve(A, 0, 1, 0,0,d);

    memset(dp, -1, sizeof(dp));
    int rightAns = solve(B, 0, 1, 0,0,d);

    cout << (rightAns - leftAns);
    return 0;
}
