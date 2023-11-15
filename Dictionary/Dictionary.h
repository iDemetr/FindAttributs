#pragma once

#ifndef DICTIONARY_H
#define DICTIONARY_H

#ifdef PDICTIONARY_EXPORTS
#define DICTIONARY_API __declspec(dllexport)
#else
#define DICTIONARY_API __declspec(dllimport)
#endif

#include "List.h"
using namespace std;

namespace SDictionary {

	template<class TKey, class TValue>
	class NodeDictionary;

	// Шаблонный тип узла словаря
	//template<class TKey, class TValue>
	#define NodeDict SDictionary::NodeDictionary<TKey, TValue>

	// Шаблонный тип списка значений узла словаря Value
	//template<class TKey, class TValue>
	#define NodeDictListValue SList::List<TValue>

	/// <summary>
	/// Пользовательский класс, реализующий структуру данных "Словарь"
	/// </summary>
	template<class TKey, class TValue>
	class Dictionary {

	public:

		Dictionary();
		~Dictionary();

		/// <summary>
		/// Конструктор копирования
		/// </summary>
		/// <param name=""></param>
		Dictionary(Dictionary&);

		NodeDict* Head, * Tail;

		/// <summary>
		/// Счётчик ключей.
		/// </summary>
		int Count;

		/// <summary>
		/// Функция создаёт узел с Ключом TKey и Значением TValue и добавляет его в словарь.
		/// </summary>
		/// <param name="TKey">Ключ</param>
		/// <param name="TValue">Значение</param>
		//void Add(TKey*, TValue*);

		/// <summary>
		/// Функция создаёт узел с Ключом TKey и Значением TValue и добавляет его в словарь.
		/// </summary>
		/// <param name="TKey">Ключ</param>
		/// <param name="TValue">Значение</param>
		void Add(const TKey&, const TValue&);

		/// <summary>
		/// Функция создаёт узел с Ключом TKey и списком значений List<TValue> и добавляет его в словарь.
		/// </summary>
		/// <param name="TKey">Ключ</param>
		/// <param name="MyList::List<TValue>">Список значений</param>
		void Add(const TKey&, const NodeDictListValue*);

		/// <summary>
		/// Функция добавления в словарь созданного узла.
		/// </summary>
		/// <param name="node">Указатель на добавляемый узел</param>
		void Append(NodeDict*);

		/// <summary>
		/// Функция проверки наличия узла с заданным ключём.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		bool Contains(const TKey&);

		/// <summary>
		/// Возвращает указатель на узел словаря
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		NodeDict* Get(const TKey&);

		/// <summary>
		/// Функция удаления по ключу.
		/// </summary>
		/// <param name="key">Ключ удаляемого узла</param>
		void Delete(const TKey&);

		/// <summary>
		/// Функия удаления по указателю на объект.
		/// </summary>
		/// <param name="node">Удаляемый узел</param>
		void Delete(const NodeDict*);

		/// <summary>
		/// Функия очистки словаря от всех созданных узлов.
		/// </summary>
		void Clear();
	};

	/// <summary>
	/// Класс узла для словаря.
	/// </summary>
	/// <typeparam name="TKey"></typeparam>
	/// <typeparam name="TValue"></typeparam>
	template<class TKey, class TValue>
	class NodeDictionary {

	public:

		/// <summary>
		/// Ключ узла.
		/// </summary>
		TKey Key;

		/// <summary>
		/// Значение узла.
		/// </summary>
		NodeDictListValue* Value;

		NodeDict* Next, *Previous;

		/// <summary>
		/// Конструктор, обнуляющуй узкатели на следующий и предыдущий 
		/// </summary>
		NodeDictionary();

		/// <summary>
		/// 
		/// </summary>
		~NodeDictionary();

		/// <summary>
		/// Создание узла с заданным TKey и TValue
		/// </summary>
		/// <typeparam name="Key"></typeparam>
		/// <typeparam name="value"></typeparam>
		NodeDictionary(const TKey&, const TValue&);

		/// <summary>
		/// Создание узла с заданным TKey и списком List<TValue>
		/// </summary>
		/// <typeparam name="Key"></typeparam>
		/// <typeparam name="value"></typeparam>
		NodeDictionary(const TKey&, const NodeDictListValue*);

		/// <summary>
		/// Конструктор копирования
		/// </summary>
		/// <param name=""></param>
		NodeDictionary(const NodeDict*);

		/// <summary>
		/// Добавление значений в узел
		/// </summary>
		/// <param name=""></param>
		void AddValue(const TValue&);

		/// <summary>
		/// Удаление значения из узла
		/// </summary>
		/// <param name=""></param>
		void DelValue(const TValue&);
	};

	// Подключение файла реализации....
	#include "Dictionary.hpp"
}
#endif