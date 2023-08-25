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

    void assignTasks(int commandId) {
        int seed = commandId + this->name.length();
        std::srand(seed);

        int tasksCount = rand() % (team->workers.size() + 1);
        std::cout << "Manager " << this->name << " assigned " << tasksCount << " tasks to the team." << std::endl;

        for (int i = 0; i < tasksCount; i++) {
            int workerIndex = rand() % team->workers.size();
            Worker* worker = team->workers[workerIndex];
            team->assignTask(worker);
        }
    }

    void setTeam(std::vector<Worker*>& workers) {
        team = new Team(workers);
    }

private:
    class Team {
    public:
        std::vector<Worker*> workers;

        explicit Team(std::vector<Worker*>& workers) : workers(workers) {}

        void assignTask(Worker* worker) {
            std::cout << "Worker " << worker->name << " received a task." << std::endl;
        }
    };

    Team* team;
};

class CEO : public Worker {
public:
    explicit CEO(const std::string& name) : Worker(name) {}

    void setManagers(std::vector<Manager*>& managers) {
        this->managers = managers;
    }

    void setCommands(std::vector<int>& commands) {
        this->commands = commands;
    }

    void startSimulation() {
        for (int command : commands) {
            int managerIndex = command % managers.size();
            Manager* manager = managers[managerIndex];
            manager->assignTasks(command);
        }
    }

private:
    std::vector<Manager*> managers;
    std::vector<int> commands;
};

int main()
{
      int numCommands, numWorkers;
    std::cout << "Enter the number of commands: ";
    std::cin >> numCommands;
    std::cout << "Enter the number of workers per command: ";
    std::cin >> numWorkers;

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

        manager->setTeam(workers);
        managers.push_back(manager);
        commands.push_back(i);
    }

    CEO* ceo = new CEO("CEO");
    ceo->setManagers(managers);
    ceo->setCommands(commands);
    ceo->startSimulation();

    // Освобождаем память
    for (Manager* manager : managers) {
        delete manager;
    }
    delete ceo;  
    
     /* Программа начинается с запроса количества команд и количество работников в каждой команде. 
Затем создаются менеджеры и рабочие, и им назначаются задачи на основе случайных чисел. В конце освобождается выделенная память.

Обратите внимание, что в этом коде нет обработки ошибок и валидации пользовательского ввода. В реальном проекте это также следует учесть.*/
    return 0;
}
