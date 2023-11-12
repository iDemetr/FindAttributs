////#include "iostream"
////#include "fstream"
//
#include "pch.h";
//
//using namespace std;
//
//struct Sentences{//list of findings
//	int n;//queue of finding;
//	string str;
//	Sentences* next_ptr;
//};
//
//struct Sentence_ptr{
//	Sentences* prev_ptr;
//	Sentences* cur_ptr;
//};
//
//struct Adjective_ending{
//	string end;
//	Adjective_ending *next_ptr;
//};	
//
//void Getting_Started();
//void input_file();
//
//Adjective_ending *start_Adjective_ending = nullptr;
//Sentences *start_Sentences_ptr = nullptr;
//const string Filter_File="Adjective.txt";
//
//int main(){
//	Getting_Started();
//	cout << "Filters were loaded"<<endl;
//	//input_file();
//	Adjective_ending *list_a = start_Adjective_ending, *pr_list_a;
//	//Show_list_of_filters
//	while(list_a!=nullptr){
//		cout << list_a->end <<", ";
//		pr_list_a=list_a->next_ptr;
//		delete list_a;
//		list_a = pr_list_a;
//	}
//	cout << endl;
//	input_file();
//	Sentences *list = start_Sentences_ptr, *pr_list;
//	//Show_list_of_filters
//	while(list!=nullptr){
//		cout<<list -> n<<' ' << list->str<<endl;
//		pr_list = list->next_ptr;
//		delete list;
//		list=pr_list;
//	}
//}
//
//void Getting_Started(){
//		ifstream File;
//		//str=Filter_File.substr(0, Filter_File.find('.'))+"1"+Filter_File.substr(Filter_File.find('.'));
//		File.open("Adjective.txt");//str
//		Adjective_ending *list_ptr=start_Adjective_ending, *prev_list_ptr=nullptr;
//		string str;
//		int pos1=0, pos2=0,j=0;
//        while(!File.eof()){
//			getline(File, str, '\n');
//			pos1=0;
//			pos2=0;
//			j=0;
//            while(j<=str.size()){
//                //cout << "str["<<j<<"]="<<str[j] <<endl;
//                if((str[j]>'a'-1 && str[j]< 'z'+1 || str[j]=='-') && j<str.size())
//                    pos2++;
//                else if(pos2>0){//seperator can be of any kind ,if j==str.size()
//                	list_ptr = new Adjective_ending;
//                	list_ptr->end=str.substr(pos1,pos2);
//                	//cout <<"Filter found, str=" <<str.substr(pos1,pos2)<<	" pos1="<< pos1 << " pos2="<<pos2+pos1<<endl;
//                	if(prev_list_ptr!=nullptr)
//                		prev_list_ptr->next_ptr=list_ptr;
//                	else
//                		start_Adjective_ending=list_ptr;
//                	list_ptr->next_ptr=nullptr;
//                	prev_list_ptr=list_ptr;
//      		   	pos1=j+1;
//      		   	pos2=0; 	
//                }
//                else
//                	pos1=j+1;
//                j++;
//	   }	
//	}
//	File.close();
//}
////last_sentece_ptr to add sentences in the list
//void input_file(){
//	ifstream File;
//	string File_name, str, str1;
//	Sentences *list_ptr=start_Sentences_ptr, *prev_list_ptr=nullptr;
//	int n=0, pos=0;//n=last_sentence_ptr->n;
//     while(!File.is_open()){
//	     if(/*!menu(File_name, file_reading) && */File_name.empty()){
//	         cout << "Enter name of file with data to work with"<<endl;
//    		 getline(cin, File_name, '\n');
//	         if(File_name.find('.') == string::npos){
//	             cout << "adding expansion\n";
//	             File_name += ".txt";
//	         }
//	         File.open(File_name, ios::in);
//	     	if(!File.is_open())
//	      	   cout << "File doesn't exist"<<endl;
//     	}
//	}
//	cout <<"File was opened"<<endl;
//	pos=0;
//	while(!File.eof()){
//			getline(File, str1, '\n');
//			if(str.empty())
//				str=str1;
//			else
//				str+=str1;
//			cout << "str="<<str << endl;
//			
//			while(str.find('.', pos)!=string::npos){
//				n++;
//				list_ptr = new Sentences;
//				list_ptr->n=n;
//				if(str[pos]==' ')pos++;
//	        	list_ptr->str=str.substr(pos,str.find('.', pos)-pos);
//	        	//cout << '#' << n << "	\""<< list_ptr->str<<"\"" << endl;
//	        	if(prev_list_ptr!=nullptr)
//	        		prev_list_ptr->next_ptr=list_ptr;
//	        	else
//	        		start_Sentences_ptr=list_ptr;
//	        	list_ptr->next_ptr=nullptr;
//	        	prev_list_ptr=list_ptr;
//	        	pos=str.find('.', pos)+1;
//				//Adding sentence str.find('.', pos);
//			}
//	}
//	File.close();
//}