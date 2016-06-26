#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)

const char ALPHABET_MIN = 'a';
const char ALPHABET_MAX = 'z';
const int ALPHABET_SIZE = ALPHABET_MAX - ALPHABET_MIN + 1;

struct State {
    vector<int> next;
    vector<int> accept;
    int failure;
    State(): next(ALPHABET_SIZE, -1), failure(-1) {}
};

vector<State> build_pma(const vector<string>& keywords) {
    vector<State> pma(1);
    // make trie
    REP(i, keywords.size()) {
        int k = 0;
        for (char ch : keywords[i]) {
            assert(ALPHABET_MIN <= ch && ch <= ALPHABET_MAX);
            ch -= ALPHABET_MIN;
            if (pma[k].next[ch] == -1) {
                pma[k].next[ch] = pma.size();
                pma.emplace_back();
            }
            k = pma[k].next[ch];
        }
        pma[k].accept.push_back(i);
    }
    // bfs
    queue<int> Q;
    REP(ch, ALPHABET_SIZE) {
        int k = pma[0].next[ch];
        if (k == -1) {
            pma[0].next[ch] = 0;
        } else {
            pma[k].failure = 0;
            Q.push(k);
        }
    }
    while (!Q.empty()) {
        int k = Q.front(); Q.pop();
        REP(ch, ALPHABET_SIZE) {
            int j = pma[k].next[ch];
            if (j == -1) continue;
            int i = pma[k].failure;
            while (pma[i].next[ch] == -1) i = pma[i].failure;
            i = pma[i].next[ch];
            pma[j].failure = i;
            vector<int> accept;
            set_union(pma[j].accept.begin(), pma[j].accept.end(),
                      pma[i].accept.begin(), pma[i].accept.end(), back_inserter(accept));
            pma[j].accept = accept;
            Q.push(j);
        }
    }
    return pma;
}

pair<int, int> transit(const vector<State>& pma, const string& s, int initial) {
    int k = initial, accept = 0;
    REP(i, s.size()) {
        char ch = s[i] - ALPHABET_MIN;
        while (pma[k].next[ch] == -1)
            k = pma[k].failure;
        k = pma[k].next[ch];
        accept += pma[k].accept.size();
    }
    return make_pair(k, accept);
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);

    int N, M, K;
    while (cin>>N>>M>>K, N|M|K) {
        unordered_map<string, int> word2id;
        vector<vector<int>> graph;
        REP(i, N) {
            string s, t; cin >> s >> t;
            if (!word2id.count(s)) {
                int id = word2id.size();
                word2id[s] = id;
            }
            if (!word2id.count(t)) {
                int id = word2id.size();
                word2id[t] = id;
            }
            graph.resize(word2id.size());
            graph[word2id[s]].push_back(word2id[t]);
        }
        vector<string> seasonword(K);
        REP(i, K) cin >> seasonword[i];

        vector<State> pma = build_pma(seasonword);

        vector<vector<int>> next_state(pma.size(), vector<int>(word2id.size()));
        vector<vector<int>> n_accept(pma.size(), vector<int>(word2id.size()));
        REP(state, pma.size()) {
            for (auto p : word2id) {
                string word; int i; tie(word, i) = p;
                tie(next_state[state][i], n_accept[state][i]) = transit(pma, word, state);
            }
        }

        vector<int> word_len(word2id.size());
        for (auto p : word2id) {
            string word; int i; tie(word, i) = p;
            word_len[i] = word.size();
        }

        using Entry = tuple<short, short, char>;
        vector<map<Entry, int>> dp(M+1);
        REP(word, word2id.size()) {
            Entry e = Entry(next_state[0][word], word, n_accept[0][word]);
            if (word_len[word] <= M && get<2>(e) <= 1)
                dp[word_len[word]][e] = 1;
        }
        REP(length, M+1) {
            REP(state, pma.size()) {
                REP(word1, word2id.size()) {
                    REP(n_season, 2) {
                        if (!dp[length].count(Entry(state, word1, n_season)))
                            continue;
                        int c = dp[length][Entry(state, word1, n_season)];
                        for (int word2 : graph[word1]) {
                            int length2 = length + word_len[word2];
                            Entry next = Entry(
                                next_state[state][word2],
                                word2,
                                n_season + n_accept[state][word2]);
                            if (length2 > M || get<2>(next) > 1) continue;
                            dp[length2][next] = (dp[length2][next] + c) % 1000000007;
                        }
                    }
                }
            }
            if (length != M) map<Entry, int>().swap(dp[length]);
        }

        int ans = 0;
        REP(state, pma.size()) REP(word, word2id.size()) if (dp[M].count(Entry(state, word, 1)))
            ans = (ans + dp[M][Entry(state, word, 1)]) % 1000000007;
        cout << ans << endl;
    }
}
