/*
* Домашнее задание к уроку 1
* курса "C++: сложные моменты"
* автор Недокунев А.В.
* среда разработки VSCode /компилятор MinGW/
* codepage UTF-8
*/
#include <iostream>
#include <experimental/optional>
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

using namespace std;

#define ALIGN 15

/*
1.	Создайте структуру Person с 3 полями: фамилия, имя, отчество. 
Поле отчество должно быть опционального типа, т.к. не у всех людей есть отчество. 
Перегрузите оператор вывода данных для этой структуры. 
Также перегрузите операторы < и == (используйте tie).
*/

typedef struct Person{
	string name;
	experimental::optional <string> middlename;
	string surname;
	Person() {}
	Person(string n, string s, experimental::optional<string> m = std::experimental::nullopt): name(n), surname(s), middlename(m) {}
	friend ostream& operator << (ostream& out, Person& p);
	bool operator < (const Person& p) {
		return (tie(name, middlename, surname) < tie(p.name, p.middlename, p.surname));
	}
	bool operator == (const Person& p) {
		return (tie(name, middlename, surname) == tie(p.name, p.middlename, p.surname));
		}
} Person;

ostream& operator << (ostream& out, Person& p) {	
	return out << setw(ALIGN) << p.surname << setw(ALIGN) << p.name << setw(ALIGN) << p.middlename.value_or("");	
}

/*
2.	Создайте структуру PhoneNumber с 4 полями:
·         код страны (целое число)
·         код города (целое число)
·         номер (строка)
·         добавочный номер (целое число, опциональный тип)
Для этой структуры перегрузите оператор вывода. 
Необходимо, чтобы номер телефона выводился в формате: +7(911)1234567 12, 
где 7 – это номер страны, 911 – номер города, 1234567 – номер, 12 – добавочный номер. 
Если добавочного номера нет, то его выводить не надо.
*/

typedef struct PhoneNumber{
	int CountryCode;
	int TownCode;
	string numPhone;
	experimental::optional<int> extNumber;
	PhoneNumber() {}
	PhoneNumber(int cc, int tc, string n, experimental::optional<int> e = experimental::nullopt): CountryCode(cc), TownCode(tc), numPhone(n), extNumber(e){};  
	friend ostream& operator << (ostream& out, PhoneNumber& p);	
	bool operator < (const PhoneNumber& p) {
		return (tie(CountryCode, TownCode, numPhone, extNumber) < tie(p.CountryCode, p.TownCode, p.numPhone, p.extNumber));
	}
	bool operator == (const PhoneNumber& p) {
		return (tie(CountryCode, TownCode, numPhone, extNumber) == tie(p.CountryCode, p.TownCode, p.numPhone, p.extNumber));
	}
} PhoneNumber;

ostream& operator << (ostream& out, PhoneNumber& p) {
	if(p.extNumber && p.extNumber.value() != 0){
		return out << "+" << p.CountryCode << "(" << p.TownCode << ")" << p.numPhone << " " << p.extNumber.value();		
	} else {
		return out << "+" << p.CountryCode << "(" << p.TownCode << ")" << p.numPhone;
	}
}

/*
3.	Создайте класс PhoneBook, который будет в контейнере хранить пары: 
Человек – Номер телефона. 
Конструктор этого класса должен принимать параметр типа ifstream – поток данных, полученных из файла. 
В теле конструктора происходит считывание данных из файла и заполнение контейнера. 
Класс PhoneBook должен содержать перегруженный оператор вывода, для вывода всех данных из контейнера в консоль.
В классе PhoneBook реализуйте метод SortByName, 
который должен сортировать элементы контейнера по фамилии людей в алфавитном порядке. 
Если фамилии будут одинаковыми, то сортировка должна выполняться по именам, 
если имена будут одинаковы, то сортировка производится по отчествам. 
Используйте алгоритмическую функцию sort.
Реализуйте метод SortByPhone, который должен сортировать элементы контейнера по номерам телефонов. 
Используйте алгоритмическую функцию sort.
Реализуйте метод GetPhoneNumber, который принимает фамилию человека, 
а возвращает кортеж из строки и PhoneNumber. 
Строка должна быть пустой, если найден ровно один человек с заданном фамилией в списке. 
Если не найден ни один человек с заданной фамилией, то в строке должна быть запись «not found», 
если было найдено больше одного человека, то в строке должно быть «found more than 1». 
Для прохода по элементам контейнера используйте алгоритмическую функцию for_each.
Реализуйте метод ChangePhoneNumber, который принимает человека и новый номер телефона 
и, если находит заданного человека в контейнере, то меняет его номер телефона на новый, иначе ничего не делает. 
Используйте алгоритмическую функцию find_if.
*/

