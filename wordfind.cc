/****************************************************************************
FILE:        wordfind.cc
AUTHOR:      Alistair Campbell and Jeffrey Clarke
DATE:        9/10/17

DESCRIPTION: A program in C++ that finds and capitalizes each letter of a 
			 given word, in a grid.
*****************************************************************************/

#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include "wordgrid.h"


using namespace std;

bool capitalized = false; // Boolean to check whether word is capitalized
int wordcount = 0; // Boolean used in capitalize function

int strlen(string s) {
	// Find the length of a given string and return its value as an int
    int len = 0;

    while (s[len])
        len++; // Advance index

    return len;
}

bool inbounds(string word, int row, int col, int xmove, int ymove, int gridlen) {
	// Calculate the bounds of each direction to be used in search 
	// function, indicated by xmove and ymove
	int xbounds = (xmove * (word.length()-1)) + row ; // Bounds of row
	int ybounds = (ymove * (word.length()-1)) + col ; // Bounds of col
	// Check if current bounds are less than or greater than length of grid
	if((xbounds < 0 or xbounds > gridlen) or (ybounds < 0 or ybounds > gridlen)) {
		return false; 
	}
	else {
		return true;
	}
}

// WRITE FOR LOOP STARTING FROM a = 0, a < wordlength; a++, 
// WE are using grid.set()
//	 Put 3 parts for grid.set()
//		part 1: (row + xmove) * a 

bool capitalize(int row, int col, string word, wordgrid & grid, int xmove = 0, int ymove = 0, int gridlen = 0) {
	// Capitalize each character in word using given row and col
	int wordlength = strlen(word);
	int gridlength = gridlen - 1; // Subtract 1 from grid length for index searching
	for(int a = 0 ; a < wordlength; a++) {
		// If index is equal to zero, check if row and col are less than grid length 
		if(a != 0) { 
			if(row < gridlength and col < gridlength) {
				row += xmove; // Increment row by movement in direction of x
				col += ymove; // Increment col by movement in direction of y
			}
		}
		char letter = grid.get(row, col); // Retrieve character from grid

		if(letter != toupper(letter)) { // Check if letter at position is already capitalized
			letter = toupper(letter); // Change character to uppercase
			grid.set(row, col, letter);
			wordcount++; // Increment word count
		}
		else {
			return false;
		}
	}
	// Compare word count to length of word to check if the correct amount of letters 
	// has been capitalized
	if(wordcount == strlen(word)) { 
		capitalized = true;
	}
	return capitalized;
}

void search(int row, int col, int xmove, int ymove, string word, wordgrid & grid, int gridlen) {
	//Search for word using given direction
	int wordlength = strlen(word);
	int gridlength = gridlen - 1; // 
	int srow = row; // Current search row
	int scol = col;	// Current search col
	for(int a = 0 ; a <= wordlength; a++) {
		if(xmove != 0 && ymove != 0) 
			if((srow != gridlength or srow < 0) && (scol != gridlength or scol < 0)) {
				if(grid.get(srow, scol) != word[a]) {
					return;
				}
				srow += xmove; // Increment search row by movement in x
				scol += ymove; // Increment search col by movement in y
			}
	}
	capitalize(row, col, word, grid, xmove, ymove, gridlen);
}

void checkdirections(int row, int col, string word, wordgrid & grid, int gridlen) {
	// Check in all possible directions for word
	int xmove = 0; // Movement in direction of x
	int ymove = 0; // Movement in direction of y
	for(int x = -1; x <= 1; x++)
		for(int y = -1; y <= 1; y++) {
			// Check bounds and search for word if word has not been found
			// and capitalized
			if(!capitalized) {
				xmove = x; // Assign xmove to current row direction (x)
				ymove = y; // Assign ymove to current col direction (y)
				if(xmove != 0 and ymove != 0) {
					if(inbounds(word, row, col, xmove, ymove, gridlen)) {
						search(row, col, xmove, ymove, word, grid, gridlen);
					}
				}
			}
			else {
				break;
			}

		}
	return;
}

//-function: bool find(string word, wordgrid & grid)------------------------
// PRE: word consists of lowercase letters
// POST: If word is found in grid, starting anywhere 
//       and in any of the 8 directions, it is converted
//       to uppercase in the grid, and true is returned.
//       otherwise, grid is unchanged, and false is returned.

bool find(string word, wordgrid & grid, int gridlen) {
// SEARCH to find beginning letter of word
	// you do it
	for(int r = 0; r < gridlen; r++)
		for(int c = 0; c < gridlen; c++)
			// Compare character at row, col and character at word[0]
			if(grid.get(r,c) == word[0]) { 
				// If the string word contains only one letter, capitalize
				// the word at its location in the grid.
				if(strlen(word) == 1) {
					capitalize(r, c, word, grid, gridlen);
					return true;
				}
				else {
					checkdirections(r, c, word, grid, gridlen); //
					if(capitalized)
						return true;
				}
			}

	return false; 
}

//------------------------------------------------------------------------
int main() {

  size_t dim = 0;  // size of the word grid
  string word = ""; // word to search for
  bool found = false;  // whether the word is found in the grid.
  string one_row = ""; // dim characters (one row) read from stdin
  string all_rows = ""; // dim x dim characters
 
  // SETUP
  cin >> dim;  // read the dimension 
  // read each row and append to the string of all rows
  for (size_t r = 0; r < dim ; r = r + 1) {
    cin >> one_row;
    all_rows += one_row;
  }
  int gridlen = strlen(one_row); // Int value for length of grid
  wordgrid grid(dim, all_rows);  // create the grid from that data

  cin >> word; // read the word

  // SEARCH  (you do)
  found = find(word, grid, gridlen);
  
  // REPORT

  if (found) {
    cout << "FOUND!" << endl;
    cout << grid;
  }    
  else
    cout << "NOT FOUND!" << endl;

}

