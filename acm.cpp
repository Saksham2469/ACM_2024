#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <utility>
#include <iomanip>

using namespace std;

struct Task {
    int id;
    double burst;
    double arrival;
    double priority;
    double remaining;
};

pair<double,double> fcfs(vector<Task> tasks) {
    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        if (a.arrival == b.arrival) return a.id < b.id;
        return a.arrival < b.arrival;
    });
    double currentTime = 0;
    double totalTurnaroundTime = 0;
    double totalWaitingTime = 0;
    int n = tasks.size();
    for (int i = 0; i < n; i++) {
        if (currentTime < tasks[i].arrival) {
            currentTime = tasks[i].arrival;
        }
        double startTime = currentTime;
        double finishTime = startTime + tasks[i].burst;
        totalTurnaroundTime += finishTime - tasks[i].arrival;
        totalWaitingTime += startTime - tasks[i].arrival;
        currentTime = finishTime;
    }
    return make_pair(totalTurnaroundTime / n, totalWaitingTime / n);
}

struct CMP_SJF {
    const vector<Task>* t;
    CMP_SJF(const vector<Task>* x) : t(x) {}
    bool operator()(int a, int b) const {
        if (abs((*t)[a].remaining - (*t)[b].remaining) < 1e-9) {
            return (*t)[a].id > (*t)[b].id;
        }
        return (*t)[a].remaining > (*t)[b].remaining;
    }
};

pair<double,double> sjf_np(vector<Task> tasks) {
    int n = tasks.size();
    vector<int> ord(n);
    for (int i = 0; i < n; i++) {
        ord[i] = i;
        tasks[i].remaining = tasks[i].burst;
    }

    sort(ord.begin(), ord.end(), [&](int a, int b) {
        if (tasks[a].arrival == tasks[b].arrival) return tasks[a].id < tasks[b].id;
        return tasks[a].arrival < tasks[b].arrival;
    });

    priority_queue<int, vector<int>, CMP_SJF> pq((CMP_SJF(&tasks)));
    int idx = 0;
    double currentTime = 0;
    double totalTurnaroundTime = 0;
    double totalWaitingTime = 0;

    while (idx < n || !pq.empty()) {
        while (idx < n && tasks[ord[idx]].arrival <= currentTime) {
            pq.push(ord[idx]);
            idx++;
        }

        if (pq.empty()) {
            if (idx < n) {
                currentTime = tasks[ord[idx]].arrival;
                continue;
            }
        } else {
            int id = pq.top(); pq.pop();
            double startTime = currentTime;
            double finishTime = startTime + tasks[id].remaining;
            totalTurnaroundTime += finishTime - tasks[id].arrival;
            totalWaitingTime += startTime - tasks[id].arrival;
            currentTime = finishTime;
        }
    }
    return make_pair(totalTurnaroundTime / n, totalWaitingTime / n);
}

pair<double,double> rr(vector<Task> tasks, double q) {
    int n = tasks.size();
    vector<int> ord(n);
    for (int i = 0; i < n; i++) ord[i] = i;

    sort(ord.begin(), ord.end(), [&](int a, int b) {
        if (tasks[a].arrival == tasks[b].arrival) return tasks[a].id < tasks[b].id;
        return tasks[a].arrival < tasks[b].arrival;
    });

    for (int i = 0; i < n; i++) tasks[i].remaining = tasks[i].burst;

    queue<int> qu;
    int idx = 0;
    double currentTime = 0;
    double totalTurnaroundTime = 0;
    double totalWaitingTime = 0;

    while (idx < n || !qu.empty()) {
        while (idx < n && tasks[ord[idx]].arrival <= currentTime) {
            qu.push(ord[idx]);
            idx++;
        }

        if (qu.empty()) {
            if (idx < n) {
                currentTime = tasks[ord[idx]].arrival;
                continue;
            }
        } else {
            int id = qu.front(); qu.pop();
            double slice = min(tasks[id].remaining, q);
            double startTime = currentTime;
            currentTime += slice;
            tasks[id].remaining -= slice;

            while (idx < n && tasks[ord[idx]].arrival <= currentTime) {
                qu.push(ord[idx]);
                idx++;
            }

            if (tasks[id].remaining > 1e-9) {
                qu.push(id);
            } else {
                totalTurnaroundTime += currentTime - tasks[id].arrival;
                totalWaitingTime += (currentTime - tasks[id].arrival) - tasks[id].burst;
            }
        }
    }
    return make_pair(totalTurnaroundTime / n, totalWaitingTime / n);
}

struct CMP_PRIORITY {
    const vector<Task>* t;
    CMP_PRIORITY(const vector<Task>* x) : t(x) {}
    bool operator()(int a, int b) const {
        if (abs((*t)[a].priority - (*t)[b].priority) < 1e-9) {
            return (*t)[a].id > (*t)[b].id;
        }
        return (*t)[a].priority > (*t)[b].priority;
    }
};

