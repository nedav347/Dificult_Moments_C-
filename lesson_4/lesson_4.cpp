/*
* Домашнее задание к уроку 3
* курса "C++: сложные моменты"
* автор Недокунев А.В.
* среда разработки VSCode /компилятор MinGW/
* codepage UTF-8
*/
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <random>

using namespace std;

/*
1. Имеется отсортированный массив целых чисел. 
Необходимо разработать функцию insert_sorted, 
которая принимает вектор и новое число и вставляет новое число в определенную позицию в векторе, 
чтобы упорядоченность контейнера сохранялась. 
Реализуйте шаблонную функцию insert_sorted, 
которая сможет аналогично работать с любым контейнером, 
содержащим любой тип значения. 
*/

void insert_sorted(vector<int>& v, int num) {
    if (*v.begin() < *(v.end()-1)) {
        auto it = lower_bound(v.begin(), v.end(), num);
        v.insert(it, num);
    } else {
        auto it = lower_bound(v.rbegin(), v.rend(), num);
        v.insert(it.base(), num);
    }
}

template<typename TC, typename TN>
void insert_sorted_templ(TC &v, TN num) {
    if (v.front() < v.back()) {
        auto it = lower_bound(v.begin(), v.end(), num);
        v.insert(it, num);
    } else {
        auto it = lower_bound(v.rbegin(), v.rend(), num);
        v.insert(it.base(), num);
    }
}

template<typename T>
void _print_(const T &v) {
    cout << "======================" << endl;
    for (const auto &i : v) {
        cout << i << ' ';
    }
    cout << endl;
}

//======================================================================
int main(const int argc, const char **argv){
	vector<int> vrising{ 1,2,4,5,6,8,9 };
	insert_sorted(vrising, 7);
    insert_sorted_templ(vrising, 3);
    _print_(vrising);

	vector<int> vfalling{ 9,8,6,5,4,2,1 };
	insert_sorted(vfalling, 7);
    insert_sorted_templ(vfalling, 3);
    _print_(vfalling);

/*
2. Сгенерируйте вектор a, состоящий из 100 вещественный чисел, 
представляющий собой значения аналогового сигнала. 
На основе этого массива чисел создайте другой вектор целых чисел b, 
представляющий цифровой сигнал, в котором будут откинуты дробные части чисел. 
Выведите получившиеся массивы чисел. 
Посчитайте ошибку, которой обладает цифровой сигнал по сравнению с аналоговым по формуле:

N-1
 ∑ (a_i-b_i)^2 ,
i=0

где:
N - количество элементов в векторе,
a - элемент вектора с дробными числами,
b - элемент вектора с целыми числами  
Постарайтесь воспользоваться алгоритмическими функциями, не используя циклы.
*/
    vector<double> num_d(100);
    generate(num_d.begin(), num_d.end(), [](){return double((rand() % 100) + double((rand() % 100) / 100.0));});
    _print_(num_d);
    vector<int> num_i(100);
    copy(num_d.begin(), num_d.end(), num_i.begin());
    _print_(num_i);
    double err = inner_product(num_d.begin(), num_d.end(), num_i.begin(), 0.0, plus<double>(), [](double a, int b){
        return pow((a-b), 2);
    });
    cout << endl << "deviation: " << err << endl;
    return 0;
}
