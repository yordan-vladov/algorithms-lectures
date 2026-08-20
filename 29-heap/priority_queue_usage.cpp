#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <string>
using namespace std;

struct Task {
    string name;
    int priority;  // по-малко число = по-важна задача
};

struct CompareTask {
    bool operator()(const Task& a, const Task& b) {
        return a.priority > b.priority;  // "по-голямо" тук = "по-нисък приоритет"
    }
};

int main() {
    cout << "--- max-heap по подразбиране ---" << endl;
    priority_queue<int> pq;
    pq.push(5);
    pq.push(1);
    pq.push(9);
    pq.push(3);

    while (!pq.empty()) {
        cout << pq.top() << " ";  // 9 5 3 1
        pq.pop();
    }
    cout << endl;

    cout << "\n--- min-heap с greater<int> ---" << endl;
    priority_queue<int, vector<int>, greater<int>> min_pq;
    min_pq.push(5);
    min_pq.push(1);
    min_pq.push(9);
    min_pq.push(3);

    while (!min_pq.empty()) {
        cout << min_pq.top() << " ";  // 1 3 5 9
        min_pq.pop();
    }
    cout << endl;

    cout << "\n--- priority_queue с custom тип (Task) ---" << endl;
    priority_queue<Task, vector<Task>, CompareTask> tasks;
    tasks.push({"Write docs", 3});
    tasks.push({"Fix bug", 1});
    tasks.push({"Server down!", 0});
    tasks.push({"Code review", 2});

    while (!tasks.empty()) {
        cout << tasks.top().name << " (priority " << tasks.top().priority << ")" << endl;
        tasks.pop();
    }
    // Server down! (priority 0)
    // Fix bug (priority 1)
    // Code review (priority 2)
    // Write docs (priority 3)

    cout << "\n--- priority_queue от двойки (симулира Dijkstra) ---" << endl;
    // pair<разстояние, връх> - min-heap по разстояние
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq_dist;
    pq_dist.push({5, 1});   // (разстояние=5, връх=1)
    pq_dist.push({2, 2});
    pq_dist.push({8, 3});

    while (!pq_dist.empty()) {
        auto [dist, node] = pq_dist.top();
        cout << "връх " << node << " с разстояние " << dist << endl;
        pq_dist.pop();
    }
    // връх 2 с разстояние 2
    // връх 1 с разстояние 5
    // връх 3 с разстояние 8

    return 0;
}
