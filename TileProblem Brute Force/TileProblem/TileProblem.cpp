// tileproblem.cpp : defines the entry point for the console application.
//
//https://www.iarcs.org.in/inoi/online-study-material/topics/dp-tiling.php

#include "stdafx.h"
// c++ program to place tiles
#include <iostream>
#include<cmath>
#include <cstring>
#include <afx.h>
#include <direct.h>
#include<chrono>

using namespace std;
using namespace chrono;

int ngridpow,ntotaldim = 0, cnt = 0;
int arr[2048][2048];
high_resolution_clock::time_point StartTime, EndTime;

// placing tile at the given coordinates,xy is the top left coords of the base case
void placeBaseCase(int x, int y,int nSkipQ)
{
	switch (nSkipQ)
	{
	case 1:
		//Q2
		arr[x][y + 2] = 2;
		arr[x][y + 3] = 2;
		arr[x + 1][y + 3] = 2;
		//Q3
		arr[x + 2][y] = 4;
		arr[x + 3][y] = 4;
		arr[x + 3][y + 1] = 4;
		//Q4
		arr[x + 2][y + 3] = 3;
		arr[x + 3][y + 2] = 3;
		arr[x + 3][y + 3] = 3;
		//Center
		arr[x + 1][y + 2] = 1;
		arr[x + 2][y + 1] = 1;
		arr[x + 2][y + 2] = 1;
		break;
	case 2:
		//Q1
		arr[x][y] = 2;
		arr[x + 1][y] = 2;
		arr[x][y + 1] = 2;
		//Q3
		arr[x + 2][y] = 3;
		arr[x + 3][y] = 3;
		arr[x + 3][y + 1] = 3;
		//Q4
		arr[x + 2][y + 3] = 4;
		arr[x + 3][y + 2] = 4;
		arr[x + 3][y + 3] = 4;
		//Center
		arr[x + 1][y + 1] = 1;
		arr[x + 2][y + 1] = 1;
		arr[x + 2][y + 2] = 1;
		break;
	case 3:
		//Q1
		arr[x][y] = 4;
		arr[x + 1][y] = 4;
		arr[x][y + 1] = 4;
		//Q2
		arr[x][y + 2] = 3;
		arr[x][y + 3] = 3;
		arr[x + 1][y + 3] = 3;
		//Q4
		arr[x + 2][y + 3] = 2;
		arr[x + 3][y + 2] = 2;
		arr[x + 3][y + 3] = 2;
		//Center
		arr[x + 1][y + 1] = 1;
		arr[x + 1][y + 2] = 1;
		arr[x + 2][y + 2] = 1;
		break;
	case 4:
		//Q1
		arr[x][y] = 3;
		arr[x + 1][y] = 3;
		arr[x][y + 1] = 3;
		//Q2
		arr[x][y + 2] = 4;
		arr[x][y + 3] = 4;
		arr[x + 1][y + 3] = 4;
		//Q3
		arr[x + 2][y] = 2;
		arr[x + 3][y] = 2;
		arr[x + 3][y + 1] = 2;
		//Center
		arr[x + 1][y + 1] = 1;
		arr[x + 1][y + 2] = 1;
		arr[x + 2][y + 1] = 1;
		break;
	default:
		break;
	}
	//if (nSkipQ != 1)
	//{
	//	cnt++;
	//	arr[x][y] = cnt;
	//	arr[x + 1][y] = cnt;
	//	arr[x][y + 1] = cnt;
	//}

	//if (nSkipQ != 2)
	//{
	//	cnt++;
	//	arr[x][y + 2] = cnt;
	//	arr[x][y + 3] = cnt;
	//	arr[x + 1][y + 3] = cnt;
	//}

	//if (nSkipQ != 3)
	//{
	//	cnt++;
	//	arr[x + 2][y] = cnt;
	//	arr[x + 3][y] = cnt;
	//	arr[x + 3][y + 1] = cnt;
	//}

	//if (nSkipQ != 4)
	//{
	//	cnt++;
	//	arr[x + 2][y + 3] = cnt;
	//	arr[x + 3][y + 2] = cnt;
	//	arr[x + 3][y + 3] = cnt;
	//}

	//cnt++;
	//if(nSkipQ != 1)arr[x + 1][y + 1] = cnt;
	//if (nSkipQ != 2)arr[x + 1][y + 2] = cnt;
	//if (nSkipQ != 3)arr[x + 2][y + 1] = cnt;
	//if (nSkipQ != 4)arr[x + 2][y + 2] = cnt;
}

//place a 3x2 block that stacks twwo tromino vertically
void place3X2Block(int x, int y)
{
	//cnt++;
	arr[x][y] = 1;
	arr[x+1][y] = 1;
	arr[x][y + 1] = 1;

	//cnt++;
	arr[x + 1][y + 1] = 2;
	arr[x + 2][y] = 2;
	arr[x + 2][y + 1] = 2;
}

//place a 2x3 block that stacks twwo tromino horizontally
void place2X3Block(int x, int y)
{
	//cnt++;
	arr[x][y] = 3;
	arr[x + 1][y] = 3;
	arr[x][y + 1] = 3;

	//cnt++;
	arr[x + 1][y + 1] = 4;
	arr[x][y + 2] = 4;
	arr[x+1][y+2] = 4;
}

