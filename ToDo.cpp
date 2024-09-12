// ToDo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "ToDo.h"


extern int n;
/*-------------------CTR----------------------------*/
ToDo::ToDo() {
	const std::string filename("task.bin");
	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open()) {
		std::cerr
			<< "Error: Failed to open file for reading."
			<< std::endl;
		return;
	}
	// aflam cate task-uri sunt in fisier
	size_t taskSize = 0;
	file.read(reinterpret_cast<char*>(&taskSize), sizeof(taskSize));

	size_t nonImportantTaskSize = 0;
	file.read(reinterpret_cast<char*>(&nonImportantTaskSize), sizeof(nonImportantTaskSize));

	file.close();
	n = taskSize + nonImportantTaskSize;
};

ToDo::ToDo(const ToDo &obj)
{
	task = obj.task;
	non_important_task = obj.non_important_task;
}



/*-------------------Functii manipulare date----------------------------*/

void ToDo::serialize(const std::string filename)
{
	std::ofstream file(filename, std::ios::binary);
	if (!file.is_open())
	{
		std::cerr << "Error: Failed to open file for writing." << std::endl;
		return;
	}
	// serializare lista `task`
	size_t taskSize = task.size();
	file.write(reinterpret_cast<const char*>(&taskSize), sizeof(taskSize));
	for (const auto& t : task)
	{
		size_t length = t.size();
		file.write(reinterpret_cast<const char*>(&length), sizeof(length));
		file.write(t.c_str(), length);
	}

	// serializare lista `non_important_task`
	size_t nonImportantTaskSize = non_important_task.size();
	file.write(reinterpret_cast<const char*>(&nonImportantTaskSize), sizeof(nonImportantTaskSize));
	for (const auto& t : non_important_task)
	{
		size_t length = t.size();
		file.write(reinterpret_cast<const char*>(&length), sizeof(length));
		file.write(t.c_str(), length);
	}
	file.close();
	n = task.size() + non_important_task.size();
}

void ToDo::deserialize(const std::string filename)
{
	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open()) {
		std::cerr
			<< "Error: Failed to open file for reading."
			<< std::endl;
		return;
	}
	// Deserializam lista `task`
	size_t taskSize = 0;
	file.read(reinterpret_cast<char*>(&taskSize), sizeof(taskSize));
	if (taskSize == 0)
		return;
	task.clear();
	for (size_t i = 0; i < taskSize; ++i)
	{
		size_t length;
		file.read(reinterpret_cast<char*>(&length), sizeof(length));
		std::string t(length, ' ');
		file.read(&t[0], length);
		task.push_back(t);
	}

	// Deserializam lista `non_important_task`
	size_t nonImportantTaskSize = 0;
	file.read(reinterpret_cast<char*>(&nonImportantTaskSize), sizeof(nonImportantTaskSize));
	if (nonImportantTaskSize == 0)
		return;
	non_important_task.clear();
	for (size_t i = 0; i < nonImportantTaskSize; ++i)
	{
		size_t length;
		file.read(reinterpret_cast<char*>(&length), sizeof(length));
		std::string t(length, ' ');
		file.read(&t[0], length);
		non_important_task.push_back(t);
	}
	file.close();

	n = task.size() + non_important_task.size();
}

void Menu()
{
	std::cout << std::endl << std::endl;
	std::string border = "============================================";
	std::string title = "\t\tToDo List Menu";

	std::cout << border << std::endl;
	std::cout << title << std::endl;
	std::cout << border << std::endl;
	std::cout << "    Numar task-uri curente: " << n << std::endl;
	std::cout << " 1. Adauga un task nou" << std::endl;
	std::cout << " 2. Afiseaza toate task-urile" << std::endl;
	std::cout << " 3. Sterge un task executat" << std::endl;
	std::cout << " 4. Sterge toate taskurile" << std::endl;
	std::cout << " Q. Iesire" << std::endl;
	std::cout << border << std::endl;
	std::cout << "Selecteaza o optiune: ";
}

