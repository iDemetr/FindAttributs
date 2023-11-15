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

	//Возможно избыточная проверка на наличие указателей.
	if (list.Head) Head = new NodeList<T>(*list.Head);
	else Head = nullptr;

	//Поиск нового адреса хвоста.
	Tail = [](NodeList<T>* node) { while (node->Next) node = node->Next; return node; } (Head);
}

template<class T>
FuncList ~List() {
	Clear();
}

//============================================================================================================================||

template<class T>
FuncListVoid Add(const T obj) {
	NodeList<T>* node = new NodeList<T>(obj);										//Передача объeкта по значению

	this->Count++;

	Append(node);
}

template<class T>
FuncListVoid Add(const T* obj) {
	NodeList<T>* node = new NodeList<T>(&*obj);										//Передача объeкта по значению

	this->Count++;

	Append(node);
}


template<class T>
FuncListVoid Add(const List<T>* list) {

	NodeList<T>* tmp = list->Head;

	while (tmp) {

		NodeList<T>* node = new NodeList<T>(tmp->Оbj);								//Передача объeкта по значению

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

	//Поиск узла с заданным ключом
	while (node && node->Оbj != obj) node = node->Next;

	//Если узел с заданным ключом найден
	if (node->Оbj == obj) {
		Delete(node);
		return;
	}

	throw string("\n Ошибка удаления, значение не найдено.");
}

template<class T>
FuncListVoid Delete(const NodeList<T>* node) {

	//Если удаляемый элемент - голова.
	if (node == Head) { Head = Head->Next; }

	else {
		NodeList<T>* tmp = Head;										//Указатель на узел, стоящий перед удаляемым.

		//Поиск узла, стоящего перед удаляемым.
		while (tmp->Next && tmp->Next != node) { tmp = tmp->Next; }

		//Если удаляемый элемент - хвост.
		if (node == Tail) { Tail = tmp; }

		//Элемент из середины списка.
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
	this->Оbj = obj;
	//else this->Оbj = NULL;

	Next = nullptr;
}

template<class T>
FuncNodeList NodeList(const T* obj) {

	if (obj)
		this->Оbj = *(obj);
	//else this->Оbj = ;

	Next = nullptr;
}

template<class T>
FuncNodeList NodeList(const NodeList<T>* Node) {

	if (Node->Next) this->Next = new NodeList<T> *(Node->Next);
	else this->Next = nullptr;

	if (Node->Оbj) this->Оbj = Node->Оbj;
	else this->Оbj = NULL;
}

template<class T>
FuncNodeList NodeList() {
	Next = nullptr;
	Оbj = NULL;
}

template<class T>
FuncNodeList ~NodeList() {
	Next = nullptr;

	//delete this->Оbj;
}

//============================================================================================================================||
