#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Worker {
public:
    std::string name;

     Worker(const string& name) : name(name) {}
};

class Manager : public Worker {
public:
     Manager(const string& name) : Worker(name) {}

    void assignTasks(int commandId) {
        int seed = commandId + this->name.length();
        std::srand(seed);

        int tasksCount = rand() % (team->workers.size() + 1);
        std::cout << "Manager " << this->name << " assigned " << tasksCount << " tasks to the team." << std::endl;

        std::vector<char> taskTypes = {'A', 'B', 'C'};
        for (int i = 0; i < tasksCount; i++) {
            int workerIndex = rand() % team->workers.size();
            Worker* worker = team->workers[workerIndex];
            char taskType = taskTypes[rand() % taskTypes.size()];
            team->assignTask(worker, taskType);
        }
    }

    void setTeam(vector<Worker*>& workers) {
        team = new Team(workers);
    }

    ~Manager() {
        delete team;
    }

private:
    class Team {
    public:
        vector<Worker*> workers;

         Team(std::vector<Worker*>& workers) : workers(workers) {}

        void assignTask(Worker* worker, char taskType) {
            std::cout << "Worker " << worker->name << " received a task of type " << taskType << "." << std::endl;
        }

        ~Team() {
            for (Worker* worker : workers) {
                delete worker;
            }
        }
    };

    Team* team;
};

class CEO : public Worker {
public:
     CEO(const std::string& name) : Worker(name) {}

    void setManagers(vector<Manager*>& managers) {
        this->managers = managers;
    }

    void setCommands(vector<int>& commands) {
        this->commands = commands;
    }

    void startSimulation() {
        for (int command : commands) {
            int managerIndex = command % managers.size();
            Manager* manager = managers[managerIndex];
            manager->assignTasks(command);
        }
    }

    ~CEO() {
        for (Manager* manager : managers) {
            delete manager;
        }
    }

private:
    vector<Manager*> managers;
    vector<int> commands;
};

int main()
{
    int numCommands, numWorkers;
    cout << "Enter the number of commands: ";
    cin >> numCommands;
    cout << "Enter the number of workers per command: ";
    cin >> numWorkers;

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

        manager->setTeam(workers);
        managers.push_back(manager);
        commands.push_back(i);
    }

    CEO* ceo = new CEO("CEO");
    ceo->setManagers(managers);
    ceo->setCommands(commands);
    ceo->startSimulation();

    delete ceo;


      
    return 0;
}