void ToDo::SetTask()
{
	while (std::cin.get() != '\n')
		continue;
	system("cls");
	std::string border = "============================================";
	std::cout << border << std::endl;
	std::cout << " 1. Adauga task important" << std::endl;
	std::cout << " 2. Adauga task neimportant" << std::endl;
	std::cout << border << std::endl;
	int choise = 0;
	std::cin >> choise;

	if (choise == 1)
	{
		system("cls");
		std::cout << "Introdu taskurile(pentru sfarsit apasa enter pe linia noua):\n";
		std::string str;
		int j = 1;

		std::cin.get();
		std::cout << j << ": ";
		getline(std::cin, str);
		while (!str.empty())
		{
			++j;
			task.push_back(str);

			std::cout << j << ": ";
			getline(std::cin, str);
		}
		n = task.size();
		system("cls");
	}
	else if (choise == 2)
	{
		system("cls");
		std::cout << "Introdu taskurile(pentru sfarsit apasa enter pe linia noua):\n";
		std::string str;
		int j = 1;

		std::cin.get();
		std::cout << j << ": ";
		getline(std::cin, str);
		while (!str.empty())
		{
			++j;
			non_important_task.push_back(str);

			std::cout << j << ": ";
			getline(std::cin, str);
		}
		n = task.size() + non_important_task.size();
		system("cls");
	}
	else
	{
		std::cin.clear();
		while (std::cin.get() != '\n')
			continue;
		throw std::invalid_argument("Alegere incorecta!");
	}
	
}

void ToDo::GetTasks()
{
	if (task.empty() && non_important_task.empty())
	{
		std::cout << "Nu sunt taskuri adaugate!\n";
		return;
	}
	else if(!non_important_task.empty() || !task.empty())
	{
		std::cout << "Task-uri importante:\n";
		int j = 0;
		for (const auto &x : task)
			std::cout << ++j << ": " << x << std::endl;
		std::cout << "Task-uri neimportante:\n";
		j = 0;
		for (const auto &x : non_important_task)
			std::cout << ++j << ": " << x << std::endl;
	}

}

