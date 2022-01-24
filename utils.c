// Copyright 2021 - 2022 Preda Diana 314CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "photo.h"

#define AMAX 3
#define BMAX 20
#define CMAX 200
#define DMAX 4

double **alloc_matrix(int height, int width)
{
	double **matrix;
	matrix = (double **)malloc(height * sizeof(double *));
	// check if the matrix was loaded
	if (!matrix) {
		fprintf(stderr, "malloc() failed\n");
		return NULL;
	}
	for (int i = 0; i < height; i++) {
		matrix[i] = (double *)malloc(width * sizeof(double));
		if (!matrix[i]) {
			// free if the malloc failed
			fprintf(stderr, "malloc() failed\n");
			for (int j = 0; j < i; j++)
				free(matrix[j]);
		free(matrix);
		return NULL;
		}
		for (int j = 0; j < width; j++)
			matrix[i][j] = 0;
	}
	return matrix;
}

void free_matrix_grayscale(photo *color_aux, int height)
{
	photo color = *color_aux;
	for (int i = 0; i < height; i++)
		free(color.matrix[i]);
	free(color.matrix);
}

void free_matrix_colored(photo *color_aux, int height)
{
	photo color = *color_aux;
	for (int i = 0; i < height; i++)
		free(color.R[i]);
	free(color.R);
	for (int i = 0; i < height; i++)
		free(color.G[i]);
	free(color.G);
	for (int i = 0; i < height; i++)
		free(color.B[i]);
	free(color.B);
}

void free_action(photo *color, int height, int loaded)
{
	if (loaded == 1)
		free_matrix_grayscale(color, height);
	if (loaded == 2)
		free_matrix_colored(color, height);
}

void free_matrix(double ***matrixa, int height)
{
	double **matrix = *matrixa;
	for (int i = 0; i < height; i++)
		free(matrix[i]);
	free(matrix);
}

void free_loaded(double ***sel, int *cds, int loaded)
{
	if (loaded == 1) {
		free_matrix(&sel[0], cds[3] - cds[1]);
	} else if (loaded == 2) {
		free_matrix(&sel[0], cds[3] - cds[1]);
		free_matrix(&sel[1], cds[3] - cds[1]);
		free_matrix(&sel[2], cds[3] - cds[1]);
	}
}

void wrong_arg(void)
{
	char comments;
	do {
		fscanf(stdin, "%c", &comments);
	} while (comments != '\n');
}

void check_comments(FILE *filename)
{
	char comments;
	fscanf(filename, "%c", &comments);
	if (comments == '#')
		wrong_arg();
	else
		fseek(filename, -1, SEEK_CUR);
}