class PhoneBook {
private:
    vector<pair<Person, PhoneNumber>> records;
public:
    PhoneBook(ifstream& infile) {
		if (!infile){
			cerr << "File not found" << endl;
            exit(1);
		}
		string strInFile;
		pair<Person, PhoneNumber> singlerecord;
		Person singlePerson;
		PhoneNumber singleNumber;
		while(!infile.eof()){
//			singlePerson.surname = getWord(infile);
			infile >> singlerecord.first.surname;
			infile >> singlerecord.first.name;
			infile >> strInFile;
			singlerecord.first.middlename = strInFile;
			infile >> singlerecord.second.CountryCode;
			infile >> singlerecord.second.TownCode;
			infile >> singlerecord.second.numPhone;
			infile >> strInFile;
			singlerecord.second.extNumber = 0; //stoi(strInFile);
			records.push_back(singlerecord);
		}
//		infile >> strInFile;
//		singlerecord.first.surname = "aaa";
    }
    friend ostream& operator<< (ostream& out, const PhoneBook& phBook );
    void SortByName(){
        sort(records.begin(), records.end(), [](pair<Person, PhoneNumber>& left, pair<Person, PhoneNumber>& right){
            return left.first < right.first;
        });
    }
    void SortByPhone(){
        sort(records.begin(), records.end(), [](pair<Person, PhoneNumber>& left, pair<Person, PhoneNumber>& right){
            return left.second < right.second;
        });
    }
	tuple<string, PhoneNumber> GetPhoneNumber(const string& s){
		int countnum=0;
		PhoneNumber num;
        for(auto record: records)
            if(s == record.first.surname) {
                countnum++;
                num = record.second;
            }
		if(countnum==0) return tie("not found", num);
		else if(countnum==1) return tie("", num);
		else return tie("found more than 1", num);
	}
    void ChangePhoneNumber(const Person& person,  PhoneNumber newPhone){
        for(int i = 0; i < records.size(); i++)
            if((const_cast<Person&>(person)) == records[i].first)
                records[i].second = newPhone;
    }
};

ostream& operator<< (ostream& out, const PhoneBook& phBook ) {
    for(auto P : phBook.records) {
        out << P.first << "\t" << P.second << endl;
    }
    return out;
}

////////////////////////////////////////////////////////////////////////////////////////
int main(const int argc, const char **argv){

   	std::ifstream file("d:\\doc\\Cplusplus_GeekBrains\\Projects\\Dificult_Moments\\lesson_1\\PhoneBook.txt"); // путь к файлу PhoneBook.txt
   	PhoneBook book(file);
   	std::cout << book;
 
   	std::cout << "------SortByPhone-------" << endl;
   	book.SortByPhone();
   	std::cout << book;
 
   	std::cout << "------SortByName--------" << endl;
   	book.SortByName();
   	std::cout << book;
 
   	std::cout << "-----GetPhoneNumber-----" << endl;
   	// лямбда функция, которая принимает фамилию и выводит номер телефона этого человека, либо строку с ошибкой
   	auto print_phone_number = [&book](const string& surname) { 
   	   	std::cout << surname << "\t"; 
   	   	auto answer = book.GetPhoneNumber(surname); 
   	   	if (get<0>(answer).empty()) 
   	   	   	std::cout << get<1>(answer); 
   	   	else 
   	   	   	std::cout << get<0>(answer); 
   	   	   	std::cout << endl; 
   	};

   	// вызовы лямбды
   	print_phone_number("Ivanov");
   	print_phone_number("Petrov");
 
   	std::cout << "----ChangePhoneNumber----" << endl;
   	book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" }, PhoneNumber{7, 123, "15344458", experimental::nullopt});
   	book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" }, PhoneNumber{ 16, 465, "9155448", 13 });
   	std::cout << book;
    
    return 0;
}