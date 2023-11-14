#include "iostream"
#include "fstream"

using namespace std;

struct Sentences{//list of findings
	int n;//queue of finding;
	string str;
	Sentences* next_ptr;
};

struct Sentence_ptr{
	Sentences* prev_ptr;
	Sentences* cur_ptr;
};

struct Adjective_ending{
	string end;
	Adjective_ending *next_ptr;
};	

void Getting_Started();
void input_file();
void sentence_list_filter();
bool filter_check(string *filter, string *sentence, int start, int length);

Adjective_ending *start_Adjective_ending = nullptr;
Sentences *start_Sentences_ptr = nullptr;
const string Filter_File="Adjective.txt";

int main(){
	Getting_Started();
	input_file();
	sentence_list_filter();
	//cout << "Filters were loaded"<<endl;
	//input_file();
	Adjective_ending *list_a = start_Adjective_ending, *pr_list_a;
	//Show_list_of_filters
	while(list_a!=nullptr){
		cout << list_a->end <<", ";
		pr_list_a=list_a->next_ptr;
		delete list_a;
		list_a = pr_list_a;
	}
	cout << endl;
	Sentences *list = start_Sentences_ptr, *pr_list;
	//Show_list_of_filters
	while(list!=nullptr){
		cout<<list -> n<<' ' << list->str<<endl;
		pr_list = list->next_ptr;
		delete list;
		list=pr_list;
	}
}

void Getting_Started(){
		ifstream File;
		//str=Filter_File.substr(0, Filter_File.find('.'))+"1"+Filter_File.substr(Filter_File.find('.'));
		File.open("Adjective.txt");//str
		Adjective_ending *list_ptr=start_Adjective_ending, *prev_list_ptr=nullptr;
		string str;
		int pos1=0, pos2=0,j=0;
        while(!File.eof()){
			getline(File, str, '\n');
			pos1=0;
			pos2=0;
			j=0;
            while(j<=str.size()){
                //cout << "str["<<j<<"]="<<str[j] <<endl;
                if((str[j]>'a'-1 && str[j]< 'z'+1 || str[j]=='-') && j<str.size())//j - in case we don't have symbol of ending file in the end'
                    pos2++;
                else if(pos2>0){//seperator can be of any kind ,if j==str.size()
                	list_ptr = new Adjective_ending;
                	list_ptr->end=str.substr(pos1,pos2);
                	//cout <<"Filter found, str=" <<str.substr(pos1,pos2)<<	" pos1="<< pos1 << " pos2="<<pos2+pos1<<endl;
                	if(prev_list_ptr!=nullptr)
                		prev_list_ptr->next_ptr=list_ptr;
                	else
                		start_Adjective_ending=list_ptr;
                	list_ptr->next_ptr=nullptr;
                	prev_list_ptr=list_ptr;
      		   	pos1=j+1;
      		   	pos2=0; 	
                }
                else
                	pos1=j+1;
                j++;
	   }	
	}
	File.close();
}

//last_sentece_ptr to add sentences in the list
void input_file(){
	ifstream File;
	string File_name, str, str1;
	Sentences *list_ptr=start_Sentences_ptr, *prev_list_ptr=nullptr;
	int n=0, pos=0;//n=last_sentence_ptr->n;
     while(!File.is_open()){
	     if(/*!menu(File_name, file_reading) && */File_name.empty()){
	         cout << "Enter name of file with data to work with"<<endl;
    		 getline(cin, File_name, '\n');
	         if(File_name.find('.') == string::npos){
	             cout << "adding expansion\n";
	             File_name += ".txt";
	         }
	         File.open(File_name, ios::in);
	     	if(!File.is_open()){
	      	   cout << "File doesn't exist"<<endl;
	      	   File_name="";
	     	}
     	}
	}
	cout <<"File was opened"<<endl;
	pos=0;
	while(!File.eof()){
			pos=0;
			getline(File, str1, '\n');
			if(str1[str1.size()-1]=='\r')
                str1=str1.substr(0, str1.size()-1);
			if(str.empty())
				str=str1;
			else
				str=str + str1;
			while(str.find('.', pos)!=string::npos){
				n++;
				list_ptr = new Sentences;
				list_ptr->n=n;
				if(str[pos]==' ')pos++;
	        	list_ptr->str=str.substr(pos,str.find('.', pos)-pos);
	        	//cout << '#' << n << "	\""<< list_ptr->str<<"\"" << endl;
	        	if(prev_list_ptr!=nullptr)
	        		prev_list_ptr->next_ptr=list_ptr;
	        	else
	        		start_Sentences_ptr=list_ptr;
	        	list_ptr->next_ptr=nullptr;
	        	prev_list_ptr=list_ptr;
	        	pos=str.find('.', pos)+1;
			}
			if(pos<str.size()){
				if(pos>0)
					str=str.substr(pos);
			}
			else
				str="";
	}
	File.close();
}

