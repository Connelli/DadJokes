#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>
#include "Uzduotis.h"

using namespace std;

struct DadJoke
{
	string Joke;
	string Punchline;

	DadJoke()
	{

	}

	DadJoke(string joke, string punchline)
	{
		Joke = joke;
		Punchline = punchline;
	}
};

void Read(string fileName, DadJoke mas[], int& n, string str[])
{
	string Joke, Punchline;
	
	ifstream fin(fileName);
	fin >> n >> ws;
	int found = 0;
	int k = -1;
	int a = n;
	int deleted = 0;

	
	for (int i = 0; i < a; i++)
	{
		getline(fin, Joke);
		fin >> ws;
		getline(fin, Punchline);
		fin >> ws;
		

		for (int j = 0; j < 4; j++)
		{
			if (Joke.find(str[j]) != string::npos || Punchline.find(str[j]) != string::npos)
			{
				found++;
				deleted++;
			}
		}
		if (found > 0)
		{
			n--;
			found = 0;
		}

		else
		{
			k++;
			mas[k] = DadJoke(Joke, Punchline);
		}
		
	}
	if (deleted > 0)
	{
		cout << "Jokes with inappropriate words ("<<deleted<<") were deleted!" << endl;
	}
	fin.close();
}
void Filter(string filename, string mas[])
{
	ifstream fin(filename);
	int a = 0;
	while (!fin.eof())
	{
		
		fin >> mas[a];
		a++;
	}
}
void PrintAll(DadJoke mas[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << i + 1 << ". "<< setw(11) << right << "Joke: " << mas[i].Joke << endl;
		cout << i + 1 << ". Punchline: " << mas[i].Punchline << endl << endl;
	}
}

void RandomFull(DadJoke mas[], int n)
{
	
	int num = (rand() % n);
	cout << num+1 << ". " << setw(9) << left << "Joke" << ": " << mas[num].Joke << endl;
	cout << num+1 << ". Punchline: " << mas[num].Punchline << endl << endl;

}

void Chosen(DadJoke mas[], int n)
{
	int num;
	cout << "Choose the number of joke" << "[1-" << n << "]: ";
	cin >> num;
	cout << num << ". " << setw(9) << left << "Joke" << ": " << mas[num-1].Joke << endl;
	cout << num << ". Punchline: " << mas[num-1].Punchline << endl << endl;
}

void Amount(int n)
{
	cout << "Amount of jokes: " << n << endl;
}

void Mix(DadJoke mas[], int n)
{
	int randjoke = (rand() % n);
	int randpunchline = (rand() % n);
	cout << randjoke + 1 << ". " << setw(9) << left << "Joke" << ": " << mas[randjoke].Joke << endl;
	cout << randpunchline + 1 << ". Punchline: " << mas[randpunchline].Punchline << endl << endl;
}

void AddNewJoke(DadJoke mas[], int &n, string str[])
{
	string Joke, Punchline;
	cout << "Enter joke: ";
	int found = 0;
	cin.ignore();
	getline(cin, Joke);
	cout << endl << "Enter punchline: ";
	getline(cin, Punchline);
	for (int i = 0; i < 6; i++)
	{
		if (Joke.find(str[i]) != string::npos || Punchline.find(str[i]) != string::npos)
		{
			found++;
		}
	}

	if (found == 0)
	{
		mas[n] = DadJoke(Joke, Punchline);
		n++;
	}
	else
	{
		cout << "The joke does not meet the requirements (inappropriate words)" << endl;;
	}
}

int main()
{
	DadJoke jokes[15];
	string filter[10];
	int n = 0;
	srand(time(NULL));
	Filter("filter.txt", filter);
	Read("jokes.txt", jokes, n, filter);

	
	int choice;
	
	do
	{
		cout << endl << "1. Print all jokes." << endl << "2. Print random joke." << endl << "3. Print mixed joke." << endl << "4. Print chosen joke." << endl << "5. Add a new joke." << endl << "6. Amount of jokes." << endl << "7. Exit." << endl << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		cout << endl << endl;
		switch (choice)
	{
	case 1:
		PrintAll(jokes, n);
		break;
	case 2:
		RandomFull(jokes, n);
		break;
	case 3:
		Mix(jokes, n);
		break;
	case 4:
		Chosen(jokes, n);
		break;
	case 5: 
		AddNewJoke(jokes, n, filter);
		break;
	case 6:
		Amount(n);
		break;
	case 7:
		cout << "Goodbye";
		break;
	default:
		cout << "Wrong choice" << endl;
	}
} 
	while (choice != 7);
}
