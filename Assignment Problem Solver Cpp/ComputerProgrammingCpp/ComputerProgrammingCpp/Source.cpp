#include<iostream>
#include<stdlib.h>
#include<time.h>

#define SIZE 100

using namespace std;

//Functions
void generateMatrix(int[][SIZE], int, int, int);
void printArray(int[][SIZE], int);
void copyArray(int[][SIZE], int, int[][SIZE]);
void rowMin(int[][SIZE], int, int[]);
void colMin(int[][SIZE], int, int[]);
void rowSubtract(int[][SIZE], int, int[]);
void colSubtract(int[][SIZE], int, int[]);
void resetRowTicks(int[], int);
void resetColTicks(int[], int);
void step0(int[][SIZE], int);
void step2(int[][SIZE], int, int[], int[]);
int step3(int[][SIZE], int, int[], int[]);
int step4(int[][SIZE], int, int[], int[]);
int step5(int[][SIZE], int, int[], int[], int[][SIZE]);
void drawRows(int[][SIZE], int, int);
void drawCols(int[][SIZE], int, int);
int findMin(int[][SIZE], int, int);
void additionalZeros(int[][SIZE], int, int[][SIZE], int);
int optimalResult(int[][SIZE], int, int[SIZE], int[][SIZE]);


void main() {

	int A[SIZE][SIZE];
	int originalA[SIZE][SIZE], copyA[SIZE][SIZE], rowMins[SIZE], colMins[SIZE], tickRows[SIZE], tickCols[SIZE], drawA[SIZE][SIZE], optimalResultNumbers[SIZE];
	int i, j, n = 10, sumOfTickRowsValues, sumOfTickColsValues, temp1, temp2, howManyLines, lower = 0, upper = 100, min, totalSum;

	srand(time(NULL));

	cout << "\t\t\t\t ---Welctome to 'Assignment Problem Solver'!---" << endl;
	cout << "Warning: In this program, the number '-1' represents the assigned zeros, the number '-2' represents eliminated zeros, the number '-5' represents the horizontal and vertical lines used to cross the lines, and the number '-6' represents the intersection points of these used horizontal and vertical lines." << endl << endl;

	cout << endl << endl << "Enter the matrix size you want to create: ";
	cin >> n;

	generateMatrix(A, n, upper, lower);
	//Array Copy
	copyArray(A, n, originalA);
	//

	//Print Original A Matrix
	cout << "-----[Original A Matrix]-----" << endl;
	printArray(originalA, n);
	cout << endl;
	//---

	//Row Reduction
	rowMin(A, n, rowMins);
	cout << endl << endl;
	rowSubtract(A, n, rowMins);
	cout << "-----[Row Reduction Matrix]-----" << endl;
	printArray(A, n);
	//
	//Column Reduction
	cout << endl;
	colMin(A, n, colMins);
	cout << endl << endl;
	colSubtract(A, n, colMins);
	cout << "-----[Column Reduction Matrix]-----" << endl;
	printArray(A, n);
	copyArray(A, n, copyA);
	

	temp1 = 0;
	temp2 = 0;	

	while (true) {
		//Reset Tick Rows and Cols
		resetRowTicks(tickRows, n);
		resetColTicks(tickCols, n);

		cout << endl << endl << "-----[Step-0 Matrix]-----" << endl;
		step0(copyA, n);
		printArray(copyA, n);
		step2(copyA, n, tickRows, tickCols);

		while (true) {
			sumOfTickRowsValues = 0;
			sumOfTickColsValues = 0;
			sumOfTickRowsValues = step3(copyA, n, tickRows, tickCols);
			sumOfTickColsValues = step4(copyA, n, tickRows, tickCols);

			if (sumOfTickRowsValues == temp1 && sumOfTickColsValues == temp2)
				break;

			temp1 = sumOfTickRowsValues;
			temp2 = sumOfTickColsValues;
		}

		howManyLines = step5(A, n, tickRows, tickCols, drawA);//drawA oluþturuldu ve line ler çizildi//How Many Lines Hesaplandý
		cout << endl << endl << "-----[Draw Lines Matrix]-----" << endl;
		printArray(drawA, n);
		cout << endl << endl << "There are " << howManyLines << " lines required to cover all zeros!" << endl;
		min = findMin(drawA, n, upper);
		if (howManyLines == n) {
			cout << "We can go to the 'Optimal Assignment'!" << endl;
			break;
		}
		else {
			cout << "The number of lines (" << howManyLines << ") is smaller than " << n << "! The smallest uncovered number is " << min << endl << endl;
			cout << endl << "-----[Additional Zeros Matrix]-----" << endl;
			additionalZeros(A, n, drawA, min);
			printArray(A, n);
			copyArray(A, n, copyA);
		}

	}

	cout << endl << endl << "---[Original Matrix]---" << endl;
	printArray(originalA, n);
	cout << endl << endl << "---[The Optimal Assignment]---" << endl;
	printArray(copyA, n);
	cout << endl;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (copyA[i][j] == -1) {
				cout << "Worker [" << i + 1 << "] ---> Job [" << j + 1 << "]" << endl;
			}
		}
	}

	totalSum = optimalResult(copyA, n, optimalResultNumbers, originalA);
	cout << endl << "The optimal value equals " << totalSum << "." << endl;
	for (i = 0; i < n; i++) {
		cout << " [" << optimalResultNumbers[i] << "]" << " ";
		if (i == n - 1)
			break;
		cout << "+";
	}
	cout << "= [" << totalSum << "]";
	
	cout << endl << endl << endl;
	system("pause");
}

