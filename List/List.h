#pragma once

#ifndef LIST_H
#define LIST_H

#ifdef LIST_EXPORTS
#define LIST_API __declspec(dllexport)
#else
#define LIST_API __declspec(dllimport)
#endif

using namespace std;

namespace SList {

	template<class T>
	class NodeList;

	template<class T>
	class List;

	/// <summary>
	/// ���������������� �����, ����������� ��������� ������ "������������ ������"
	/// </summary>
	template<class T>
	class List {

	public:
		List();
		~List();

		/// <summary>
		/// ����������� �����������
		/// </summary>
		/// <param name=""></param>
		List(const List<T> &);

		/// <summary>
		/// ������� ���������.
		/// </summary>
		int Count;

		NodeList<T> *Head, *Tail;

		/// <summary>
		/// ������� ������ ���� � ������� ���� T � ��������� ��� � ������.
		/// </summary>
		/// <param name="T">��������</param>
		void Add(const T);

		/// <summary>
		/// ������� ������ ���� � ������� ���� T � ��������� ��� � ������.
		/// </summary>
		/// <param name="T">��������</param>
		void Add(const T *);

		/// <summary>
		/// ������� ������ ���� � ��������� ���� T � ��������� ��� � ������.
		/// </summary>
		/// <param name="T">��������</param>
		//void Add(const T &);

		/// <summary>
		/// ����������� �������.
		/// </summary>
		void Add(const List<T> *);

		/// <summary>
		/// ������� ���������� � ������ ���������� ����.
		/// </summary>
		/// <param name="node">��������� �� ����������� ����</param>
		void Append(NodeList<T> *&);

		/// <summary>
		/// ������� �������� �� �����.
		/// </summary>
		/// <param name="key">�������� ���������� ����.</param>
		void Delete(const T &);

		/// <summary>
		/// ������ �������� �� ��������� �� ������.
		/// </summary>
		/// <param name="node">��������� ����.</param>
		void Delete(const NodeList<T> *);

		/// <summary>
		/// ������ ������� ������.
		/// </summary>
		void Clear();
	};

	/// <summary>
	/// ����� ���� ��� ������������ ������.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<class T>
	class NodeList {

	public:
		T �bj;

		NodeList<T> *Next;

		/// <summary>
		/// �����������, ���������� �������� �� ��������� � ���������� ��������
		/// </summary>
		NodeList();

		/// <summary>
		/// 
		/// </summary>
		~NodeList();

		/// <summary>
		/// �������� ���� � �������� ���������.
		/// </summary>
		/// <typeparam name="T"></typeparam>
		NodeList(const T&);

		/// <summary>
		/// �������� ���� � �������� ���������.
		/// </summary>
		/// <typeparam name="T"></typeparam>
		NodeList(const T*);

		/// <summary>
		/// ����������� �����������
		/// </summary>
		/// <param name=""></param>
		NodeList(const NodeList<T> *);
	};
	
	// ����������� ����� ����������....
	#include "List.hpp"
}

#endif