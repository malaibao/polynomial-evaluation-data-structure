//Maribelle Leong
//300275185
//COSC 222 Lab3
//A C++ Program to calculate the coefficient and exponent of polynomials
//using linked list.

//Result file: result.txt
//textFile 1: num1.txt
//textFile 2: num2.txt

#include <iostream>
#include <fstream>
using namespace std;

//polyTerm class
struct polyTerm
{
	int root;
	int exp;
	polyTerm *next;
};

//public class for heads and tails
struct polyTerm *poly1 = NULL;
struct polyTerm *poly2 = NULL;
struct polyTerm *tail1 = NULL;
struct polyTerm *tail2 = NULL;

//fuction to add item into list
void addItem(int i, int j, int count)
{
	polyTerm *temp = new polyTerm;
	temp->root = i;
	temp->exp = j;
	temp->next = NULL;

	if(count == 1){				//a control to decide which list to add item into
		if(poly1 == NULL){	//poly1 or poly2
			poly1 = temp;
			tail1 = temp;
		}else if(poly1 == tail1){
			poly1->next = temp;
			tail1 = temp;
		}else{
			tail1->next = temp;
			tail1 = temp;
		}
	}else{
		if(poly2 == NULL){
			poly2 = temp;
			tail2 = temp;
		}else if(poly2 == tail2){
			poly2->next = temp;
			tail2 = temp;
		}else{
			tail2->next = temp;
			tail2 = temp;
		}
	}
}

//function to print the list
void print(polyTerm *start){
	polyTerm *current = start;

	while(current->next != NULL){
		cout << "polyRoot: " << current->root << " polyExp: " << current->exp
		<< endl; 				//checkingStatement
		current = current->next;
	}
	cout << "polyRoot: " << current->root << " polyExp: " << current->exp
	<< endl;					//checkingStatement
}

//Function to save result into a text file
void output(polyTerm *newList){
	ofstream outFile;
	outFile.open("result.txt");

	while(newList != NULL){
			int root = newList->root;
			int exp = newList->exp;
		if(root != 0)								//handle the zero root
			outFile << root << endl;
		if(root != 0 && exp != 0)		//handle the zero exp
			outFile << exp << endl;

		newList = newList->next;
	}
	outFile.close();
}

//Function to first add all the big exp from either of the poly equation
//make the 2 lists to be on the same pace
void calculate(){
	void calculateTotal(polyTerm * a, polyTerm *b);
	polyTerm *newList = NULL;
	polyTerm *current = NULL;

	if(poly1->exp > poly2->exp){
		polyTerm *add = new polyTerm;
		add->root = poly1->root;
		add->exp = poly1->exp;
		add->next = NULL;

		newList = add;
		poly1 = poly1->next;
		current = newList;
		while(poly1 != NULL && poly2 != NULL && poly1->exp != poly2->exp){
			current->next = poly1;
			poly1 = poly1->next;
			current = current->next;
		}
		current->next = NULL;
	}else if(poly2->exp > poly1->exp){
		polyTerm *add = new polyTerm;
		add->root = poly2->root;
		add->exp = poly2->exp;

		poly2 = poly2->next;
		newList = add;
		current = newList;

		while(poly1 != NULL && poly2 != NULL && poly1->exp != poly2->exp){
			current->next = poly2;
			poly2 = poly2->next;
			current = current->next;
		}
	}

	calculateTotal(newList, current);
}

void calculateTotal(polyTerm *newList, polyTerm *tail)
{
	//when both lists still have elements
	while(poly1 != NULL && poly2 != NULL){

		polyTerm *add = new polyTerm;

		if(poly1->exp > poly2->exp){
			add->root = poly1->root;
			add->exp = poly1->exp;

			if(newList != NULL){	//if the newList is empty
				tail->next = add;
				tail = add;
			}else{								//if the newList has elements
				newList = add;
				tail = add;
			}

			poly1 = poly1->next;

		}else if(poly2->exp > poly1->exp){
			add->root = poly2->root;
			add->exp = poly2->exp;

			if(newList != NULL){	//if the newList is empty
				tail->next = add;
				tail = add;
			}else{								//if the newList has elements
				newList = add;
				tail = add;
			}

			poly2 = poly2->next;

		}else if(poly1->exp == poly2->exp){
			add->root = poly1->root + poly2->root;
			add->exp = poly1->exp;
			add->next = NULL;

			if(tail != NULL){
				tail->next = add;
				tail = add;
			}else{
				newList = add;
				tail = add;
			}
			poly1 = poly1->next;
			poly2 = poly2->next;
		}
	}

	//connect the tail to the rest of the elements
	//in poly1 or poly2
	if(poly1 == NULL)
		tail->next = poly2;
	else
		tail->next = poly1;

	cout << endl << "--------FINAL RESULT-----------" <<endl;
	print(newList);
	output(newList);
}

int main()
{
	int count = 1;
	ifstream inFile;
	inFile.open("num1.txt");

	int i = 0;
	while(inFile >> i)
	{
		int j= 0;
		inFile >> j;
		addItem(i, j, count);
	}

	inFile.close();
	print(poly1);						//print poly1

	count++;
	cout << endl;

	ifstream inFile2;
	inFile2.open("num2.txt");
	int ii;
	while(inFile2 >> ii)
	{
		int jj = 0;
		inFile2 >> jj;
		addItem(ii, jj, count);
	}
	inFile2.close();
	print(poly2);					//print poly2

	calculate();

	return 0;
};
