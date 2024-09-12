#include "ToDo.h"									// include biblioteci: iostream, list, string, alghoritm, iterator 


int n;												// n este variabila globala pentru numarul curent de task-uri

using std::cout;
using std::cin;
using std::endl;


int main()
{
	ToDo task;										// obiect folosit pentru a seta tasku-rile
	char ch;										// variabila pentru parcurgerea prin meniu

							// Inceput executie program
	do
	{
		Menu();
		cin >> ch;									// alegerea categoriei din meniu
		switch (toupper(ch))						// setarea caracterului in majuscula
		{
		case '1':									// case pentru a seta task-uri
			try
			{
				task.SetTask();							// metoda SetTask()
				task.serialize();
			}
			catch (const std::exception& ex)
			{
				cout << ex.what() << endl;
			}
			break;
		case '2':									// case pentru a afisa task-urile
			system("cls");							// stergerea consolei inainte de afisarea datelor
			task.deserialize();
			task.GetTasks();
			break;
		case '3':									// case pentru a sterge un anumit task
			try										// bloc try-cath pentru a prelua o eroare in timpul executiei in caz ca stergem un task care nu exista
			{
				system("cls");
				task.DeleteTask();					// metoda DeleteTask()
			}
			catch (const std::exception& ex)		// preluarea erorii
			{
				cout << ex.what();					// afisarea unui mesaj informativ
			}
			break;
		case '4':									// case pentru a sterge toate task-urile
			try										// bloc try-cath pentru a prelua o eroare in timpul executiei in caz ca stergem task-uri care nu exista
			{
				task.DeleteAllTask();				// metoda DeleteAllTask()
			}
			catch (const std::exception& ex)		// preluarea erorii
			{
				cout << ex.what();					// afisarea unui mesaj informativ
			}
			break;
		case 'Q': system("cls"); cout << "\nBye\n"; break;// iesire din program
		default: cout << "Optiune invalida!";
			while (cin.get() != '\n')
				continue;
			break;
		}
	} while (toupper(ch) != 'Q');					// cat timp nu este apasat 'Q' sa se execute programul

	return 0;
}