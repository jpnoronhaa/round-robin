#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
using namespace std;

class PCB {
  public:
    string name;
    int priority;
    int burst_time;
    int waiting_time;
    int completion_time;
    int remaining_time;
    bool finished;
};

int numberProcesses = 0;
int quantum = 0;
int queuesLength[4] = {0,0,0,0};
int totalTime = 0;
PCB** queues;
PCB* priority0;
PCB* priority1;
PCB* priority2;
PCB* priority3;

PCB* readFile() {
  fstream file;
  file.open("input.txt", ios::in);
  if (file.is_open()) {
    string line;
    getline(file, line);
    istringstream iss(line);
    iss >> numberProcesses;
    getline(file, line);
    istringstream qtd(line);
    qtd >> quantum;
    PCB* processes = (PCB *)malloc(numberProcesses * sizeof(PCB));
    int i = 0;
    while(getline(file, line)){
      istringstream iss(line);
      if (!(iss >> processes[i].name >> processes[i].priority >> processes[i].burst_time)) { break; }
      processes[i].remaining_time = processes[i].burst_time;
      processes[i].waiting_time = 0;
      processes[i].completion_time = 0;
      processes[i].finished = false;
      i++;
    }
    file.close();
    return processes;
  }
  return NULL;
}

void createPriorityQueue (PCB* processes) {
  for (int i = 0; i < numberProcesses; i++) {
    switch (processes[i].priority) {
      case 0:
        queuesLength[0] += 1;
        break;
      case 1:
        queuesLength[1] += 1;
        break;
      case 2:
        queuesLength[2] += 1;
        break;
      case 3:
        queuesLength[3] += 1;
        break;
      default:
        break;
    }
  }
  priority0 = (PCB *)malloc(queuesLength[0] * sizeof(PCB));
  priority1 = (PCB *)malloc(queuesLength[1] * sizeof(PCB));
  priority2 = (PCB *)malloc(queuesLength[2] * sizeof(PCB));
  priority3 = (PCB *)malloc(queuesLength[3] * sizeof(PCB));
  int counters[4] = {0, 0, 0, 0,};
  for (int i = 0; i < numberProcesses; i++) {
    switch (processes[i].priority) {
      case 0:
        priority0[counters[0]] = processes[i];
        counters[0] += 1;
        break;
      case 1:
        priority1[counters[1]] = processes[i];
        counters[1] += 1;
        break;
      case 2:
        priority2[counters[2]] = processes[i];
        counters[2] += 1;
        break;
      case 3:
        priority3[counters[3]] = processes[i];
        counters[3] += 1;
        break;
      default:
        break;
    }
  }
}

void runProcesses() {
  bool finished = false;
  int timer = 0;

  while (!finished) {
    finished = true;
    for (int i = 0; i < queuesLength[0]; i++) {
      if (!priority0[i].finished) {
        finished = false;

        if ((priority0[i].remaining_time - quantum) < 0) {
          timer += priority0[i].remaining_time;
          priority0[i].remaining_time = 0;
        } else {
          priority0[i].remaining_time -= quantum;
          timer += quantum;
        }

        if (priority0[i].remaining_time == 0) {
          priority0[i].finished = true;
          priority0[i].waiting_time = timer - priority0[i].burst_time;
          priority0[i].completion_time = priority0[i].burst_time + priority0[i].waiting_time;
        }
      }
    }

    for (int i = 0; i < queuesLength[1]; i++) {
      if (!priority1[i].finished) {
        finished = false;

        if ((priority1[i].remaining_time - quantum) < 0) {
          timer += priority1[i].remaining_time;
          priority1[i].remaining_time = 0;
        } else {
          priority1[i].remaining_time -= quantum;
          timer += quantum;
        }

        if (priority1[i].remaining_time == 0) {
          priority1[i].finished = true;
          priority1[i].waiting_time = timer - priority1[i].burst_time;
          priority1[i].completion_time = priority1[i].burst_time + priority1[i].waiting_time;
        }
      }
    }

    for (int i = 0; i < queuesLength[2]; i++) {
      if (!priority2[i].finished) {
        finished = false;

        if ((priority2[i].remaining_time - quantum) < 0) {
          timer += priority2[i].remaining_time;
          priority2[i].remaining_time = 0;
        } else {
          priority2[i].remaining_time -= quantum;
          timer += quantum;
        }

        if (priority2[i].remaining_time == 0) {
          priority2[i].finished = true;
          priority2[i].waiting_time = timer - priority2[i].burst_time;
          priority2[i].completion_time = priority2[i].burst_time + priority2[i].waiting_time;
        }
      }
    }

    for (int i = 0; i < queuesLength[3]; i++) {
      if (!priority3[i].finished) {
        finished = false;

        if ((priority3[i].remaining_time - quantum) < 0) {
          timer += priority3[i].remaining_time;
          priority3[i].remaining_time = 0;
        } else {
          priority3[i].remaining_time -= quantum;
          timer += quantum;
        }

        if (priority3[i].remaining_time == 0) {
          priority3[i].finished = true;
          priority3[i].waiting_time = timer - priority3[i].burst_time;
          priority3[i].completion_time = priority3[i].burst_time + priority3[i].waiting_time;
        }
      }
    }
  }

  totalTime = timer;
}

int main() {
  PCB* processes = readFile();
  createPriorityQueue(processes);
  cout << "Lista 1 " << endl; 
  for (int j = 0; j < queuesLength[0]; j++) {
    cout << priority0[j].name << " " << priority0[j].priority << " " << priority0[j].burst_time << endl;
  }
  cout << "Lista 2 " << endl; 
  for (int j = 0; j < queuesLength[1]; j++) {
    cout << priority1[j].name << " " << priority1[j].priority << " " << priority1[j].burst_time << endl;
  }
  cout << "Lista 3 " << endl; 
  for (int j = 0; j < queuesLength[2]; j++) {
    cout << priority2[j].name << " " << priority2[j].priority << " " << priority2[j].burst_time << endl;
  }
  cout << "Lista 4 " << endl; 
  for (int j = 0; j < queuesLength[3]; j++) {
    cout << priority3[j].name << " " << priority3[j].priority << " " << priority3[j].burst_time << endl;
  }

  runProcesses();
  cout << "Tempo total: " << totalTime << endl;

  cout << "Lista 1 " << endl; 
  for (int j = 0; j < queuesLength[0]; j++) {
    cout << priority0[j].name << " " << priority0[j].waiting_time << " " << priority0[j].completion_time << endl;
  }
  cout << "Lista 2 " << endl; 
  for (int j = 0; j < queuesLength[1]; j++) {
    cout << priority1[j].name << " " << priority1[j].waiting_time << " " << priority1[j].completion_time << endl;
  }
  cout << "Lista 3 " << endl; 
  for (int j = 0; j < queuesLength[2]; j++) {
    cout << priority2[j].name << " " << priority2[j].waiting_time << " " << priority2[j].completion_time << endl;
  }
  cout << "Lista 4 " << endl; 
  for (int j = 0; j < queuesLength[3]; j++) {
    cout << priority3[j].name << " " << priority3[j].waiting_time << " " << priority3[j].completion_time << endl;
  }
  
  return 0;
}

