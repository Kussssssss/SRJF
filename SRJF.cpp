// Bài tập về nhà

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process
{
    int id;
    int AT;
    int BT;
    int ST;
    int ET;
    int RT;
    bool checked;
};

void SRJF(vector<Process> &processes)
{
    int time = 0;
    bool cpuBusy = false;
    Process *currentProcess = nullptr;

    while (true)
    {
        bool allchecked = true;
        for (Process &p : processes)
        {
            if (!p.checked)
            {
                allchecked = false;
                break;
            }
        }
        if (allchecked)
            break;

        vector<Process *> arrived;
        for (Process &p : processes)
        {
            if (p.AT <= time && !p.checked)
            {
                arrived.push_back(&p);
            }
        }

        if (!arrived.empty())
        {
            sort(arrived.begin(), arrived.end(), [](Process *a, Process *b)
                 { return a->RT < b->RT; });

            if (currentProcess != arrived.front())
            {
                if (cpuBusy)
                {
                    cout << "P" << currentProcess->id << ": come out: " << time << ", ";
                }
                currentProcess = arrived.front();
                if (currentProcess->ST == -1)
                {
                    currentProcess->ST = time;
                }
                cout << "P" << currentProcess->id << ": come in: " << time << ", ";
                cpuBusy = true;
            }
        }

        if (cpuBusy)
        {
            currentProcess->RT--;
            if (currentProcess->RT == 0)
            {
                currentProcess->ET = time + 1;
                cout << "P" << currentProcess->id << ": end: " << currentProcess->ET << endl;
                currentProcess->checked = true;
                cpuBusy = false;
            }
        }
        time++;
    }
}

int main()
{
    cout << "Example 1 --> Output:" << endl;
    vector<Process> processes1 = {
        {1, 0, 10, -1, -1, 10, false},
        {2, 1, 3, -1, -1, 3, false},
        {3, 2, 2, -1, -1, 2, false},
        {4, 3, 1, -1, -1, 1, false},
        {5, 4, 5, -1, -1, 5, false}};
    SRJF(processes1);

    cout << endl;

    cout << "Example 2 --> Output:" << endl;
    vector<Process> processes2 = {
        {1, 0, 10, -1, -1, 10, false},
        {2, 2, 29, -1, -1, 29, false},
        {3, 4, 3, -1, -1, 3, false},
        {4, 5, 7, -1, -1, 7, false},
        {5, 7, 12, -1, -1, 12, false}};
    SRJF(processes2);

    return 0;
}
