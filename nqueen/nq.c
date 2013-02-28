/**
 * Program to solve the N-Queen problem in C
 * Includes a "replay" feature also a performance measure
 *
 * Author : Ahmed Azaan (azaan@outlook.com)
 * Feb-2013
 *
 * This program was written as a means of visualizing backtracking algorithms
 * and not as a high performance N-Queen solution generator.
 *
 **/

#define _BSD_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>

#define C_BOLD_RED "\e[1;31m"
#define C_RESET "\e[m"

#define MAX_GRID 30

#define QUEEN true
#define EMPTY false

bool solve();
void draw();
bool valid(int, int);
double calculate(const struct rusage*, const struct rusage*);

// global game structure to avoid cluttering namespace
struct
{
	int n;
	bool grid[MAX_GRID][MAX_GRID];

	bool performance;
	bool replay;

	int sleep;

	int recurse;
	int verify;

	double t_cpu;
}
g;

int main(int argc, char *argv[])
{
	// initializations
	g.replay = true;
	g.performance = false;

	g.sleep = 500 * 1000;
	g.recurse = 0;
	g.verify = 0;

	// parse arguments
	if (argc >= 2)
	{
		g.n = atoi(argv[1]);

		if (g.n > MAX_GRID)
		{
			printf("Increase MAX_GRID and recompile!\n");
			return 1;
		}

		if (argc == 3)
			if (argv[2][1] == 'q')
			{
				g.replay = false;
				g.performance = true;
			}
			else if (argv[2][1] == 't')
			{
				g.sleep = atoi(&argv[2][2]) * 1000;

			}
	}
	else
	{
		printf("Usage : %s N [-q|-t(MS)]\n", argv[0]);
		printf("\t-q = Quiet Mode (no output with performance measure)\n");
		printf("\t-t(MS) = Time in milisecond for replay movements (no effect with -q)\n");
		printf("\n\tEg: %s 5 -q\n", argv[0]);
		printf("\tEg: %s 5 -t200\n", argv[0]);
		return 1;
	}

	if (solve())
		draw();
	else
		printf("No solution for %d-Queen Problem\n", g.n);

	if (g.performance)
		printf("CPU time         : %.6fs", g.t_cpu);

	printf("\n\n");
	return 0;
}

/**
 * Draws the board on the screen with some stats
 **/
void draw()
{
	system("clear");
	for (int i = 0; i < g.n; i++)
	{
		printf("\n\t");
		for (int j = 0; j < g.n; j++)
			if (g.grid[i][j] == QUEEN)
				printf(C_BOLD_RED " X " C_RESET);
			else
				printf(" . ");
	}

	printf("\n\nRecursive calls  : %d\n", g.recurse);
	printf("Validation calls : %d\n", g.verify);
}

/**
 * Recursively solve nqueens using a backtracking algorithm
 **/
bool nqueen(int row)
{
	g.recurse++;

	if (g.replay)
	{
		draw();
		usleep(g.sleep);
	}

	// if we have finished all rows, we have succeded
	if (row >= g.n)
		return true;

	for (int i = 0; i < g.n; i++)
	{
		g.grid[row][i] = QUEEN;

		if (valid(row, i) && nqueen(row+1))
			return true;
		else
			g.grid[row][i] = EMPTY;
	}

	return false;
}

/**
 * Decorator for nqueen function also measures performance of nqueen()
 **/
bool solve()
{
	struct rusage before, after;

	getrusage(RUSAGE_SELF, &before);
	bool result =  nqueen(0);
	getrusage(RUSAGE_SELF, &after);

	g.t_cpu = calculate(&before, &after);
	return result;
}

/**
 * Validates a g.grid for (i, j) value
 * Returns: true for no violation of constraints, false otherwise
 **/
bool valid(int row, int col)
{
	g.verify++;

	// row validation implied by backtracking algorithm

	// column validation
	int count = 0;
	for (int i = 0; i < g.n; i++)
		if (g.grid[i][col] == QUEEN && ++count > 1)
			return false;

	// diagonals

	// left up
	for (int i = row-1, j = col-1; i >= 0 && j >= 0; i--, j--)
		if (g.grid[i][j] == QUEEN)
			return false;

	// right up
	for (int i = row-1, j = col+1; i >= 0 && j < g.n; i--, j++)
		if (g.grid[i][j] == QUEEN)
			return false;

	// no violations if we reached till here
	return true;
}

/**
 * credit: CS50-Harvard
 * Returns number of seconds between b and a.
 **/
double calculate(const struct rusage* b, const struct rusage* a)
{
    if (b == NULL || a == NULL)
    {
        return 0.0;
    }
    else
    {
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                 (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                 (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
                / 1000000.0);
    }
}