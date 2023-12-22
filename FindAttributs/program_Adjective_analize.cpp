#include "pch.h"
#include "Agjective.H"

using namespace std;

//int main() {
	//cout << "Filters were loaded"<<endl;
	//input_file();
	//
	//Adjective_ending* list_a = start_Adjective_ending, * pr_list_a;
	//Show_list_of_filters
	//while (list_a != nullptr) {
	//	cout << list_a->end << ", ";
	//	pr_list_a = list_a->next_ptr;
	//	delete list_a;
	//	list_a = pr_list_a;
	//}
	//cout << endl;
	//
	////Sentences* list = start_Sentences_ptr, * pr_list;
	////Show_list_of_filters
	//while (list != nullptr) {
	//	cout << list->n << ' ' << list->str << endl;
	//	pr_list = list->next_ptr;
	//	delete list;
	//	list = pr_list;
	//}
//}

bool filter_check(string*, string*, int, int);
int getEndedSentences(const std::string&, const int&);

//-----------------------------------------------------------------------------------------------------||

List<std::string> Getting_Started() {

	/// <summary>
	/// Список окончаний
	/// </summary>
	List<std::string> Adjective_ending;

	ifstream File(Filter_File);
	
	cout << "\n Подготовка к анализу... \n Считывание фильтров...";

	if (!File.is_open()) {
		cout << "\n Файл фильтров не обнаружен по пути: " << Filter_File;
		cout << "\n Завершение программы...";
		getchar();
		throw new exception("Не удаётся отрыть файл: Data\\Adjective.txt");
	}
		
	string str;
	int pos1 = 0, pos2 = 0, j = 0;

	while (!File.eof()) {
		getline(File, str, '\n');
		pos1 = 0;
		pos2 = 0;
		j = 0;
		while (j <= str.size()) {
			//cout << "str["<<j<<"]="<<str[j] <<endl;
			if ((str[j] > 'а' - 1 && str[j] < 'я' + 1 || str[j] == '-') && j < str.size())//j - in case we don't have symbol of ending file in the end
				pos2++;
			else if (pos2 > 2) {//seperator can be of any kind ,if j==str.size()
				Adjective_ending.Add(str.substr(pos1, pos2));
				//cout <<"Filter found, str=" <<str.substr(pos1,pos2)<<	" pos1="<< pos1 << " pos2="<<pos2+pos1<<endl;
				pos1 = j + 1;
				pos2 = 0;
			}
			else
				pos1 = j + 1;
			j++;
		}
	}
	File.close();
	return Adjective_ending;
}

//-----------------------------------------------------------------------------------------------------||

LSentences* Define_Sentences(std::ifstream &file) {
	
	ofstream oStr(NumeredSentences);
	oStr << "Файл пронумерованных предложений, подверженных анализу.";

	LSentences *Sentences = new LSentences;
	string str, str1;

	cout << "\n Формирование списка предложений.";

	int n = 0, pos = 0, point(0);//n=last_sentence_ptr->n;
	while (!file.eof()) {
		pos = 0;
		getline(file, str1, '\n');
		
		if (str1.size() == 0)
			continue;

		if (str1[str1.size() - 1] == '\r')
			str1 = str1.substr(0, str1.size() - 1);
		
		if (str.empty())
			str = str1;
		else
			str = str + str1;

		while (point = getEndedSentences(str, pos), point != string::npos) {
			// Пропуск пробелов между окончанием предложения и началом нового.
			while(str[pos] == ' ') { pos++; }
			point++;

			string s = str.substr(pos, point - pos);
			Sentences->Add({ ++n, s});
			oStr << "\n" << n << ": " << s;
			pos = point + 1;
			if (pos >= str.size())
				break;
			//cout << '#' << n << "	\""<< list_ptr->str<<"\"" << endl;
		}

		if (pos < str.size()) {
			if (pos > 0)
				str = str.substr(pos);
		}
		else
			str = "";
	}

	file.close();

	int res = (Sentences) ? Sentences->Count : 0;
	cout << "\n Обнаружено " << res << " предложений.";

	return Sentences;
}

int getEndedSentences(const std::string& str, const int& pos) {

	int point = str.find("...", pos);
	
	if(point != string::npos)
		point += str.substr(point+3, str.size() - point - 3).find('.') + 3;
	else 
		point = str.find('.', pos);
	

	if (point != string::npos) {
		char ch = str[point - 1];
		if (ch >= 'А' && ch <= 'Я') {
			point++;
			string s = str.substr(point, str.size() - point);
			int p = s.find('.');
			if (p != string::npos)
				point += p;
			else
				point = p;
		}
	}
	
	if(point == string::npos)
		point = str.find('!', pos);

	if(point == string::npos)
		point = str.find('?', pos);

	if(point == string::npos)
		point = str.find(';', pos);

	return point;
}