void saveOutput()
{
	CString szAppPath;
	LPTSTR pBuffer = szAppPath.GetBuffer(255);
	GetCurrentDirectory(255, pBuffer);
	szAppPath.ReleaseBuffer();

	CString szSrc = _T("");
	szSrc = szAppPath + _T("\\Display\\") + _T("DPResult.csv");
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
// quadrant 
// 1  | 2
// ______
// 3  | 4

// driver program to test above function
int main()
{
	printf("[Brute Force]\n");
	printf("After 10 iterations:\n");

	//Run 10 times to get average run time
	for (int i = 4; i < 11; i++)
	{
		double total_time = 0.0;

		for (int j = 0; j < 10; j++)
		{
			duration<double, std::milli> time_span;

			memset(arr, 0, sizeof(arr));
			// power of grid dimension 2^ngridpow
			ngridpow = i;
			ntotaldim = pow(2, ngridpow);
			// Starting Row index for areas besides base case
			int nStartIdxBesidesBC = 0;
			// Last Row index for areas besides base case
			int nEndIdxBesidesBC = 0;
			// Starting Col index for areas besides base case
			int nStartIdyBesidesBC = 0;
			// Last Col index for areas besides base case
			int nEndIdyBesidesBC = 0;

			//Flag for odd power
			bool bOddPower = 0;

			StartTime = high_resolution_clock::now();

			//If odd exponential
			if (ngridpow % 2)
			{
				//Base case for odd has 8X4+4X4 dimension
				nStartIdxBesidesBC = (ntotaldim - 8) / 2;
				nEndIdxBesidesBC = nStartIdxBesidesBC + 7;
				nStartIdyBesidesBC = ntotaldim / 2 - 4;
				nEndIdyBesidesBC = nStartIdyBesidesBC + 7;
				bOddPower = 1;
			}
			//If even exponential
			else
			{
				//Base case for even has 4X2+2X2 dimension
				nStartIdxBesidesBC = (ntotaldim - 4) / 2;
				//ALthough is 4 row, but index wise the last idx is plus 3
				nEndIdxBesidesBC = nStartIdxBesidesBC + 3;
				nStartIdyBesidesBC = ntotaldim / 2 - 2;
				nEndIdyBesidesBC = nStartIdyBesidesBC + 3;
			}

			//printf("X start:%d,X End: %d,Y start :%d,Y end:%d\n",nStartIdxBesidesBC,nEndIdxBesidesBC,nStartIdyBesidesBC,nEndIdyBesidesBC);
			int row = 0, col = 0;

			while (row <= ntotaldim && col <= ntotaldim)
			{
				//Skip Q2 area
				if (row < ntotaldim / 2 && col >= ntotaldim / 2)
				{
					//go down 2 rows in areas besides base case as 2x3 block is used, else 3 rows as 3x2 block is used
					if (row<nStartIdyBesidesBC || row>nEndIdyBesidesBC)
						row += 3;
					else
						row += 2;
					//reset col to left hand size
					col = 0;
				}
				//Skip the base case area.
				else if (row >= nStartIdxBesidesBC && row <= nEndIdxBesidesBC && col >= nStartIdyBesidesBC && col <= nEndIdyBesidesBC)
				{
					//jump 8 columns for odd,4 column for even
					if (bOddPower)
						col += 8;
					else
						col += 4;
				}
				//Areas besides base case.
				else if (row >= nStartIdxBesidesBC && row <= nEndIdxBesidesBC && (col < nStartIdyBesidesBC || col > nEndIdyBesidesBC))
				{
					//Areas besides base case need to use 2x3 blocks
					place2X3Block(row, col);
					//Index 3 columns
					col += 3;

					//Reach the right most,reset to first column
					if (col >= ntotaldim - 1)
					{
						//Index to 2 rows below
						row += 2;
						//Reset col to 0
						col = 0;
					}
				}
				//Other areas
				else
				{
					//Other areas use 3x2 blocks to fill the area greedily
					place3X2Block(row, col);
					col += 2;
					//Index 3 rows down and reset column when reaches the right most
					if (col >= ntotaldim - 1)
					{
						row += 3;
						col = 0;
					}
				}
			}

			//Put base case here
			if (!bOddPower)
			{
				//Place base case at middle, skip Q2
				placeBaseCase(ntotaldim / 2 - 2, ntotaldim / 2 - 2, 2);
			}
			else
			{
				//Place base case at middle,Skip Q2
				placeBaseCase(ntotaldim / 2 - 2, ntotaldim / 2 - 2, 2);
				//Place base case at Q1,skip Q4
				placeBaseCase(ntotaldim / 2 - 4, ntotaldim / 2 - 4, 4);
				//Place base case at Q3,skip Q2
				placeBaseCase(ntotaldim / 2, ntotaldim / 2 - 4, 2);
				//Place base case at Q4,skip Q1
				placeBaseCase(ntotaldim / 2, ntotaldim / 2, 1);
			}
			EndTime = high_resolution_clock::now();
			time_span = EndTime - StartTime;
			total_time += time_span.count();
			//printf("Iteration %d: Time for 2^%d : %.3f ms\n",j+1 , i, time_span.count());
		}
		total_time = total_time / 10.0;
		printf("Average Time for 2^%d : %.3f ms\n", i, total_time);
	}

	if (_mkdir("Display") == 0);
	//Comment out to save
		saveOutput();
	getchar();
}
