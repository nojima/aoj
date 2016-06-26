const char ALPHABET_MIN = 'a';
const char ALPHABET_MAX = 'z';
const int ALPHABET_SIZE = ALPHABET_MAX - ALPHABET_MIN + 1;

struct State {
    vector<int> next;
    vector<int> accept;
    int failure;
    State(): next(ALPHABET_SIZE, -1), failure(-1) {}
};

// Verified: AOJ 2257 (Sakura Poetry)
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
