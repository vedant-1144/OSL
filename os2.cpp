#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Process {
    int pid, arrival, burst, priority, ct, tat, wt, remaining;
};

void calculateMetrics(vector<Process> &p) {
    for (auto &proc : p) {
        proc.tat = proc.ct - proc.arrival;
        proc.wt = proc.tat - proc.burst;
    }
}

void printTable(const vector<Process> &p) {
    
    cout << "\n" << setw(6) << "PID" << setw(10) << "Arrival" << setw(10) << "Burst"
         << setw(15) << "Completion" << setw(15) << "Turnaround" << setw(15) << "Waiting\n";

    for (const auto &proc : p) {
        cout << setw(6) << proc.pid << setw(10) << proc.arrival << setw(10) << proc.burst
             << setw(15) << proc.ct << setw(15) << proc.tat << setw(15) << proc.wt << "\n";
    }
}

void fcfs(vector<Process> p) {

    sort(p.begin(), p.end(), [](const Process &a, const Process &b) {
        return a.arrival < b.arrival;
    });
    
    int time = p[0].arrival;
    for (auto &proc : p) {
        if (time < proc.arrival) {
            time = proc.arrival;
        }
        time += proc.burst;
        proc.ct = time;
    }
    
    calculateMetrics(p);
    printTable(p);
}

void sjfNonPreemptive(vector<Process> &p) {
    int time = 0, completed = 0;
    while (completed < p.size()) {
        int idx = -1, min_burst = 1e9;
        for (int i = 0; i < p.size(); i++) {
            if (p[i].arrival <= time && p[i].ct == 0 && p[i].burst < min_burst) {
                min_burst = p[i].burst;
                idx = i;
            }
        }
        if (idx == -1) time++;
        else {
            time += p[idx].burst;
            p[idx].ct = time;
            completed++;
        }
    }
    calculateMetrics(p);
    printTable(p);
}

void sjfPreemptive(vector<Process> &p) {
    int time = 0, completed = 0;
    while (completed < p.size()) {
        int idx = -1, minBurst = 1e9;
        for (int i = 0; i < p.size(); i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && p[i].remaining < minBurst) {
                minBurst = p[i].remaining;
                idx = i;
            }
        }
        if (idx == -1) time++;
        else {
            time++;
            p[idx].remaining--;
            if (p[idx].remaining == 0) {
                p[idx].ct = time;
                completed++;
            }
        }
    }
    calculateMetrics(p);
    printTable(p);
}

void priorityNonPreemptive(vector<Process> &p) {
    int time = 0, completed = 0, n = p.size();
    while (completed < n) {
        int idx = -1, min_priority = 1e9;
        
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].ct == 0 && p[i].priority < min_priority) {
                min_priority = p[i].priority;
                idx = i;
            }
        }
        if (idx == -1) time++;
        else {
            time += p[idx].burst;
            p[idx].ct = time;
            completed++;
        }
    }
    calculateMetrics(p);
    printTable(p);
}

void priorityPreemptive(vector<Process> &p) {
    int time = 0, completed = 0, n = p.size();
    while (completed < n) {
        int idx = -1, min_priority = 1e9;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && p[i].priority < min_priority) {
                min_priority = p[i].priority;
                idx = i;
            }
        }
        if (idx == -1) time++;
        else {
            time++;
            p[idx].remaining--;
            if (p[idx].remaining == 0) {
                p[idx].ct = time;
                completed++;
            }
        }
    }
    calculateMetrics(p);
    printTable(p);
}

void roundRobin(vector<Process>& p, int tq) {
    int time = 0, completed = 0;
    queue<int> q;
    vector<bool> isQueued(p.size(), false);

    while (completed < p.size()) {
        for (int i = 0; i < p.size(); i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && !isQueued[i]) {
                q.push(i);
                isQueued[i] = true;
            }
        }

        if (q.empty()) {
            time++;
            continue;
        }

        int i = q.front(); q.pop();
        int execTime = min(p[i].remaining, tq);
        
        time += execTime;
        p[i].remaining -= execTime;
        
        for (int j = 0; j < p.size(); j++) {
            if (p[j].arrival <= time && p[j].remaining > 0 && !isQueued[j]) {
                q.push(j);
                isQueued[j] = true;
            }
        }

        if (p[i].remaining == 0) {
            p[i].ct = time;
            completed++;
        } else {
            q.push(i);
        }
    }

    calculateMetrics(p);
    printTable(p);
}

int main() {
    int choice, tq;
    while (true) {
        int n;
        cout << "Enter number of processes (Enter 0 to exit): ";
        cin >> n;
        if (n == 0) break;

        vector<Process> p(n);

        for (int i = 0; i < n; i++) {
            p[i].pid = i + 1;
            cout << "Enter Arrival and Burst Time for P" << p[i].pid << ": ";
            cin >> p[i].arrival >> p[i].burst;
            p[i].remaining = p[i].burst;
        }

        cout << "Select Scheduling Algorithm:\n1. FCFS\n2. SJF (Non-Preemptive)\n3. SJF (Preemptive)\n4. Priority (Non-Preemptive)\n5. Priority (Preemptive)\n6. Round Robin\nChoice: ";
        cin >> choice;

        if (choice == 4 || choice == 5) {
            for (int i = 0; i < n; i++) {
                cout << "Enter Priority for P" << p[i].pid << ": ";
                cin >> p[i].priority;
            }
        }

        if (choice == 6) {
            cout << "Enter Time Quantum: ";
            cin >> tq;
        }

        switch (choice) {
            case 1: fcfs(p); break;
            case 2: sjfNonPreemptive(p); break;
            case 3: sjfPreemptive(p); break;
            case 4: priorityNonPreemptive(p); break;
            case 5: priorityPreemptive(p); break;
            case 6: roundRobin(p, tq); break;
            default: cout << "Invalid choice!\n"; continue;
        }
    }
    return 0;
}
