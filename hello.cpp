class Solution {
public:
    int minArrivalsToDiscard(vector<int>& arrivals, int w, int m) {
        unordered_map<int, int> freq;
        int discarded = 0;
        int start = 0, end = 0;

        vector<int> dis(arrivals.size(), 1);

        // Initialize the first window
        for (; end < min(w, (int)arrivals.size()); end++) {
            if (freq[arrivals[end]] >= m) {
                discarded++;
                dis[end] = -1; // mark discarded
            } else {
                freq[arrivals[end]]++;
            }
        }

        // Slide the window
        while (end < arrivals.size()) {
            if (dis[start] != -1) {
                freq[arrivals[start]]--;
            }
            start++;
            // process new arrival
            if (freq[arrivals[end]] >= m) {
                discarded++;
                dis[end] = -1;
            } else {
                freq[arrivals[end]]++;
            }
            end++;

            // remove the element going out of the window
            
        }

        return discarded;
    }
};©leetcode