
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<vector>
#include<string>
#include "stack.h" //written by Zsuzsanna Dianovics

using namespace std;

//---------------------------------------
// CS421 File ll1.cpp for HW3A LL1 Table-Driven Parser
// Your name: Zsuzsanna Dianovics
// Date: March 26, 2020
//---------------------------------------

// Complete this to fit the HW3A specification - look for **
// Must have the same types of tracing couts as my demo program.

// Feel free to use a stack class or use a vector
// to implement your stack.  The stack will contain characters.

vector<char> M[3][2];  // the table of rules 
					   // 3 rows for S, A, B
					   // 2 rows for 0, 1
	   // Each slot contains a rule's right side
	   // which is a vector of characters

//  ------- conversion functions ------------------------

//global stack 
stack st;


// PURPOSE: to convert non-terms S, A, B to table rows 0, 1, 2
// PARAMETER: C character to convert to int
// RETURN: int that is the version of C
int toRow(char C)
{
	//if the character is a C, convert to zero
	if (C == 'S') { return 0; }
	//if the character is a A, convert to 1
	else if (C == 'A') { return 1; }
	//if neither, return -1 for error
	return -1;
}

// PURPOSE: to convert '0' and '1' to table columns 0 and 1 
// PARAMETER: c character to convert to int
// RETURN: int that is the version of c
int toCol(char c)
{
	// if the character is a 0, convert to zero
	if (c == '0') { return 0; }
	//if the character is a 1, convert to 1
	else if (c == '1') { return 1; }
	//if neither, return -1 for error
	return 1;
}

// PURPOSE: to convert row 0, 1, 2 to non-terms S, A and B
// PARAMETER: r int to convert to char
// RETURN: char that is the version of r
char toNonterm(int r)
{
	// if the int is a 0, convert to 'S'
	if (r == 0) { return 'S'; }
	// if the int is a 1, convert to 'A'
	else if (r == 1) { return 'A'; }
	// if the int is a 2, convert to 'B'
	else if (r == 2) { return 'B'; }
	//else return error
	else { return 'E'; }

}


// DONE: complete the following functions.-----------------------------

// PURPOSE: to display a rule's rhs which is in vector V
// PARAMETER: V vector that has rhs data
// RETURN: none
void displayVector(vector<char> V)
{
	//if the V is empty, return a space
	if (V.empty()) { cout << " "; }
	//display V horizontally e.g. 0 A 0
	else {
		//run through the vector in a loop
		//print as go
		for (int i = 0; i < V.size(); i++)
		{
			cout << V[i] << " ";
		}
		//move over a column
		cout << "\t";
	}
}

// PURPOSE: remove whitespace from string
// PARAMETER: s string to strip
// RETURN: string that is clear of whitespace
string stripper(string s)
{
	//string to return
	string s2;
	//run through the string in a loop
	for (int i = 0; i < s.length(); i++)
	{
		//if it is a space, so nothing
		if (s[i] == ' ')
		{
		}
		//otherwise, add the char to the string
		else
		{
			s2 += s[i];
		}
	}
	//return the string
	return s2;
}

