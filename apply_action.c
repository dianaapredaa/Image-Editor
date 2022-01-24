// Copyright 2021 - 2022 Preda Diana 314CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "utils.h"
#include "photo.h"

#define AMAX 4
#define BMAX 20
#define CMAX 200
#define DMAX 20
#define MIN 0
#define MAX 255

double clamp(double x)
{
	if (x < MIN)
		x = MIN;
	else if (x > MAX)
		x = MAX;
	return x;
}

void apply_edge(photo *color, double ***sel, int *cds, int wd, int ht)
{
	// create the kernel matrix for edge
	double sum;
	int edge[AMAX][AMAX];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			edge[i][j] = -1;
	edge[1][1] = 8;

	for (int i = cds[1]; i < cds[3]; i++)
		for (int j = cds[0]; j < cds[2]; j++)
			if (i > 0 && j > 0 && i < ht - 1 && j < wd - 1) {
				// initialize the sum
				sum = 0;
				for (int k = 0; k < 3; k++)
					for (int p = 0; p < 3; p++)
						// sum the pixels from the 3 * 3 matrxi formed around
						// the pixel we work on
						sum = sum + edge[k][p] * color->R[i + k - 1][j + p - 1];
				// use clamp function to check if the values exceed the
				// maximum or minimum allowed
				sel[0][i - cds[1]][j - cds[0]] = clamp(sum);

				sum = 0;
				for (int k = 0; k < 3; k++)
					for (int p = 0; p < 3; p++)
						sum = sum + edge[k][p] * color->G[i + k - 1][j + p - 1];
				sel[1][i - cds[1]][j - cds[0]] = clamp(sum);

				sum = 0;
				for (int k = 0; k < 3; k++)
					for (int p = 0; p < 3; p++)
						sum = sum + edge[k][p] * color->B[i + k - 1][j + p - 1];
				sel[2][i - cds[1]][j - cds[0]] = clamp(sum);
			}
	// copy the new values back in the main matrix
	for (int i = cds[1]; i < cds[3]; i++)
		for (int j = cds[0]; j < cds[2]; j++) {
			color->R[i][j] = sel[0][i - cds[1]][j - cds[0]];
			color->G[i][j] = sel[1][i - cds[1]][j - cds[0]];
			color->B[i][j] = sel[2][i - cds[1]][j - cds[0]];
		}
	printf("APPLY EDGE done\n");
}

void apply_sharpen(photo *color, double ***sel, int *cds, int wd, int ht)
{
	// create the kernel matrix for sharpen
	double sum;
	int sharpen[AMAX][AMAX];
	sharpen[0][0] = 0;
	sharpen[0][1] = -1;
	sharpen[0][2] = 0;
	sharpen[1][0] = -1;
	sharpen[1][1] = 5;
	sharpen[1][2] = -1;
	sharpen[2][0] = 0;
	sharpen[2][1] = -1;
	sharpen[2][2] = 0;

	for (int i = cds[1]; i < cds[3]; i++)
		for (int j = cds[0]; j < cds[2]; j++)
			if (i > 0 && j > 0 && i < ht - 1 && j < wd - 1) {
				// initialize the sum
				sum = 0;
				for (int k = 0; k < 3; k++)
					for (int p = 0; p < 3; p++)
						// sum the pixels from the 3 * 3 matrxi formed around
						// the pixel we work on
						sum = sum + sharpen[k][p] *
							color->R[i + k - 1][j + p - 1];
				// use clamp function to check if the values exceed the
				// maximum or minimum allowed
				sel[0][i - cds[1]][j - cds[0]] = clamp(sum);

				sum = 0;
				for (int k = 0; k < 3; k++)
					for (int p = 0; p < 3; p++)
						sum = sum + sharpen[k][p] *
							color->G[i + k - 1][j + p - 1];
				sel[1][i - cds[1]][j - cds[0]] = clamp(sum);

				sum = 0;
				for (int k = 0; k < 3; k++)
					for (int p = 0; p < 3; p++)
						sum = sum + sharpen[k][p] *
							color->B[i + k - 1][j + p - 1];
				sel[2][i - cds[1]][j - cds[0]] = clamp(sum);
			}
	// copy the new values back in the main matrix
	for (int i = cds[1]; i < cds[3]; i++)
		for (int j = cds[0]; j < cds[2]; j++) {
			color->R[i][j] = sel[0][i - cds[1]][j - cds[0]];
			color->G[i][j] = sel[1][i - cds[1]][j - cds[0]];
			color->B[i][j] = sel[2][i - cds[1]][j - cds[0]];
		}

	printf("APPLY SHARPEN done\n");
}

