#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>
#include <climits>

using namespace std;
struct Vertex {
    int a, b;
    int cost;
    string action;

    Vertex(int a, int b, int cost, const string& action)
        : a(a), b(b), cost(cost), action(action) {}

    bool operator>(const Vertex& other) const {
        return cost > other.cost;
    }
};

class Jug {
public:
    Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA)
        : Ca(Ca), Cb(Cb), N(N), cfA(cfA), cfB(cfB), ceA(ceA), ceB(ceB), cpAB(cpAB), cpBA(cpBA) {}

    int solve(string& solution);

private:
    int Ca, Cb, N;
    int cfA, cfB, ceA, ceB, cpAB, cpBA;
    
    void tryAction(int a, int b, int newA, int newB, int costAction, int costReverse, int ceA, int ceB, int cp, string action, vector<vector<int>>& dist, vector<vector<string>>& actions, priority_queue<Vertex, vector<Vertex>, greater<Vertex>>& pq);
};
