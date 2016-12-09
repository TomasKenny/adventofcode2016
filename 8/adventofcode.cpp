// adventofcode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <assert.h>

#define DISPLAY_WIDTH 50
#define DISPLAY_HEIGHT 6

void Rect(char display[][DISPLAY_WIDTH], int x, int y){
	for(int i = 0; i < y; i++){
		for(int j = 0; j < x; j++){
			display[i][j] = 1;
		}
	}
}

void RotateRow(char display[][DISPLAY_WIDTH], int row, int shift){
	char rowTemp[DISPLAY_WIDTH];
	for(int i = 0; i < DISPLAY_WIDTH; i++){
		rowTemp[(i + shift) % DISPLAY_WIDTH] = display[row][i];
	}
	memcpy(&display[row], rowTemp, sizeof(rowTemp));
}

void RotateCol(char display[][DISPLAY_WIDTH], int column, int shift){
	char colTemp[DISPLAY_HEIGHT];
	for(int i = 0; i < DISPLAY_HEIGHT; i++){
		colTemp[(i + shift) % DISPLAY_HEIGHT] = display[i][column];
	}
	for(int i = 0; i < DISPLAY_HEIGHT; i++){
		display[i][column] = colTemp[i];
	}
}

int CountLit(char display[][DISPLAY_WIDTH]){
	int sum = 0;
	for(int i = 0; i < DISPLAY_HEIGHT; i++){
		for(int j = 0; j < DISPLAY_WIDTH; j++){
			sum += display[i][j];
		}
	}
	return sum;
}

void Print(char display[][DISPLAY_WIDTH]){
	for(int i = 0; i < DISPLAY_HEIGHT; i++){
		for(int j = 0; j < DISPLAY_WIDTH; j++){
			putchar(display[i][j] ? '#' : '.');
		}
		putchar('\n');
	}
	putchar('\n');
}

int main()
{
	char display[6][50] = {0};

	FILE* fd = fopen("c:\\Users\\tomas.naplava\\Desktop\\input.txt", "r");
	std::string buffer;
	buffer.resize(100);

	Print(display);

	while(fgets(&buffer[0], 100, fd)){
		if(buffer.find("rect") == 0){
			int width = atoi(&buffer[0] + 5);
			int height = atoi(&buffer[0] + buffer.find("x") + 1);
			Rect(display, width, height);
		}
		else if(buffer.find("rotate") == 0){
			bool rotateRows = buffer.find("row") != std::string::npos;
			int index = atoi(&buffer[0] + buffer.find("=") + 1);
			int shiftVal = atoi(&buffer[0] + buffer.rfind(" ") + 1);
			if(rotateRows){
				RotateRow(display, index, shiftVal);
			}
			else{
				RotateCol(display, index, shiftVal);
			}
		}
		else{
			assert(false);
		}
		Print(display);
	}

	printf("%d\n", CountLit(display));
	getchar();
    return 0;
}

