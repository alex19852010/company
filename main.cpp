#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>


using namespace std;

 class Worker {
public:
    std::string name;

    explicit Worker(const std::string& name) : name(name) {}
};

class Manager : public Worker {
public:
    explicit Manager(const std::string& name) : Worker(name) {}

    void assignTasks(int commandId, std::vector<Worker*>& workers) {
        int seed = commandId + this->name.length();
        std::srand(seed);

        int tasksCount = rand() % (workers.size() + 1);
        std::cout << "Manager " << this->name << " assigned " << tasksCount << " tasks to the team." << std::endl;

        std::vector<char> taskTypes = {'A', 'B', 'C'};
        for (int i = 0; i < tasksCount; i++) {
            int workerIndex = rand() % workers.size();
            Worker* worker = workers[workerIndex];
            char taskType = taskTypes[rand() % taskTypes.size()];
            assignTask(worker, taskType);
        }
    }

    void assignTask(Worker* worker, char taskType) {
        std::cout << "Worker " << worker->name << " received a task of type " << taskType << "." << std::endl;
    }
};

class CEO : public Worker {
public:
    explicit CEO(const std::string& name) : Worker(name) {}

    void startSimulation(int numCommands, int numWorkers) {
        std::vector<Manager*> managers;
        std::vector<int> commands;

        for (int i = 0; i < numCommands; i++) {
            std::string managerName = "Manager " + std::to_string(i);
            Manager* manager = new Manager(managerName);

            std::vector<Worker*> workers;
            for (int j = 0; j < numWorkers; j++) {
                std::string workerName = "Worker " + std::to_string(i * numWorkers + j);
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
    std::cout << "Enter the number of commands: ";
    std::cin >> numCommands;
    std::cout << "Enter the number of workers per command: ";
    std::cin >> numWorkers;

    CEO* ceo = new CEO("CEO");
    ceo->startSimulation(numCommands, numWorkers);

    delete ceo;
 
    return 0;
}
