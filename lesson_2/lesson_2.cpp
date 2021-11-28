/*
* Домашнее задание к уроку 2
* курса "C++: сложные моменты"
* автор Недокунев А.В.
* среда разработки VSCode /компилятор MinGW/
* codepage UTF-8
*/
#include <iostream>
#include <optional>
#include <ostream>
#include <utility>
#include <fstream>
#include <vector>
#include <tuple>
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <sstream>
#include "Timer.hpp"

using namespace std;

#define ALIGN 15

/*
1.	Реализуйте шаблонную функцию Swap, 
которая принимает два указателя и обменивает местами значения, 
на которые указывают эти указатели 
(нужно обменивать именно сами указатели, переменные должны оставаться в тех же адресах памяти).
*/

template<class Type>
void Swap (Type*& ptr1, Type*& ptr2) {
	Type* tmpptr = ptr1;
	ptr1 = ptr2;
	ptr2 = tmpptr;
} 

/*
2.	Реализуйте шаблонную функцию SortPointers, 
которая принимает вектор указателей и сортирует указатели по значениям, на которые они указывают.
*/

template<class Type>
void SortPointers(vector<Type*> vectorptr){
	sort(vectorptr.begin(), vectorptr.end(), [](Type* left, Type* right){return *left < *right;});
}

/*
3.	Подсчитайте количество гласных букв в книге “Война и мир”. 
Для подсчета используйте 4 способа:
- count_if и find
- count_if и цикл for
- цикл for и find
- 2 цикла for
Замерьте время каждого способа подсчета и сделайте выводы.
*/

void TestCounters(ifstream& in){
	int counter = 0;
	string vowels = "aeiouyAEIOUY";
	string s;
	Timer timer;
//----------count_if & find-------------------------
	timer.start("count_if & find");
	while(!in.eof()) {
		getline(in, s);
		counter += count_if(s.begin(), s.end(), [&vowels](char n){return vowels.find(n) != string::npos;});		 
	}
	cout << "count_if & find " << counter << " vowels" << endl;
	timer.print();
	s = "";
	counter = 0;
//----------count_if & for-------------------------
	timer.start("count_if & for");
	while(!in.eof()) {
		getline(in, s);
		counter += count_if(s.begin(), s.end(), [&vowels](char n){
			for(char ch : vowels) 
					if(n == ch) return true;		
			return false;
		});		 
	}
	cout << "count_if & for " << counter << " vowels" << endl;
	timer.print();
	s = "";
	counter = 0;
//----------for & find-------------------------
	timer.start("for & find");
	int i = 0;
	while(!in.eof()) {
		getline(in, s);
		for(char a : vowels) {
			i=0;
			while(true){				
				i = s.find(a, i)+1;
				if(i == 0) break;
				++counter;
			}	
		}
	}
	cout << "for & find " << counter << " vowels" << endl;
	timer.print();
	s = "";
	counter = 0;
//----------for & for-------------------------
	timer.start("2for");
	while(!in.eof()) {
		getline(in, s);
		for(char a : vowels) {
			for(char b : s)
				if(a == b) ++counter;
		}
	}
	cout << "2for " << counter << " vowels" << endl;
	timer.print();
}
//======================================================================
int main(const int argc, const char **argv){

int *ptra = new int(10);
int *ptrb = new int(20);
cout << "a = " << *ptra << " ptra = " << ptra << endl;
cout << "b = " << *ptrb << " ptrb = " << ptrb << endl;
Swap(ptra, ptrb);
cout << "a = " << *ptra << " ptra = " << ptra << endl;
cout << "b = " << *ptrb << " ptrb = " << ptrb << endl;

vector <int *> MyVectorPtr; //доделать тест для сортировки
// = {1,3,8,4,6,2,5,7,9,0};

ifstream file("e:\\GB\\Projects\\lesson_2\\WarandPeace.txt");
TestCounters(file);
/*
count_if & find 1095552 vowels
count_if & find: 119.68 ms            II
count_if & for 1095552 vowels
count_if & for: 393.946 ms            III/IV
for & find 1095552 vowels
for & find:     73.8029 ms            I
2for 1095552 vowels
2for:   399.93 ms                     III/IV
*/
    return 0;
}