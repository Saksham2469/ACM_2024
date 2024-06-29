#include <bits/stdc++.h>
using namespace std;

struct Task
{
    double id;
    double burstTime;
    double arrivalTime;
    double priority;
    double remainingTime;

    Task(double id, double burstTime, double arrivalTime, double priority = 0)
        : id(id), burstTime(burstTime), arrivalTime(arrivalTime), priority(priority), remainingTime(burstTime) {}
};

bool compareBurstTime(const Task &a, const Task &b)
{
    return a.burstTime < b.burstTime;
}

bool compareArrivalTime(const Task &a, const Task &b)
{
    return a.arrivalTime < b.arrivalTime;
}

bool comparePriority(const Task &a, const Task &b)
{
    return a.priority > b.priority;
}

void fcfs(const vector<Task> &tasks, vector<double> &summary)
{
    vector<Task> fcfsTasks = tasks;
    sort(fcfsTasks.begin(), fcfsTasks.end(), compareArrivalTime);

    double totalTurnaroundTime = 0;
    double totalWaitingTime = 0;
    double currentTime = 0;

    for (const auto &task : fcfsTasks)
    {
        double startTime = max(currentTime, task.arrivalTime);
        double completionTime = startTime + task.burstTime;
        double turnaroundTime = completionTime - task.arrivalTime;
        double waitingTime = startTime - task.arrivalTime;

        totalTurnaroundTime += turnaroundTime;
        totalWaitingTime += waitingTime;

        currentTime = completionTime;
    }

    double avgTurnaroundTime = totalTurnaroundTime / fcfsTasks.size();
    double avgWaitingTime = totalWaitingTime / fcfsTasks.size();

    summary.push_back(avgTurnaroundTime);
    summary.push_back(avgWaitingTime);
}

void sjf(const vector<Task> &tasks, vector<double> &summary)
{
    vector<Task> sjfTasks = tasks;
    sort(sjfTasks.begin(), sjfTasks.end(), compareArrivalTime);

    double totalTurnaroundTime = 0;
    double totalWaitingTime = 0;
    double currentTime = 0;
    priority_queue<Task, vector<Task>, decltype(&compareBurstTime)> pq(compareBurstTime);

    size_t i = 0;
    while (i < sjfTasks.size() || !pq.empty())
    {
        if (pq.empty())
        {
            currentTime = max(currentTime, sjfTasks[i].arrivalTime);
        }

        while (i < sjfTasks.size() && sjfTasks[i].arrivalTime <= currentTime)
        {
            pq.push(sjfTasks[i]);
            i++;
        }

        if (!pq.empty())
        {
            Task task = pq.top();
            pq.pop();
            double startTime = currentTime;
            double completionTime = startTime + task.burstTime;
            double turnaroundTime = completionTime - task.arrivalTime;
            double waitingTime = startTime - task.arrivalTime;

            totalTurnaroundTime += turnaroundTime;
            totalWaitingTime += waitingTime;

            currentTime = completionTime;
        }
    }

    double avgTurnaroundTime = totalTurnaroundTime / sjfTasks.size();
    double avgWaitingTime = totalWaitingTime / sjfTasks.size();

    summary.push_back(avgTurnaroundTime);
    summary.push_back(avgWaitingTime);
}

void rr(const vector<Task> &tasks, double quantum, vector<double> &summary)
{
    vector<Task> rrTasks = tasks;
    sort(rrTasks.begin(), rrTasks.end(), compareArrivalTime);

    double totalTurnaroundTime = 0;
    double totalWaitingTime = 0;
    double currentTime = 0;
    queue<Task> q;
    size_t i = 0;

    while (i < rrTasks.size() || !q.empty())
    {
        if (q.empty())
        {
            currentTime = max(currentTime, rrTasks[i].arrivalTime);
        }

        while (i < rrTasks.size() && rrTasks[i].arrivalTime <= currentTime)
        {
            q.push(rrTasks[i]);
            i++;
        }

        if (!q.empty())
        {
            Task task = q.front();
            q.pop();

            double timeSlice = min(task.remainingTime, quantum);
            task.remainingTime -= timeSlice;
            currentTime += timeSlice;

            while (i < rrTasks.size() && rrTasks[i].arrivalTime <= currentTime)
            {
                q.push(rrTasks[i]);
                i++;
            }

            if (task.remainingTime > 0)
            {
                q.push(task);
            }
            else
            {
                double turnaroundTime = currentTime - task.arrivalTime;
                double waitingTime = turnaroundTime - task.burstTime;

                totalTurnaroundTime += turnaroundTime;
                totalWaitingTime += waitingTime;
            }
        }
    }

    double avgTurnaroundTime = totalTurnaroundTime / rrTasks.size();
    double avgWaitingTime = totalWaitingTime / rrTasks.size();

    summary.push_back(avgTurnaroundTime);
    summary.push_back(avgWaitingTime);
}