void ToDo::DeleteTask()
{
	
	this->deserialize();

	int j = 0;
	std::cout << "Task-uri importante\n";
	for (auto &i : task)
		std::cout << ++j <<": " << i << std::endl;
	j = 0;
	std::cout << "Task-uri ne-importante\n";
	for (auto &i : non_important_task)
		std::cout << ++j << ": " << i << std::endl;

	if (task.empty() && non_important_task.empty())
	{
		std::cout << "Nu sunt taskuri adaugate!\n";
		return;
	}

	try
	{
		std::string border = "============================================";
		std::cout << border << std::endl;
		std::cout << " 1. Sterge task important" << std::endl;
		std::cout << " 2. Sterge task neimportant" << std::endl;
		std::cout << border << std::endl;
		int choise = 0;
		std::cin >> choise;
		if (choise == 1)
		{
			if (task.size() == 0)
				throw std::invalid_argument("Nu sunt task-uri importante adaugate!\n");

			std::cout << "Introdu numarul taskului: ";
			int index;
			std::cin >> index;
			if (!std::cin)
			{
				std::cin.clear();
				while (std::cin.get() != '\n')
					continue;
				throw std::invalid_argument("Introdu numar, nu litera sau simbol!\n");
			}

			if (index < 1 || index > task.size())
				throw std::invalid_argument("Invalid index!\n");

			auto it = task.begin();
			if (index == 1)
			{
				task.pop_front();
				n = task.size() + non_important_task.size();

				this->serialize("temp.bin");
				remove("task.bin");
				rename("temp.bin", "task.bin");
				return;
			}

			else if (index == n)
			{
				task.pop_back();
				n = task.size() + non_important_task.size();

				this->serialize("temp.bin");
				remove("task.bin");
				rename("temp.bin", "task.bin");
				return;
			}

			std::advance(it, index - 1);
			task.erase(it);
			n = task.size() + non_important_task.size();

			this->serialize("temp.bin");
			remove("task.bin");
			rename("temp.bin", "task.bin");
		}

		else if (choise == 2)
		{
			if (non_important_task.size() == 0)
				throw std::invalid_argument("Nu sunt task-uri neimportante adaugate!\n");

			std::cout << "Introdu numarul taskului: ";
			int index;
			std::cin >> index;
			if (!std::cin)
			{
				std::cin.clear();
				while (std::cin.get() != '\n')
					continue;
				throw std::invalid_argument("Introdu numar, nu litera sau simbol!\n");
			}

			if (index < 1 || index > non_important_task.size())
				throw std::invalid_argument("Invalid index!\n");

			auto it = non_important_task.begin();
			if (index == 1)
			{
				non_important_task.pop_front();
				n = non_important_task.size() + task.size();

				this->serialize("temp.bin");
				remove("task.bin");
				rename("temp.bin", "task.bin");
				return;
			}

			else if (index == n)
			{
				non_important_task.pop_back();
				n = non_important_task.size() + task.size();

				this->serialize("temp.bin");
				remove("task.bin");
				rename("temp.bin", "task.bin");
				return;
			}

			std::advance(it, index - 1);
			non_important_task.erase(it);
			n = non_important_task.size() + task.size();

			this->serialize("temp.bin");
			remove("task.bin");
			rename("temp.bin", "task.bin");
		}

	}

	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}

	//////////////////////////////////////////////////////
	/*if (task.empty() && non_important_task.empty())
	{
		std::cout << "Nu sunt taskuri adaugate!\n";
		return;
	}

	try
	{
		std::string border = "============================================";
		std::cout << border << std::endl;
		std::cout << " 1. Sterge task important" << std::endl;
		std::cout << " 2. Sterge task neimportant" << std::endl;
		std::cout << border << std::endl;
		int choise = 0;
		std::cin >> choise;
		if (choise == 1)
		{
			if (task.size() == 0)
				throw std::invalid_argument("Nu sunt task-uri importante adaugate!\n");

			std::cout << "Introdu numarul taskului: ";
			int index;
			std::cin >> index;
			if (!std::cin)
			{
				std::cin.clear();
				while (std::cin.get() != '\n')
					continue;
				throw std::invalid_argument("Introdu numar, nu litera sau simbol!\n");
			}

			if (index < 1 || index > task.size())
				throw std::invalid_argument("Invalid index!\n");

			auto it = task.begin();
			if (index == 1)
			{
				task.pop_front();
				n = task.size() + non_important_task.size();
				return;
			}

			else if (index == n)
			{
				task.pop_back();
				n = task.size() + non_important_task.size();
				return;
			}

			std::advance(it, index - 1);
			task.erase(it);
			n = task.size() + non_important_task.size();
		}

		else if (choise == 2)
		{
			if (non_important_task.size() == 0)
				throw std::invalid_argument("Nu sunt task-uri neimportante adaugate!\n");

			std::cout << "Introdu numarul taskului: ";
			int index;
			std::cin >> index;
			if (!std::cin)
			{
				std::cin.clear();
				while (std::cin.get() != '\n')
					continue;
				throw std::invalid_argument("Introdu numar, nu litera sau simbol!\n");
			}

			if (index < 1 || index > non_important_task.size())
				throw std::invalid_argument("Invalid index!\n");

			auto it = non_important_task.begin();
			if (index == 1)
			{
				non_important_task.pop_front();
				n = non_important_task.size() + task.size();
				return;
			}

			else if (index == n)
			{
				non_important_task.pop_back();
				n = non_important_task.size() + task.size();
				return;
			}

			std::advance(it, index - 1);
			non_important_task.erase(it);
			n = non_important_task.size() + task.size();
		}

	}

	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}*/
}

void ToDo::DeleteAllTask()
{
	system("cls");
	if (task.empty() && non_important_task.empty())
	{
		std::cout << "Nu sunt taskuri adaugate!\n";
		return;
	}
	std::ofstream fout;
	fout.open("temp.bin");
	fout.close();
	task.clear();
	non_important_task.clear();
	remove("task.bin");
	rename("temp.bin", "task.bin");
	n = 0;
}
