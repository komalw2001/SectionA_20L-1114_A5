#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>

using namespace std;

// sorts words array in descending order of length of words
void SortWordList(string* &strArray, int size)
{
	for (int i=0; i < size; i++)
	{
		for (int j=0; j < (size-1); j++)
		{
			if (strArray[j+1].length() > strArray[j].length())
			{
				string temp=strArray[j];
				strArray[j]=strArray[j+1];
				strArray[j+1]=temp;
			}
		}
	}
}

// initialises all characters of grid to null
void InitialiseGrid(char** &Grid, int rows, int columns)
{
	for (int i=0; i < rows; i++)
	{
		for (int j=0; j < columns; j++)
		{
			Grid[i][j]='\0';
		}
	}
}

// adds a word at (r,c) diagonally right downwards on the grid if it is empty
bool AddDiagonalDownRight(char** &grid, string word, int row, int column)
{
	for (int i=0; i < word.length(); i++)
	{
		if (grid[row+i][column+i] != '\0' && grid[row+i][column+i] != word[i]) // if any space is filled and it is not the character required for the new word, returns false
			return false;
	}

	for (int i=0; i < word.length(); i++)
	{
		grid[row+i][column+i]=word[i];
	}

	return true;
}

// adds a word at (r,c) diagonally right upwards on the grid if it is empty
bool AddDiagonalUpRight(char** &grid, string word, int row, int column)
{
	for (int i=0; i < word.length(); i++)
	{
		if (grid[row-i][column+i] != '\0' && grid[row-i][column+i] != word[i]) 
			return false;
	}

	for (int i=0; i < word.length(); i++)
	{
		grid[row-i][column+i]=word[i];
	}

	return true;
}

// adds a word at (r,c) diagonally left downwards on the grid if it is empty
bool AddDiagonalDownLeft(char** &grid, string word, int row, int column)
{
	for (int i=0; i < word.length(); i++)
	{
		if (grid[row+i][column-i] != '\0' && grid[row+i][column-i] != word[i])
			return false;
	}

	for (int i=0; i < word.length(); i++)
	{
		grid[row+i][column-i]=word[i];
	}

	return true;
}

// adds a word at (r,c) diagonally left upwards on the grid if it is empty
bool AddDiagonalUpLeft(char** &grid, string word, int row, int column)
{
	for (int i=0; i < word.length(); i++)
	{
		if (grid[row-i][column-i] != '\0' && grid[row-i][column-i] != word[i])
			return false;
	}

	for (int i=0; i < word.length(); i++)
	{
		grid[row-i][column-i]=word[i];
	}

	return true;
}

// adds a word at (r,c) from left to right on the grid if it is empty
bool AddLeftToRight(char** &grid, string word, int row, int column)
{
	for (int i=0; i < word.length(); i++)
	{
		if (grid[row][column+i] != '\0' && grid[row][column+i] != word[i])
			return false;
	}

	for (int i=0; i < word.length(); i++)
	{
		grid[row][column+i]=word[i];
	}

	return true;
}

// adds a word at (r,c) from right to left on the grid if it is empty
bool AddRightToLeft(char** &grid, string word, int row, int column)
{
	for (int i=0; i < word.length(); i++)
	{
		if (grid[row][column-i] != '\0' && grid[row][column-i] != word[i])
			return false;
	}

	for (int i=0; i < word.length(); i++)
	{
		grid[row][column-i]=word[i];
	}

	return true;
}

// adds a word at (r,c) from top to bottom on the grid if it is empty
bool AddTopToBottom(char** &grid, string word, int row, int column)
{
	for (int i=0; i < word.length(); i++)
	{
		if (grid[row+i][column] != '\0' && grid[row+i][column] != word[i])
			return false;
	}

	for (int i=0; i < word.length(); i++)
	{
		grid[row+i][column]=word[i];
	}

	return true;
}

// adds a word at (r,c) from bottom to top on the grid if it is empty
bool AddBottomToTop(char** &grid, string word, int row, int column)
{
	for (int i=0; i < word.length(); i++)
	{
		if (grid[row-i][column] != '\0' && grid[row-i][column] != word[i])
			return false;
	}

	for (int i=0; i < word.length(); i++)
	{
		grid[row-i][column]=word[i];
	}

	return true;
}

