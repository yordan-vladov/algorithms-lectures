#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Activity { int start, end; };

int activitySelection(vector<Activity>& activities) {
    sort(activities.begin(), activities.end(),
         [](Activity& a, Activity& b) { return a.end < b.end; });

    int count = 1;
    int lastEnd = activities[0].end;

    for (size_t i = 1; i < activities.size(); i++) {
        if (activities[i].start >= lastEnd) {
            count++;
            lastEnd = activities[i].end;
        }
    }

    return count;
}

int main() {
    vector<Activity> activities = {
        {1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 9},
        {5, 9}, {6, 10}, {8, 11}, {8, 12}, {2, 14}
    };

    cout << "Максимален брой дейности: " << activitySelection(activities) << endl;
    // Изход: 3

    return 0;
}
