// tileproblem.cpp : defines the entry point for the console application.
//
//https://www.iarcs.org.in/inoi/online-study-material/topics/dp-tiling.php

#include "stdafx.h"
// c++ program to place tiles
#include <iostream>
#include<cmath>
//#include<winbase.h>
#include <cstring>
#include <afx.h>
#include <direct.h>
using namespace std;

/*int ngridpow, ntotaldim = 0, nIteration = 0, cnt = 0;
int arr[1024][1024];
int gcnt = 0;

// placing tile at the given coordinates,xy is the top left coords of the base case
void placeBaseCase(int x, int y, int nSkipQ)
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
	//cnt = 0;
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

void saveOutput(int ncnt)
{
	CString szAppPath;
	LPTSTR pBuffer = szAppPath.GetBuffer(255);
	GetCurrentDirectory(255, pBuffer);
	szAppPath.ReleaseBuffer();

	CString szSrc = _T("");
	CString sz;
	sz.Format(_T("%d"), ncnt);
	szSrc = szAppPath + _T("\\Display\\DPResult") + sz + _T(".csv");
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

void recursiveCall(int x, int y, int nSkipQ, int nPower, int origin)
{
	//Quarter: work for 2^4 ,2^6 only, but not 2^5 or 2^8,9 or 10 will infinite loop
	//Odd -1 , even -2 ??
	if (nPower == ngridpow - 1)
	{
		switch (origin)
		{
		case 1:
			if (nSkipQ != 4)return;
			break;
		case 2:
			if (nSkipQ != 3)return;
			break;
		case 3:
			if (nSkipQ != 2)return;
			break;
		case 4:
			if (nSkipQ != 1)return;
			break;
		default:break;
		}
	}

	gcnt++;
	saveOutput(gcnt);

	//Skip placeBaseCase for the first time of recursiveCall,as the base case is placed before entering the recursiveCall.
	if (nPower != 0)
		placeBaseCase(x - 2, y - 2, nSkipQ);

	//If Q1 is not skipped,placeBaseCase at Q1
	if (nSkipQ != 1)
		placeBaseCase(x - 4, y - 4, 4);
	//If Q2 is not skipped,placeBaseCase at Q2
	if (nSkipQ != 2)
		placeBaseCase(x - 4, y, 3);
	//If Q3 is not skipped,placeBaseCase at Q3
	if (nSkipQ != 3)
		placeBaseCase(x, y - 4, 2);
	//If Q4 is not skipped,placeBaseCase at Q4
	if (nSkipQ != 4)
		placeBaseCase(x, y, 1);

	//Make sure we do not exceed the iteration calculated, before calling the next recursiveCall
	if (nPower + 1 < nIteration)
	{
		//For even number of iteration only, we do recursiveCall for other 3 quadrants 
		//For odd number of iteration,we just do recursiveCall in one direction only
		if ((nPower + 1) % 2)
		{
			//Do recursiveCall on Q1
			if (nSkipQ != 1)
			{
				printf("Q1RQ 3Q:Power %d  Origin :%d\n", nPower + 1, origin);
				//Only initialize the origin for the first time
				if (nPower == 0)
					recursiveCall(x - 4, y - 4, 4, nPower + 1, 1);
				else
					recursiveCall(x - 4, y - 4, 4, nPower + 1, origin);
			}
			//Do recursiveCall on Q2
			if (nSkipQ != 2)
			{
				printf("Q2RQ 3Q:Power %d Origin :%d\n", nPower + 1, origin);
				if (nPower == 0)
					recursiveCall(x - 4, y + 4, 3, nPower + 1, 2);
				else
					recursiveCall(x - 4, y + 4, 3, nPower + 1, origin);
			}
			//Do recursiveCall on Q3
			if (nSkipQ != 3)
			{
				printf("Q3RQ 3Q:Power %d Origin :%d\n", nPower + 1, origin);
				if (nPower == 0)
					recursiveCall(x + 4, y - 4, 2, nPower + 1, 3);
				else
					recursiveCall(x + 4, y - 4, 2, nPower + 1, origin);
			}
			//Do recursiveCall on Q4
			if (nSkipQ != 4)
			{
				printf("Q4RQ 3Q:Power %d Origin :%d\n", nPower + 1, origin);
				if (nPower == 0)
					recursiveCall(x + 4, y + 4, 1, nPower + 1, 4);
				else
					recursiveCall(x + 4, y + 4, 1, nPower + 1, origin);
			}
		}
		else
		{
			//Continue recursiveCall in Q1 direction
			if (nSkipQ == 4)
			{
				printf("Q1RQ DG:Power %d\n", nPower + 1);
				recursiveCall(x - 4, y - 4, 4, nPower + 1, origin);
			}
			//Since this is specific tiling problem with Q2 disabled.
			else if (nSkipQ == 3)
			{
				printf("Q2RQ DG:Power %d\n", nPower + 1);
				recursiveCall(x - 4, y + 4, 3, nPower + 1, origin);
			}
			//Continue recursiveCall in Q3 direction
			else if (nSkipQ == 2)
			{
				printf("Q3RQ DG:Power %d\n", nPower + 1);
				recursiveCall(x + 4, y - 4, 2, nPower + 1, origin);
			}
			//Continue recursiveCall in Q4 direction
			else if (nSkipQ == 1)
			{
				printf("Q4RQ DG:Power %d\n", nPower + 1);
				recursiveCall(x + 4, y + 4, 1, nPower + 1, origin);
			}
		}
	}
}
// quadrant 
// 1  | 2
// ______
// 3  | 4
// driver program to test above function
int main()
{
	memset(arr, 0, sizeof(arr));
	// power of grid dimension 2^ngridpow
	ngridpow = 7;
	ntotaldim = pow(2, ngridpow);
	//Times to run the recursiveCall function
	nIteration = pow(2, ngridpow - 3);
	//Put base case at middle,Skip Q2
	placeBaseCase(ntotaldim / 2 - 2, ntotaldim / 2 - 2, 2);

	//Proceed with recursiveCall for 2^3 and above
	if (ngridpow>2)
		recursiveCall(ntotaldim / 2, ntotaldim / 2, 2, 0, 0);

	if (_mkdir("Display") == 0);
	gcnt++;
	saveOutput(gcnt);
	getchar();
}
*/