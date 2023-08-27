#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>


using namespace std;

 class Worker {
public:
    string name;

     Worker(const string& name) : name(name) {}
};

class Manager : public Worker {
public:
     Manager(const string& name) : Worker(name) {}

    void assignTasks(int commandId, vector<Worker*>& workers) {
        int seed = commandId + this->name.length();
        srand(seed);

        int tasksCount = rand() % (workers.size() + 1);
        cout << "Manager " << this->name << " assigned " << tasksCount << " tasks to the team." << endl;

        vector<char> taskTypes = {'A', 'B', 'C'};
        for (int i = 0; i < tasksCount; i++) {
            int workerIndex = rand() % workers.size();
            Worker* worker = workers[workerIndex];
            char taskType = taskTypes[rand() % taskTypes.size()];
            assignTask(worker, taskType);
        }
    }

    void assignTask(Worker* worker, char taskType) {
        cout << "Worker " << worker->name << " received a task of type " << taskType << "." << endl;
    }
};

class CEO : public Worker {
public:
     CEO(const string& name) : Worker(name) {}

    void startSimulation(int numCommands, int numWorkers) {
        vector<Manager*> managers;
        vector<int> commands;

        for (int i = 0; i < numCommands; i++) {
            string managerName = "Manager " + to_string(i);
            Manager* manager = new Manager(managerName);

            std::vector<Worker*> workers;
            for (int j = 0; j < numWorkers; j++) {
                string workerName = "Worker " + to_string(i * numWorkers + j);
                Worker* worker = new Worker(workerName);
                workers.push_back(worker);
            }

            managers.push_back(manager);
            commands.push_back(i);
            manager->assignTasks(i, workers);
        }

        // Освобождаем память
        for (Manager* manager : managers) {
            delete manager;
        }
    }
};

int main()
{
    int numCommands, numWorkers;
    cout << "Enter the number of commands: ";
    cin >> numCommands;
    cout << "Enter the number of workers per command: ";
    cin >> numWorkers;

    CEO* ceo = new CEO("CEO");
    ceo->startSimulation(numCommands, numWorkers);

    delete ceo;
 
    return 0;
}
