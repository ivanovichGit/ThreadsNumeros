/* Nombre: ThreadsNumeros
* Objetivo: Crear un programa que ejecute 10 threads, cada uno sumará 100 números
aleatorios entre 1 y 1000. Mostrar el resultado de cada thread. Enunciar el
thread con puntación más alta
 Fecha: 18 Agosto 2025
 */

#include<iostream>
#include<memory>
#include<thread>
#include<string>
#include<print>
#include<mutex>
#include<condition_variable>
#include<cstdlib>
#include <vector> // For vector 10 numbers
#include <numeric> // Required for std::accumulate

class CalSum {
    private:
        std::vector<int> numsVec;
        int finalSum;
        std::string name;

    public:
        void setnumsVec() {
            // Get a different random number each time the program runs
            srand(time(0));

            for(int i = 0; i < 100; i++) {
                numsVec.insert(numsVec.begin(),rand() % 1001);
            }
        }

        std::vector<int> getnumsVec() {
            std::cout <<  name <<": [ ";
            for (auto& n : numsVec) {
                std::cout << n << " ";
            }
            std::cout << "]" << std::endl;
            return numsVec;
        }

        void setFinalSum() {
            // std::accumulate(start_iterator, end_iterator, initial_value_of_sum)
            this -> finalSum = std::accumulate(numsVec.begin(), numsVec.end(), 0);
        }

        int getFinalSum() {
            return finalSum;
        }

        std::string getName() {
            return name;
        }

        void calSumIndv(){
            this -> setnumsVec();
            // this -> getnumsVec();
            this -> setFinalSum();
            std::cout << name << " Sum: "<<  finalSum << std::endl;
        }

        // Constructor
        CalSum(std::string name):name(name) {
        }
};

int main() {
    // Objects
    CalSum alan("Alan");
    CalSum bryan("Bryan");
    CalSum chris("Chris");
    CalSum dani("Dani");
    CalSum emma("Emma");
    CalSum fred("Fred");
    CalSum gina("Gina");
    CalSum hugo("Hugo");
    CalSum ivan("Ivan");
    CalSum julia("Julia");

    // Vector Objs and Threads
    std::vector<CalSum*> objs = { &alan,&bryan,&chris,&dani,&emma,&fred,&gina,&hugo,&ivan,&julia};
    std::vector<std::thread> threads;

    // 10 threads by reference from all objs
    for (auto& obj : objs) {
        // Create new thread
        threads.emplace_back([&](){
            obj->calSumIndv();
        });
    }

    // 10 Joins by reference from all threads created
    for (auto& th : threads) {
        th.join();
    }

    // Compare them with Objs Vector
    std::string maxName;
    int maxSum = 0;

    // First is max
    maxName = objs[0]->getName();
    maxSum = objs[0]->getFinalSum();;

    // Compare all and save max
    for (int i = 1; i < 10; i++) {
        if (maxSum < objs[i]->getFinalSum()) {
            maxName = objs[i]->getName();
            maxSum = objs[i]->getFinalSum();;
        }
    }

    // Final Result
    std::cout << "\nMax Result: " << maxName << " - " << maxSum << std::endl;

    return 0;
}