// fills extra spaces in grid with random alphabets
void FillExtraSpaces(char** &Grid, int rows, int columns)
{
	for (int i=0; i < rows; i++)
	{
		for (int j=0; j < columns; j++)
		{
			if (Grid[i][j] == '\0')
				Grid[i][j]=rand() % 26 + 65; // generates a random character from A-Z
		}
	}
}

// fills the grid
bool GenerateGrid(char** &Grid, const string* words, int TotalWords, int rows, int columns)
{
	InitialiseGrid(Grid,rows,columns);

	bool filled=false; // to check whether the words have been filled in the grid
	bool all_filled=true; // to ensure ALL words have been filled

	int wordcount=0;
	int loopcount=0; // to check if a word is unable to be placed after looping twice
	while (!filled && loopcount < 2)
	{
		loopcount++;
		for (int r=0; r < rows; r++)
		{
			for (int c=0; c < columns; c++)
			{
				int word_length=words[wordcount].length();
				bool added=false; // indicates whether the word has been added to the grid

				if ((c+word_length-1 < columns) && (r+word_length-1 < rows))
				{
					added=AddDiagonalDownRight(Grid,words[wordcount],r,c);

				}

				if (!added && (c+word_length-1 < columns) && (r-word_length+1 >= 0))
				{
					added=AddDiagonalUpRight(Grid,words[wordcount],r,c);
				}

				if (!added && (r+word_length-1 < rows) && (c-word_length+1 >= 0))
				{
					added=AddDiagonalDownLeft(Grid,words[wordcount],r,c);
				}

				if (!added && (r-word_length+1 >= 0) && (c-word_length+1 >= 0))
				{
					added=AddDiagonalUpLeft(Grid,words[wordcount],r,c);
				}

				if (!added && (c+word_length-1 < columns))
				{
					added=AddLeftToRight(Grid,words[wordcount],r,c);
				}

				if (!added && (c-word_length+1 >= 0))
				{
					added=AddRightToLeft(Grid,words[wordcount],r,c);
				}

				if (!added && (r+word_length-1 < rows))
				{
					added=AddTopToBottom(Grid,words[wordcount],r,c);
				}

				if (!added && (r-word_length+1 >= 0))
				{
					added=AddBottomToTop(Grid,words[wordcount],r,c);
				}

				if (added || loopcount > 1)
				{
					if (loopcount > 1)
						all_filled=false;
					wordcount++;
					loopcount=0;
				}
			}
		}
		if (wordcount >= TotalWords)
			filled=true;
	}
	
	FillExtraSpaces(Grid,rows,columns);

	if (all_filled)
		return true;

	return false;
}

// writes grid to output file
void OutputGrid(char** Grid, int rows, int columns, ofstream &FOUT)
{
	for (int i=0; i < rows; i++)
	{
		for (int j=0; j < columns; j++)
		{
			FOUT<<Grid[i][j]<<" ";
		}
		FOUT<<endl;
	}
}

// reads the word grid matrix from file and stores it in matrix array
void InputMatrix(ifstream& FREAD, char** matrix, int rows, int columns)
{
	for (int i=0; i < rows; i++)
	{
		for (int j=0; j < columns; j++)
		{
			FREAD>>matrix[i][j];
		}
	}
}

// searches for word horizontally from left to right
string SearchLeftToRight(string SearchWord, char** matrix, int rows, int columns)
{
	int SW_length=SearchWord.length();
	string indexes=""; // initialised to null so that if word not found, function returns null
	
	for (int r=0; r < rows; r++)
	{
		for (int c=0; c < (columns-SW_length); c++)
		{
			string Word="";
			for (int i=c; i < (c+SW_length); i++)
			{
				Word+=matrix[r][i]; // extracting words of the same size as searchword from left to right
			}

			if (Word == SearchWord)
			{
				indexes = "{" + to_string(r) + "," + to_string(c) + "}{" + to_string(r) + "," + to_string(c+SW_length-1) + "}"; // string of format: {starting_row,starting_column}{ending_row,ending_column}
				return indexes;
			}
		}
	}
	return indexes;
}

