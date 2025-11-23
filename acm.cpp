#include <bits/stdc++.h>
using namespace std;

struct Task {
    int id;
    long double bt, at, pr;
};

pair<long double,long double> fcfs(vector<Task> v) {
    int n = v.size();
    sort(v.begin(), v.end(), [&](const Task &a, const Task &b){
        if (a.at == b.at) return a.id < b.id;
        return a.at < b.at;
    });
    long double t = 0, sumTat = 0, sumWt = 0;
    for (auto &x : v) {
        if (t < x.at) t = x.at;
        t += x.bt;
        long double tat = t - x.at;
        sumTat += tat;
        sumWt += tat - x.bt;
    }
    return {sumTat / n, sumWt / n};
}

pair<long double,long double> sjf(vector<Task> v) {
    int n = v.size();
    sort(v.begin(), v.end(), [&](const Task &a, const Task &b){
        if (a.at == b.at) return a.id < b.id;
        return a.at < b.at;
    });
    using Node = pair<long double,int>;
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    int i = 0, done = 0;
    long double t = 0, sumTat = 0, sumWt = 0;
    while (done < n) {
        while (i < n && v[i].at <= t) {
            pq.push({v[i].bt, i});
            i++;
        }
        if (pq.empty()) {
            t = v[i].at;
            continue;
        }
        auto cur = pq.top(); pq.pop();
        int idx = cur.second;
        if (t < v[idx].at) t = v[idx].at;
        t += v[idx].bt;
        long double tat = t - v[idx].at;
        sumTat += tat;
        sumWt += tat - v[idx].bt;
        done++;
    }
    return {sumTat / n, sumWt / n};
}

pair<long double,long double> rr(vector<Task> v, long double q) {
    int n = v.size();
    sort(v.begin(), v.end(), [&](const Task &a, const Task &b){
        if (a.at == b.at) return a.id < b.id;
        return a.at < b.at;
    });
    vector<long double> rem(n);
    for (int i = 0; i < n; i++) rem[i] = v[i].bt;
    long double t = 0, sumTat = 0, sumWt = 0;
    int done = 0, iNext = 0;
    queue<int> ready;

    while (done < n) {
        if (ready.empty()) {
            if (iNext < n) {
                if (t < v[iNext].at) t = v[iNext].at;
                ready.push(iNext);
                iNext++;
            }
        }
        int idx = ready.front(); ready.pop();
        long double runFor = min(q, rem[idx]);
        t += runFor;
        rem[idx] -= runFor;
        if (rem[idx] > 0) {
            ready.push(idx);
        } else {
            long double tat = t - v[idx].at;
            sumTat += tat;
            sumWt += tat - v[idx].bt;
            done++;
        }
        while (iNext < n && v[iNext].at <= t) {
            ready.push(iNext);
            iNext++;
        }
    }
    return {sumTat / n, sumWt / n};
}

pair<long double,long double> priority_np(vector<Task> v) {
    int n = v.size();
    sort(v.begin(), v.end(), [&](const Task &a, const Task &b){
        if (a.at == b.at) return a.id < b.id;
        return a.at < b.at;
    });
    using Node = pair<long double,int>;
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    int i = 0, done = 0;
    long double t = 0, sumTat = 0, sumWt = 0;
    while (done < n) {
        while (i < n && v[i].at <= t) {
            pq.push({v[i].pr, i});
            i++;
        }
        if (pq.empty()) {
            t = v[i].at;
            continue;
        }
        auto cur = pq.top(); pq.pop();
        int idx = cur.second;
        if (t < v[idx].at) t = v[idx].at;
        t += v[idx].bt;
        long double tat = t - v[idx].at;
        sumTat += tat;
        sumWt += tat - v[idx].bt;
        done++;
    }
    return {sumTat / n, sumWt / n};
}

pair<long double,long double> priority_p(vector<Task> v) {
    int n = v.size();
    sort(v.begin(), v.end(), [&](const Task &a, const Task &b){
        if (a.at == b.at) return a.id < b.id;
        return a.at < b.at;
    });
    vector<long double> rem(n);
    for (int i = 0; i < n; i++) rem[i] = v[i].bt;
    using Node = pair<long double,int>;
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    int iNext = 0, done = 0;
    long double t = 0, sumTat = 0, sumWt = 0;
    const long double INF = numeric_limits<long double>::infinity();

    while (done < n) {
        while (iNext < n && v[iNext].at <= t) {
            pq.push({v[iNext].pr, iNext});
            iNext++;
        }
        if (pq.empty()) {
            t = v[iNext].at;
            continue;
        }
        auto cur = pq.top(); pq.pop();
        int idx = cur.second;
        long double nextArrival = (iNext < n ? v[iNext].at : INF);
        long double timeToFinish = rem[idx];
        long double timeToNextArrival = nextArrival - t;
        if (timeToFinish <= timeToNextArrival) {
            t += timeToFinish;
            rem[idx] = 0;
            long double tat = t - v[idx].at;
            sumTat += tat;
            sumWt += tat - v[idx].bt;
            done++;
        } else {
            t += timeToNextArrival;
            rem[idx] -= timeToNextArrival;
            pq.push({v[idx].pr, idx});
        }
    }
    return {sumTat / n, sumWt / n};
}

int main() {
    int n;
    cin >> n;
    vector<Task> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].bt >> v[i].at >> v[i].pr;
        v[i].id = i;
    }
    long double quantum;
    cin >> quantum;

    auto f = fcfs(v);
    auto s = sjf(v);
    auto r = rr(v, quantum);
    auto pn = priority_np(v);
    auto pp = priority_p(v);

    cout << fixed << setprecision(4);
    cout << "Algorithm|Avg Turnaround Time|Avg Waiting Time\n";
    cout << "FCFS|" << f.first << "|" << f.second << "\n";
    cout << "SJF|" << s.first << "|" << s.second << "\n";
    cout << "Round Robin (Q=" << quantum << ")|" << r.first << "|" << r.second << "\n";
    cout << "Priority (Non-preemptive)|" << pn.first << "|" << pn.second << "\n";
    cout << "Priority (Preemptive)|" << pp.first << "|" << pp.second << "\n";
}
