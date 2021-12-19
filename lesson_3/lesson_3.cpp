/*
* Домашнее задание к уроку 3
* курса "C++: сложные моменты"
* автор Недокунев А.В.
* среда разработки VSCode /компилятор MinGW/
* codepage UTF-8
*/
#include <iostream>
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

using namespace std;

/*
1.	Написать функцию, добавляющую в конец списка вещественных чисел элемент, 
значение которого равно среднему арифметическому всех его элементов.
*/

/*
2.	Создать класс, представляющий матрицу. Реализовать в нем метод, вычисляющий определитель матрицы.
*/
template <typename Type>
class LESSON32{
private:
    Type** M; // матрица
    int m; // количество строк и столбцов
    int n; // количество столбцов
public:
    LESSON32(){
        n = m = 0;
        M = nullptr; // необязательно
    }
    LESSON32(int _m, int _n){
        m = _m;
        n = _n;
// Выделить память для матрицы
// Выделить память для массива указателей
        M = (Type**) new Type*[m]; // количество строк, количество указателей
// Выделить память для каждого указателя
        for (int i = 0; i < m; i++){
            M[i] = (Type*)new Type[n];
        }
// заполнить массив M нулями
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                M[i][j] = 0;
            }
        }
    }
// Конструктор копирования - обязательный
    LESSON32(const LESSON32& _M){
    // Создается новый объект для которого виделяется память
    // Копирование данных *this <= _M
        m = _M.m;
        n = _M.n;
    // Выделить память для M
        M = (Type**) new Type*[m]; // количество строк, количество указателей
        for (int i = 0; i < m; i++)
            M[i] = (Type*) new Type[n];
    // заполнить значениями
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                M[i][j] = _M.M[i][j];
    }
    // методы доступа
    Type GetMij(int i, int j){
        if ((m > 0) && (n > 0))
            return M[i][j];
        else
            return 0;
    }
    void SetMij(int i, int j, Type value){
        if ((i < 0) || (i >= m))
            return;
        if ((j < 0) || (j >= n))
            return;
        M[i][j] = value;
    }
    // метод, вычисляющий определитель матрицы
    int Determinant(){
        if ((m > 0) && (n > 0) && (m == n)){ //оиераделитель вычисляется только для квадратных матриц
            int dt = 0;
            if (m == 1) dt = M[0][0];
            if (m == 2) dt = det2(); //M[0][0] * M[1][1] - M[0][1] * M[1][0];
            if (m > 2) dt = det3();
            return dt;
        }
        return 0;
    }
    // метод, выводящий матрицу
    void Print(const char* ObjName){
        cout << "Object: " << ObjName << endl;
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                cout << M[i][j] << "\t";
            }
            cout << endl;
        }
        cout << "---------------------" << endl << endl;
    }
    // оператор копирования - обязательный
    LESSON32 operator=(const LESSON32& _M){
        if (n > 0){
        // освободить память, выделенную ранее для объекта *this
            for (int i = 0; i < m; i++){
                delete[] M[i];
            }
        }
        if (m > 0){
            delete[] M;
        }
        // Копирование данных M <= _M
        m = _M.m;
        n = _M.n;
        // Выделить память для M опять
        M = (Type**) new Type*[m]; // количество строк, количество указателей
        for (int i = 0; i < m; i++){
            M[i] = (Type*) new Type[n];
        }
        // заполнить значениями
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                M[i][j] = _M.M[i][j];
            }
        }
        return *this;
    }
// Деструктор - освобождает память, выделенную для матрицы
    ~LESSON32(){
        if (n > 0){
        // освободить выделенную память для каждой строки
            for (int i = 0; i < m; i++){
                delete[] M[i];
            }
        }
        if (m > 0) delete[] M;
    }
};

int det2(){
    //
}

int det3(){
    //
}
/*
3.Реализовть собственный класс итератора, 
с помощью которого можно будет проитерироваться по диапазону целых чисел в цикле for-range-based.
*/

//======================================================================
int main(const int argc, const char **argv){
    // тест для класса LESSON32
    LESSON32<int> M(2, 3);
    M.Print("M");

    // Заполнить матрицу значеннями по формуле
    int i, j;
    for (i = 0; i < 2; i++){
        for (j = 0; j < 3; j++){
            M.SetMij(i, j, i + j);
        }
    }

    M.Print("M");
    
    LESSON32<int> M2 = M; // вызов конструктора копирования
    M2.Print("M2");

    LESSON32<int> M3; // вызов оператора копирования - проверка
    M3 = M;
    M3.Print("M3");

    LESSON32<int> M4;
    M4 = M3 = M2 = M; // вызов оператора копирования в виде "цепочки"
    M4.Print("M4");

    return 0;
}