void apply_blur(photo *color, double ***sel, int *cds, int wd, int ht)
{
	// create the kernel matrix for blur
	double sum;
	int blur[AMAX][AMAX];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			blur[i][j] = 1;

	for (int i = cds[1]; i < cds[3]; i++)
		for (int j = cds[0]; j < cds[2]; j++)
			if (i > 0 && j > 0 && i < ht - 1 && j < wd - 1) {
				// initialize the sum
				sum = 0;
				for (int k = 0; k < 3; k++)
					for (int p = 0; p < 3; p++)
						// sum the pixels from the 3 * 3 matrxi formed around
						// the pixel we work on
						sum = sum + blur[k][p] *
							color->R[i + k - 1][j + p - 1];
				// use clamp function to check if the values exceed the
				// maximum or minimum allowed
				sel[0][i - cds[1]][j - cds[0]] = clamp(sum / 9.0);

				sum = 0;
				for (int k = 0; k < 3; k++)
					for (int p = 0; p < 3; p++)
						sum = sum + blur[k][p] *
							color->G[i + k - 1][j + p - 1];
				sel[1][i - cds[1]][j - cds[0]] = clamp(sum / 9.0);

				sum = 0;
				for (int k = 0; k < 3; k++)
					for (int p = 0; p < 3; p++)
						sum = sum + blur[k][p] *
							color->B[i + k - 1][j + p - 1];
				sel[2][i - cds[1]][j - cds[0]] = clamp(sum / 9.0);
			}
	// copy the new values back in the main matrix
	for (int i = cds[1]; i < cds[3]; i++)
		for (int j = cds[0]; j < cds[2]; j++) {
			color->R[i][j] = sel[0][i - cds[1]][j - cds[0]];
			color->G[i][j] = sel[1][i - cds[1]][j - cds[0]];
			color->B[i][j] = sel[2][i - cds[1]][j - cds[0]];
		}

	printf("APPLY BLUR done\n");
}

void apply_gaussian_blur(photo *color, double ***sel, int *cds,
						 int wd, int ht)
{
	// create the kernel matrix for gaussian_blur
	double sum;
	int gauss[AMAX][AMAX];
	gauss[0][0] = 1;
	gauss[0][1] = 2;
	gauss[0][2] = 1;
	gauss[1][0] = 2;
	gauss[1][1] = 4;
	gauss[1][2] = 2;
	gauss[2][0] = 1;
	gauss[2][1] = 2;
	gauss[2][2] = 1;

	for (int i = cds[1]; i < cds[3]; i++)
		for (int j = cds[0]; j < cds[2]; j++)
			if (i > 0 && j > 0 && i < ht - 1 && j < wd - 1) {
				// initialize the sum
				sum = 0;
				for (int k = 0; k < 3; k++)
					for (int p = 0; p < 3; p++)
						// sum the pixels from the 3 * 3 matrxi formed around
						// the pixel we work on
						sum = sum + gauss[k][p] *
							color->R[i + k - 1][j + p - 1];
				// use clamp function to check if the values exceed the
				// maximum or minimum allowed
				sel[0][i - cds[1]][j - cds[0]] = clamp(sum / 16.0);

				sum = 0;
				for (int k = 0; k < 3; k++)
					for (int p = 0; p < 3; p++)
						sum = sum + gauss[k][p] *
							color->G[i + k - 1][j + p - 1];
				sel[1][i - cds[1]][j - cds[0]] = clamp(sum / 16.0);

				sum = 0;
				for (int k = 0; k < 3; k++)
					for (int p = 0; p < 3; p++)
						sum = sum + gauss[k][p] *
							color->B[i + k - 1][j + p - 1];
				sel[2][i - cds[1]][j - cds[0]] = clamp(sum / 16.0);
			}
	// copy the new values back in the main matrix
	for (int i = cds[1]; i < cds[3]; i++)
		for (int j = cds[0]; j < cds[2]; j++) {
			color->R[i][j] = sel[0][i - cds[1]][j - cds[0]];
			color->G[i][j] = sel[1][i - cds[1]][j - cds[0]];
			color->B[i][j] = sel[2][i - cds[1]][j - cds[0]];
		}

	printf("APPLY GAUSSIAN_BLUR done\n");
}

void apply_action(photo *color, double ***sel, int *cds, int loaded,
				  int ht, int wd)
{
	char arg[DMAX];
	fgets(arg, DMAX, stdin);
	// check if there is any parameter
	if (arg[0] == '\n') {
		printf("Invalid command\n");
	} else {
		// check if the image is rgb
		if (loaded == 2) {
			// choose the type of filter
			if (strstr(arg, "EDGE"))
				apply_edge(color, sel, cds, wd, ht);

			else if (strstr(arg, "SHARPEN"))
				apply_sharpen(color, sel, cds, wd, ht);

			else if (strstr(arg, "GAUSSIAN_BLUR"))
				apply_gaussian_blur(color, sel, cds, wd, ht);

			else if (strstr(arg, "BLUR"))
				apply_blur(color, sel, cds, wd, ht);
			else
				printf("APPLY parameter invalid\n");

		} else {
			printf("Easy, Charlie Chaplin\n");
		}
	}
}
