//Student 1    ID: 152120181120 Name: Ahmet Ata Þentürk
//Student 2    ID: 152120171109 Name: Olçan Satýr
//Date:23.10.2021
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#define SIZE 100
using namespace std;


int CountSizeOfBlobs(int NoR, int NoC, int row, int col, char blobs[][SIZE], float* sumOfRowCoord,float* sumOfColCoord);
void printMatrix(int row, int col, char blobs[][SIZE]);
float getAverage(float sum, float size);
void printResults(int blob, int NoOfPixels,float CoMRow,float CoMCol);

int main()
{
	fstream inputFile;
	char filename[30];
	cout << "Enter the filename: ";
	cin >> filename;

	inputFile.open(filename, ios::in);
	if (!inputFile)
	{
		cout << "File open failed" << endl;
		return 0;
	}
	
	char blobs[100][100],ch;
	int row, col, i, j;

	inputFile >> row;
	inputFile >> col;
	inputFile.get();
	i = 0, j = 0;
	while (!inputFile.eof())
	{
		inputFile.get(ch);
		blobs[i][j] = ch;
		j++;
		if (ch == '\n')
		{
			i++;
			j = 0;
		}
	}

	printMatrix(row, col, blobs);
	cout << endl << endl;

	int blobArray[30];
	int blobNumber = 0; 
	float sizeOfBlob;

	//Copying the two dimensional array
	char tempBlobArray[100][100];
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			tempBlobArray[i][j] = blobs[i][j];
		}
	}

	//Result table
	cout << "+------+------------+---------+------------+" << endl;
	cout << "| BLOB | NoOfPixels | CoM Row | CoM Column |" << endl;
	cout << "+------+------------+---------+------------+" << endl;


	float sumOfRowCoord = 0.0;
	float sumOfColCoord = 0.0;
	float CoMRow;
	float CoMCol;
	
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			sizeOfBlob = CountSizeOfBlobs(row, col, i, j, tempBlobArray,&sumOfRowCoord,&sumOfColCoord);

			if (sizeOfBlob > 0)
			{
				CoMRow = getAverage(sumOfRowCoord, sizeOfBlob);
				CoMCol = getAverage(sumOfColCoord, sizeOfBlob);

				printResults(blobNumber + 1, sizeOfBlob, CoMRow, CoMCol);
				
				sumOfRowCoord = 0;
				sumOfColCoord = 0;

				blobArray[blobNumber] = sizeOfBlob;
				blobNumber++;
			}
		}
	}
	cout << "+------+------------+---------+------------+" << endl;
		
	cout << endl;
	system("pause");
}

void printResults(int blob, int NoOfPixels, float CoMRow, float CoMCol)
{
	cout <<"|"<<setw(6)<<  blob ;
	cout << "|" << setw(12) << NoOfPixels;
	cout << "|" << setw(9) << fixed << setprecision(2) << CoMRow;
	cout << "|" << setw(12) << fixed << setprecision(2) << CoMCol<<"|";
	cout << endl;
}


float getAverage(float sum, float size)
{
	float average;
	average = sum / size;
	return average;
}


void printMatrix(int row,int col,char blobs[][SIZE])
{
	int i = 0, a = 0, j = 0;

	//Table
	cout << "   ";
	for (i = 0; i < col; i++)
	{
		cout << a;
		a++;
		if (a == 10)
		{
			a = 0;
		}
	}

	cout << endl << "  +";

	for (i = 0; i < col; i++)
	{
		cout << "-";
	}
	cout << "+" << endl;

	//Printing matrix into table
	for (i = 0; i < row; i++)
	{
		cout << setw(2) << i << "|";
		for (j = 0; j < col; j++)
		{
			cout << blobs[i][j];

		}
		cout << "|" << i;
		cout << endl;
	}

	cout <<"  +";

	for (i = 0; i < col; i++)
	{
		cout << "-";
	}
	cout << "+" << endl;

	cout << "   ";
	a = 0;
	for (i = 0; i < col; i++)
	{
		cout << a;
		a++;
		if (a == 10)
		{
			a = 0;
		}
	}

	cout << endl;
}


int CountSizeOfBlobs(int NoR, int NoC, int row, int col, char blobs[][SIZE], float* sumOfRowCoord, float* sumOfColCoord)
{
	if (row < 0 || row >= NoR|| col < 0 || col >= NoC)
		return 0;
	if (blobs[row][col] == ' ')
	{
		return 0;
	}
		
	else
	{
		blobs[row][col] = ' ';
		*sumOfRowCoord = *sumOfRowCoord + row;
		*sumOfColCoord = *sumOfColCoord + col;

		return (1 +			CountSizeOfBlobs(NoR,NoC, row - 1, col - 1,blobs,sumOfRowCoord, sumOfColCoord) +
							CountSizeOfBlobs(NoR, NoC, row - 1, col, blobs,sumOfRowCoord, sumOfColCoord) +
							CountSizeOfBlobs(NoR, NoC, row - 1, col + 1, blobs,sumOfRowCoord, sumOfColCoord) +
							CountSizeOfBlobs(NoR, NoC, row, col - 1, blobs, sumOfRowCoord, sumOfColCoord) +
							CountSizeOfBlobs(NoR, NoC, row, col + 1, blobs, sumOfRowCoord, sumOfColCoord) +
							CountSizeOfBlobs(NoR, NoC, row + 1, col - 1, blobs, sumOfRowCoord, sumOfColCoord) +
							CountSizeOfBlobs(NoR, NoC, row + 1, col, blobs, sumOfRowCoord, sumOfColCoord) +
							CountSizeOfBlobs(NoR, NoC, row + 1, col + 1, blobs, sumOfRowCoord, sumOfColCoord));
	}
}
