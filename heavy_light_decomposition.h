struct Node {
    int parent;
    vector<int> children;
};

struct HLNode {
    int parent;
    int position;   // position in the parent's path.
    vector<int> children;
    vector<int> path;
};

// 木の Heavy-Light Decomposition を行う。
// Arguments:
//   tree: 木。
//   root: 根となるノードの番号。
// Returns:
//   vector<HLNode>: 縮約後の木。
//   int: 縮約後の木の根となるノードの番号。
// Verified: AOJ 2170 (Marked Ancestor)
pair<vector<HLNode>, int> heavy_light_decomposition(const vector<Node>& tree, int root) {
    vector<HLNode> decomposed;
    stack<int> S, loop, max_weight, max_index, total_weight, indices;
    int index, weight;

    {
        S.push(root);
start:
        int u = S.top();
        if (tree[u].children.empty()) {
            decomposed.push_back((HLNode){-1, -1, vector<int>(), vector<int>(1, u)});
            weight = 1;
            index = decomposed.size()-1;
            S.pop();
            if (!S.empty()) goto ret;
        } else {
            max_weight.push(-1); max_index.push(-1); total_weight.push(0); loop.push(0);
            while (loop.top() < (int)tree[u].children.size()) {
                S.push(tree[u].children[loop.top()]);
                goto start;
ret:
                u = S.top();
                indices.push(index);
                total_weight.top() += weight;
                if (weight > max_index.top()) {
                    max_weight.top() = weight;
                    max_index.top() = index;
                }
                ++loop.top();
            }
            int m = max_index.top();
            REP(i, tree[u].children.size()) {
                int idx = indices.top(); indices.pop();
                if (idx == m) continue;
                decomposed[idx].parent = m;
                decomposed[idx].position = decomposed[m].path.size();
                decomposed[m].children.push_back(idx);
            }
            decomposed[m].path.push_back(u);
            weight = total_weight.top()+1;
            index = m;
            max_weight.pop(); max_index.pop(); total_weight.pop(); loop.pop(); S.pop();
            if (!S.empty()) goto ret;
        }
    }

    for (auto& node : decomposed) {
        reverse(node.path.begin(), node.path.end());
        if (node.parent != -1)
            node.position = decomposed[node.parent].path.size() - node.position - 1;
    }
    return make_pair(move(decomposed), index);
}