pair<double,double> priority_np(vector<Task> tasks) {
    int n = tasks.size();
    vector<int> ord(n);
    for (int i = 0; i < n; i++) {
        ord[i] = i;
        tasks[i].remaining = tasks[i].burst;
    }

    sort(ord.begin(), ord.end(), [&](int a, int b) {
        if (tasks[a].arrival == tasks[b].arrival) return tasks[a].id < tasks[b].id;
        return tasks[a].arrival < tasks[b].arrival;
    });

    priority_queue<int, vector<int>, CMP_PRIORITY> pq((CMP_PRIORITY(&tasks)));
    int idx = 0;
    double currentTime = 0;
    double totalTurnaroundTime = 0;
    double totalWaitingTime = 0;

    while (idx < n || !pq.empty()) {
        while (idx < n && tasks[ord[idx]].arrival <= currentTime) {
            pq.push(ord[idx]);
            idx++;
        }

        if (pq.empty()) {
            if (idx < n) {
                currentTime = tasks[ord[idx]].arrival;
                continue;
            }
        } else {
            int id = pq.top(); pq.pop();
            double startTime = currentTime;
            double finishTime = startTime + tasks[id].remaining;
            totalTurnaroundTime += finishTime - tasks[id].arrival;
            totalWaitingTime += startTime - tasks[id].arrival;
            currentTime = finishTime;
        }
    }
    return make_pair(totalTurnaroundTime / n, totalWaitingTime / n);
}

pair<double,double> priority_p(vector<Task> tasks) {
    int n = tasks.size();
    vector<int> ord(n);
    for (int i = 0; i < n; i++) {
        ord[i] = i;
        tasks[i].remaining = tasks[i].burst;
    }

    sort(ord.begin(), ord.end(), [&](int a, int b) {
        if (tasks[a].arrival == tasks[b].arrival) return tasks[a].id < tasks[b].id;
        return tasks[a].arrival < tasks[b].arrival;
    });

    priority_queue<int, vector<int>, CMP_PRIORITY> pq((CMP_PRIORITY(&tasks)));
    int idx = 0;
    double currentTime = 0;
    double totalTurnaroundTime = 0;
    double totalWaitingTime = 0;

    while (idx < n || !pq.empty()) {
        while (idx < n && tasks[ord[idx]].arrival <= currentTime) {
            pq.push(ord[idx]);
            idx++;
        }

        if (pq.empty()) {
            if (idx < n) {
                currentTime = tasks[ord[idx]].arrival;
                continue;
            }
        } else {
            int id = pq.top(); pq.pop();

            double execTime = tasks[id].remaining;
            if (idx < n && tasks[ord[idx]].arrival < currentTime + execTime) {
                execTime = tasks[ord[idx]].arrival - currentTime;
            }

            tasks[id].remaining -= execTime;
            currentTime += execTime;

            while (idx < n && tasks[ord[idx]].arrival <= currentTime) {
                pq.push(ord[idx]);
                idx++;
            }

            if (tasks[id].remaining > 1e-9) {
                pq.push(id);
            } else {
                totalTurnaroundTime += currentTime - tasks[id].arrival;
                totalWaitingTime += (currentTime - tasks[id].arrival) - tasks[id].burst;
            }
        }
    }
    return make_pair(totalTurnaroundTime / n, totalWaitingTime / n);
}

int main() {
    int n;
    if (!(cin >> n)) return 0;
    vector<Task> tasks(n);

    for (int i = 0; i < n; i++) {
        if (!(cin >> tasks[i].burst >> tasks[i].arrival >> tasks[i].priority)) return 0;
        tasks[i].id = i + 1;
        tasks[i].remaining = tasks[i].burst;
    }

    double quantum;
    if (!(cin >> quantum)) return 0;

    pair<double,double> f = fcfs(tasks);
    pair<double,double> s = sjf_np(tasks);
    pair<double,double> r = rr(tasks, quantum);
    pair<double,double> pn = priority_np(tasks);
    pair<double,double> pp = priority_p(tasks);

    cout << fixed << setprecision(1);
    cout << "Algorithm|Avg Turnaround Time|Avg Waiting Time" << endl;
    cout << "FCFS|" << f.first << "|" << f.second << endl;
    cout << "SJF|" << s.first << "|" << s.second << endl;
    cout << "Round Robin (Q=" << quantum << ")|" << r.first << "|" << r.second << endl;
    cout << "Priority (Non-preemptive)|" << pn.first << "|" << pn.second << endl;
    cout << "Priority (Preemptive)|" << pp.first << "|" << pp.second << endl;

    return 0;
}