// searches for word horizontally from right to left
string SearchRightToLeft(string SearchWord, char** matrix, int rows, int columns)
{
	int SW_length=SearchWord.length();
	string indexes="";

	for (int r=0; r < rows; r++)
	{
		for (int c=0; c < (columns-SW_length); c++)
		{
			string Word="";
			for (int i=c+SW_length-1; i >= c; i--)
			{
				Word+=matrix[r][i];
			}

			if (Word == SearchWord)
			{
				indexes = "{" + to_string(r) + "," + to_string(c+SW_length-1) + "}{" + to_string(r) + "," + to_string(c) + "}";
				return indexes;
			}
		}
	}
	return indexes;
}

// searches for word vertically from top to bottom
string SearchTopToBottom(string SearchWord, char** matrix, int rows, int columns)
{
	int SW_length=SearchWord.length();
	string indexes="";

	for (int r=0; r < (rows-SW_length); r++)
	{
		for (int c=0; c < columns; c++)
		{
			string Word="";
			for (int i=r; i < (r+SW_length); i++)
			{
				Word+=matrix[i][c];
			}

			if (Word == SearchWord)
			{
				indexes = "{" + to_string(r) + "," + to_string(c) + "}{" + to_string(r+SW_length-1) + "," + to_string(c) + "}";
				return indexes;
			}
		}
	}
	return indexes;
}

// searches for word vertically from bottom to top
string SearchBottomToTop(string SearchWord, char** matrix, int rows, int columns)
{
	int SW_length=SearchWord.length();
	string indexes="";
	
	for (int r=0; r < (rows-SW_length); r++)
	{
		for (int c=0; c < columns; c++)
		{
			string Word="";
			for (int i=r+SW_length-1; i >= r; i--)
			{
				Word+=matrix[i][c];
			}

			if (Word == SearchWord)
			{
				indexes = "{" + to_string(r+SW_length-1) + "," + to_string(c) + "}{" + to_string(r) + "," + to_string(c) + "}";
				return indexes;
			}
		}
	}
	return indexes;
}

// searches for word diagonally downwards in the right direction
string SearchDiagonalDownRight(string SearchWord, char** matrix, int rows, int columns)
{
	int SW_length=SearchWord.length();
	string indexes="";
	
	for (int r=0; r < (rows-SW_length); r++)
	{
		for (int c=0; c < (columns-SW_length); c++)
		{
			string Word="";
			for (int i=0; i < SW_length; i++)
			{
				Word+=matrix[r+i][c+i];
			}

			if (Word == SearchWord)
			{
				indexes = "{" + to_string(r) + "," + to_string(c) + "}{" + to_string(r+SW_length-1) + "," + to_string(c+SW_length-1) + "}";
				return indexes;
			}
		}
	}
	return indexes;
}

// searches for word diagonally upwards in the left direction
string SearchDiagonalUpLeft(string SearchWord, char** matrix, int rows, int columns)
{
	int SW_length=SearchWord.length();
	string indexes="";
	
	for (int r=0; r < (rows-SW_length); r++)
	{
		for (int c=0; c < (columns-SW_length); c++)
		{
			string Word="";
			for (int i=SW_length-1; i >= 0; i--)
			{
				Word+=matrix[r+i][c+i];
			}

			if (Word == SearchWord)
			{
				indexes = "{" + to_string(r+SW_length-1) + "," + to_string(c+SW_length-1) + "}{" + to_string(r) + "," + to_string(c) + "}";
				return indexes;
			}
		}
	}
	return indexes;
}

// searches for word diagonally downwards in the left direction
string SearchDiagonalDownLeft(string SearchWord, char** matrix, int rows, int columns)
{
	int SW_length=SearchWord.length();
	string indexes="";
	
	for (int r=0; r < (rows-SW_length); r++)
	{
		for (int c=columns-1; c >= (SW_length-1); c--)
		{
			string Word="";
			for (int i=r, j=c; i < (r+SW_length); i++, j--)
			{
				Word+=matrix[i][j];
			}

			if (Word == SearchWord)
			{
				indexes = "{" + to_string(r) + "," + to_string(c) + "}{" + to_string(r+SW_length-1) + "," + to_string(c-SW_length+1) + "}";
				return indexes;
			}
		}
	}
	return indexes;
}

