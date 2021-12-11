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

#define MATRIX_SIZE 3

using namespace std;

/*
1.	Написать функцию, добавляющую в конец списка вещественных чисел элемент, 
значение которого равно среднему арифметическому всех его элементов.
*/
void AverageAdd (list<int>& l){
    int average = 0;
    for (auto a : l){
        average += a;
    }
    l.push_back(average / l.size());
}

/*
2.	Создать класс, представляющий матрицу. Реализовать в нем метод, вычисляющий определитель матрицы.
*/
class LESSON_32{
    private:
        int _a;
        vector<vector<int>> _M;
    public:
        LESSON_32(){};
        LESSON_32(int a){
            _a = a;
            _M.resize(_a, vector<int> (_a));
        };
        int Get (int i, int j){
            if ((i > _a) || (j > _a)){
                return -1;
            }
            if ((i > 0) || (j > 0)){
                return _M[i][j];
            }
            return 0;
        }
        void Set (int i, int j, int a){
            if ((i >= _a) || (j >= _a)){
                cout << "Invalid element" << endl;
                return;
            }
            _M[i][j] = a;
        }
        void Print(){
            for (int i = 0; i < MATRIX_SIZE; ++i){
                for (int j = 0; j < MATRIX_SIZE; ++j){
                    cout << _M[i][j] << "\t";
                }
                cout << endl;
            }
            cout << "---------------------" << endl;
        }
        int Determinant(){
            int dt = 0;
            if (_a == 1) return _M[0][0];
            if (_a == 2) return _M[0][0]*_M[1][1] - _M[0][1]*_M[1][0];
            for (int col = 0; col < _a; ++col){
                LESSON_32 minor(_a - 1);
                int mrow = 0;
                int mcol = 0;
                for (int row = 1; row < _a; ++row){
                    for (int tempcol = 0; tempcol < _a; ++tempcol){
                        if (tempcol != col){
                            minor.Set(mrow, mcol++, _M[row][tempcol]);
                        }
                    }
                    mcol = 0;
                    mrow++;
                }
                dt =+ (col % 2 == 0 ? 1 : -1) * _M[0][col] * minor.Determinant();
            }
            return dt;
        }
        ~LESSON_32(){
            _M.clear();
        };
};

/*
3.Реализовть собственный класс итератора, 
с помощью которого можно будет проитерироваться по диапазону целых чисел в цикле for-range-based.
*/
class MyIterator
{
private:
    vector<int> diapazon;
    int* myptr;
public:
    MyIterator(vector<int>& p){
        diapazon = p;
        myptr = &diapazon[0]; //.begin().operator->();
    }
    ~MyIterator(){
        diapazon.clear();
    }
    int* begin(){
        return &diapazon[0];
    }
    int* end(){
        return &diapazon[0] + diapazon.size();
    }
    int* operator++ (){
        return myptr++;
    }
    bool operator!= (int value){
        return *myptr == value;
    };
    int operator*(){
        return *myptr; 
    };
};

//======================================================================
int main(const int argc, const char **argv){
    list<int> My_list = {1,2,3,4,5,6,7,8,9};
    AverageAdd(My_list);
    for (auto a : My_list){
        cout << a << " ";
    }
    LESSON_32 M1(MATRIX_SIZE);
    M1.Print();
    for (int i = 0; i < MATRIX_SIZE; ++i){
        for (int j = 0; j < MATRIX_SIZE; ++j){
            M1.Set(i, j, i+j);
        }
        cout << endl;
    }
    M1.Print();
    cout << M1.Determinant() << endl;
    vector<int> v1 = {3,4,7};
    MyIterator iter1(v1);
    for (auto a : iter1){
        cout << a << " ";
    }
    cout << endl;

    return 0;
}