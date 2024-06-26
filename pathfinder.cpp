#include <iostream>
#include "matrixcell.hpp"
#include "pathfinder.hpp"

using namespace std;

vector<vector<Cell>> calculatePath(vector<vector<double>>& matrix, int rows, int cols)
{ 
    // Create a 2D vector to store the distance and direction information for each cell.
    vector<vector<Cell>> paths(rows, vector<Cell>(cols));

    for (int i=0;i<rows;i++) 
    {
        for (int j=0;j<cols;j++) 
        {
            // Initialize the top row of the path with the distances from the matrix plus starting column.
            if (i==0) 
            {               
                paths[0][j].distance  = matrix[0][j];   
                paths[0][j].startColumn = j;
            }
            else 
            {
                // First assume first minimum distance is South and calculate the value
                double dir = paths[i-1][j].distance + matrix[i][j]; 
                double min = dir;
                // Flag value to identify traversal direction
                // SOUTH(S) = 1.0 | SOUTHEAST(SE) = 1.4 |SOUTHWEST(SW) = 1.4
                int dirFlag = 0;
                
                // SOUTH was the less costly traversal in the matrix
                if (dirFlag==0) 
                {
                    paths[i][j].directions = paths[i-1][j].directions;  
                    paths[i][j].directions.push_back("S");
                    paths[i][j].startColumn = paths[i-1][j].startColumn;           
                }
                // SOUTHWEST was the less costly traversal in the matrix
                if (min>paths[i-1][j+1].distance + matrix[i][j] * 1.4 && j<cols - 1) 
                {
                    min = paths[i-1][j+1].distance + matrix[i][j] * 1.4;
                    dirFlag = 1;
                    paths[i][j].directions = paths[i-1][j+1].directions;
                    paths[i][j].directions.push_back("SW");
                    paths[i][j].startColumn = paths[i-1][j+1].startColumn;
                    
                }
                // SOUTHEAST was the less costly traversal in the matrix
                if (min>paths[i-1][j-1].distance + matrix[i][j] * 1.4 && j>0) 
                {   
                    min = paths[i-1][j-1].distance + matrix[i][j] * 1.4;
                    dirFlag = 2;
                    paths[i][j].directions = paths[i-1][j-1].directions;
                    paths[i][j].directions.push_back("SE");
                    paths[i][j].startColumn = paths[i-1][j-1].startColumn;
                }
                paths[i][j].distance = min;
            }
        }
    }
    return paths;
}
