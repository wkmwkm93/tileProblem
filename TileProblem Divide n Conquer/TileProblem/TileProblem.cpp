// tileproblem.cpp : defines the entry point for the console application.
//
#include "stdafx.h"
// c++ program to place tiles
#include <iostream>
#include<cmath>
#include<chrono>

using namespace std;
using namespace chrono;

int ngridpow,ntotaldim = 0, b, a, cnt = 0;
int arr[1024][1024];
high_resolution_clock::time_point StartTime, EndTime;

// placing tile at the given coordinates
void place(int x1, int y1, int x2,
	int y2, int x3, int y3)
{
	//cnt is to show the same tile,display purpose
	cnt++;
	arr[x1][y1] = cnt;
	arr[x2][y2] = cnt;
	arr[x3][y3] = cnt;
}
// quadrant names
// 1 2
// 3 4

// function based on divide and conquer
int tile(int n, int x, int y)
{
	//r is x coord for the missing tile, c for y
	int r, c;
	//base class is 2x2.display the tile and end current iteration
	if (n == 2) {
		cnt++;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (arr[x + i][y + j] == 0) {
					arr[x + i][y + j] = cnt;
				}
			}
		}
		return 0;
	}
	//always start from the top left of a divided region, so x and y is the top left coordinate
	// finding hole location
	for (int i = x; i < x + n; i++) {
		for (int j = y; j < y + n; j++) {
			if (arr[i][j] != 0)
				r = i, c = j;
		}
	}

	// if missing tile is 1st quadrant
	if (r < x + n / 2 && c < y + n / 2)
		place(x + n / 2, y + (n / 2) - 1, x + n / 2,
			y + n / 2, x + n / 2 - 1, y + n / 2);

	// if missing tile is in 3rd quadrant
	else if (r >= x + n / 2 && c < y + n / 2)
		place(x + (n / 2) - 1, y + (n / 2), x + (n / 2),
			y + n / 2, x + (n / 2) - 1, y + (n / 2) - 1);

	// if missing tile is in 2nd quadrant
	else if (r < x + n / 2 && c >= y + n / 2)
		place(x + n / 2, y + (n / 2) - 1, x + n / 2,
			y + n / 2, x + n / 2 - 1, y + n / 2 - 1);

	// if missing tile is in 4th quadrant
	else if (r >= x + n / 2 && c >= y + n / 2)
		place(x + (n / 2) - 1, y + (n / 2), x + (n / 2),
			y + (n / 2) - 1, x + (n / 2) - 1,
			y + (n / 2) - 1);

	// diving it again in 4 quadrants
	//Q2,skip the first time only
	if(n<ntotaldim)
		tile(n / 2, x, y + n / 2);
	//Q1
	tile(n / 2, x, y);
	//Q3
	tile(n / 2, x + n / 2, y);
	//Q4
	tile(n / 2, x + n / 2, y + n / 2);

	return 0;
}

// driver program to test above function
int main()
{
	//Run 10 times to get average run time		
	printf("[Divide & Conquer]\n");
	printf("After 10 iterations:\n");

	for (int i = 4; i <11 ; i++)
	{
		double total_time = 0.0;

		for (int j = 0; j < 10; j++)
		{
			duration<double, std::milli> time_span;
			memset(arr, 0, sizeof(arr));
			// power of grid dimension 2^ngridpow
			ngridpow = i;
			ntotaldim = pow(2, ngridpow);
			int nq2x = pow(2, ngridpow) / 2 - 1;
			int nq2y = pow(2, ngridpow) / 2;
			// here tile can not be placed
			arr[nq2x][nq2y] = -1;

			StartTime = high_resolution_clock::now();
			tile(ntotaldim, 0, 0);
			EndTime = high_resolution_clock::now();
			time_span = EndTime - StartTime;
			total_time += time_span.count();
			//printf("Iteration %d: Time for 2^%d : %.3f ms\n",j+1 , i, time_span.count());
		}
		total_time = total_time/10.0;
		printf("Average Time for 2^%d : %.3f ms\n", i, total_time);
	}

	for (int i = 0; i < ntotaldim; i++) {
		for (int j = 0; j < ntotaldim; j++)
			printf("%3d,", arr[i][j]);
		printf("\n");
	}

	getchar();
}