void generateMatrix(int A[][SIZE], int n, int upper, int lower) {
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			A[i][j] = (rand() % upper - lower + 1) + lower;
		}
	}
}

void printArray(int A[][SIZE], int n) {
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			cout << A[i][j] << "\t";
		}
		cout << endl;
	}

}

void copyArray(int A[][SIZE], int n, int copyA[][SIZE]) {
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			copyA[i][j] = A[i][j];
		}
	}
}

void rowMin(int A[][SIZE], int n, int rowMins[SIZE]) {
	int i, j, min;
	for (i = 0; i < n; i++) {
		min = A[i][0];
		for (j = 0; j < n; j++) {
			if (A[i][j] < min)
				min = A[i][j];
		}
		rowMins[i] = min;
	}
	cout << endl << "Row mins: " << endl;
	for (i = 0; i < n; i++) {
		cout << rowMins[i] << "\t";
	}
	cout << endl;
}

void colMin(int A[][SIZE], int n, int colMins[SIZE]) {
	int i, j, min;
	for (i = 0; i < n; i++) {
		min = A[0][i];
		for (j = 0; j < n; j++) {
			if (A[j][i] < min)
				min = A[j][i];
		}
		colMins[i] = min;
	}
	cout << endl << "Col mins: " << endl;
	for (i = 0; i < n; i++) {
		cout << colMins[i] << "\t";
	}
	cout << endl;
}

void rowSubtract(int A[][SIZE], int n, int rowMins[]) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			A[i][j] -= rowMins[i];
		}
	}

}

void colSubtract(int A[][SIZE], int n, int colMins[]) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			A[j][i] -= colMins[i];
		}
	}

}

void resetRowTicks(int tickRows[], int n) {
	int i;
	
	for (i = 0; i < n; i++) {
		tickRows[i] = 0;	
	}
}

void resetColTicks(int tickCols[], int n) {
	int i;

	for (i = 0; i < n; i++) {
		tickCols[i] = 0;
	}
}

