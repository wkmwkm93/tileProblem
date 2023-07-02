// tileproblem.cpp : defines the entry point for the console application.
//
#include "stdafx.h"
// c++ program to place tiles
#include <iostream>
#include<cmath>
//#include<winbase.h>
#include <cstring>
#include <afx.h>
#include <direct.h>
#include<chrono>
using namespace std;
using namespace chrono;

int ngridpow,ntotaldim = 0,nIteration=0, cnt = 0;
int arr[1024][1024];
high_resolution_clock::time_point StartTime, EndTime;

// placing tile at the given coordinates,xy is the top left coords of the base case
void placeBaseCase(int x, int y)
{
	//Q1
	arr[x-2][y-2] = 2;
	arr[x-2][y-1] = 2;
	arr[x-1][y-2] = 2;
	//Q3
	arr[x][y-2] = 3;
	arr[x+1][y-2] = 3;
	arr[x+1][y-1] = 3;
	//Q4
	arr[x][y + 1] = 4;
	arr[x + 1][y + 1] = 4;
	arr[x + 1][y] = 4;
	//Center
	arr[x][y] = 1;
	arr[x][y-1] = 1;
	arr[x-1][y-1] = 1;
}

void saveOutput()
{
	CString szAppPath;
	LPTSTR pBuffer = szAppPath.GetBuffer(255);
	GetCurrentDirectory(255, pBuffer);
	szAppPath.ReleaseBuffer();

	CString szSrc = _T("");
	szSrc = szAppPath + _T("\\Display\\DPResult.csv");
	CStdioFile f;
	if (f.Open(szSrc, CFile::modeCreate | CFile::modeReadWrite))
	{
		f.SeekToBegin();

		for (int i = 0; i < ntotaldim; i++)
		{
			CString szRow;
			for (int j = 0; j < ntotaldim; j++)
			{
				CString szDisp;
				szDisp.Format(_T("%d,"), arr[i][j]);
				szRow += szDisp;
			}
			//remove the last comma
			szRow.Delete(szRow.GetLength() - 1);
			szRow += _T("\n");
			f.WriteString(szRow);
		}
		f.Close();
	}
}

void copySolution(int nPower)
{
	//nOffset = 4,8
	int nOffset = pow(2, nPower);
	int prevOffset = pow(2, nPower - 1);

	//Copy solution directly to Q3,skipping Q2
	for(int row= 0;row < nOffset;row++)
		for (int col = 0; col < nOffset; col++)
		{
			if (row < nOffset / 2 && col >= nOffset / 2)
				continue;
			//Use prevOffset to get index of previous solution from center point
			//Destination has the same row, col is 2^(current power) below center point
			arr[ntotaldim/2+row][ntotaldim/2-nOffset+col] = arr[ntotaldim / 2 + row - prevOffset][ntotaldim / 2 + col - prevOffset];
		}
	//Copy solution in clockwise rotation to Q1, skipping Q4
	for (int row = 0; row < nOffset; row++)
		for (int col = 0; col < nOffset; col++)
		{
			if (row >= nOffset / 2 && col >= nOffset / 2)
				continue;

			//Destination row start from 2^(current power) above center point
			//col is also 2^(current power) less than center point
			//Swap row and col to copy previous solution in clockwise manner
			arr[ntotaldim / 2 - nOffset + row][ntotaldim / 2 - nOffset + col] = arr[ntotaldim / 2 - col + prevOffset -1][ntotaldim / 2 + row - prevOffset];
		}

	//Copy solution in clockwise rotation to Q4, skipping Q1
	for (int row = 0; row < nOffset; row++)
		for (int col = 0; col < nOffset; col++)
		{
			if (row < nOffset / 2 && col < nOffset / 2)
				continue;
			//Destination row and col is at center point
			//Swap row and col to copy previous solution in anticlockwise manner
			arr[ntotaldim / 2 + row][ntotaldim / 2 + col] = arr[ntotaldim / 2 + col - prevOffset][ntotaldim / 2 - row + prevOffset - 1];
		}
}

// quadrant 
// 1  | 2
// ______
// 3  | 4
// driver program to test above function
int main()
{
	printf("[Dynamic Programing]\n");
	printf("After 10 iterations:\n");

	for (int i = 4; i <11; i++)
	{
		double total_time = 0.0;
		//Run 10 times to get average run time
		for (int j = 0; j < 10; j++)
		{
			duration<double, std::milli> time_span;

			memset(arr, 0, sizeof(arr));
			// power of grid dimension 2^ngridpow
			ngridpow = i;
			ntotaldim = pow(2, ngridpow);

			StartTime = high_resolution_clock::now();

			placeBaseCase(ntotaldim / 2, ntotaldim / 2);

			for (int i = 2; i < ngridpow; i++)
				copySolution(i);

			EndTime = high_resolution_clock::now();
			time_span = EndTime - StartTime;
			total_time += time_span.count();
		}

		total_time = total_time / 10.0;
		printf("Average Time for 2^%d : %.3f ms\n", i, total_time);
	}

	if (_mkdir("Display") == 0);
	//Comment out to save
	//saveOutput();
	getchar();
}