//-----------------------------------------------------------------------------------------------------||

DictAdjectives* sentence_list_filter(LSentences *Sentences) {

	List<std::string> Adjective_ending = Getting_Started();

	cout << "\n Анализ текста...";

	DictAdjectives* Adjectives = new DictAdjectives();

	string* str;
	int pos = 0, pos1 = 0;//pos - start, pos1 - length
	bool adding = 0;

	int status(0);

	auto tmp = Sentences->Head;
	//cycle of sentences
	while (tmp != nullptr) {

		std::cout << "\r Completed " << status << "/" << Sentences->Count << std::flush;

#ifndef NDEBUG
		//Sleep(40);
#endif
		str = &(tmp->Оbj.second);
		//cout << "str="<<*str<<endl;
		pos = 0;
		while (pos < (*str).size()) {
			while ((*str)[pos + pos1] >= 'а' && (*str)[pos + pos1] <= 'я' ||
				(*str)[pos + pos1]>='А' && (*str)[pos + pos1] <= 'Я' ||
				(*str)[pos + pos1] == '-') 
			{
				pos1++;
			}

			//ends = start_Adjective_ending;
			auto ends = Adjective_ending.Head;
			if (pos1 > 0) {
				//cout <<"start="<< pos << "    length="<<pos1<< " word="<<(*str).substr(pos,pos1) << endl;
				while (ends != nullptr && !filter_check(&(ends->Оbj), str, pos, pos1))
					ends = ends->Next;

				if (ends != nullptr) {
					string tmpstr = (*str).substr(pos, pos1);
					Adjectives->Add(tmpstr, &tmp->Оbj);
				}
			}
			pos += pos1 + 1;
			pos1 = 0;
		}
		status++;
		tmp = tmp->Next;
	}

	std::cout << "\r Completed " << status << "/" << Sentences->Count << std::flush;
	cout << "\r Анализ завершён." << std::flush;

#pragma region --- Сортировка ---

	auto tmpPtr = Adjectives->Head;
	auto pivot = tmpPtr;
	bool inv = 1;
	//find the middle of list
	while (tmpPtr) {
		inv = !inv;
		if (inv)
			pivot = pivot->Next;
		tmpPtr = tmpPtr->Next;
	}
	QuickSort_Dict(Adjectives->Head, pivot, Adjectives->Tail, Adjectives);

#pragma endregion

 	return Adjectives;
}

//-----------------------------------------------------------------------------------------------------||

/// <summary>
/// 
/// </summary>
/// <param name="filter"></param>
/// <param name="sentence"></param>
/// <param name="start"></param>
/// <param name="length"></param>
/// <returns></returns>
bool filter_check(string* filter, string* sentence, int start, int length) {
	bool prefix = 0;
	bool postfix = 0;
	//cout << "cur_word=\""<<(*sentence).substr(start, length) << "\"	cur_filter="<<(*filter)<<endl;
	//cout << "start="<<start<<" end="<<start+length<<endl;
	if (length <= (*filter).size())//cout << "Too short"<<endl;
		return 0;
	if ((*filter)[(*filter).size() - 1] == '-')
		prefix = 1;
	if ((*filter)[0] == '-') {
		postfix = 1;
		start += (length - (*filter).size() + postfix) * !prefix/*case of ending*/ - prefix * 2;//2 is minimal size of part of word before postfix
		length = ((*filter).size() - postfix) * !prefix + prefix * (length - 2);
	}
	if (!(prefix && postfix))
		length = (*filter).size() - 1 - prefix * 2;
	int j = postfix;
	//cout << "word_part=\""<<(*sentence).substr(start, length)<<"\"	searching="<<(*filter).substr(postfix, (*filter).size()-1-prefix)<<endl;
	//cout << "s_start="<<start<<" s_end="<<start+length<<endl;
	for (int i = start; i < start + length - postfix + 1 && j < (*filter).size() - prefix - postfix + 1; i++) {//postfix indecates that there should be at least 1 character after
		//cout << "sentence["<<i<<"]="<<(*sentence)[i] << "  filter["<<j<<"]="<<(*filter)[j]<<endl;
		if ((*filter)[j] == (*sentence)[i])
			j++;
		else
			j = postfix;
		if (!(prefix && postfix) && j == postfix)
			i = start + length;
	}
	//cout << "j="<<j<<" we got:"<<(*filter).size()-prefix-postfix+1<<endl;
	if (j == (*filter).size() - prefix - postfix + 1)
		return 1;
	return 0;
}