void priorityNonPreemptive(const vector<Task> &tasks, vector<double> &summary)
{
    vector<Task> priorityTasks = tasks;
    sort(priorityTasks.begin(), priorityTasks.end(), compareArrivalTime);

    double totalTurnaroundTime = 0;
    double totalWaitingTime = 0;
    double currentTime = 0;
    priority_queue<Task, vector<Task>, decltype(&comparePriority)> pq(comparePriority);

    size_t i = 0;
    while (i < priorityTasks.size() || !pq.empty())
    {
        if (pq.empty())
        {
            currentTime = max(currentTime, priorityTasks[i].arrivalTime);
        }

        while (i < priorityTasks.size() && priorityTasks[i].arrivalTime <= currentTime)
        {
            pq.push(priorityTasks[i]);
            i++;
        }

        if (!pq.empty())
        {
            Task task = pq.top();
            pq.pop();
            double startTime = currentTime;
            double completionTime = startTime + task.burstTime;
            double turnaroundTime = completionTime - task.arrivalTime;
            double waitingTime = startTime - task.arrivalTime;

            totalTurnaroundTime += turnaroundTime;
            totalWaitingTime += waitingTime;

            currentTime = completionTime;
        }
    }

    double avgTurnaroundTime = totalTurnaroundTime / priorityTasks.size();
    double avgWaitingTime = totalWaitingTime / priorityTasks.size();

    summary.push_back(avgTurnaroundTime);
    summary.push_back(avgWaitingTime);
}

void priorityPreemptive(const vector<Task> &tasks, vector<double> &summary)
{
    vector<Task> priorityTasks = tasks;
    sort(priorityTasks.begin(), priorityTasks.end(), compareArrivalTime);

    double totalTurnaroundTime = 0;
    double totalWaitingTime = 0;
    double currentTime = 0;
    priority_queue<Task, vector<Task>, decltype(&comparePriority)> pq(comparePriority);

    size_t i = 0;
    while (i < priorityTasks.size() || !pq.empty())
    {
        if (pq.empty())
        {
            currentTime = max(currentTime, priorityTasks[i].arrivalTime);
        }

        while (i < priorityTasks.size() && priorityTasks[i].arrivalTime <= currentTime)
        {
            pq.push(priorityTasks[i]);
            i++;
        }

        if (!pq.empty())
        {
            Task task = pq.top();
            pq.pop();
            double timeSlice = min(task.remainingTime, 1.0);
            task.remainingTime -= timeSlice;
            currentTime += timeSlice;

            while (i < priorityTasks.size() && priorityTasks[i].arrivalTime <= currentTime)
            {
                pq.push(priorityTasks[i]);
                i++;
            }

            if (task.remainingTime > 0)
            {
                pq.push(task);
            }
            else
            {
                double turnaroundTime = currentTime - task.arrivalTime;
                double waitingTime = turnaroundTime - task.burstTime;

                totalTurnaroundTime += turnaroundTime;
                totalWaitingTime += waitingTime;
            }
        }
    }

    double avgTurnaroundTime = totalTurnaroundTime / priorityTasks.size();
    double avgWaitingTime = totalWaitingTime / priorityTasks.size();

    summary.push_back(avgTurnaroundTime);
    summary.push_back(avgWaitingTime);
}

int main()
{
    double numTasks = 10;
    cin >> numTasks;

    vector<Task> tasks;
    double burstTime, arrivalTime, priority;
    for (double i = 0; i < numTasks; ++i)
    {
        cin >> burstTime >> arrivalTime >> priority;
        tasks.emplace_back(i + 1, burstTime, arrivalTime, priority);
    }

    double quantum;
    cin >> quantum;

    vector<double> summary_fcfs;
    fcfs(tasks, summary_fcfs);

    vector<double> summary_sjf;
    sjf(tasks, summary_sjf);

    vector<double> summary_rr;
    rr(tasks, quantum, summary_rr);

    vector<double> summary_priority_nonpreemptive;
    priorityNonPreemptive(tasks, summary_priority_nonpreemptive);

    vector<double> summary_priority_preemptive;
    priorityPreemptive(tasks, summary_priority_preemptive);

    cout << "\nSummary Table (Average Turnaround Time and Average Waiting Time):\n";
    cout << "------------------------------------------------------------------\n";
    cout << setw(30) << "Algorithm" << setw(25) << "Avg Turnaround Time" << setw(25) << "Avg Waiting Time" << endl;
    cout << "------------------------------------------------------------------\n";
    cout << setw(30) << "FCFS";
    for (const auto &value : summary_fcfs)
    {
        cout << setw(25) << fixed << setprecision(4) << value;
    }
    cout << endl;

    cout << setw(30) << "SJF";
    for (const auto &value : summary_sjf)
    {
        cout << setw(25) << fixed << setprecision(4) << value;
    }
    cout << endl;

    cout << setw(30) << "Round Robin (Quantum = " << quantum << ")";
    for (const auto &value : summary_rr)
    {
        cout << setw(16) << fixed << setprecision(4) << value;
    }
    cout << endl;

    cout << setw(30) << "Priority (Non-preemptive)";
    for (const auto &value : summary_priority_nonpreemptive)
    {
        cout << setw(25) << fixed << setprecision(4) << value;
    }
    cout << endl;

    cout << setw(30) << "Priority (Preemptive)";
    for (const auto &value : summary_priority_preemptive)
    {
        cout << setw(25) << fixed << setprecision(4) << value;
    }
    cout << endl;

    cout << "------------------------------------------------------------------\n";

    return 0;
}
