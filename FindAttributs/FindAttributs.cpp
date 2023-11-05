// FindAttributs.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#pragma once
#include "pch.h";

using namespace std;
using namespace SDictionary;
using namespace MyList;

int main()
{
    Dictionary<int, List<std::string>> dict;

    int a(0);
    string str("aaaa");

    List<string> LStr;

    LStr.Add(&str);


    dict.Add(&a, &LStr);

    std::cout << "Hello World!\n";
}