//-----------------------------------------------------------------------------------------------------||

/// <summary>
/// Сравнивает слова в алфавитном порядке
/// </summary>
/// <param name="word1"></param>
/// <param name="word2"></param>
/// <returns></returns>
bool word_compare(string& word1, string& word2) {
	int W1 = 0, W2 = 0;
	for (int i = 0; i < word1.size() && i < word2.size(); i++) {
		if (word1[0] >= 'А' && word1[0] <= 'Я') W1 = 'А' - 'а';
		else W1 = 0;
		if (word2[0] >= 'А' && word2[0] <= 'Я') W2 = 'А' - 'а';
		else W2 = 0;
		if ((int)word1[i] - W1 > (int)word2[i] - W2) //if(word1[i]>word2[i])
			return false;
		else if (word1[i] - W1 != word2[i] - W2)
			return true;
	}
	if (word1.size() > word2.size()) //if(word1.size()>word2.size())
		return false;
	return true;
}


template<class TKey, class TValue>
void QuickSort_Dict(NodeDict* start_dict, NodeDict* dict_pivot, NodeDict* end_dict, DictAdjectives* dict) {
	string pivot = dict_pivot->Key;//ptr to word relatively which sorting is being executed

	int counter = 0;

	NodeDict* buf_lptr, * buf_rptr;
	//operating pointers to move by dict

	NodeDict* left_ptr = start_dict,
		* right_ptr = end_dict,
		* buf_ptr = nullptr;

	//pointers to next QuickSort iteration
	NodeDict* next_pivot_left = start_dict,
			* next_pivot_right = end_dict;

	//inverting flags, when true next_pivot ptrs move further
	bool left = true, right = true;
	while (left_ptr != right_ptr) {
		//Left
		while (word_compare(left_ptr->Key, pivot) && left_ptr != dict_pivot) {
			left ^= true;
			left_ptr = left_ptr->Next;
			if (left)
				next_pivot_left = next_pivot_left->Next;
		}
		//Right
		while (word_compare(pivot, right_ptr->Key) && dict_pivot != right_ptr) {
			right ^= true;
			right_ptr = right_ptr->Previous;
			if (right)
				next_pivot_right = next_pivot_right->Previous;
		}
		//Swapping
		if (left_ptr != right_ptr) {

			if (left_ptr->Previous != nullptr)
				left_ptr->Previous->Next = right_ptr;
			else
				dict->Head = right_ptr;
			if (right_ptr->Next != nullptr)
				right_ptr->Next->Previous = left_ptr;
			else
				dict->Tail = left_ptr;
			//case them side by side of each other skippped will be operated inside nodes themselves
			if (left_ptr->Next != right_ptr) {
				left_ptr->Next->Previous = right_ptr;
				right_ptr->Previous->Next = left_ptr;
			}
			//changing next pivots, they should stay in place relatively the ends of list
			if (next_pivot_left == left_ptr)
				next_pivot_left = right_ptr;
			if (next_pivot_right == right_ptr)
				next_pivot_right = left_ptr;
			if (start_dict == left_ptr)
				start_dict = right_ptr;
			if (end_dict == right_ptr)
				end_dict = left_ptr;
			//changing ptrs inside nodes themselves
			buf_lptr = left_ptr->Next;
			buf_rptr = right_ptr->Previous;


			left_ptr->Next = right_ptr->Next;
			right_ptr->Previous = left_ptr->Previous;

			if (buf_lptr != right_ptr) {
				left_ptr->Previous = buf_rptr;
				right_ptr->Next = buf_lptr;
			}
			else {//will be pointing on each other
				left_ptr->Previous = right_ptr;
				right_ptr->Next = left_ptr;
			}
			buf_ptr = left_ptr;
			if (dict_pivot != right_ptr)
				left_ptr = right_ptr->Next;
			else
				left_ptr = right_ptr;
			if (dict_pivot != buf_ptr/* || left_ptr==right_ptr*/)
				right_ptr = buf_ptr->Previous;
			else
				right_ptr = buf_ptr;
		}
	}
	pivot = "";
	//Sorting left side from pivot
	if (dict_pivot != start_dict && dict_pivot->Previous != start_dict)//otherwise the dict 1 elem or 2 elem long incl. pivot - so it's sorted guaranteed
		QuickSort_Dict(start_dict, next_pivot_left, dict_pivot->Previous, dict);
	//Sorting right side from pivot
	if (dict_pivot != end_dict && dict_pivot != end_dict->Previous)
		QuickSort_Dict(dict_pivot->Next, next_pivot_right, end_dict, dict);
}

//-----------------------------------------------------------------------------------------------------||
