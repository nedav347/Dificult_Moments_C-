/*
* Домашнее задание к уроку 5
* курса "C++: сложные моменты"
* автор Недокунев А.В.
* среда разработки VSCode /компилятор MinGW/
* codepage UTF-8
*/
#include <iostream>
#include <set>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
//#include <random>

using namespace std;

/*
1. Создать шаблонную функцию, 
которая принимает итераторы на начало и конец последовательности слов, 
и выводящую в консоль список уникальных слов 
(если слово повторяется больше 1 раза, то вывести его надо один раз). 
Продемонстрировать работу функции, передав итераторы различных типов.
*/

template <typename T>
void printUniq(T begin, T end) {
    set<string> unique {};
	unique.insert(begin, end);
	cout << "//-----------------------" << endl;
    for (const auto& s : unique) {
		cout << s.c_str() << endl;
	}
}


/*
2. Используя ассоциативный контейнер, 
напишите программу, 
которая будет считывать данные введенные пользователем 
из стандартного потока ввода и разбивать их на предложения. 
Далее программа должна вывести пользователю все предложения, отсортировав их по длине.
*/

void splitToSentences() {
	string strInput, strSentence;
	multimap<int, string> sentences{};
    cout << "Enter text (if you end, please press ENTER twice):";
	do {
		getline(cin, strInput);
		for ( const auto& charSentence : strInput) {
            strSentence += charSentence;
			if (charSentence == '.' || charSentence == '!' || charSentence == '?')
			{
				auto it = find_if(strSentence.begin(), strSentence.end(),[](char ch){return ch!=' ';});
                if (it != strSentence.end()) strSentence = strSentence.substr(it - strSentence.begin());
                sentences.insert({ strSentence.length(), strSentence });
				strSentence = {};
			}
		}
	} while (strInput != "");
    for (const auto& itemSentence : sentences) {
	    cout << itemSentence.second << " ( " << itemSentence.first << " )" << endl;
	}

}
//======================================================================
int main(const int argc, const char **argv){

    vector<string> v = {"lorem","ipsum","dolor","sit","amet","consectetur","adipiscing","elit","sit","do","eiusmod","incididunt","ut","labore","et","dolor","magna","aliqua"};
    list<string> l = {"lorem","ipsum","dolor","sit","amet","consectetur","adipiscing","elit","sit","do","eiusmod","incididunt","ut","labore","et","dolor","magna","aliqua"};
    printUniq(v.begin(), v.end());
    printUniq(l.begin(), l.end());

    splitToSentences();
/*
Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua! Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat? Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
*/

    return 0;
}
