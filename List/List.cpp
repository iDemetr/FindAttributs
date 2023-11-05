#include "pch.h"
#include "List.h"

namespace MyList {

	//Предворительное инстанцирование шаблонов
	template List<string>;
	template List<int>;
	template List<double>;
	template List<float>;

	template<class T>	
	List<T>::List() {
		Head = Tail = nullptr;

		Count = 0;
	}

	template<class T>
	List<T>::List(List<T> &list) {
		Count = list.Count;

		//Возможно избыточная проверка на наличие указателей.
		if(list.Head) Head = new NodeList<T>(*list.Head);
		else Head = nullptr;

		//Поиск нового адреса хвоста.
		Tail = [](NodeList<T> *node) { while(node->Next) node = node->Next; return node; } (Head);
	}

	template<class T>
	List<T>::~List() {
		Clear();
	}

	template<class T>
	void List<T>::Add(T *obj) {
		NodeList<T> *node = new NodeList<T>(obj);																	//Передача объeкта по значению

		this->Count++;

 		Append(node);
	}

	template<class T>
	void List<T>::Add(List<T> *list) {

		NodeList<T> *tmp = list->Head;

		while(tmp) {

			NodeList<T> *node = new NodeList<T>(tmp->Оbj);																	//Передача объeкта по значению
			
			this->Count++;
			
			Append(node);

			tmp = tmp->Next;
		}
	}

	template<class T>
	void List<T>::Append(NodeList<T> *&node) {

		if(Head == nullptr) Head = Tail = node;

		else { 
			Tail->Next = node; 
			Tail = node;
		}
	}


	template<class T>
	void List<T>::Delete(T *obj) {

		NodeList<T> *node = this->Head;

		//Поиск узла с заданным ключом
		while(node && *node->Оbj != *obj) node = node->Next;

		//Если узел с заданным ключом найден
		if(*node->Оbj == *obj) {
			Delete(node);
			return;
		}

		throw string("\n Ошибка удаления, значение не найдено.");
	}

	template<class T>
	void List<T>::Delete(NodeList<T> *node) {

		//Если удаляемый элемент - голова.
		if(node == Head) { Head = Head->Next; }

		else {
			NodeList<T> *tmp = Head;										//Указатель на узел, стоящий перед удаляемым.

			//Поиск узла, стоящего перед удаляемым.
			while(tmp->Next && tmp->Next != node) { tmp = tmp->Next; }

			//Если удаляемый элемент - хвост.
			if(node == Tail) { Tail = tmp; }

			//Элемент из середины списка.
			else { tmp->Next = node->Next; }
		}

		delete node;
		Count--;
	}

	template<class T>
	void List<T>::Clear() {
		NodeList<T> *node;

		while(Head) {
			node = Head->Next;
			delete Head;

			Head = node;
		}

		Count = 0;
	}

	//============================================================================================================================||

	template<class T>
	NodeList<T>::NodeList(T *obj) {

		if(obj) this->Оbj = new T(*obj);
		else this->Оbj = nullptr;

		Next = nullptr;
	}

	template<class T>
	NodeList<T>::NodeList(NodeList<T> &Node) {

		if(Node.Next) this->Next = new NodeList<T>(*Node.Next);
		else this->Next = nullptr;

		if(Node.Оbj) this->Оbj = new T(*Node.Оbj);
		else this->Оbj = nullptr;
	}

	template<class T>
	NodeList<T>::NodeList() {
		Next = Оbj = nullptr;
	}

	template<class T>
	NodeList<T>::~NodeList() {
		Next = nullptr;

		delete this->Оbj;
	}
}