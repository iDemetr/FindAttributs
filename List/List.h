#pragma once

#ifndef LIST_H
#define LIST_H

#ifdef LIST_EXPORTS
#define LIST_API __declspec(dllexport)
#else
#define LIST_API __declspec(dllimport)
#endif

using namespace std;

namespace MyList {

	template<class T>
	class List;

	template<class T>
	class NodeList;

	/// <summary>
	/// Пользовательский класс, реализующий структуру данных "Односвязаный список"
	/// </summary>
	template<class T>
	class __declspec(dllexport) List {

	public:
		List();
		~List();

		/// <summary>
		/// Конструктор копирования
		/// </summary>
		/// <param name=""></param>
		List(List<T> &);

		/// <summary>
		/// Счётчик элементов.
		/// </summary>
		int Count;

		NodeList<T> *Head, *Tail;

		/// <summary>
		/// Функция создаёт узел с Значением типа T и добавляет его в список.
		/// </summary>
		/// <param name="T">Ключ</param>
		void Add(T *);

		/// <summary>
		/// Объединение списков.
		/// </summary>
		void Add(List<T> *);

		/// <summary>
		/// Функция добавления в список созданного узла.
		/// </summary>
		/// <param name="node">Указатель на добавляемый узел</param>
		void Append(NodeList<T> *&);

		/// <summary>
		/// Функция удаления по ключу.
		/// </summary>
		/// <param name="key">Значение удаляемого узла.</param>
		void Delete(T *);

		/// <summary>
		/// Функия удаления по указателю на объект.
		/// </summary>
		/// <param name="node">Удаляемый узел.</param>
		void Delete(NodeList<T> *);

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
	class __declspec(dllexport) NodeList {

	public:
		T *Оbj;

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
		NodeList(T*);

		/// <summary>
		/// Конструктор копирования
		/// </summary>
		/// <param name=""></param>
		NodeList(NodeList<T> &);
	};
}

#endif