#pragma once
#ifndef _TODO_H
#define _TODO_H
#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <iterator>
#include <fstream>

class ToDo
{
private:

	std::list<std::string> task;
	std::list<std::string> non_important_task;

public:
	ToDo();
	~ToDo() {}
	ToDo(const ToDo&);

	
	void SetTask();
	void GetTasks();
	void DeleteTask();
	void DeleteAllTask();
	
	void serialize(const std::string filename ="task.bin");
	void deserialize(const std::string filename = "task.bin");

};

void Menu();
#endif