// searches for word diagonally upwards in the right direction
string SearchDiagonalUpRight(string SearchWord, char** matrix, int rows, int columns)
{
	int SW_length=SearchWord.length();
	string indexes="";
	
	for (int r=0; r < (rows-SW_length); r++)
	{
		for (int c=columns-1; c >= (SW_length-1); c--)
		{
			string Word="";
			for (int i=r+SW_length-1, j=c-SW_length+1; i >= r; i--, j++)
			{
				Word+=matrix[i][j];
			}

			if (Word == SearchWord)
			{
				indexes = "{" + to_string(r+SW_length-1) + "," + to_string(c-SW_length+1) + "}{" + to_string(r) + "," + to_string(c) + "}";
				return indexes;
			}
		}
	}
	return indexes;
}

// finds the indexes of the word and stores them in the file
void FindWord(ofstream& WriteFile, string SearchWord, char** Matrix, int rows, int columns)
{
	string index=SearchLeftToRight(SearchWord,Matrix,rows,columns); // string variable which will store the line to be written in file

	if (index == "") // if word not found
	{
		index=SearchRightToLeft(SearchWord,Matrix,rows,columns);
	}

	if (index == "")
	{
		index=SearchTopToBottom(SearchWord,Matrix,rows,columns);
	}

	if (index == "")
	{
		index=SearchBottomToTop(SearchWord,Matrix,rows,columns);
	}

	if (index == "")
	{
		index=SearchDiagonalDownRight(SearchWord,Matrix,rows,columns);
	}

	if (index == "")
	{
		index=SearchDiagonalUpLeft(SearchWord,Matrix,rows,columns);
	}

	if (index == "")
	{
		index=SearchDiagonalDownLeft(SearchWord,Matrix,rows,columns);
	}

	if (index == "")
	{
		index=SearchDiagonalUpRight(SearchWord,Matrix,rows,columns);
	}

	if (index != "")
	{
		WriteFile<<index<<endl;
		cout<<index<<endl;
	}
	else
	{
		WriteFile<<"Not Found"<<endl;
		cout<<"Not Found"<<endl;
	}
}

