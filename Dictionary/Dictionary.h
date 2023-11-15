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

	// ��������� ��� ���� �������
	//template<class TKey, class TValue>
	#define NodeDict SDictionary::NodeDictionary<TKey, TValue>

	// ��������� ��� ������ �������� ���� ������� Value
	//template<class TKey, class TValue>
	#define NodeDictListValue SList::List<TValue>

	/// <summary>
	/// ���������������� �����, ����������� ��������� ������ "�������"
	/// </summary>
	template<class TKey, class TValue>
	class Dictionary {

	public:

		Dictionary();
		~Dictionary();

		/// <summary>
		/// ����������� �����������
		/// </summary>
		/// <param name=""></param>
		Dictionary(Dictionary&);

		NodeDict* Head, * Tail;

		/// <summary>
		/// ������� ������.
		/// </summary>
		int Count;

		/// <summary>
		/// ������� ������ ���� � ������ TKey � ��������� TValue � ��������� ��� � �������.
		/// </summary>
		/// <param name="TKey">����</param>
		/// <param name="TValue">��������</param>
		//void Add(TKey*, TValue*);

		/// <summary>
		/// ������� ������ ���� � ������ TKey � ��������� TValue � ��������� ��� � �������.
		/// </summary>
		/// <param name="TKey">����</param>
		/// <param name="TValue">��������</param>
		void Add(const TKey&, const TValue&);

		/// <summary>
		/// ������� ������ ���� � ������ TKey � ������� �������� List<TValue> � ��������� ��� � �������.
		/// </summary>
		/// <param name="TKey">����</param>
		/// <param name="MyList::List<TValue>">������ ��������</param>
		void Add(const TKey&, const NodeDictListValue*);

		/// <summary>
		/// ������� ���������� � ������� ���������� ����.
		/// </summary>
		/// <param name="node">��������� �� ����������� ����</param>
		void Append(NodeDict*);

		/// <summary>
		/// ������� �������� ������� ���� � �������� ������.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		bool Contains(const TKey&);

		/// <summary>
		/// ���������� ��������� �� ���� �������
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		NodeDict* Get(const TKey&);

		/// <summary>
		/// ������� �������� �� �����.
		/// </summary>
		/// <param name="key">���� ���������� ����</param>
		void Delete(const TKey&);

		/// <summary>
		/// ������ �������� �� ��������� �� ������.
		/// </summary>
		/// <param name="node">��������� ����</param>
		void Delete(const NodeDict*);

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
	class NodeDictionary {

	public:

		/// <summary>
		/// ���� ����.
		/// </summary>
		TKey Key;

		/// <summary>
		/// �������� ����.
		/// </summary>
		NodeDictListValue* Value;

		NodeDict* Next, *Previous;

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
		NodeDictionary(const TKey&, const TValue&);

		/// <summary>
		/// �������� ���� � �������� TKey � ������� List<TValue>
		/// </summary>
		/// <typeparam name="Key"></typeparam>
		/// <typeparam name="value"></typeparam>
		NodeDictionary(const TKey&, const NodeDictListValue*);

		/// <summary>
		/// ����������� �����������
		/// </summary>
		/// <param name=""></param>
		NodeDictionary(const NodeDict*);

		/// <summary>
		/// ���������� �������� � ����
		/// </summary>
		/// <param name=""></param>
		void AddValue(const TValue&);

		/// <summary>
		/// �������� �������� �� ����
		/// </summary>
		/// <param name=""></param>
		void DelValue(const TValue&);
	};

	// ����������� ����� ����������....
	#include "Dictionary.hpp"
}
#endif