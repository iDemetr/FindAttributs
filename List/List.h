#pragma once

#ifndef LIST_H
#define LIST_H

//#ifndef LIST_EXPORTS
#define LIST_API __declspec(dllexport)
//#else
//#define LIST_API __declspec(dllimport)
//#endif

using namespace std;

namespace MyList {

	//template<class T>
	//class List;

	template<class T>
	class NodeList;

	/// <summary>
	/// Пользовательский класс, реализующий структуру данных "Односвязаный список"
	/// </summary>
	template<class T>
	class LIST_API List {

	public:
		List();
		~List();

		/// <summary>
		/// Конструктор копирования
		/// </summary>
		/// <param name=""></param>
		List(const List<T> &);

		/// <summary>
		/// Счётчик элементов.
		/// </summary>
		int Count;

		NodeList<T> *Head, *Tail;

		/// <summary>
		/// Функция создаёт узел с классом типа T и добавляет его в список.
		/// </summary>
		/// <param name="T">Значение</param>
		void Add(const T);

		/// <summary>
		/// Функция создаёт узел с классом типа T и добавляет его в список.
		/// </summary>
		/// <param name="T">Значение</param>
		void Add(const T *);

		/// <summary>
		/// Функция создаёт узел с Значением типа T и добавляет его в список.
		/// </summary>
		/// <param name="T">Значение</param>
		//void Add(const T &);

		/// <summary>
		/// Объединение списков.
		/// </summary>
		void Add(const List<T> *);

		/// <summary>
		/// Функция добавления в список созданного узла.
		/// </summary>
		/// <param name="node">Указатель на добавляемый узел</param>
		void Append(NodeList<T> *&);

		/// <summary>
		/// Функция удаления по ключу.
		/// </summary>
		/// <param name="key">Значение удаляемого узла.</param>
		void Delete(const T &);

		/// <summary>
		/// Функия удаления по указателю на объект.
		/// </summary>
		/// <param name="node">Удаляемый узел.</param>
		void Delete(const NodeList<T> *);

		/// <summary>
		/// Функия очистки списка.
		/// </summary>
		void Clear();
	};

	/// <summary>
	/// Класс узла для односвязного списка.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<class T>
	class LIST_API NodeList {

	public:
		T Оbj;

		NodeList<T> *Next;

		/// <summary>
		/// Конструктор, обнуляющуй узкатели на следующий и предыдущий элементы
		/// </summary>
		NodeList();

		/// <summary>
		/// 
		/// </summary>
		~NodeList();

		/// <summary>
		/// Создание узла с заданным значением.
		/// </summary>
		/// <typeparam name="T"></typeparam>
		NodeList(const T&);

		/// <summary>
		/// Создание узла с заданным значением.
		/// </summary>
		/// <typeparam name="T"></typeparam>
		NodeList(const T*);

		/// <summary>
		/// Конструктор копирования
		/// </summary>
		/// <param name=""></param>
		NodeList(const NodeList<T> *);
	};
}

#endif