int main()
{
	char LetterChoice;

	do
	{

		cout<<"-----------------WORD SEARCH-----------------"<<endl<<endl;
		cout<<"1. Create Grid (Enter C)."<<endl;
		cout<<"2. Search Words from Grid (Enter S)."<<endl;
		cout<<"3. Quit (Enter Q)."<<endl;
		cout<<"Enter letter (C/S/Q): ";
		cin>>LetterChoice;

		if (toupper(LetterChoice) == 'C')
		{

			string InputFileName, OutputFileName;
			int WordCount, rows, columns;
			ifstream ReadFile;
			char** Grid=0;

			bool CorrectExt = false;
			do
			{
				cout<<"Enter name of text file containing list of words: ";
				cin>>InputFileName;

				if (InputFileName.length() < 5 || (InputFileName.substr( (InputFileName.length() - 4), 4) != ".txt" && InputFileName.substr((InputFileName.length() - 4), 4) != ".TXT"))
				{
					cout<<"File must have a name with a .txt extension!"<<endl;
				}
				else
				{
					CorrectExt = true;

					ReadFile.open(InputFileName);
					if (!ReadFile)
					{
						cout<<"File does not exist! Re-enter file name!"<<endl;
					}
				}

			}
			while(!CorrectExt || !ReadFile);

			cout<<"Enter the number of words: ";
			cin>>WordCount;
			cout<<"Enter the number of rows and columns for the grid to be created: "<<endl;
			cout<<"Enter rows: ";
			cin>>rows;
			cout<<"Enter columns: ";
			cin>>columns;

			cout<<"Enter the name of the output file to create: ";
			cin>>OutputFileName;
			
			string* Words = new string[WordCount];
			for (int i=0; i < WordCount; i++)
			{
				ReadFile>>Words[i];
			}

			ReadFile.close();

			SortWordList(Words,WordCount);

			if (rows < Words[0].length() && columns < Words[0].length())
			{
				cout<<"Grid cannot be formed, press any key to return to the home screen."<<endl;
			}
			else
			{
				// allocating memory for grid
				Grid = new char*[rows];
				for (int i=0; i < rows; i++)
				{
					Grid[i]= new char[columns];
				}

				bool done = GenerateGrid(Grid, Words, WordCount, rows, columns);
	
				if (OutputFileName.length() < 5 || (OutputFileName.substr((OutputFileName.length() - 4), 4) != ".txt" && OutputFileName.substr((OutputFileName.length() - 4), 4) != ".TXT"))
					OutputFileName+=".txt";
				ofstream WriteFile(OutputFileName);
				OutputGrid(Grid,rows,columns,WriteFile);
				cout<<"Grid generated and saved in file named: "<<OutputFileName<<"!"<<endl;
				
				if (!done)
					cout<<"Unable to add some words due to less space remaining!"<<endl;

				WriteFile.close();

				// memory deallocation:

				delete[] Words;
				Words=0;

				for (int i=0; i < rows; i++)
				{
					delete Grid[i];
				}
				delete[] Grid;
				Grid=0;

			}

			system("pause");
		}
		else if (toupper(LetterChoice) == 'S')
		{
			string InputFileName, GridFileName, OutputFileName;
			ifstream ReadGridFile;
			ifstream ReadInputFile;
			ofstream WriteFile;

			bool CorrectExt = false;
			do
			{
				cout<<"Enter the name of the file containing the grid: "<<endl;
				cin>>GridFileName;

				if (GridFileName.length() < 5 || (GridFileName.substr( (GridFileName.length() - 4), 4) != ".txt" && GridFileName.substr((GridFileName.length() - 4), 4) != ".TXT"))
				{
					cout<<"File must have a name with a .txt extension!"<<endl;
				}
				else
				{
					CorrectExt = true;

					ReadGridFile.open(GridFileName);
					if (!ReadGridFile)
					{
						cout<<"File does not exist! Re-enter file name!"<<endl;
					}
				}

			}
			while(!CorrectExt || !ReadGridFile);

			CorrectExt = false;
			do
			{

				cout<<"Enter the name of the input file containing the words and dimensions of the grid: "<<endl;
				cin>>InputFileName;

				if (InputFileName.length() < 5 || (InputFileName.substr( (InputFileName.length() - 4), 4) != ".txt" && InputFileName.substr((InputFileName.length() - 4), 4) != ".TXT"))
				{
					cout<<"File must have a name with a .txt extension!"<<endl;
				}
				else
				{
					CorrectExt = true;

					ReadInputFile.open(InputFileName);
					if (!ReadInputFile)
					{
						cout<<"File does not exist! Re-enter file name!"<<endl;
					}
				}

			}
			while(!CorrectExt || !ReadInputFile);

			cout<<"Enter the name of the output file to be created: "<<endl;
			cin>>OutputFileName;
			if (OutputFileName.length() < 5 || (OutputFileName.substr((OutputFileName.length() - 4), 4) != ".txt" && OutputFileName.substr((OutputFileName.length() - 4), 4) != ".TXT"))
				OutputFileName+=".txt";
			WriteFile.open(OutputFileName);

			char** Matrix=0; // to store the matrix of characters for word search
			int rows=0, columns=0, WordCount=0;
			string SearchWord;

			ReadInputFile>>rows>>columns;
	
			// dynamic allocation of memory for matrix
			Matrix = new char*[rows];
			for (int i=0; i < rows; i++)
				Matrix[i]=new char[columns];

			InputMatrix(ReadGridFile, Matrix, rows, columns);

			ReadGridFile.close();

			ReadInputFile>>WordCount;
			
			cout<<"Search Results: "<<endl;

			// loop for reading and processing each word, also prints the search results
			for (int i=0; i < WordCount; i++)
			{
				ReadInputFile>>SearchWord;

				FindWord(WriteFile,SearchWord,Matrix,rows,columns);
			}
	
			cout<<endl<<"Output file ("<<OutputFileName<<") created."<<endl;

			ReadInputFile.close();
			WriteFile.close();

			// deallocation of memory to avoid memory leakage
			for (int i=0; i < rows; i++)
			{
				delete[] Matrix[i];
			}
			delete[] Matrix;
			Matrix=0; // to avoid dangling pointer
			
			system("pause");

		}
		else if (toupper(LetterChoice) == 'Q')
		{
			cout<<"Quitting.."<<endl;
		}
		else
		{
			cout<<"Incorrect letter entered! This letter has no command!"<<endl;
		}
	
		cout<<endl<<endl<<endl;

	}
	while(toupper(LetterChoice) != 'Q');

	return 0;
}