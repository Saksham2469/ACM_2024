#include <bits/stdc++.h>
using namespace std;

struct Task {
    int id;
    double burst;
    double arrival;
    double priority;
    double remaining;
};

bool cmpArrival(const Task &a, const Task &b) {
    if (a.arrival == b.arrival) return a.id < b.id;
    return a.arrival < b.arrival;
}

struct CMP_SJF {
    vector<Task> *t;
    CMP_SJF(vector<Task> *ref) { t = ref; }
    bool operator()(int a, int b) const {
        if ((*t)[a].burst == (*t)[b].burst)
            return (*t)[a].arrival > (*t)[b].arrival;
        return (*t)[a].burst > (*t)[b].burst;
    }
};

struct CMP_PRIORITY {
    vector<Task> *t;
    CMP_PRIORITY(vector<Task> *ref) { t = ref; }
    bool operator()(int a, int b) const {
        if ((*t)[a].priority == (*t)[b].priority)
            return (*t)[a].arrival > (*t)[b].arrival;
        return (*t)[a].priority < (*t)[b].priority;
    }
};

pair<double,double> fcfs(vector<Task> tasks) {
    sort(tasks.begin(), tasks.end(), cmpArrival);
    double time = 0, totalT = 0, totalW = 0;
    int n = tasks.size();

    for (int i = 0; i < n; i++) {
        if (time < tasks[i].arrival) time = tasks[i].arrival;
        double start = time;
        double finish = start + tasks[i].burst;
        totalT += finish - tasks[i].arrival;
        totalW += start - tasks[i].arrival;
        time = finish;
    }
    return make_pair(totalT/n, totalW/n);
}

pair<double,double> sjf_np(vector<Task> tasks) {
    int n = tasks.size();
    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;

    sort(order.begin(), order.end(), 
        [&](int a, int b){ return tasks[a].arrival < tasks[b].arrival; }
    );

    priority_queue<int, vector<int>, CMP_SJF> pq((CMP_SJF(&tasks)));
    int idx = 0;
    double time = 0, totalT = 0, totalW = 0;
    
    while (idx < n || !pq.empty()) {
        if (pq.empty() && time < tasks[order[idx]].arrival)
            time = tasks[order[idx]].arrival;

        while (idx < n && tasks[order[idx]].arrival <= time) {
            pq.push(order[idx]);
            idx++;
        }

        if (!pq.empty()) {
            int id = pq.top(); pq.pop();
            double start = time;
            double finish = start + tasks[id].burst;
            totalT += finish - tasks[id].arrival;
            totalW += start - tasks[id].arrival;
            time = finish;
        }
    }

    return make_pair(totalT/n, totalW/n);
}

pair<double,double> rr(vector<Task> tasks, double q) {
    int n = tasks.size();
    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;

    sort(order.begin(), order.end(), 
        [&](int a, int b){ return tasks[a].arrival < tasks[b].arrival; }
    );

    queue<int> que;
    int idx = 0;
    double time = 0, totalT = 0, totalW = 0;

    while (idx < n || !que.empty()) {
        if (que.empty() && time < tasks[order[idx]].arrival)
            time = tasks[order[idx]].arrival;

        while (idx < n && tasks[order[idx]].arrival <= time) {
            que.push(order[idx]);
            idx++;
        }

        int id = que.front(); que.pop();

        double slice = min(tasks[id].remaining, q);
        tasks[id].remaining -= slice;
        time += slice;

        while (idx < n && tasks[order[idx]].arrival <= time) {
            que.push(order[idx]);
            idx++;
        }

        if (tasks[id].remaining > 0)
            que.push(id);
        else {
            double tat = time - tasks[id].arrival;
            double wt = tat - tasks[id].burst;
            totalT += tat;
            totalW += wt;
        }
    }

    return make_pair(totalT/n, totalW/n);
}

pair<double,double> priority_np(vector<Task> tasks) {
    int n = tasks.size();
    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;

    sort(order.begin(), order.end(), 
        [&](int a, int b){ return tasks[a].arrival < tasks[b].arrival; }
    );

    priority_queue<int, vector<int>, CMP_PRIORITY> pq((CMP_PRIORITY(&tasks)));
    int idx = 0;
    double time = 0, totalT = 0, totalW = 0;

    while (idx < n || !pq.empty()) {
        if (pq.empty() && time < tasks[order[idx]].arrival)
            time = tasks[order[idx]].arrival;

        while (idx < n && tasks[order[idx]].arrival <= time) {
            pq.push(order[idx]);
            idx++;
        }

        int id = pq.top(); pq.pop();
        double start = time;
        double finish = start + tasks[id].burst;
        totalT += finish - tasks[id].arrival;
        totalW += start - tasks[id].arrival;
        time = finish;
    }

    return make_pair(totalT/n, totalW/n);
}

pair<double,double> priority_p(vector<Task> tasks) {
    int n = tasks.size();
    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;

    sort(order.begin(), order.end(), 
        [&](int a, int b){ return tasks[a].arrival < tasks[b].arrival; }
    );

    priority_queue<int, vector<int>, CMP_PRIORITY> pq((CMP_PRIORITY(&tasks)));
    int idx = 0;
    double time = 0, totalT = 0, totalW = 0;

    while (idx < n || !pq.empty()) {
        if (pq.empty() && time < tasks[order[idx]].arrival)
            time = tasks[order[idx]].arrival;

        while (idx < n && tasks[order[idx]].arrival <= time) {
            pq.push(order[idx]);
            idx++;
        }

        int id = pq.top(); pq.pop();

        double nextArrival = (idx < n ? tasks[order[idx]].arrival : 1e18);
        double slice = min(tasks[id].remaining, nextArrival - time);

        time += slice;
        tasks[id].remaining -= slice;

        while (idx < n && tasks[order[idx]].arrival <= time) {
            pq.push(order[idx]);
            idx++;
        }

        if (tasks[id].remaining > 0)
            pq.push(id);
        else {
            double tat = time - tasks[id].arrival;
            double wt = tat - tasks[id].burst;
            totalT += tat;
            totalW += wt;
        }
    }

    return make_pair(totalT/n, totalW/n);
}

int main() {
    int n;
    cin >> n;
    vector<Task> tasks(n);

    for (int i = 0; i < n; i++) {
        double b, a, p;
        cin >> b >> a >> p;
        tasks[i].id = i + 1;
        tasks[i].burst = b;
        tasks[i].arrival = a;
        tasks[i].priority = p;
        tasks[i].remaining = b;
    }

    double quantum;
    cin >> quantum;

    pair<double,double> f = fcfs(tasks);
    pair<double,double> s = sjf_np(tasks);
    pair<double,double> r = rr(tasks, quantum);
    pair<double,double> pn = priority_np(tasks);
    pair<double,double> pp = priority_p(tasks);

    cout << "Algorithm|Avg Turnaround Time|Avg Waiting Time\n";
    cout << "FCFS|" << f.first << "|" << f.second << "\n";
    cout << "SJF|" << s.first << "|" << s.second << "\n";
    cout << "Round Robin (Q=" << quantum << ")|" << r.first << "|" << r.second << "\n";
    cout << "Priority (Non-preemptive)|" << pn.first << "|" << pn.second << "\n";
    cout << "Priority (Preemptive)|" << pp.first << "|" << pp.second << "\n";

    return 0;
}
