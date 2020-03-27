
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<vector>
#include<string>
#include "stack.h"

using namespace std;

//---------------------------------------
// CS421 File ll1.cpp for HW3A LL1 Table-Driven Parser
// Your name: **
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
stack st;


// to convert non-terms S, A, B to table rows 0, 1, 2
int toRow(char C)
{
	//**  bunch of if then else
	if (C == 'S') return 0;
	else if (C == 'A') return 1;
	return -1;
}

// to convert '0' and '1' to table columns 0 and 1 
int toCol(char c)
{
	// ** bunch of if then else
	if (c == '0') return 0;
	else if (c == '1') return 1;
	return 1;
}

// to convert row 0, 1, 2 to non-terms S, A and B
char toNonterm(int r)
{
	// ** bunch of if then else
	if (r == 0) { return 'S'; }
	else if (r == 1) { return 'A'; }
	else if (r == 2) { return 'B'; }
	else { return 'E'; }

}


// ** Then complete the following functions.-----------------------------

// to display a rule's rhs which is in vector V
void displayVector(vector<char> V)
{
	if (V.empty()) { cout << " ";  }
	// ** display V horizontally e.g. 0 A 0
	else {

		for (int i = 0; i < V.size(); i++)
		{
			cout << V[i] << " ";
		}
		cout << "\t" ;
	}
}

string stripper(string s)
{
	string s2;
	for (int i=0; i < s.length(); i++)
	{
		if (s[i] == ' ')
		{}
		else
		{
			s2 += s[i];
		}
		
	}
	return s2;
}

// to read in the rules into M, make sure ; is not stored
void readrules()
{
	string rules = "C:\\Users\\dever\\Desktop\\Spring2020\\TheoryComp\\cs421files\\CS421Progs\\HW3A_LL1\\rules";
	ifstream fin(rules, ios::in);
	int count = 0;
	char ch;
	int row, col;

	//read first line
	getline(fin, rules, ';');

	// read string till end of file
	while (!(fin.eof()))
	{
		//cout << "read line: " << rules << endl << endl;
		rules = stripper(rules);
		// first character in the string at [0]
		row = toRow(rules[count++]);

		//second character at [1]
		ch = rules[count++];

		//also, asign no column
		col = toCol(ch);

		//create new vector to be added to M[row][col]
		vector<char> cell ;

		//first char in cell is [1]
		//cout << "pushing to cell: " << ch << endl;
		cell.push_back(ch);

		//get next char [2]
		ch = rules[count++];

		//run to end of string
		while (ch != '\0')
		{
			cell.push_back(ch);
			ch = rules[count++];
		}
		//add cell to M table
		M[row][col] = cell;

		//increment count for string
		count = 0;

		//clear bits
		fin.clear();
		fin.ignore();

		//get next string
		getline(fin, rules, ';');
	}


	//   Display the table nicely  
	//    use toNonterm to show row labels (S, A, B)
	//    use displayVector for each content 
	for (int i = 0; i < 3; i++)
	{
		cout << toNonterm(i) << ":\t";
		for (int j = 0; j < 2; j++)
		{
			displayVector(M[i][j]);
			cout << " ";
		}
		cout << endl;
	}

}

//  pushes V contents to the stack 
void addtostack(vector<char> V)
{
	cout << "adding rhs of a rule to the stack. " << endl;
	int size = V.size();
	int count = 1;
	// **  be careful of the order
	while (!V.empty())
	{
		char ch = V[size - count++];
		st.push(ch);		
		V.pop_back();
	}
	//cout << "Stack:\n";
	st.displayAll();
}

int main()
{
	readrules();  // M is filled and displayed 
	
	string ss;

	cout << "Enter a string made of 0's and/or 1's: ";
	cin >> ss;

	// DONE push 'S' onto the stack to start

	st.push('$');
	st.push('S');

	//cout << "Stack:\n";
	// DONE display the stack vertically from top to bottom
	st.displayAll();
	
	int index = 0;  // index for ss
	char top, popped;
	char current = ss[index];
	//cout << "current char is: " << current << endl;
	
	
	st.topElem(top);
	//cout << " Top of stack is: " << top << endl;

	while (current != '\0')  // for each char of ss
	{
		cout << "current char is: " << current << endl;
		//cout << "Top is: " << top << " Current char: " << current << endl;

		if (top == '$' && current == '$')
		{
			//cout << "Accept! ($ == current char)\n";
			break;
		}
		else if (top == 'S' || top == 'A' || top == 'B')
		{
			if ((current - 48) > 1)
			{
				break;
			}
			//cout << "Nonterminal\n";
			st.pop(popped);
			//find which cell to add to stack
			//find the row
			for (int i = 0; i < 3; i++)
			{
				if (top == toNonterm(i)) {
					addtostack(M[i][current-48]);
				}
			}
		}
		else if (top == current)
		{
			cout << "matched!\n";
			st.pop(popped);
			st.displayAll();
			index++;
		}
		else if (!st.isEmpty() && (top == '$'))
		{
			break;
		}
		else
		{
			
			break;
		}
		st.topElem(top);
		current = ss[index];

	} //end while ss string

	if(top == '$' && current == '$')
	{ cout << ">>Accept!\n";}
	else if (top == '$' && current != '$')
	{
		cout << ">>Error - stack is empty. Reject!\n";
	}
	else if (current != top)
	{
		cout << ">>Mismatch error. Reject!\n";
	}
	else if ((current - 48) > 1)
	{
		cout << ">>Error - no rule. Reject!\n";
	}

		// Based on ss[i] and 
		//    the top of stack, update the stack: 
		// ** note that empty stack will cause immediate failure  
		// ** note that top of stack terminal and ss[i] mismatching
		//    will cause immediate failure 
		// ** note that no entry in M for the top of stack (non-terminal)
		//    and ss[i] will cause immediate
		//    failure  (use toRow and toCol to look up M)
		// ** otherwise, addtoStack the M entry based on ss[i] and the top of stack 



  // ** Here, check for success for failure based on stack empty or not

}// end of main
