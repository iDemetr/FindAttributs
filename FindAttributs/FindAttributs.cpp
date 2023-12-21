#pragma once

#include "pch.h"
#include "Agjective.H"

using namespace std;
using namespace SDictionary;
using namespace SList;

void printCMD(DictAdjectives*);
void printFile(DictAdjectives*);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::cout << "\n\t Запуск алгоритма поиска определений в предложениях!";
	std::cout << "\n-----------------------------------------------------------";
	std::cout << "\n\n Для начала работы, нажмите любую клавишу...";

	_getch(); system("cls");

#ifdef NDEBUG

	ifstream File;
	string nameFile;

	do {
		if (/*!menu(File_name, file_reading) && */nameFile.empty()) {
			std::cout << "\n Введите название файла или путь к файлу:";
			getline(cin, nameFile, '\n');
			if (nameFile.find('.') == string::npos) {
				std::cout << "\n Добавление расширения.";
				nameFile += ".txt";
			}

			File.open(nameFile);
			if (!File.is_open()) {
				std::cout << "\n Файл не существует.";
				nameFile = "";
			}
		}
	} while (!File.is_open());

	auto LSentences = Define_Sentences(File);
	auto adjectives = sentence_list_filter(LSentences);

	std::cout << "\n\n В тексте найдено " << adjectives->Count << " определений.";
	
	menu s = NoN;

	while (s != quit) {
		
		std::cout << "\n\n Вывести результат в консоль.	 (1)";
		std::cout << "\n Вывести результат в файл.	 (2)";
		std::cout << "\n Выйти из программы.	        (esc)";

	while (s = (menu)_getch(), s < PrintCMD && s > PrintFile && s != quit);
		switch (s) {
		case PrintCMD:
			printCMD(adjectives);
			break;
		case PrintFile:
			printFile(adjectives);
			break;
		case quit:
			break;
		}
	}


	cout << "\n\n Завершение программы...";
	_getch();

#else
	ifstream File("Data/Analized Text.txt");
	auto LSentences = Define_Sentences(File);
	auto adjectives = sentence_list_filter(LSentences);
	printFile(adjectives);

#endif 
}

/// <summary>
/// Вывод словаря в консоль
/// </summary>
/// <param name="dict"></param>
void printCMD(DictAdjectives* dict) {
	auto tmp = dict->Head;

	std::cout << "\n\n Список определений, с перечислением номеров предложений:";

	int i(0);
	while (tmp) {
		std::cout << "\n " << ++i << ": " << tmp->Key << " - ";

		auto tmp2 = tmp->Value->Head;
		while (tmp2) {
			std::cout << tmp2->Оbj->first<< ", ";
			tmp2 = tmp2->Next;
		}

		tmp = tmp->Next;
	}
}

/// <summary>
/// Вывод словаря в файл
/// </summary>
/// <param name="dict"></param>
void printFile(DictAdjectives* dict) {

	ofstream file(AdjectivesRes);
	if (!file.is_open()) {
		return;
	}

	std::cout << "\n\n Сохранение в файл: " << AdjectivesRes;

	try {
		auto tmp = dict->Head;

		file << " Список определений, с перечислением номеров предложений:";

		int i(0);
		while (tmp) {
			file << "\n " << ++i << ": " << tmp->Key << " - ";

			auto tmp2 = tmp->Value->Head;
			while (tmp2) {
				file << tmp2->Оbj->first << ", ";
				tmp2 = tmp2->Next;
			}

			tmp = tmp->Next;
		}

		std::cout << "\n\n Результат сохранен.\n";
	}
	catch (exception& e) {
		std::cout << "\n\n Error! " << e.what();
	}

	file.close();
}

#pragma region --- Подсказка по пользованию кастомных структур ---
/*
	//Наш словарь
	Dictionary<int, string> dict;

	int a(0);
	string str("aaaa");

	// Cписок предложений
	List<string> LStr;
	LStr.Add("asdasd");		// Добавление анонимное
	LStr.Add(str);			// Добавление переменной

	// По канону добавление значений по ключу требовало получить указатель на узел через get(key) и
	// уже у узла обращаться к списку его значений и добавлять значение в него.

	// Но теперь взаимодействие со словарём стало гораздно удобнее:
	// по 1 ключу можно добавлять новые значения, которые автоматически упаковываются в списки

	dict.Add(a, &LStr);		// создание узла с ключом 0 со списком предложений
	dict.Add(1, "new");		// создание узла с ключом 1 с одним предложением
	dict.Add(1, "new");		// добавление в узел с ключом 1 новое предложение
	dict.Add(0, "oooooo");	// Добавление по ключу 0 нового предложения
	dict.Add(3, NULL);		// Создание нового узла без значений

	std::cout << "Hello World!\n";
*/
#pragma endregion
