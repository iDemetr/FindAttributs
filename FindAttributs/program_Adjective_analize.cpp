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

//-----------------------------------------------------------------------------------------------------||

List<std::string> Getting_Started() {

	/// <summary>
	/// Список окончаний
	/// </summary>
	List<std::string> Adjective_ending;

	ifstream File(Filter_File);
	
	cout << "\n Подготовка к анализу... \n Считывание фильтров...";

	if (!File.is_open()) {
		cout << "\n Файл фильтров не обнаружен по пути: Data\\!";
		throw new exception("Не удаётся отрыть файл Data\\Adjective.txt");
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
	
	//ifstream file(fileName);

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

		while (point = str.find('.', pos), point != string::npos) {
			// Пропуск пробелов между окончанием предложения и началом нового.
			while(str[pos] == ' ') { pos++; }

			Sentences->Add({ ++n, str.substr(pos, point - pos)});
			pos = point + 1;
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

#ifdef NDEBUG
		Sleep(20);
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
					Adjectives->Add((*str).substr(pos, pos1), tmp);
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