void sentence_list_filter(){
	Sentences *list=start_Sentences_ptr;
	Adjective_ending *ends=start_Adjective_ending;
	string *str;
	int pos=0, pos1=0;//pos - start, pos1 - length
	bool adding=0;
	while(list!=nullptr){//cycle of sentences
		str=&(list->str);
		//cout << "str="<<*str<<endl;
		pos=0;
		while(pos<(*str).size()){
			while((*str)[pos+pos1]>'a'-1 && (*str)[pos+pos1]<'z'+1 || (*str)[pos+pos1]>'A'-1 && (*str)[pos+pos1]<'Z'+1)
				pos1++;
			ends=start_Adjective_ending;
			if(pos1>0){
				//cout <<"start="<< pos << "    length="<<pos1<< " word="<<(*str).substr(pos,pos1) << endl;
				while(ends!=nullptr &&!filter_check(&(ends->end), str, pos, pos1))
					ends=ends->next_ptr;
				if(ends!=nullptr) //ADDING
					cout << (*str).substr(pos, pos1)<<endl;
			}
			pos+=pos1+1;
			pos1=0;
		}
		list=list->next_ptr;
	}
}
	
bool filter_check(string *filter, string *sentence, int start, int length){
	bool prefix=0;
	bool postfix=0;
	//cout << "cur_word=\""<<(*sentence).substr(start, length) << "\"	cur_filter="<<(*filter)<<endl;
	//cout << "start="<<start<<" end="<<start+length<<endl;
	if(length<=(*filter).size())//cout << "Too short"<<endl;
		return 0;
	if((*filter)[(*filter).size()-1]=='-')
		prefix=1;
	if((*filter)[0]=='-'){
		postfix=1;
		start+=(length-(*filter).size()+postfix)*!prefix/*case of ending*/-prefix*2;//2 is minimal size of part of word before postfix
		length=((*filter).size()-postfix)*!prefix + prefix*(length-2);
	}	
	if(!(prefix && postfix))
		length=(*filter).size()-1-prefix*2;
	int j=postfix;
	//cout << "word_part=\""<<(*sentence).substr(start, length)<<"\"	searching="<<(*filter).substr(postfix, (*filter).size()-1-prefix)<<endl;
	//cout << "s_start="<<start<<" s_end="<<start+length<<endl;
	for(int i=start;i<start+length-postfix+1 && j<(*filter).size()-prefix-postfix+1;i++){//postfix indecates that there should be at least 1 character after
		//cout << "sentence["<<i<<"]="<<(*sentence)[i] << "  filter["<<j<<"]="<<(*filter)[j]<<endl;
		if((*filter)[j] == (*sentence)[i])
			j++;
		else
			j=postfix;
		if(!(prefix&&postfix) && j==postfix)
			i=start+length;
	}
	//cout << "j="<<j<<" we got:"<<(*filter).size()-prefix-postfix+1<<endl;
	if(j==(*filter).size()-prefix-postfix+1)
		return 1;
	return 0;
}