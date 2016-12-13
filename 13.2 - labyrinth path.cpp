#include "stdafx.h"
#include <vector>
#include <set>
#include <assert.h>
#include <algorithm>

int CountBinaryOnes(int val){
    static const int binaryOnes[16] = {
        0, 1, 1, 2,    //0, 1, 2, 3
        1, 2, 2, 3, //4,5,6,7
        1, 2, 2, 3, //8,9,10,11
        2, 3, 3, 4
    };
   
    int count = 0;
    while(val){
        count += binaryOnes[val & 0xF];
        val >>= 4;
    }
    return count;
}

void PrintGrid(char grid[][50]){
    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 50; j++){
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

struct Point{
	Point(int x, int y, int dest):
        x(x),
        y(y),
        distance(dest)
	{}
    
    int x;
    int y;
    int distance;
    bool operator==(const Point o) const { 
		return x == o.x && y == o.y;
	}
};

bool IsValid(const Point & p, char grid[][50]){
    return (p.x >= 0) && (p.y >= 0) && (grid[p.y][p.x] == '.');
}

int Search(char grid[][50], int maxPath){
    std::vector<Point> visitedPoints;
	visitedPoints.push_back(Point(1, 1, 0));
	
    for(int current = 0; current < visitedPoints.size(); current++){
		Point currentPoint = visitedPoints[current];
		if(currentPoint.distance > maxPath){
			return current;
		}
		
        //left, right, up and down
		int directions[4][2] = {
			{-1, 0}, {1, 0}, {0, -1}, {0, 1}
		};
		for(int i = 0; i < sizeof(directions) / sizeof(directions[0]); i++){
			Point p = Point(
				currentPoint.x + directions[i][0], 
				currentPoint.y + directions[i][1], 
				currentPoint.distance + 1
			);

			if(std::find(visitedPoints.begin(), visitedPoints.end(), p) == visitedPoints.end()){
				if(IsValid(p, grid)){
					visitedPoints.push_back(p);
				}
			}
		}
    }

}

int main()
{
    char grid[50][50];
    const int favoriteNum = 1358;            ////////////////////
   
    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 50; j++){
            int val = j*j + 3*j + 2*j*i + i + i*i + favoriteNum;
            grid[i][j] = (CountBinaryOnes(val) & 0x1) ? '#' : '.';
        }
    }

    PrintGrid(grid);

    printf("%d\n", Search(grid, 50));
    getchar();
    return 0;
}