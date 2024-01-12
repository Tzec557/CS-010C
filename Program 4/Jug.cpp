#include "Jug.h"

//solve is used to check input and find the solution if one exists
//returns -1 if invalid inputs. solution set to empty string.
//returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
//returns 1 if solution is found and stores solution steps in solution string.
int Jug::solve(string& solution) {
    if (Ca <= 0 || Cb <= 0 || Ca > Cb || N > Cb || Cb > 1000) {
         solution = "";
        return -1;
    }
    if (cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 || cpAB < 0 || cpBA < 0) {
         solution = "";
        return -1;
    }

    vector<vector<int>> dist(Ca + 1, vector<int>(Cb + 1, INT_MAX));
    vector<vector<string>> actions(Ca + 1, vector<string>(Cb + 1, ""));

    priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;
    pq.push(Vertex(0, 0, 0, ""));

    dist[0][0] = 0;

    while (!pq.empty()) {
        Vertex current = pq.top();
        pq.pop();

        if (current.a == 0 && current.b == N) {
            solution = current.action + "success " + to_string(current.cost);
            return 1;
        }

        if (current.cost > dist[current.a][current.b]){
            continue;
        }

        tryAction(current.a, current.b, Ca, current.b, cfA, cfB, ceA, ceB, cpAB, "fill A", dist, actions, pq);
        tryAction(current.a, current.b, current.a, Cb, cfB, cfA, ceB, ceA, cpBA, "fill B", dist, actions, pq);
        tryAction(current.a, current.b, 0, current.b, ceA, ceB, cfA, cfB, cpAB, "empty A", dist, actions, pq);
        tryAction(current.a, current.b, current.a, 0, ceB, ceA, cfB, cfA, cpBA, "empty B", dist, actions, pq);

        int pourAmount = min(current.a, Cb - current.b);
        tryAction(current.a, current.b, current.a - pourAmount, current.b + pourAmount, cpAB, cpBA, ceA, ceB, cpAB, "pour A B", dist, actions, pq);

        pourAmount = min(current.b, Ca - current.a);
        tryAction(current.a, current.b, current.a + pourAmount, current.b - pourAmount, cpBA, cpAB, ceB, ceA, cpBA, "pour B A", dist, actions, pq);
    }

    solution = "";
    return 0;
}

void Jug::tryAction(int a, int b, int newA, int newB, int costAction, int costReverse, int ceA, int ceB, int cp, string action, vector<vector<int>>& dist, vector<vector<string>>& actions, priority_queue<Vertex, vector<Vertex>, greater<Vertex>>& pq) {
    if (newA >= 0 && newB >= 0 && newA <= Ca && newB <= Cb) {
        int newCost = dist[a][b] + costAction;
        if (newCost < dist[newA][newB]) {
            dist[newA][newB] = newCost;
            actions[newA][newB] = actions[a][b] + action + "\n";
            pq.push(Vertex(newA, newB, newCost, actions[newA][newB]));
        }
    }
}