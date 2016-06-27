#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)

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

template <typename Int>
struct FenwickTree {
  vector<Int> data;
  explicit FenwickTree(int n): data(n, -1) {}
  void set(int i, Int x) { for (; i < (int)data.size(); i |= i+1) data[i] = max(data[i], x); }
  Int maximum(int i) const { Int s = -1; for (; i >= 0; i = (i & (i+1)) - 1) s = max(s, data[i]); return s; }
};

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);

    int N, Q;
    while (cin>>N>>Q, N|Q) {
        vector<Node> tree(N);
        tree[0].parent = -1;
        FOR(i, 1, N) {
            int p; cin >> p; --p;
            tree[i].parent = p;
            tree[p].children.push_back(i);
        }

        auto t = heavy_light_decomposition(tree, 0);
        auto& decomposed = t.first;
        int root = t.second;

        vector<int> node_mapping(N);
        vector<int> position_mapping(N);
        REP(i, decomposed.size()) {
            auto& node = decomposed[i];
            REP(j, node.path.size()) {
                int v = node.path[j];
                node_mapping[v] = i;
                position_mapping[v] = j;
            }
        }

        vector<FenwickTree<int>> fenwick_trees;
        for (auto& node : decomposed)
            fenwick_trees.emplace_back(node.path.size());
        fenwick_trees[root].set(0, 0);

        long long sum = 0;
        REP(query_index, Q) {
            char q; int v; cin >> q >> v; --v;
            int u = node_mapping[v], p = position_mapping[v];
            if (q == 'M') {
                fenwick_trees[u].set(p, p);
            } else if (q == 'Q') {
                int ans = 0;
                while (u != -1) {
                    int k = fenwick_trees[u].maximum(p);
                    if (k != -1) {
                        ans = decomposed[u].path[k];
                        break;
                    }
                    p = decomposed[u].position;
                    u = decomposed[u].parent;
                }
                sum += ans + 1;
            } else {
                assert(false);
            }
        }
        cout << sum << '\n';
    }
}
