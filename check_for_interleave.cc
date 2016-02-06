/**
 * This is a dynamic programing implementation for checking
 * if a string is interleaved of two other strings.
 */
#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
bool DEBUG_MODE = true;

/**
 * Function: printTable
 * This is a helper function to print out the content of
 * a table of size row x column.
 * @param table			the 2D table
 * @param row			the number of rows of table
 * @param col			the number of columns of table
 * @return nothing
 */
void
printTable(bool** table, int row, int col)
{
	std::cout << "Memoization table" << std::endl;
	for (int i = 0; i <= row; i++)
	{
		for (int j = 0; j <= col; j++)
		{
			std::string true_or_false = table[i][j] ? "true" : "false";
			std::cout << true_or_false << "\t";
		}
		std::cout << "\n";
	}
}

/**
 * Function: isInterleaved
 * This function checks to see if a string is interleaved
 * between two other strings.
 * @param a	one of the possible source string
 * @param b	one of the possible source string
 * @param c	string to check if interleaved
 * @return true or false
 */
bool
isInterleaved(char* a, char* b, char* c)
{
	int len_a = std::strlen(a);
	int len_b = std::strlen(b);
	int len_c = std::strlen(c);

	if (len_a + len_b == 0 && len_c == 0)
	{
		// all empty strings
		return true;
	}

	if (len_a + len_b < len_c)
	{
		// string in question is longer than string a and b combine
		return false;
	}

	int i, j = 0;
	std::cout << "Creating table ..." << std::endl;
	// create a memoization table
	//bool mt[len_a][len_b];
	bool** mt;

	// initialization of memoization table
	std::cout << "Starting initialization process..." << std::endl;

    mt = new bool *[len_a + 1];
	for (i = 0; i <= len_a; i++)
	{
		//std::cout << i;
		mt[i] = new bool [len_b + 1];
	}

    for (i = 0; i <= len_a;i++)
    {
      for (j = 0; j <= len_b; j++ )
      {
        mt[i][j] = false;
      }
    }

	// determine if string C is interleaved of A and B by utilizing memoization table
	std::cout << "Determining interleave ..." << std::endl;
	for(i = 0; i <= len_a; i++)
	{
		for(j = 0; j <= len_b; j++)
		{
			if (i == 0 && j == 0)
			{
				// empty strings
				mt[i][j] = true;
			}

			if (i == 0 && j >= 1 && c[j-1] == b[j-1])
			{
				// string a is empty; compare char in string b and c
				mt[i][j] = mt[i][j-1];
			}
			else if (j == 0 && i >= 1 && c[i-1] == a[i-1])
			{
				// string b is empty; compare char in string a and c
				mt[i][j] = mt[i-1][j];
			}

			// both strings is not empty
			// case 1 - character of A matches with character of C but not B
			if (i >= 1 && a[i-1] == c[i+j-1] && b[j-1] != c[i+j-1])
			{
				mt[i][j] = mt[i-1][j];
			}
			// case 2 - character of B matches with character of C but not A
			else if (j >= 1 && b[j-1] == c[i+j-1] && a[i-1] != c[i+j-1])
			{
				mt[i][j] = mt[i][j-1];
			}
			//case 3 - character of both A and B matches with C
			else if (j >= 1 && i >= 1 && a[i-1] == c[i+j-1] && b[j-1] == c[i+j-1])
			{
				mt[i][j] = mt[i-1][j] || mt[i][j-1];
			}
		}
	}
	if (DEBUG_MODE)
	{
		printTable(mt, len_a, len_b);
	}

	// last entry in the memoization table indicates if string C is interleaved
	return mt[len_a][len_b];
}

int main(int argc, char** argv)
{
	if (argc != 4)
	{
		std::cerr << "Invalid usage.\nFormat: <executable name> <string a> <string b> <string c>" << std::endl;
		return -1;
	}
	/*
	char* a = "abc";
	char* b = "def";
	char* c = "abcdef";
	*/
	char* a = argv[1];
	char* b = argv[2];
	char* c = argv[3];

	bool is_interleaved = isInterleaved(a, b, c);

	if (is_interleaved)
	{
		std::cout << c << " is interleaved of " << a << " and " << b << std::endl;
	}
	else
	{
		std::cout << c << " is not interleaved of " << a << " and " << b << std::endl;
	}
	
	return 0;
}
