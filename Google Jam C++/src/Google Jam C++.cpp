//============================================================================
// Name        : Google.cpp
// Author      : Thomas Horn
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

int count(const vector<int>& v, int n)
{
	int m = 0;
	for (int i = 0; i < v.size(); ++i)
	{
		if (v[i] == n) m++;
	}

	return m;
}

string print(vector<vector<vector<int> > >& people)
{
	cout << "PRINT: " << endl;
	for (int i = 0; i < people.size(); ++i)
	{
		for (int j = 0; j < people[i].size(); ++j)
		{
			if (people[i][j].size() != 2)
			{
				cout << "size: " << people[i][j].size() << " ";
				continue;
			}

			cout << people[i][j][0] << " " << people[i][j][1] << " ";

		}

		cout << endl;
	}
}

vector<vector<vector<int> > > clean(vector<vector<vector<int> > >& people, vector<int>& solution)
{
	vector<vector<vector<int> > > newPeople;
	// delete each satisfied person and delete irrelevant flavours
	for (int j = 0; j < people.size(); ++j)
	{
		bool satisfied = false;
		vector<vector<int> > flavours;
		for (int k = 0; k < people[j].size(); ++k)
		{
			int flavour = people[j][k][0] - 1;
			int malted = people[j][k][1];
			if (solution[flavour] == -1)
			{
				// flavour is still relevant
				flavours.push_back(people[j][k]);
				continue;
			}

			if (solution[flavour] == malted)
			{
				//is satisfied
				satisfied = true;
				break;
			}

			// flavour is irrelevant and can be deleted (don't add to flavours)
		}

		if (!satisfied)
		{
			newPeople.push_back(flavours);
		}
	}

	return newPeople;
}

vector<int> solveOne(vector<vector<vector<int> > >& people, vector<int>& solution)
{
	for (int i = 0; i < people.size(); ++i)
	{
		int likes = people[i].size();
		// one flavour must be in solution
		if (likes == 1)
		{
			int flavour = people[i][0][0];
			int malted = people[i][0][1];
			// flavors goes from 1 to N
			if (solution[flavour - 1] == -1)
			{
				solution[flavour - 1] = malted;
			}
			else if (solution[flavour - 1] != malted)
			{
				cout << "IMPOSSIBLE" << endl;
				return vector<int>();
			}
			else
			{
			}
		}
	}
	return solution;
}

void printPermuts(vector<vector<int> > permuts)
{
	for (int i = 0; i < permuts.size(); ++i)
	{
		for (int j = 0; j < permuts[i].size(); ++j)
		{
			cout << permuts[i][j];
		}

		cout << endl;
	}
}
bool myfunction (const vector<int>& x,const vector<int>& y)
{
	int n = count(x, 1);
	int m = count(y, 1);
	return (n <= m);
}
vector<vector<int> > getAllPermuts(int n)
{
	vector<vector<int> >  result;
	if (n == 1)
	{
		vector<int> zero;
		zero.push_back(0);
		vector<int> one;
		one.push_back(1);
		result.push_back(zero);
		result.push_back(one);
		return result;
	}
	else
	{
		vector<vector<int> >  permuts = getAllPermuts(n-1);
		for (int i = 0; i < permuts.size(); ++i)
		{
			vector<int> copy(permuts[i]);
			copy.push_back(0);
			permuts[i].push_back(1);
			result.push_back(copy);
			result.push_back(permuts[i]);
		}
	}
	// sort
	sort (result.begin(), result.end(), myfunction);
	return result;
}

bool test(vector<vector<vector<int> > >& people, vector<int>& solution)
{
	for (int i = 0; i < people.size(); ++i)
	{
		bool satisfied = false;
		for (int j = 0; j < people[i].size(); ++j)
		{
			int flavour = people[i][j][0];
			int malted = people[i][j][1];

			if (solution[flavour - 1] == malted)
			{
				satisfied = true;
				break;
			}
		}

		if (!satisfied)
		{
			return false;
		}
	}

	return true;
}

vector<int> solveAll(vector<vector<vector<int> > >& people, vector<int>& solution)
{
	vector<int> permutFlavours;

	for (int i = 0; i < solution.size(); ++i)
	{
		if (solution[i] != -1)
		{
			continue;
		}

		permutFlavours.push_back(i);
	}

	vector<vector<int> > allPermuts = getAllPermuts(permutFlavours.size());

	for (int i = 0; i < allPermuts.size(); ++i)
	{
		for (int j = 0; j < allPermuts[i].size(); ++j)
		{
			solution[permutFlavours[j]] = allPermuts[i][j];
		}

		if (test(people, solution))
		{

		}
	}
}

int countMinusOnes(vector<int>& v)
{
	return count(v, -1);
}



string solve(vector<vector<vector<int> > >& people, int numFlavours)
{
	vector<int> solution(numFlavours, -1);
	int minusOnes = countMinusOnes(solution);
	while(true)
	{
		solution = solveOne(people, solution);
		if (solution.size() == 0) return "IMPOSSIBLE";
		int newMinusOnes = countMinusOnes(solution);
		if (minusOnes == newMinusOnes) {
			cout << "Same -1" << endl;
			break;
		}
		minusOnes = newMinusOnes;
		people = clean(people, solution);
		if (people.size() == 0)
		{
			cout << "All people satisfied" << endl;
			for (int i = 0; i < solution.size(); ++i)
			{
				if (solution[i] == -1)
				{
					solution[i] = 0;
				}
			}

			break;
		}

	}
	if (people.size() > 0)
	{
		// try all possibilities
		solution = solveAll(people, solution);
	}
	//print(people);

	ostringstream result;
	for (int i = 0; i < numFlavours; ++i)
	{
		result << solution[i] << " ";
	}
	return result.str();
}



int main() {
	string filename = "/home/thomas/Downloads/B-small-practice.in";
	string filename2 = "/home/thomas/milkshakes";
	ifstream infile(filename.c_str());
	int tests;
	infile >> tests;
	cout << "Number Tests: " << tests << endl;

	int numFlavours, numPeople;
	while (infile >> numFlavours >> numPeople)
	{
		cout << "Flavours: " << numFlavours << ", people: " << numPeople << endl;
		vector<vector<vector<int> > > people;
		people.reserve(numPeople);
		for (int i = 0; i < numPeople; ++i)
		{
			int likes;
			infile >> likes;
			vector<vector<int> > flavours;
			flavours.reserve(numFlavours);
			int flavour, malted;
			for (int j = 0; j < likes; ++j)
			{
				infile >> flavour;
				infile >> malted;
				vector<int> one;
				one.push_back(flavour);
				one.push_back(malted);
				flavours.push_back(one);
			}

			people.push_back(flavours);
		}

		string solution = solve(people, numFlavours);
		cout << "Solution: " << solution << endl;
		//print(people);
	}


	cout << "End" << endl; // prints !!!Hello World!!!
	return 0;
}


