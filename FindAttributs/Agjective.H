#pragma once

#ifndef ADJECTIVE_H
#define ADJECTIVE_H

#include <filesystem>

using namespace std;
using namespace std::filesystem;
using namespace SDictionary;
using namespace SList;


/// <summary>
/// ���� �������� 
/// </summary>
const std::string Filter_File = "Data/Adjective.txt";

/// <summary>
/// �������������� ����
/// </summary>
const std::string AdjectivesRes = "Data/Adjectives_Result.txt";
/// <summary>
/// �������������� ����
/// </summary>
const std::string NumeredSentences = "Data/Numered Sentences.txt";

/// <summary>
/// ����
/// </summary>
enum menu { NoN = -1, PrintCMD = '1', PrintFile, quit = 27 };

/// <summary>
/// �����������
/// first - ���������� ����� �����������
/// second - �����������
/// </summary>
typedef std::pair<int, std::string> Sentence;

/// <summary>
/// ������� ����������� �����������
/// </summary>
typedef Dictionary<std::string, Sentence*> DictAdjectives;

/// <summary>
/// ������ �����������, ���:
/// first - ���������� ����� �����������
/// second - �����������
/// </summary>
typedef List<Sentence> LSentences;

/// <summary>
/// ������� ������� ���������� ������� �� �����
/// </summary>
/// <param name="start_dict"></param>
/// <param name="dict_pivot"></param>
/// <param name="end_dict"></param>
template<class TKey, class TValue>
void QuickSort_Dict(NodeDict* start_dict, NodeDict* dict_pivot, NodeDict* end_dict, DictAdjectives*);

/// <summary>
/// �������� ������ �������� ��� ������ �����������
/// </summary>
List<std::string> Getting_Started();
/// <summary>
/// ��������� ������ �����������
/// </summary>
/// <param name="stream">�������� �����</param>
/// <returns></returns>
LSentences* Define_Sentences(std::ifstream&);

/// <summary>
/// ��������� ������� ����������� �� ������ �����������
/// </summary>
/// <param name="Sentences">��������� �����������</param>
DictAdjectives* sentence_list_filter(LSentences*);


#endif