void step0(int copyA[][SIZE], int n) {
	int i, j, k, counter, tempJ, newCounter = 0, flag = -1;
	int *p;

	p = &copyA[0][0];

	while (true) {
		newCounter = 0;
		for (i = 0; i < n; i++) {
			counter = 0;
			for (j = 0; j < n; j++) {
				if (copyA[i][j] == 0) {
					counter++;
					p = &copyA[i][j];
					tempJ = j;
				}
			}
			if (counter == 1) {
				for (k = 0; k < n; k++) {
					if (copyA[k][tempJ] == 0) {
						copyA[k][tempJ] = -2;
						newCounter++;
					}
				}
				*p = -1;
				newCounter++;
			}
		}

		for (i = 0; i < n; i++) {
			counter = 0;
			for (j = 0; j < n; j++) {
				if (copyA[j][i] == 0) {
					counter++;
					p = &copyA[j][i];
					tempJ = j;
				}
			}
			if (counter == 1) {
				for (k = 0; k < n; k++) {
					if (copyA[tempJ][k] == 0) {
						copyA[tempJ][k] = -2;
						newCounter++;
					}							
				}
				*p = -1;
				newCounter++;
			}

		}
		

		if (newCounter == 0)
			break;

	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (copyA[i][j] == 0) {
				flag = 1;
				p = &copyA[i][j];
				break;
			}
		}
	}
	
	if (flag == 1) {
		*p = -2;
		return step0(copyA, n);
	}

	

}

void step2(int copyA[][SIZE], int n, int tickRows[], int tickCols[]) {
	int i, j, counter, flag;
	for (i = 0; i < n; i++) {
		flag = -1;
		counter = 0;
		for (j = 0; j < n; j++) {
			if (copyA[i][j] == -1) {
				flag = 1;
			}
			else if (copyA[i][j] == 0|| copyA[i][j] == -2) {
				counter++;
			}
		}
		if (flag != 1 && counter > 0) {
			tickRows[i] = 1;
		}
	}
}

int step3(int copyA[][SIZE], int n, int tickRows[], int tickCols[]) {
	int i, j, sumOfTickRowsValues = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (tickRows[i] == 1) {
				if (copyA[i][j] == -1 || copyA[i][j] == -2 || copyA[i][j] == 0) {
					tickCols[j] = 1;
				}
			}
		}
	}

	for (i = 0; i < n; i++) {
		sumOfTickRowsValues += tickRows[i];
	}

	return sumOfTickRowsValues;
}

int step4(int copyA[][SIZE], int n, int tickRows[], int tickCols[]) {
	int i, j, sumOfTickColsValues = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (tickCols[j] == 1 && copyA[i][j] == -1) {
				tickRows[i] = 1;
			}
		}
	}

	for (i = 0; i < n; i++) {
		sumOfTickColsValues += tickCols[i];
	}

	return sumOfTickColsValues;
}

int step5(int A[][SIZE], int n , int tickRows[], int tickCols[], int drawA[][SIZE]) {
	int i, j, howManyLines = 0;
	copyArray(A, n, drawA);

	//Draw Rows
	for (i = 0; i < n; i++) {
		if (tickRows[i] == 0) {
			drawRows(drawA, n, i);
			howManyLines++;
		}
	}
	//Draw Cols
	for (i = 0; i < n; i++) {
		if (tickCols[i] == 1) {
			drawCols(drawA, n, i);
			howManyLines++;
		}
	}
	
	return howManyLines;
}

void drawRows(int drawA[][SIZE], int n, int x) {
	int i, j;

	for (i = 0; i < n; i++) {
		drawA[x][i] = -5;
	}
}

void drawCols(int drawA[][SIZE], int n, int x) {
	int i, j;

	for (i = 0; i < n; i++) {
		if (drawA[i][x] == -5) {
			drawA[i][x] = -6;
			continue;
		}
		drawA[i][x] = -5;
	}
}

int findMin(int drawA[][SIZE], int n, int upper) {
	int i, j, min = upper;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (drawA[i][j] != -5 && drawA[i][j] != -6) {
				if (min > drawA[i][j]) {
					min = drawA[i][j];
				}
			}
		}
	}

	return min;
}

void additionalZeros(int A[][SIZE], int n, int drawA[][SIZE], int min) {
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (drawA[i][j] == -6) {
				A[i][j] += min;
			}
			else if (drawA[i][j] == -5)
				continue;
			else {
				A[i][j] -= min;
			}
		}
	}

}

int optimalResult(int copyA[][SIZE], int n, int optimalResultNumbers[SIZE], int originalA[][SIZE]) {
	int i, j, sum = 0;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (copyA[i][j] == -1) {
				optimalResultNumbers[i] = originalA[i][j];
				sum += originalA[i][j];
			}
		}
	}

	return sum;
}