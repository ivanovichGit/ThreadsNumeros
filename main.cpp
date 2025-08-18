/* Nombre: ThreadsNumeros
Objetivo: Crear un programa que ejecute 10 threads, cada uno sumará 100 números aleatorios entre 1 y 1000.
Mostrar el resultado de cada thread. Enunciar el thread con puntación más alta.
Fecha: 18 Agosto 2025
Creador: Ivanovich Chiu
 */

#include<iostream>
#include<thread>
#include<string>
#include<cstdlib>
#include<vector>
#include<numeric>

class RandomThrds {
    private:
        std::vector<int> randomVec;
        int randomSum;
        std::string name;

    public:
        void setRandomNums() {
            for(int i = 0; i < 100; i++) {
                randomVec.push_back(rand() % 1001);
            }
        }

        std::vector<int> getRandomVec() {
            std::cout <<  name <<": [ ";
            for (auto& n : randomVec) {
                std::cout << n << " ";
            }
            std::cout << "]" << std::endl;
            return randomVec;
        }

        void calRandomSum() {
            // std::accumulate(start_iterator, end_iterator, initial_value_of_sum)
            this -> randomSum = std::accumulate(randomVec.begin(), randomVec.end(), 0);
        }

        int getRandomSum() {
            return randomSum;
        }

        void printRandomSum() const {
            std::cout << name << " Sum: " << randomSum << std::endl;
        }

        std::string getName() {
            return name;
        }

        // Calculate Obj metrics
        void calObj(){
            setRandomNums();
            calRandomSum();
            printRandomSum();
        }

        // Constructor
        RandomThrds(std::string name):name(name) {}
};

int main() {
    // Get a different random number each time the program runs
    srand(time(0));

    // Objects
    RandomThrds alan("Alan");
    RandomThrds bryan("Bryan");
    RandomThrds chris("Chris");
    RandomThrds dani("Dani");
    RandomThrds emma("Emma");
    RandomThrds fred("Fred");
    RandomThrds gina("Gina");
    RandomThrds hugo("Hugo");
    RandomThrds ivan("Ivan");
    RandomThrds julia("Julia");

    // Vector of objects and threads
    std::vector<RandomThrds*> objs = {&alan,&bryan,&chris,&dani,&emma,&fred,&gina,&hugo,&ivan,&julia};
    std::vector<std::thread> threads;

    // 10 threads by reference from all objs
    for (auto& obj : objs) {
        // Create new thread
        threads.emplace_back([&](){
            obj->calObj();
        });
    }

    // 10 Joins by reference from all threads
    for (auto& th : threads) {
        th.join();
    }

    // Compare them using the objects vector
    std::string maxName;
    int maxSum = 0;

    // First is max
    maxName = objs[0]->getName();
    maxSum = objs[0]->getRandomSum();;

    // Compare all and save max
    for (int i = 1; i < 10; i++) {

        if (maxSum < objs[i]->getRandomSum()) {

            maxName = objs[i]->getName();
            maxSum = objs[i]->getRandomSum();;

        }
    }

    // Max Result
    std::cout << "\nMax Result: " << maxName << " - " << maxSum << std::endl;

    return 0;
}
