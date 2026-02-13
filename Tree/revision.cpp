#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/* -------------------- 1. Traversals -------------------- */

// Inorder Traversal (LNR)
void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

// Preorder Traversal (NLR)
void preorder(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

// Postorder Traversal (LRN)
void postorder(TreeNode* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->val << " ";
}

// Level Order Traversal (BFS)
void levelOrder(TreeNode* root) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* cur = q.front(); q.pop();
        cout << cur->val << " ";
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
}

/* -------------------- 2. Height & Diameter -------------------- */

int height(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}

int diameterUtil(TreeNode* root, int& ans) {
    if (!root) return 0;
    int lh = diameterUtil(root->left, ans);
    int rh = diameterUtil(root->right, ans);
    ans = max(ans, lh + rh);
    return 1 + max(lh, rh);
}

int diameter(TreeNode* root) {
    int ans = 0;
    diameterUtil(root, ans);
    return ans;
}

/* -------------------- 3. Path-Related -------------------- */

// Root-to-leaf path sum
bool hasPathSum(TreeNode* root, int sum) {
    if (!root) return false;
    if (!root->left && !root->right) return sum == root->val;
    return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
}

// All root-to-leaf paths
void allPathsUtil(TreeNode* root, vector<int>& path, vector<vector<int>>& res) {
    if (!root) return;
    path.push_back(root->val);
    if (!root->left && !root->right) res.push_back(path);
    else {
        allPathsUtil(root->left, path, res);
        allPathsUtil(root->right, path, res);
    }
    path.pop_back();
}

vector<vector<int>> allRootToLeafPaths(TreeNode* root) {
    vector<vector<int>> res;
    vector<int> path;
    allPathsUtil(root, path, res);
    return res;
}

// Maximum path sum in a binary tree
int maxPathSumUtil(TreeNode* root, int& maxSum) {
    if (!root) return 0;
    int l = max(0, maxPathSumUtil(root->left, maxSum));
    int r = max(0, maxPathSumUtil(root->right, maxSum));
    maxSum = max(maxSum, l + r + root->val);
    return root->val + max(l, r);
}

int maxPathSum(TreeNode* root) {
    int maxSum = INT_MIN;
    maxPathSumUtil(root, maxSum);
    return maxSum;
}

/* -------------------- 4. View-Related -------------------- */

// Top view
void topView(TreeNode* root) {
    if (!root) return;
    map<int, int> mp;
    queue<pair<TreeNode*, int>> q;
    q.push({root, 0});
    while (!q.empty()) {
        auto [node, hd] = q.front(); q.pop();
        if (!mp.count(hd)) mp[hd] = node->val;
        if (node->left) q.push({node->left, hd - 1});
        if (node->right) q.push({node->right, hd + 1});
    }
    for (auto& p : mp) cout << p.second << " ";
}

// Bottom view
void bottomView(TreeNode* root) {
    if (!root) return;
    map<int, int> mp;
    queue<pair<TreeNode*, int>> q;
    q.push({root, 0});
    while (!q.empty()) {
        auto [node, hd] = q.front(); q.pop();
        mp[hd] = node->val;
        if (node->left) q.push({node->left, hd - 1});
        if (node->right) q.push({node->right, hd + 1});
    }
    for (auto& p : mp) cout << p.second << " ";
}

// Left view
void leftView(TreeNode* root) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int n = q.size();
        for (int i = 0; i < n; i++) {
            TreeNode* cur = q.front(); q.pop();
            if (i == 0) cout << cur->val << " ";
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
    }
}

// Right view
void rightView(TreeNode* root) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int n = q.size();
        for (int i = 0; i < n; i++) {
            TreeNode* cur = q.front(); q.pop();
            if (i == n - 1) cout << cur->val << " ";
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
    }
}

