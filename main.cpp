#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Worker;
class Team;
class Manager;
class Company;

// Класс Роботник
class Worker {
private:
  string name;
  bool isBusy;
  string taskType;

public:
  Worker(const string& name) : name(name), isBusy(false), taskType("") {}

  void setBusy(bool status, const string& task) {
    isBusy = status;
    taskType = task;
    cout << name << " is now busy with task " << taskType << endl;
  }

  string getName() const { return name; }
  bool getIsBusy() const { return isBusy; }
};

// Класс Команда
class Team {
private:
  vector<Worker*> workers;

public:
  void addWorker(Worker* worker) {
    workers.push_back(worker);
  }

  vector<Worker*> getWorkers() const { return workers; }
};

// Класс Менеджер
class Manager : public Worker {
private:
  Team* team;
  int id;

public:
  Manager(const string& name, int id) : Worker(name), team(nullptr), id(id) {}

  void setTeam(Team* t) {
    team = t;
  }

  void assignTasks(int command) {
    if (team == nullptr) return;

    // вычисление количества задач
    int tasksCount = rand() % (team->getWorkers().size() + 1);

    string taskTypes[] = { "A", "B", "C" };

    for (Worker* worker : team->getWorkers()) {
      if (!worker->getIsBusy() && tasksCount > 0) {
        worker->setBusy(true, taskTypes[rand() % 3]);
        tasksCount--;
      }
    }
  }
};

// Класс "Компания" (роль "Босса")
class Company {
private:
  vector<Manager*> managers;

public:
  void addManager(Manager* manager) {
    managers.push_back(manager);
  }

  void giveCommand(int command) {
    for (Manager* manager : managers) {
      manager->assignTasks(command);
    }
  }
};

int main() {

   srand(time(0));

  int numManagers, numWorkers;
  cout << "Enter the number of managers: ";
  cin >> numManagers;
  cout << "Enter the number of workers for each manager: ";
  cin >> numWorkers;

  Company company;
  vector<vector<Worker*>> allWorkers;

  for (int i = 1; i <= numManagers; ++i) {
    Manager* manager = new Manager("Manager" + to_string(i), i);
    Team* team = new Team();

    vector<Worker*> workers;
    for (int j = 1; j <= numWorkers; ++j) {
      Worker* worker = new Worker("Worker" + to_string(i) + "_" + to_string(j));
      workers.push_back(worker);
      team->addWorker(worker);
    }


    allWorkers.push_back(workers);
    manager->setTeam(team);
    company.addManager(manager);
  }

  bool allBusy = false;
  while (!allBusy) {
    int command;
    cout << "Enter a command (integer) for the company: ";
    cin >> command;

    company.giveCommand(command);

    allBusy = true;
    for (const auto& workers : allWorkers) {
      for (const auto& worker : workers) {
        if (!worker->getIsBusy()) {
          allBusy = false;
          break;
        }
      }
      if (!allBusy) break;
    }
  }

  cout << "All workers are busy. Program is completed." << endl;

  return 0;
}
  
