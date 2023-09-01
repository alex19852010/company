#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Worker {
public:
  string name;
  bool isBusy;
  string taskType;

  Worker(const string& name) : name(name), isBusy(false), taskType("") {}

  void setBusy(bool status, const string& task) {
    isBusy = status;
    taskType = task;
  }
};

class Manager : public Worker {
public:
  Manager(const string& name) : Worker(name) {}

  void assignTasks(vector<Worker*>& workers, int command) {
    int tasksCount = rand() % (command + 1);
    cout << "Manager " << this->name << " assigned " << tasksCount << " tasks." << endl;
    if (tasksCount == 0) {
      return;  // If no tasks, return without assigning
    }

    string taskTypes[3] = { "A", "B", "C" };

    int assigned = 0;
    for (Worker* worker : workers) {
      if (!worker->isBusy) {
        string task = taskTypes[rand() % 3];
        worker->setBusy(true, task);
        assigned++;
        cout << "Worker " << worker->name << " is now busy with task type " << task << "." << endl;
        if (assigned >= tasksCount) break;
      }
    }
  }
};

class Boss {
public:
  void giveCommand(vector<Manager*>& managers, vector<vector<Worker*>>& allWorkers) {
    int command;
    cout << "Enter the command number: ";
    cin >> command;

    for (size_t i = 0; i < managers.size(); ++i) {
      managers[i]->assignTasks(allWorkers[i], command);
    }
  }
};

int main() {
  srand(static_cast<unsigned int>(time(0)));

  int numManagers, numWorkers;
  cout << "Enter the number of managers: ";
  cin >> numManagers;
  cout << "Enter the number of workers for each manager: ";
  cin >> numWorkers;

  // Create workers and managers based on user input
  vector<vector<Worker*>> allWorkers;
  vector<Manager*> managers;

  for (int i = 1; i <= numManagers; ++i) {
    Manager* manager = new Manager("M" + to_string(i));
    managers.push_back(manager);

    vector<Worker*> workers;
    for (int j = 1; j <= numWorkers; ++j) {
      workers.push_back(new Worker("W" + to_string(i) + "_" + to_string(j)));
    }
    allWorkers.push_back(workers);
  }

  // Create boss
  Boss boss;

  bool allBusy = false;
  while (!allBusy) {
    boss.giveCommand(managers, allWorkers);

    // Check if all workers are busy
    allBusy = true;
    for (const auto& workers : allWorkers) {
      for (const auto& worker : workers) {
        if (!worker->isBusy) {
          allBusy = false;
          break;
        }
      }
      if (!allBusy) break;
    }
  }

  cout << "All workers are busy. Program is terminating." << endl;

  // Cleanup
  for (const auto& workers : allWorkers) {
    for (const auto& worker : workers) {
      delete worker;
    }
  }
  for (const auto& manager : managers) {
    delete manager;
  }

  return 0;
}
