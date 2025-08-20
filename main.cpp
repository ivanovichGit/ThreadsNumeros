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

class RandomThread {
    private:
        std::vector<int> randomVector;
        int randomSum;
        std::string name;

        void setRandomNumbers() {
            for(int i = 0; i < 100; i++) {
                randomVector.push_back(rand() % 1001);
            }
        }

        void runRandomSum() {
            // std::accumulate(start_iterator, end_iterator, initial_value_of_sum)
            this -> randomSum = std::accumulate(randomVector.begin(), randomVector.end(), 0);
        }

        void printRandomSum() const {
            std::cout << name << " Sum: " << randomSum << std::endl;
        }

    public:
        std::vector<int> getRandomVector() {
            std::cout <<  name <<": [ ";
            for (auto& n : randomVector) {
                std::cout << n << " ";
            }
            std::cout << "]" << std::endl;
            return randomVector;
        }
        int runRandomSum() {
            return randomSum;
        }
        std::string getName() {
            return name;
        }

        // Calculate Obj metrics
        void execute(){
            setRandomNumbers();
            calRandomSum();
            printRandomSum();
        }

        // Constructor
        RandomThread(std::string name):name(name) {}
};

int main() {
    // Get a different random number each time the program runs
    srand(time(0));

    // Objects
    RandomThread alan("Alan");
    RandomThread bryan("Bryan");
    RandomThread chris("Chris");
    RandomThread dani("Dani");
    RandomThread emma("Emma");
    RandomThread fred("Fred");
    RandomThread gina("Gina");
    RandomThread hugo("Hugo");
    RandomThread ivan("Ivan");
    RandomThread julia("Julia");

    // Vector of objects and threads
    std::vector<RandomThread*> objs = {&alan,&bryan,&chris,&dani,&emma,&fred,&gina,&hugo,&ivan,&julia};
    std::vector<std::thread> threads;

    // 10 threads by reference from all objs
    for (auto& obj : objs) {
        // Create new thread
        threads.emplace_back([&](){
            obj->execute();
        });
    }

    // 10 Joins by reference from all threads
    for (auto& th : threads) {
        th.join();
    }

    // Sort with pointers
    std::sort(objs.begin(), objs.end(),
    [](RandomThread* firstPointer, RandomThread* secondPointer) {
              return firstPointer->getRandomSum() > secondPointer->getRandomSum();
          });

    // Max Result with Sort
    std::cout << "\nMax Result: " << objs[0]->getName() << " - " << objs[0]->getRandomSum()<< std::endl;

    return 0;
}
