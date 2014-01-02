// 1187.cpp - ICPC Ranking
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct team {
    int id;
    int solved;
    int penalty;
    vector<int> not_accepted;

    team(int id, int n_problems):
        id(id), solved(0), penalty(0), not_accepted(n_problems) {}

    bool operator<(const team& rhs) const {
        if (solved != rhs.solved)
            return solved > rhs.solved;
        if (penalty != rhs.penalty)
            return penalty < rhs.penalty;
        return id > rhs.id;
    }
};

int main()
{
    ios::sync_with_stdio(false);

    int M, T, P, R;
    while (cin >> M >> T >> P >> R, M) {
        vector<team> teams;
        for (int t = 0; t < T; ++t) {
            teams.emplace_back(t + 1, P);
        }

        for (int r = 0; r < R; ++r) {
            int m, t, p, j;
            cin >> m >> t >> p >> j;
            team& team = teams[t - 1];
            if (j == 0) {
                team.solved += 1;
                team.penalty += m + team.not_accepted[p - 1] * 20;
            } else {
                team.not_accepted[p - 1] += 1;
            }
        }

        sort(teams.begin(), teams.end());

        for (int t = 0; t < T; ++t) {
            if (t > 0) {
                if (teams[t].solved  == teams[t - 1].solved &&
                    teams[t].penalty == teams[t - 1].penalty)
                    cout << "=";
                else
                    cout << ",";
            }
            cout << teams[t].id;
        }
        cout << endl;
    }
}
