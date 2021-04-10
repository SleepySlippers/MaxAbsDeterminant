#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <deque>

const double EPS = 1e-9;

double det(int n, std::vector<int> b){
    std::vector<double> a;
    for (size_t i = 0 ; i < b.size(); ++i){
        a.push_back(b[i]);
    }
    double det = 1;
    for (size_t i = 0; i < n; ++i){
        int k = i;
        for (size_t j = i + 1; j < n; ++j){
            if (fabs(a[j * n + i]) > fabs(a[k * n + i])){
                k = j;
            }
        }
        if (fabs(a[k * n + i]) < EPS){
            det = 0;
            break;
        }
        for (size_t j = 0; j < n; ++j){
            std::swap(a[i * n + j], a[k * n + j]);
        }
        if (i != k){
            det = -det;
        }
        det *= a[i * n + i];
        for (size_t j = i + 1; j < n; ++j){
            a[i * n + j] /= a[i * n + i];
        }
        for (size_t j = 0; j < n; ++j){
            if (j != i && fabs(a[j * n + i]) > EPS){
                for (size_t k = i + 1; k < n; ++k){
                    a[j * n + k] -= a[i * n + k] * a[j * n + i];
                }
            }
        }
    }
    return fabs(det);
}

std::string ToString(const std::vector<int>& a){
    std::string ans;
    for (int x: a){
        ans += std::to_string(x) + " ";
    }
    return ans;
}

void SwapRelativeMainDiagonal(std::vector < int > &a, int x, int y, int sz){
    int n = sqrt(a.size()) + 1e-5;
    for (size_t i = 0; i < sz; ++i){
        for (size_t j = i + 1; j < sz; ++j){
            std::swap(a[(x + i) * n + y + j], a[(x + j) * n + y + i]);
        }
    }
}

void SwapRelativeNonMainDiagonal(std::vector < int > &a, int x, int y, int sz){
    int n = sqrt(a.size()) + 1e-5;
    for (size_t i = 0; i < sz; ++i){
        for (size_t j = i + 1; j < sz; ++j){
            std::swap(a[(x + i) * n + y + sz - 1 - j], a[(x + j) * n + y + sz - 1 - i]);
        }
    }
}

std::tuple<int, double, std::vector<int> > bfs(const std::vector<int>& a){
    int n = sqrt(a.size()) + 1e-5;
    std::unordered_map<std::string, int> dist;
    std::deque < std::pair < std::vector < int >, int > > que;
    dist[ToString(a)] = 0;
    que.emplace_back(a, 0);
    double max_det = det(n, a);
    int min_dist = 0;
    std::vector<int> max_matr = a;
    int k = 0;
    while (!que.empty()){
#ifdef _DEBUG
        std::cerr << ++k << std::endl;
#endif
        std::vector<int> cur;
        int dst;
        std::tie(cur, dst) = que.front();
        que.pop_front();
        for (size_t x = 0; x < n; ++x){
            for (size_t y = 0; y < n; ++y){
                for (size_t k = 2; k <= std::min(n - x, n - y); ++k){
                    SwapRelativeMainDiagonal(cur, x, y, k);
                    std::string s = ToString(cur);
                    auto it = dist.find(s);
                    if (it == dist.end()){
                        double tmp = det(n, cur);
                        if (tmp > max_det){
                            max_det = tmp;
                            max_matr = cur;
                            min_dist = dst + 1;
                        }
                        que.emplace_back(cur, dst + 1);
                        dist[s] = dst + 1;
                    }
                    SwapRelativeMainDiagonal(cur, x, y, k);
                    SwapRelativeNonMainDiagonal(cur, x, y, k);
                    s = ToString(cur);
                    it = dist.find(s);
                    if (it == dist.end()){
                        double tmp = det(n, cur);
                        if (tmp > max_det){
                            max_det = tmp;
                            max_matr = cur;
                            min_dist = dst + 1;
                        }
                        que.emplace_back(cur, dst + 1);
                        dist[s] = dst + 1;
                    }
                }
            }
        }
    }
    return { min_dist, max_det, max_matr };
}

int main() {
#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n;
    std::cin >> n;
    std::vector < int > a(n * n, 0);
    for (size_t i = 0; i < n; ++i){
        for (size_t j = 0; j < n; ++j){
            std::cin >> a[i * n + j];
        }
    }
    std::cout << "Matrix:\n";
    auto ans = bfs(a);
    for (size_t i = 0; i < n; ++i){
        for (size_t j = 0; j < n; ++j){
            std::cout << std::get<2>(ans)[i * n + j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "Max det abs: " << std::get<1>(ans) << "\nMin steps:" << std::get<0>(ans) << std::endl;

    return 0;
}
