#include <iostream>

using namespace std;

// class wordgrid provides an infrastructure for square (DxD)
// grids of letters. Each slot is referenced with a row number r,
// 0 <= r < D and a column number c, 0 <= c < D.

wordgrid::wordgrid(size_t d, string data) {

// PRE: second parameter is an long string of lowercase letters,
// which is the data for all the rows of the d x d grid.
// (data.length() == d * d)
// POST: initialize the instance with the data.
//------------------------------------------------------------------------
	_size = d;
	int count = -1;
	int grid[d][d];
	for(int r = 0; r < d; r++)
		for(int c = 0; c < d; c++)
			count++;
			grid[r][c] = data[count];
}
size_t wordgrid::size() const {

// RETURN: The dimension of the grid (length of one side)
//------------------------------------------------------------------------
	return _size;
}
char wordfind::get(size_t r, size_t c) const {

// PRE: r < size() and c < size()
// RETURN: the character at position (r,c)
//------------------------------------------------------------------------
	if((row > 0 && row < _size) && (col > 0 and col < size))
		if(r < size() and c < size())
			return grid[r][c];
}
void wordfind::set(size_t r, size_t c, char v) {

// PRE: same as get
// POST: the character at position (r,c) is now v
//------------------------------------------------------------------------
	grid[r][c] = v;
}
void wordfind::output(ostream & ostr) const {

// POST: The contents of the grid are produced on the
// output stream in rows terminated by newlines.
//------------------------------------------------------------------------
	for(int i = 0; i < _size; i++)
		ostr << grid[row] << endl;
}
























