#include "pch.h"
#include "Dictionary.h"

using namespace MyList;
namespace SDictionary {

#pragma region --- ��������������� ��������������� �������� ---

	//��������������� ��������������� �������� �������
	template Dictionary<std::string, std::string>;
	template Dictionary<string, int>;
	template Dictionary<string, double>;
	template Dictionary<string, float>;
	
	template Dictionary<int, string>;
	template Dictionary<int, int>;
	template Dictionary<int, double>;
	template Dictionary<int, float>;
	
	template Dictionary<double, string>;
	template Dictionary<double, int>;
	template Dictionary<double, double>;
	template Dictionary<double, float>;
	
	template Dictionary<float, string>;
	template Dictionary<float, int>;
	template Dictionary<float, double>;
	template Dictionary<float, float>;

	//��������������� ��������������� �������� ������
	//template MyList::List<string>;
	//template MyList::List<int>;
	//template MyList::List<double>;
	//template MyList::List<float>;

#pragma endregion

	//============================================================================================================================||

	template<class TKey, class TValue>
	Dictionary<TKey, TValue>::Dictionary() {
		Head = Tail = nullptr;

		Count = 0;
	}

	template<class TKey, class TValue>
	Dictionary<TKey, TValue>::Dictionary(Dictionary<TKey, TValue>& dictoinary) {
		Count = dictoinary.Count;

		//�������� ���������� �������� �� ������� ����������.
		if (dictoinary.Head) Head = new NodeDict(*dictoinary.Head);
		else Head = nullptr;

		//����� ������ ������ ������.
		Tail = [](NodeDictionary<TKey, TValue>* node) { while (node->Next) node = node->Next; return node; } (Head);
	}

	template<class TKey, class TValue>
	Dictionary<TKey, TValue>::~Dictionary() {
		Clear();
	}

	//============================================================================================================================||

	template<class TKey, class TValue>
	void Dictionary<TKey, TValue>::Add(const TKey& key, const TValue& value) {

		//�������� �� ������������ ������.
		if (Contains(key)) {
			NodeDict* node = Dictionary::Get(key);
			node->AddValue(value);
		}
		else {
			NodeDict* node = new NodeDict(key, value);
			Append(node);
		}
		this->Count++;
	}

	template<class TKey, class TValue>
	void Dictionary<TKey, TValue>::Add(const TKey& key, const NodeDictListValue* list) {

		//�������� �� ������������ ������.
		if (Contains(key)) {
			throw string("\n A node with such a key is already in the dictionary!!"); return;
		}

		NodeDict* node = new NodeDict(key, list);

		this->Count++;

		Append(node);
	}

	template<class TKey, class TValue>
	void Dictionary<TKey, TValue>::Append(NodeDict* node) {

		if (this->Head == nullptr) {
			this->Head = this->Tail = node;
		}
		else {
			this->Tail->Next = node;
			node->Previous = Tail;
			Tail = node;
		}
	}

	template<class TKey, class TValue>
	bool Dictionary<TKey, TValue>::Contains(const TKey& key) {

		NodeDict* node = Head;

		while (node) { if (node->Key == key) { return true; } else node = node->Next; }

		return false;
	}

	template<class TKey, class TValue>
	NodeDict* Dictionary<TKey, TValue>::Get(const TKey& key) {

		NodeDict* node = Head;

		while (node) { if (node->Key == key) { return node; } else node = node->Next; }

		return nullptr;
	}

	template<class TKey, class TValue>
	void Dictionary<TKey, TValue>::Delete(const TKey& key) {

		NodeDictionary<TKey, TValue>* node = this->Head;

		//����� ���� � �������� ������
		while (node && node->Key != key)
			node = node->Next;

		//���� ���� � �������� ������ ������
		if (node->Key == key) {
			Delete(node);
			return;
		}

		throw string("\n ������ ��������, ���� �� ������ ����� �� �������.");
	}

	template<class TKey, class TValue>
	void Dictionary<TKey, TValue>::Delete(const NodeDict* node) {

		//���� ��������� ������� - ������.
		if (node == Head) { Head = Head->Next; }

		//���� ��������� ������� - �����.
		else if (node == Tail) { Tail = Tail->Previous; }

		//������� �� �������� ������.
		else {
			node->Previous->Next = node->Next;
			node->Next->Previous = node->Previous;
		}

		delete node;
	}

	template<class TKey, class TValue>
	void Dictionary<TKey, TValue>::Clear() {
		NodeDictionary<TKey, TValue>* node;

		while (Head) {
			node = Head->Next;
			delete Head;

			Head = node;
		}
	}

	//============================================================================================================================||

	template<class TKey, class TValue>
	NodeDictionary<TKey, TValue>::NodeDictionary() {
		Next = Previous = nullptr;
		Value = new NodeDictListValue();
		//Key = NULL;
	}

	template<class TKey, class TValue>
	NodeDictionary<TKey, TValue>::NodeDictionary(const TKey& key, const TValue& value) {

		//if (key) 
			Key = key;
		//else Key = NULL;

		//if (value) 
			Value = new NodeDictListValue();
			Value->Add(value);
		//else Value = NULL;

		Next = Previous = nullptr;
	}

	template<class TKey, class TValue>
	NodeDictionary<TKey, TValue>::NodeDictionary(const TKey& key, const NodeDictListValue* list) {
		//if (key) 
			Key = key;
		//else Key = NULL;

		//if (value) 
			Value = new NodeDictListValue(*list);
		//else Value = NULL;

		Next = Previous = nullptr;
	}

	template<class TKey, class TValue>
	NodeDictionary<TKey, TValue>::NodeDictionary(const NodeDict* node) {

		if (node.Next) this->Next = new NodeDict(node->Next);
		else this->Next = nullptr;

		if (node.Previous) this->Previous = new NodeDict(node->Previous);
		else this->Previous = nullptr;


		if (node.Key) this->Key = node->Key;
		else this->Key = NULL;

		if (node.Value) this->Value = new NodeDictListValue(node->Value);
		else this->Value = nullptr;
	}

	template<class TKey, class TValue>
	NodeDictionary<TKey, TValue>::~NodeDictionary() {
		Next = nullptr; Previous = nullptr;

		//delete Key; 
		delete Value;
	}

	//============================================================================================================================||
	
	template<class TKey, class TValue>
	void NodeDictionary<TKey, TValue>::AddValue(const TValue& value) {
		try { this->Value->Add(value); }
		catch (exception& e) { throw string(e.what()); }
	}

	template<class TKey, class TValue>
	void NodeDictionary<TKey, TValue>::DelValue(const TValue& value) {
		try { this->Value->Delete(value); }
		catch (string& mess) { throw mess; }
		catch (exception& e) { throw string(e.what()); }
	}
}