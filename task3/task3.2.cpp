#include <bits/stdc++.h>
using namespace std;

using ld = long double;

struct Point {
    ld x, y;
};

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

ld rand_ld(ld l, ld r) {
    uniform_real_distribution<ld> dist(l, r);
    return dist(rng);
}

// Пусть треугольник с точками в (0, 0), (1, 0) и (1, h)
// y = h * x
bool insideTriangle(const Point& p, ld h) {
    if (p.x < 0 || p.x > 1 || p.y < 0 || p.y > h) {
        return false;
    }
    return p.y <= h * p.x;
}

// Расстояние до гипотенузы
ld distanceToHypotenuse(const Point& p, ld h) {
    // Прямая: h*x - y = 0
    return abs(h * p.x - p.y) / sqrt(h * h + 1*1);
}

const int ITERATIONS = 1E5;

ld get_real_ans(int n) {
    return M_PI*M_PI / (2 * n*n);
}

ld make_ans(ld res, int n) {
    return res * 2 * tanl(M_PI / n);
}


void print(vector<int>elems, vector<ld> table, const string& name) {
    ofstream out(name);

    out << setprecision(16) << fixed;

    out << "сторон у многоугольника | результат\n";

    for (int i = 0; i < elems.size(); i++) {
        out << elems[i] << " | " << table[i] << "\n";
    }
}

int main() {
    vector<int> elems;
    for (int n = 4; n <= 20; n++) {
        elems.push_back(n);
    }
    int elem = 10;
    while (elem < 1E9) {
        elem*=10;
        elems.push_back(elem);
    }
    vector<ld>ans;
    for (int n : elems) {
        // Высота прямоугольника.
        ld h = tanl(M_PI / n);

        int all  = 0;
        int cnt_vins = 0;

        for (int i = 0; i < ITERATIONS; ++i) {
            Point p{rand_ld(0.0, 1.0), rand_ld(0.0, h)};

            if (!insideTriangle(p, h)) {
                continue;
            }
            all++;
            if (p.y < distanceToHypotenuse(p, h)) {
                cnt_vins++;
            }
        }
        if (all == 0) {
            ans.push_back(make_ans(0.0, n));
        } else {
            ld res = static_cast<ld>(cnt_vins) / all;
            ans.push_back(make_ans(res, n));
        }
    }
    print(elems, ans, "task3.2.result.txt");

    vector<ld>delta;

    for (int i = 0; i < elems.size(); i++) {
        delta.push_back(abs(ans[i] - get_real_ans(elems[i])));
    }

    print(elems, delta, "task3.2.delta_result.txt");
    return 0;
}


