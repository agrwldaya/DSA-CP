// top view (using level order )
// buttom view
// left view (left value of each level or the 0th index of each level)
// right view (right  value of each level or n-1th index of each level)


// top view

class Solution {
  public:
    vector<int> topView(Node *root) {
        if (!root) return {};

        map<int, int> mp; // horizontal distance -> value
        queue<pair<Node*, int>> q; // node, horizontal distance

        q.push({root, 0});

        while (!q.empty()) {
            auto [node, l] = q.front();
            q.pop();

            // First time we encounter this horizontal distance
            if (mp.find(l) == mp.end()) {
                mp[l] = node->data;
            }

            if (node->left)  q.push({node->left, l - 1});
            if (node->right) q.push({node->right, l + 1});
        }

        vector<int> ans;
        for (auto &p : mp) {
            ans.push_back(p.second);
        }
        return ans;
    }
};



// buttom view

class Solution {
  public:
    vector<int> bottomView(Node *root) {
        // Your Code Here
        if (!root) return {};

        map<int, int> mp; // horizontal distance -> value
        queue<pair<Node*, int>> q; // node, horizontal distance

        q.push({root, 0});

        while (!q.empty()) {
            auto [node, l] = q.front();
            q.pop();

            mp[l] = node->data;

            if (node->left)  q.push({node->left, l - 1});
            if (node->right) q.push({node->right, l + 1});
        }

        vector<int> ans;
        for (auto &p : mp) {
            ans.push_back(p.second);
        }
        return ans;
    }
};


// left view
class Solution {
  public:
    vector<int> leftView(Node *root) {
        if (!root) return {};
        
        vector<int> ans;
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                Node* node = q.front();
                q.pop();
                
                // First node in this level
                if (i == 0) {
                    ans.push_back(node->data);
                }
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        return ans;
    }
};
