#pragma once

#ifndef DICTIONARY_H
#define DICTIONARY_H

#ifdef DICTIONARY_EXPORTS
#define DICTIONARY_API __declspec(dllexport)
#else
#define DICTIONARY_API __declspec(dllimport)
#endif

#include "List.h"
using namespace std;

namespace SDictionary {

	template<class TKey, class TValue>
	class NodeDictionary;

	/// <summary>
	/// ���������������� �����, ����������� ��������� ������ "�������"
	/// </summary>
	template<class TKey, class TValue>
	class __declspec(dllexport) Dictionary {

	public:

		Dictionary();
		~Dictionary();

		/// <summary>
		/// ����������� �����������
		/// </summary>
		/// <param name=""></param>
		Dictionary(Dictionary&);

		NodeDictionary<TKey, TValue>* Head, * Tail;

		/// <summary>
		/// ������� ������.
		/// </summary>
		int Count;

		/// <summary>
		/// ������� ������ ���� � ������ TKey � ��������� TValue � ��������� ��� � �������.
		/// </summary>
		/// <param name="TKey">����</param>
		/// <param name="TValue">��������</param>
		void Add(TKey*, TValue*);

		/// <summary>
		/// ������� ���������� � ������� ���������� ����.
		/// </summary>
		/// <param name="node">��������� �� ����������� ����</param>
		void Append(NodeDictionary<TKey, TValue>*);

		/// <summary>
		/// ������� �������� ������� ���� � �������� ������.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		bool Contains(TKey*);

		/// <summary>
		/// ���������� ��������� �� ���� �������
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		NodeDictionary<TKey, TValue>* Get(TKey*);

		/// <summary>
		/// ������� �������� �� �����.
		/// </summary>
		/// <param name="key">���� ���������� ����.</param>
		void Delete(TKey*);

		/// <summary>
		/// ������ �������� �� ��������� �� ������.
		/// </summary>
		/// <param name="node">��������� ����.</param>
		void Delete(NodeDictionary<TKey, TValue>*);

		/// <summary>
		/// ������ ������� ������� �� ���� ��������� �����.
		/// </summary>
		void Clear();
	};

	/// <summary>
	/// ����� ���� ��� �������.
	/// </summary>
	/// <typeparam name="TKey"></typeparam>
	/// <typeparam name="TValue"></typeparam>
	template<class TKey, class TValue>
	class __declspec(dllexport) NodeDictionary {

	public:

		/// <summary>
		/// ���� ����.
		/// </summary>
		TKey* Key;

		/// <summary>
		/// �������� ����.
		/// </summary>
		TValue* Value;

		NodeDictionary<TKey, TValue>* Next, * Previous;

		/// <summary>
		/// �����������, ���������� �������� �� ��������� � ���������� 
		/// </summary>
		NodeDictionary();

		/// <summary>
		/// 
		/// </summary>
		~NodeDictionary();

		/// <summary>
		/// �������� ���� � �������� TKey � TValue
		/// </summary>
		/// <typeparam name="Key"></typeparam>
		/// <typeparam name="value"></typeparam>
		NodeDictionary(TKey*, TValue*);

		/// <summary>
		/// ����������� �����������
		/// </summary>
		/// <param name=""></param>
		NodeDictionary(NodeDictionary&);

		/// <summary>
		/// ���������� �������� � ����
		/// </summary>
		/// <param name=""></param>
		template<class T>
		void AddValue(MyList::List<T>*);

		/// <summary>
		/// �������� �������� �� ����
		/// </summary>
		/// <param name=""></param>
		template<class T>
		void DelValue(T*);
	};
}
#endif