#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Worker {
public:
    string name;
    string task;

    Worker(const string& name) : name(name) {}

    bool isTaskAssigned() {
        return !task.empty();
    }
};

class Team {
public:
    vector<Worker*> workers;

    void addWorker(Worker* worker) {
        workers.push_back(worker);
    }

    bool allWorkersBusy() {
        for (Worker* worker : workers) {
            if (!worker->isTaskAssigned()) {
                return false;
            }
        }
        return true;
    }
};

class Manager {
public:
    string name;

    Manager(const string& name) : name(name) {}

    void assignTasks(Team& team, int tasksCount) {
        cout << "Manager " << this->name << " assigned " << tasksCount << " tasks to the team." << endl;

        vector<char> taskTypes = {'A', 'B', 'C'};
        int workerIndex = 0;

        while (tasksCount > 0 && !team.allWorkersBusy()) {
            Worker* worker = team.workers[workerIndex];
            if (!worker->isTaskAssigned()) {
                char taskType = taskTypes[rand() % taskTypes.size()];
                worker->task = taskType;
                cout << "Worker " << worker->name << " received a task of type " << taskType << "." << endl;
                tasksCount--;
            }
            workerIndex = (workerIndex + 1) % team.workers.size();
        }
    }
};

class CEO {
public:
    string name;

    CEO(const string& name) : name(name) {}

    void startSimulation(int numCommands, int numWorkers) {
        srand(time(0));

        for (int i = 0; i < numCommands; i++) {
            string managerName = "Manager " + to_string(i + 1);
            Manager* manager = new Manager(managerName);

            Team team;
            for (int j = 0; j < numWorkers; j++) {
                string workerName = "Worker " + to_string(i * numWorkers + j);
                Worker* worker = new Worker(workerName);
                team.addWorker(worker);
            }

            int tasksCount = rand() % (team.workers.size() + 1);
            manager->assignTasks(team, tasksCount);
            cout << endl;

            // Удаление созданных объектов
            for (Worker* worker : team.workers) {
                delete worker;
            }
            delete manager;
        }

    }
};


int main()
{
    int numCommands, numWorkers;
    cout << "Enter the number of commands: ";
    cin >> numCommands;
    cout << "Enter the number of workers in each command: ";
    cin >> numWorkers;

    CEO* ceo = new CEO("CEO");
    ceo->startSimulation(numCommands, numWorkers);

    delete ceo;
    return 0;
      
    return 0;
}
