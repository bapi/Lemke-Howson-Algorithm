#include <stdio.h>

#include <math.h>

#include <stdlib.h>

#include <time.h>

int main()
{

	int i, j, m, n, found, choice = 0, outing, temp;

	int piv_row_1=0, piv_col_1=0, piv_row_2=0, piv_col_2=0, exit_flg=0, count=0;

	double min_ratio, r, sum, pivot, piv_r_el;

	clock_t t1, t2;

	printf("\nEnter the size of the game:\n");

	printf("\nEnter m:\n");scanf("%d",&m);

	printf("\nEnter n:\n");scanf("%d",&n);

	double T_1[n][m+1],T_2[m][n+1],x[m],y[n],ratio_1[n],ratio_2[m];

	int nbv_1[m], nbv_2[n], bv_1[n], bv_2[m];

	for(i = 0; i < m; i++)
	{
		x[i] = (double)0.0;

		nbv_1[i] = i;

		bv_2[i] = i;
	}

	for(j = 0; j < n; j++)
	{ 
		y[j] = (double)0.0;
		
		nbv_2[j] = m + j;
		
		bv_1[j] = m + j;
	}

	//////////////////The two matrices///////////////////////////////////

	printf("\n\nTo input your own matrices enter 1 else to play with random matrices enter 2 : ");

	scanf("%d", &choice);

	//-------------------------------------------------------------------//

	/////////////////////Two tableaues////////////////////////////////////	

	if(choice == 1)
	{	
		printf("\nEnter A row-wise:\n");//e.g. for A[2][3] = {{0.5,0.6,1},{1.5,1,.75}}, enter 0.5, enter 0.6, enter 1, ..., enter 0.75.

		for(i = 0; i < m; i++)
		{ 
			for(j = 0; j < n; j++)
				scanf("%lf",&T_2[i][j]);

			T_2[i][n] = 1.0;
			
		}
	}
	else
		for(i = 0; i < m; i++)
		{
			for(j = 0; j < n; j++)
				T_2[i][j] = (1.f*(double)rand()) / RAND_MAX;
	
			T_2[i][n] = 1.0;
		}

	

	if(choice == 1)
	{	
		printf("\nEnter B row-wise:\n");

		for(i = 0; i < m; i++)
		{
			for(j = 0; j < n; j++)
				scanf("%lf",&T_1[j][i]);
				
		}

		for(j = 0; j < n; j++)T_1[j][m] = 1.0;
	}
	else
		for(j = 0; j < n; j++)
		{
			for(i = 0; i < m; i++)
				T_1[j][i] = (1.f*(double)rand()) / RAND_MAX;
				
			T_1[j][m] = 1.0;
		}

	printf("\n\n\n\n*************The pivotings go below******************\n\n");

	////////////////////////////////Pivoting/////////////////////////////////
	
	t1=clock();
	
	while(exit_flg == 0)
	{	
		count++;

		printf("\nNo of iterations=%d\n",count);
	
		min_ratio = (double)(1 << 30);
	
		for(i = 0; i < n; i++)
		{	
			if(T_1[i][piv_col_1] > 0)
			{
				r = T_1[i][m] / T_1[i][piv_col_1];

				ratio_1[i] = r;

				if(min_ratio > r)
				{
					min_ratio=r;

					piv_row_1=i;
				}
			}
			else
				ratio_1[i] = (double)(1 << 30);
		}

		if(fabs(min_ratio - (double)(1 << 30)) < (1 >> 25))
		{
			printf("\nThere is no leaving variable, so the L-H algo can not move further!\n");

			exit_flg = 1; break;
		}

		if (fabs(min_ratio - (double)(0.0)) < (1 >> 25))
			{
				printf("\nThe given game is degenerate!\n");

				exit_flg = 1; break;
			}

		pivot=T_1[piv_row_1][piv_col_1];

		temp = nbv_1[piv_col_1];
	
		nbv_1[piv_col_1] = bv_1[piv_row_1];
	
		outing = bv_1[piv_row_1];
	
		bv_1[piv_row_1] = temp;
		
		for(j = 0; j <= m; j++)
		{
			if(j != piv_col_1)
			{
				piv_r_el = T_1[piv_row_1][j];
			
				for(i = 0; i < n; i++)			
				{
					if(i != piv_row_1)
						T_1[i][j] = T_1[i][j] - T_1[i][piv_col_1] * piv_r_el / pivot;
					else
						T_1[i][j] = piv_r_el / pivot;
				}
			}
		}
	
		for(i = 0; i < n; i++)
			if(i != piv_row_1)
				T_1[i][piv_col_1] = -T_1[i][piv_col_1] / pivot;	
			else					
				T_1[i][piv_col_1] = 1 / pivot;
	
		found=0;
	
		for(i = 0; i < n; i++)
			if(nbv_2[i] == outing)
			{
				found = 1;

				piv_col_2=i;
				
				break;
			}

		if(found == 0)
			exit_flg = 1;
		else
		{	
			min_ratio = (double)(1 << 30);
		
			for(i = 0; i < m; i++)
			{	
				if(T_2[i][piv_col_2] > 0)
				{
					r = T_2[i][n] / T_2[i][piv_col_2];
					
					ratio_2[i] = r;

					if(min_ratio > r)
					{
						min_ratio = r;
					
						piv_row_2 = i;
					}
				}
				else 
					ratio_2[i] = (double)(1 << 30);
			}

			if(fabs(min_ratio - (double)(1 << 30)) < (1 >> 25))
			{
				printf("\nThere is no leaving variable, so the L-H algo can not move further!\n");

				exit_flg = 1; break;
			}

			if (fabs(min_ratio - (double)(0.0)) < (1 >> 25))
			{
				printf("\nThe given game is degenerate!\n");

				exit_flg = 1; break;
			}

			pivot=T_2[piv_row_2][piv_col_2];

			temp = nbv_2[piv_col_2];

			outing = bv_2[piv_row_2];

			nbv_2[piv_col_2] = bv_2[piv_row_2];

			bv_2[piv_row_2] = temp;	

			for(j = 0; j <= n; j++)
			{
				if(j != piv_col_2)
				{
					piv_r_el = T_2[piv_row_2][j];
				
					for(i = 0; i < m; i++)			
					{
						if(i != piv_row_2)
							T_2[i][j] = T_2[i][j] - T_2[i][piv_col_2] * piv_r_el / pivot;
						else
							T_2[i][j] = piv_r_el/pivot;
					}
				}
			}
	
			for(i = 0; i < m; i++)
				if(i != piv_row_2)
					T_2[i][piv_col_2] = -T_2[i][piv_col_2] / pivot;	
				else					
					T_2[i][piv_col_2] = 1 / pivot;

			found = 0;
	
			for(i = 0; i < m; i++)
				if(nbv_1[i] == outing)
				{
					found = 1;

					piv_col_1 = i; break;
				}		

			if(found == 0)
				exit_flg = 1;
		}		
	}
	
	sum = 0;

	for(i = 0; i < n; i++)
		if(bv_1[i] < m)
			{
				x[bv_1[i]] = T_1[i][m];
				
				sum = sum + x[bv_1[i]];
			}
			
	for(i = 0; i < m; i++)
		x[i] = x[i] / sum;
	
	sum = 0;

	for(i = 0; i < m; i++)
		if(bv_2[i] >= m)
		{
			y[bv_2[i] - m] = T_2[i][n];
			
			sum = sum + y[bv_2[i] - m];
		}

	for(i = 0; i < n; i++)
		y[i] = y[i] / sum;

	t2 = clock();

	printf("\n\nThe Nash equilibrium strategies of the given game are as follows:\n\n");

	printf("\nFor Player 1:");

	for(i = 0; i < m; printf("\tX_%d = %f,", i , x[i]), i++);

	printf("\n\n\nFor Player 2:");

	for(i = 0; i < n; printf("\tY_%d = %f,", i, y[i]), i++);

	printf("\nTime in seconds = %f\n", (1.0*(t2-t1))/CLOCKS_PER_SEC);

	printf("\nNo of iterations = %d\n", count);

	return 0;
}
