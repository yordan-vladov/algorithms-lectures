#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<int> nearestNeighborTSP(vector<vector<double>>& dist, int start) {
    int n = dist.size();
    vector<bool> visited(n, false);
    vector<int> route;

    int current = start;
    visited[current] = true;
    route.push_back(current);

    for (int step = 1; step < n; step++) {
        int nearest = -1;
        double nearestDist = 1e18;

        for (int city = 0; city < n; city++) {
            if (!visited[city] && dist[current][city] < nearestDist) {
                nearest = city;
                nearestDist = dist[current][city];
            }
        }

        visited[nearest] = true;
        route.push_back(nearest);
        current = nearest;
    }

    return route;
}

double routeLength(vector<int>& route, vector<vector<double>>& dist) {
    double total = 0;
    for (size_t i = 0; i + 1 < route.size(); i++)
        total += dist[route[i]][route[i + 1]];
    total += dist[route.back()][route[0]];  // връщане в началото
    return total;
}

int main() {
    // A(0,0) B(1,5) C(5,2) D(6,6) E(8,3)
    vector<pair<double,double>> cities = {{0,0}, {1,5}, {5,2}, {6,6}, {8,3}};
    int n = cities.size();

    vector<vector<double>> dist(n, vector<double>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = hypot(cities[i].first - cities[j].first,
                                cities[i].second - cities[j].second);

    vector<int> route = nearestNeighborTSP(dist, 0);

    cout << "Маршрут: ";
    for (int city : route) cout << city << " ";
    cout << endl;
    cout << "Дължина: " << routeLength(route, dist) << endl;

    return 0;
}