// PURPOSE: to read in the rules into M
// PARAMETER: none
// RETURN: none
// uses: stripper(), toNonterm(), displayVector()
/*
Algorithm:
	open file
	get first line, delimited with ';'
	start loop to read while there are lines to read
		strip the line read
		get first two chars, one is row, other col
		create new vector, cell'
		add to cell the ch read
		read next character
		in a loop read the next ch until end of line
			add ch to cell
			advance to next ch
		add the cell to M
		clear fin
		reset count
		read next line
	close file
	display the table read

*/
void readrules()
{
	string rules = "C:\\Users\\dever\\Desktop\\Spring2020\\TheoryComp\\cs421files\\CS421Progs\\HW3A_LL1\\rules";
	ifstream fin(rules, ios::in);
	//ifstream fin ("rules", ios::in);

	int count = 0;			//traverse the string input
	char ch;				//the char read
	int row, col;			//values for row and column

	//read first line, delimit with ;
	getline(fin, rules, ';');

	// read string till end of file
	while (!(fin.eof()))
	{
		//remove whitespace from line read 
		rules = stripper(rules);

		// first character in the string at [0]
		row = toRow(rules[count++]);

		//second character at [1]
		ch = rules[count++];

		//assign ch to column, as well
		col = toCol(ch);

		//create new vector to be added to M[row][col]
		vector<char> cell;

		//add to cell vector
		cell.push_back(ch);

		//get next char [2]
		ch = rules[count++];

		//run to end of string
		while (ch != '\0')
		{
			//add each char to the cell
			cell.push_back(ch);
			//get next char
			ch = rules[count++];
		}
		//add cell to M table
		M[row][col] = cell;

		//reset count for string
		count = 0;

		//clear bits
		fin.clear();
		fin.ignore();

		//get next string
		getline(fin, rules, ';');
	}
	//close file
	fin.close();

	//   Display the table nicely  
	//    use toNonterm to show row labels (S, A, B)
	//    use displayVector for each content 
	for (int i = 0; i < 3; i++)
	{
		//label for row
		cout << toNonterm(i) << ":\t";
		//print each row's vectors
		for (int j = 0; j < 2; j++)
		{
			displayVector(M[i][j]);
			cout << " ";
		}
		cout << endl;
	}

}

// PURPOSE: pushes V contents to the stack 
// PARAMETER: V vector
// RETURN: none
void addtostack(vector<char> V)
{
	cout << "adding rhs of a rule to the stack " << endl;

	//get size of V
	int size = V.size();

	//count at 1 
	int count = 1;

	// add V to the stack in reverse
	while (!V.empty())
	{
		char ch = V[size - count++];
		st.push(ch);
		V.pop_back();
	}
	//display the stack
	st.displayAll();
}

// PURPOSE: to read client entred string and check 
//     if each character is appropriate
/*
Algorithm:

*/

int main()
{
	// M is filled and displayed 
	readrules();

	//User entered input
	string ss;			//hold the read input
	int index = 0;  	// index for ss
	char top, popped;	//hold char from ss and stack

	cout << "Enter a string made of 0's and/or 1's: ";
	cin >> ss;

	// push '$' and 'S' onto the stack to start
	st.push('$');
	st.push('S');

	// DONE display the stack vertically from top to bottom
	st.displayAll();

	//get first char in string
	char current = ss[index];

	//peek at the top of the stack
	st.topElem(top);

	// for each char of ss
	while (current != '\0')
	{
		cout << "current char is: " << current << endl;

		//check if we are at the bottom of the stack and need to accept
		if (top == '$' && current == '$')
		{
			break;
		}

		//if the top of the stack is a Nonterminal
		else if (top == 'S' || top == 'A' || top == 'B')
		{
			//if the current char is greater than 1
			//then it is out of the scope of the language
			if ((current - 48) > 1)
			{
				break;
			}

			//otherwise, pop the stack
			st.pop(popped);

			//find which cell to add to stack
			for (int i = 0; i < 3; i++)
			{
				//find the row
				if (top == toNonterm(i)) {
					addtostack(M[i][current - 48]);
				}
			}
		}
		//if the top matches the current char
		else if (top == current)
		{
			cout << "matched!\n";
			st.pop(popped);
			st.displayAll();
			index++;
		}
		//if the only thing in the stack is $, but still have char to read
		else if (!st.isEmpty() && (top == '$'))
		{
			break;
		}
		//generally, nothing left to check
		else
		{
			break;
		}

		//get the next top
		st.topElem(top);
		//get next char
		current = ss[index];

	} //end while ss string


	//Results:

	//if we reach $ at same time for both, accept
	if (top == '$' && current == '$')
	{
		cout << ">>Accept!\n";
	}
	//if there is still char in the stack, other than $
	else if (top == '$' && current != '$')
	{
		cout << ">>Error - stack is empty. Reject!\n";
	}
	//if the current doesn't match the top
	else if (current != top)
	{
		cout << ">>Mismatch error. Reject!\n";
	}
	//if we can't find a rule
	else if ((current - 48) > 1)
	{
		cout << ">>Error - no rule. Reject!\n";
	}


}// end of main
