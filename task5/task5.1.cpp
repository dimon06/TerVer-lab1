#include <bits/stdc++.h>

using namespace std;

mt19937 gen(1337);

using ld = long double;
using ll = long long;

const ld E = exp(1.0);
const int MAX_N = 15;
const int ITERATION = 1E4;

vector<ll> factorials;

void gen_factorials() {
    factorials.assign(MAX_N + 1, 1);
    ll n = 1;
    for (int i = 1; i <= MAX_N; i++) {
        n *= i;
        factorials[i] = n;
    }
}


ld get_random() {
    uint32_t rd = gen();
    return static_cast<ld>(rd) / gen.max();
}

// "подбрасываю" монетку в испытаниях Бернулли
int is_win(ld p) {
    if (get_random() <= p) {
        return 1;
    }
    return 0;
}

ld get_real_ans(int n, int k, ld p) {
    ld lambda = n * p;
    return pow(E, -lambda) * pow(lambda, k) / factorials[k];
}

// проверяю выпало ли k орлов среди n монет с вероятностью p
bool simulate(int n, int k, ld p) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt += is_win(p);
    }
    if (cnt == k) {
        return true;
    }
    return false;
}

void print(vector<vector<vector<ld>>> table, const char *name) {
    ofstream out(name);

    out << setprecision(16) << fixed;

    for (int i = 1; i <= MAX_N; i++) {
        out << i << " испытаний:\n";
        out << "значение k \\ значение p\n";

        for (int j = 0; j < i; j++) {
            out << "k = " << j << ": ";
            for (int p = 1; p < 10; p++) {
                out << table[i][j][p] << " ";
            }
            out << "\n";
        }
        out << "\n\n";
    }
}


int main() {
    gen_factorials();

    vector<vector<vector<ld>>> ans(MAX_N+1, vector<vector<ld>>(MAX_N + 1, vector<ld>(10, 0.0)));
    vector<vector<vector<ld>>> real_ans(MAX_N+1, vector<vector<ld>>(MAX_N + 1, vector<ld>(10, 0.0)));

    for (int n = 1; n <= MAX_N; n++) {
        for (int k = 0; k <= n; k++) {
            for (int p_ind = 1; p_ind < 10; p_ind++) {
                ld p = static_cast<ld>(p_ind) / 10;

                int cnt_vins = 0;
                for (int i = 0; i < ITERATION; i++) {
                    if (simulate(n, k, p)) {
                        cnt_vins++;
                    }
                }
                ans[n][k][p_ind] = static_cast<ld>(cnt_vins) / ITERATION;
                real_ans[n][k][p_ind] = get_real_ans(n, k, p);
            }
        }
    }

    vector<vector<vector<ld>>> delta(MAX_N+1, vector<vector<ld>>(MAX_N + 1, vector<ld>(10, 0.0)));

    for (int i = 1; i <= MAX_N; i++) {
        for (int j = 0; j <= i; j++) {
            for (int p = 1; p < 10; p++) {
                delta[i][j][p] = abs(ans[i][j][p] - real_ans[i][j][p]);
            }
        }
    }

    print(ans, "task5.1.result.txt");
    print(delta, "task5.1.delta_result.txt");
}
