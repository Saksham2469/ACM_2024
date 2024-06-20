#include <bits/stdc++.h>

using namespace std;

struct Task
{
    double id;
    double burstTime;
    double arrivalTime;
    double priority;

    Task(double id, double burstTime, double arrivalTime, double priority = 0)
        : id(id), burstTime(burstTime), arrivalTime(arrivalTime), priority(priority) {}
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
        double completionTime = currentTime + task.burstTime;
        double turnaroundTime = completionTime - task.arrivalTime;
        double waitingTime = currentTime - task.arrivalTime;

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
    sort(sjfTasks.begin(), sjfTasks.end(), compareBurstTime);

    double totalTurnaroundTime = 0;
    double totalWaitingTime = 0;
    double currentTime = 0;

    for (const auto &task : sjfTasks)
    {
        double completionTime = currentTime + task.burstTime;
        double turnaroundTime = completionTime - task.arrivalTime;
        double waitingTime = currentTime - task.arrivalTime;

        totalTurnaroundTime += turnaroundTime;
        totalWaitingTime += waitingTime;

        currentTime = completionTime;
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

    for (const auto &task : rrTasks)
    {
        double completionTime = currentTime + task.burstTime;
        double turnaroundTime = completionTime - task.arrivalTime;
        double waitingTime = currentTime - task.arrivalTime;

        totalTurnaroundTime += turnaroundTime;
        totalWaitingTime += waitingTime;

        currentTime = completionTime;
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

    for (const auto &task : priorityTasks)
    {
        double completionTime = currentTime + task.burstTime;
        double turnaroundTime = completionTime - task.arrivalTime;
        double waitingTime = currentTime - task.arrivalTime;

        totalTurnaroundTime += turnaroundTime;
        totalWaitingTime += waitingTime;

        currentTime = completionTime;
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

    for (const auto &task : priorityTasks)
    {
        double completionTime = currentTime + task.burstTime;
        double turnaroundTime = completionTime - task.arrivalTime;
        double waitingTime = currentTime - task.arrivalTime;

        totalTurnaroundTime += turnaroundTime;
        totalWaitingTime += waitingTime;

        currentTime = completionTime;
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
        cin >> burstTime;
        cin >> arrivalTime;
        cin >> priority;
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
        cout << setw(25) << fixed << setprecision(4) << value;
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