// Vertical order traversal
void verticalOrder(TreeNode* root) {
    if (!root) return;
    map<int, vector<int>> mp;
    queue<pair<TreeNode*, int>> q;
    q.push({root, 0});
    while (!q.empty()) {
        auto [node, hd] = q.front(); q.pop();
        mp[hd].push_back(node->val);
        if (node->left) q.push({node->left, hd - 1});
        if (node->right) q.push({node->right, hd + 1});
    }
    for (auto& p : mp) {
        for (int v : p.second) cout << v << " ";
        cout << endl;
    }
}

/* -------------------- 5. Tree Construction -------------------- */

TreeNode* buildFromInPre(vector<int>& inorder, vector<int>& preorder, int inL, int inR, int& preIndex, unordered_map<int,int>& mp) {
    if (inL > inR) return NULL;
    TreeNode* root = new TreeNode(preorder[preIndex++]);
    int inIndex = mp[root->val];
    root->left = buildFromInPre(inorder, preorder, inL, inIndex - 1, preIndex, mp);
    root->right = buildFromInPre(inorder, preorder, inIndex + 1, inR, preIndex, mp);
    return root;
}

TreeNode* constructFromInPre(vector<int>& inorder, vector<int>& preorder) {
    unordered_map<int,int> mp;
    for (int i = 0; i < inorder.size(); i++) mp[inorder[i]] = i;
    int preIndex = 0;
    return buildFromInPre(inorder, preorder, 0, inorder.size()-1, preIndex, mp);
}

TreeNode* buildFromInPost(vector<int>& inorder, vector<int>& postorder, int inL, int inR, int& postIndex, unordered_map<int,int>& mp) {
    if (inL > inR) return NULL;
    TreeNode* root = new TreeNode(postorder[postIndex--]);
    int inIndex = mp[root->val];
    root->right = buildFromInPost(inorder, postorder, inIndex + 1, inR, postIndex, mp);
    root->left = buildFromInPost(inorder, postorder, inL, inIndex - 1, postIndex, mp);
    return root;
}

TreeNode* constructFromInPost(vector<int>& inorder, vector<int>& postorder) {
    unordered_map<int,int> mp;
    for (int i = 0; i < inorder.size(); i++) mp[inorder[i]] = i;
    int postIndex = postorder.size() - 1;
    return buildFromInPost(inorder, postorder, 0, inorder.size()-1, postIndex, mp);
}

/* -------------------- 6. Special -------------------- */

// Morris Traversal (O(1) space inorder)
void morrisInorder(TreeNode* root) {
    TreeNode* cur = root;
    while (cur) {
        if (!cur->left) {
            cout << cur->val << " ";
            cur = cur->right;
        } else {
            TreeNode* pre = cur->left;
            while (pre->right && pre->right != cur) pre = pre->right;
            if (!pre->right) {
                pre->right = cur;
                cur = cur->left;
            } else {
                pre->right = NULL;
                cout << cur->val << " ";
                cur = cur->right;
            }
        }
    }
}

// Check if balanced (AVL property)
bool isBalancedUtil(TreeNode* root, int& height) {
    if (!root) { height = 0; return true; }
    int lh, rh;
    if (!isBalancedUtil(root->left, lh)) return false;
    if (!isBalancedUtil(root->right, rh)) return false;
    height = 1 + max(lh, rh);
    return abs(lh - rh) <= 1;
}

bool isBalanced(TreeNode* root) {
    int h;
    return isBalancedUtil(root, h);
}

// Symmetric tree check
bool isMirror(TreeNode* a, TreeNode* b) {
    if (!a && !b) return true;
    if (!a || !b) return false;
    return a->val == b->val && isMirror(a->left, b->right) && isMirror(a->right, b->left);
}

bool isSymmetric(TreeNode* root) {
    return !root || isMirror(root->left, root->right);
}

// Count subtrees with given sum
int countSubtreesWithSumUtil(TreeNode* root, int X, int& count) {
    if (!root) return 0;
    int sum = root->val + countSubtreesWithSumUtil(root->left, X, count) + countSubtreesWithSumUtil(root->right, X, count);
    if (sum == X) count++;
    return sum;
}

int countSubtreesWithSum(TreeNode* root, int X) {
    int count = 0;
    countSubtreesWithSumUtil(root, X, count);
    return count;
}
