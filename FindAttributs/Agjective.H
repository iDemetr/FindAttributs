#pragma once

#ifndef ADJECTIVE_H
#define ADJECTIVE_H

#include <filesystem>

using namespace std;
using namespace std::filesystem;
using namespace SDictionary;
using namespace SList;


/// <summary>
/// Файл фильтров 
/// </summary>
const std::string Filter_File = "Data/Adjective.txt";

/// <summary>
/// Результирующий файл
/// </summary>
const std::string AdjectivesRes = "Data/Adjectives_Result.txt";
/// <summary>
/// Результирующий файл
/// </summary>
const std::string NumeredSentences = "Data/Numered Sentences.txt";

/// <summary>
/// Меню
/// </summary>
enum menu { NoN = -1, PrintCMD = '1', PrintFile, quit = 27 };

/// <summary>
/// Предложение
/// first - порядковый номер предложения
/// second - предложение
/// </summary>
typedef std::pair<int, std::string> Sentence;

/// <summary>
/// Словарь распозннных определений
/// </summary>
typedef Dictionary<std::string, Sentence*> DictAdjectives;

/// <summary>
/// Список предложений, где:
/// first - порядковый номер предложения
/// second - предложение
/// </summary>
typedef List<Sentence> LSentences;

/// <summary>
/// Функция быстрой сортировки словаря по ключу
/// </summary>
/// <param name="start_dict"></param>
/// <param name="dict_pivot"></param>
/// <param name="end_dict"></param>
template<class TKey, class TValue>
void QuickSort_Dict(NodeDict* start_dict, NodeDict* dict_pivot, NodeDict* end_dict);

/// <summary>
/// Парсится список фильтров для поиска определений
/// </summary>
List<std::string> Getting_Started();
/// <summary>
/// Формирует список предложений
/// </summary>
/// <param name="stream">Файловый поток</param>
/// <returns></returns>
LSentences* Define_Sentences(std::ifstream&);

/// <summary>
/// Формирует словарь определений из списка предложений
/// </summary>
/// <param name="Sentences">Коллекция предложений</param>
DictAdjectives* sentence_list_filter(LSentences*);


#endif