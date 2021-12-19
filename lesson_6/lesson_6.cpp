/*
* Домашнее задание к уроку 6
* курса "C++: сложные моменты"
* автор Недокунев А.В.
* среда разработки VSCode /компилятор MinGW/
* codepage UTF-8
*/
#include <iostream>
#include <mutex>
#include <thread>
#include <set>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
//#include <random>

using namespace std;

mutex m;

/*
1.	Создайте потокобезопасную оболочку для объекта cout. 
Назовите ее pcout. 
Необходимо, чтобы несколько потоков могли обращаться к pcout и информация выводилась в консоль. 
Продемонстрируйте работу pcout.
*/

void pcout(string out) {
    m.lock();
    cout << out <<endl;
    m.unlock();
}

/*
2.	Реализовать функцию, возвращающую i-ое простое число 
(например, миллионное простое число равно 15485863). 
Вычисления реализовать во вторичном потоке. 
В консоли отображать прогресс вычисления. 
*/

void printPbar(int percent) {
	cout << "\r[";
	for (int i = 0; i < 100; ++i) {
		if (i <= percent) cout << "#";
		else cout << "-";
	}
	cout << "] " << percent << " %";
}


int isPrime(int num) {
    if (num == 2) return 1;
    if (num == 0 || num == 1 || num % 2 == 0) return 0;
    for (int i = 3; i * i <= num; i += 2){
        if (num % i == 0) return 0;
    }
    return 1;
}

void findPrime(int num, pair<int, int>& countPrime) {
    while(countPrime.first < num) {
        countPrime.second++;
        if (isPrime(countPrime.second)) {
            countPrime.first++;
        }
    }
}

int simpleNumeric(int serialNumber) {
	const float progress =  static_cast<float>(serialNumber) / 100; //прогрессбар по проценту от номера найденного простого числа к номеру искомого
	pair<int, int> numeric{0,1}; //numeric.first - счетчик простых чисел, пока 0, numeric.second - число-кандидат для проверки на простое число, 1, потому что ряд простых начинается с 2, а в цикле while функции findPrime первым идет numeric.second++.
	thread calculate(findPrime, serialNumber, ref(numeric));
	calculate.detach(); //делаем поток calculate фоновым (отсоединяем поток)
	while (numeric.first < serialNumber) {
		this_thread::sleep_for(200ms);// каждые 200мс перерисовываем прогрессбар
		m.lock();
		printPbar(static_cast<int>(numeric.first / progress));
		m.unlock();
	}
    cout << endl << "A prime number with an ordinal number " << serialNumber << " is ";
	return numeric.second;
}

/*
3.	Промоделировать следующую ситуацию. 
Есть два человека (2 потока): хозяин и вор. 
Хозяин приносит домой вещи 
(функция добавляющая случайное число в вектор с периодичностью 1 раз в секунду). 
При этом у каждой вещи есть своя ценность. 
Вор забирает вещи 
(функция, которая находит наибольшее число и удаляет из вектора с периодичностью 1 раз в 0.5 секунд), 
каждый раз забирает вещь с наибольшей ценностью. 
*/

//void printHome(int countThings) {
//	cout << "\rHome has " << countThings << " things";
//}

void owner(multiset<int>& things) {
    while (!things.empty()) {
        m.lock();
        things.insert(rand() % 100);
        cout << "\rHome has " << things.size() << " things   ";
//        cout << "Home has " << things.size() << " things (owner)" << endl;
        m.unlock();
        this_thread::sleep_for(1s);
    }
    cout << endl << "owner end";
}

void theif(multiset<int>& things) {
    while (!things.empty()) {
        m.lock();
        things.erase(--things.end());
        cout << "\rHome has " << things.size() << " things   ";
//        cout << "Home has " << things.size() << " things (thief)" << endl;
        m.unlock();
        this_thread::sleep_for(500ms);
    }
    cout << endl << "theif end";
}

//======================================================================
int main(const int argc, const char **argv){

    thread t_1(pcout, "It's thread #1");
    thread t_2(pcout, "It's thread #2");
    thread t_3(pcout, "It's thread #3");
    t_1.join();
    t_2.join();
    t_3.join();

    int oNumber = 0;
    cout << "Enter ordimal number ";
    cin >> oNumber;
    cout << simpleNumeric(oNumber) << endl;

    multiset<int> things{};
   	for (size_t i = 0; i < 10; ++i) things.insert(rand() % 100);
    thread O(owner, ref(things));
    thread T(theif, ref(things));
    O.join();
    T.join();

    return 0;
}
