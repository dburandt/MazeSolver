
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

// change to 15 for handin
#define m 15

char maze[m][m];

string path = "";

int numSolutions = 0;

// Precondition: maze must be 15x15,
//               maze must have entrance at 0,1,
//               maze must have >=1 exit(s)
// Postcondition: maze saved as a 2D array
void set_up_maze(char maze[m][m]) {
    
    
    int row = 0;
    int col = 0;
    char next;
    
    // read text file
    ifstream infile;
    infile.open("maze.txt");

    // save text file to a 2D array
    while (!infile.eof()) {
        infile >> next;
        if (next == '\n') {
            row++;
            col = 0;
        } else {
            maze[row][col] = next;
            col++;
        }
    }
    infile.close();
}

// Precondition:  path is a valid string
// Postcondition: path printed to console
void print(string path) {
    cout << "Path " << numSolutions << ": " << path << endl;
}

// Precondition: maze
// Postcondition:
void generate_all_paths(char maze[m][m], int row, int col, string path) {
    
    if (maze[row][col] != 'S')
        path.append(",");
    
    path += maze[row][col];
    
    if (row < 0 || col < 0 || row > m-1 || col > m-1) { return; }
    if (maze[row][col] == '#') {
        return;
    }

    maze[row][col] = '#';
    
    if (col == m-1) {
        numSolutions++;
        print(path);
        return;
    }
    
    if (maze[row][col+1] != '#') {
        string path_right (path);
        generate_all_paths(maze, row, col+1, path_right);
    }
    if (maze[row+1][col] != '#') {
        string path_down (path);
        generate_all_paths(maze, row+1, col, path_down);
    }
    if (maze[row][col-1] != '#') {
        string path_left (path);
        generate_all_paths(maze, row, col-1, path_left);
    }
    if (maze[row-1][col] != '#') {
        string path_up (path);
        generate_all_paths(maze, row-1, col, path_up);
    }
}

int main(int argc, const char * argv[]) {
    char maze[m][m];
    set_up_maze(maze);
    generate_all_paths(maze, 1, 0, "");
    cout << numSolutions << " total paths" << endl;

    return 0;
}
