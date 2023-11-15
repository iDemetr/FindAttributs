#pragma once

#define FuncList inline SList::List<T>::
#define FuncListVoid inline void SList::List<T>::
#define FuncNodeList inline SList::NodeList<T>::

//============================================================================================================================||

template<class T>
FuncList List() {
	Head = Tail = nullptr;

	this->Count = 0;
}

template<class T>
FuncList List(const List<T>& list) {
	this->Count = list.Count;

	//�������� ���������� �������� �� ������� ����������.
	if (list.Head) Head = new NodeList<T>(*list.Head);
	else Head = nullptr;

	//����� ������ ������ ������.
	Tail = [](NodeList<T>* node) { while (node->Next) node = node->Next; return node; } (Head);
}

template<class T>
FuncList ~List() {
	Clear();
}

//============================================================================================================================||

template<class T>
FuncListVoid Add(const T obj) {
	NodeList<T>* node = new NodeList<T>(obj);										//�������� ���e��� �� ��������

	this->Count++;

	Append(node);
}

template<class T>
FuncListVoid Add(const T* obj) {
	NodeList<T>* node = new NodeList<T>(&*obj);										//�������� ���e��� �� ��������

	this->Count++;

	Append(node);
}


template<class T>
FuncListVoid Add(const List<T>* list) {

	NodeList<T>* tmp = list->Head;

	while (tmp) {

		NodeList<T>* node = new NodeList<T>(tmp->�bj);								//�������� ���e��� �� ��������

		this->Count++;

		Append(node);

		tmp = tmp->Next;
	}
}

template<class T>
FuncListVoid Append(NodeList<T>*& node) {

	if (Head == nullptr) Head = Tail = node;

	else {
		Tail->Next = node;
		Tail = node;
	}
}


template<class T>
FuncListVoid Delete(const T& obj) {

	NodeList<T>* node = this->Head;

	//����� ���� � �������� ������
	while (node && node->�bj != obj) node = node->Next;

	//���� ���� � �������� ������ ������
	if (node->�bj == obj) {
		Delete(node);
		return;
	}

	throw string("\n ������ ��������, �������� �� �������.");
}

template<class T>
FuncListVoid Delete(const NodeList<T>* node) {

	//���� ��������� ������� - ������.
	if (node == Head) { Head = Head->Next; }

	else {
		NodeList<T>* tmp = Head;										//��������� �� ����, ������� ����� ���������.

		//����� ����, �������� ����� ���������.
		while (tmp->Next && tmp->Next != node) { tmp = tmp->Next; }

		//���� ��������� ������� - �����.
		if (node == Tail) { Tail = tmp; }

		//������� �� �������� ������.
		else { tmp->Next = node->Next; }
	}

	delete node;
	Count--;
}

template<class T>
FuncListVoid Clear() {
	NodeList<T>* node;

	while (Head) {
		node = Head->Next;
		delete Head;

		Head = node;
	}

	Count = 0;
}

//============================================================================================================================||

template<class T>
FuncNodeList NodeList(const T& obj) {

	//if(obj) 
	this->�bj = obj;
	//else this->�bj = NULL;

	Next = nullptr;
}

template<class T>
FuncNodeList NodeList(const T* obj) {

	if (obj)
		this->�bj = *(obj);
	//else this->�bj = ;

	Next = nullptr;
}

template<class T>
FuncNodeList NodeList(const NodeList<T>* Node) {

	if (Node->Next) this->Next = new NodeList<T> *(Node->Next);
	else this->Next = nullptr;

	if (Node->�bj) this->�bj = Node->�bj;
	else this->�bj = NULL;
}

template<class T>
FuncNodeList NodeList() {
	Next = nullptr;
	�bj = NULL;
}

template<class T>
FuncNodeList ~NodeList() {
	Next = nullptr;

	//delete this->�bj;
}

//============================================================================================================================||
