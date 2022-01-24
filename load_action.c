// Copyright 2021 - 2022 Preda Diana 314CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "select_action.h"
#include "photo.h"

#define AMAX 3
#define BMAX 20
#define CMAX 200
#define DMAX 4

double **load_ascii(int width, int height, FILE *filename)
{
	double **matrix = alloc_matrix(height, width);

	if (!matrix) {
		printf("malloc() failed\n");
		return NULL;
	}

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			fscanf(filename, "%lf", &matrix[i][j]);

	return matrix;
}

double **load_binary(int width, int height, FILE *filename)
{
	double **matrix = alloc_matrix(height, width);

	if (!matrix) {
		printf("malloc() failed\n");
		return NULL;
	}

	unsigned char tmp;

	fread(&tmp, sizeof(unsigned char), 1, filename);

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			fread(&tmp, sizeof(unsigned char), 1, filename);
			matrix[i][j] = (double)tmp;
		}

	return matrix;
}

void load_ascii_rgb(int width, int height, FILE *filename, photo *color)
{
	color->R = alloc_matrix(height, width);
	color->G = alloc_matrix(height, width);
	color->B = alloc_matrix(height, width);

	if (!color->R || !color->G || !color->B) {
		printf("malloc() failed\n");
		return;
	}

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			fscanf(filename, "%lf", &color->R[i][j]);
			fscanf(filename, "%lf", &color->G[i][j]);
			fscanf(filename, "%lf", &color->B[i][j]);
		}
}

void load_binary_rgb(int width, int height, FILE *filename, photo *color)
{
	color->R = alloc_matrix(height, width);
	color->G = alloc_matrix(height, width);
	color->B = alloc_matrix(height, width);

	if (!color->R || !color->G || !color->B) {
		printf("malloc() failed\n");
		return;
	}

	unsigned char tmp1, tmp2, tmp3;

	fread(&tmp1, sizeof(unsigned char), 1, filename);

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			fread(&tmp1, sizeof(unsigned char), 1, filename);
			fread(&tmp2, sizeof(unsigned char), 1, filename);
			fread(&tmp3, sizeof(unsigned char), 1, filename);
			color->R[i][j] = (double)tmp1;
			color->G[i][j] = (double)tmp2;
			color->B[i][j] = (double)tmp3;
		}
}

void load_action(photo *color, char *filename, int *width, int *height,
				 int *loaded, int *maxvalue, char *type
				, double ***sel, int *cds)
{
	FILE *f = fopen(filename, "rb");

	// check if the file can be open
	if (!f) {
		fprintf(stdout, "Failed to load %s\n", filename);
		free_action(color, *height, *loaded);
		free_loaded(sel, cds, *loaded);
		*loaded = 0;
	} else {
		// free previous image if necessary
		free_action(color, *height, *loaded);
		free_loaded(sel, cds, *loaded);

		// check for comments

		check_comments(f);
		fscanf(f, "%s", type);
		check_comments(f);
		fscanf(f, "%d%d", width, height);
		check_comments(f);
		fscanf(f, "%d", maxvalue);
		check_comments(f);

		// loaded = 1 stands for grayscale
		// loaded = 2 stands for rgb
		if (strcmp(type, "P2") == 0) {
			// load a grayscale image in ascii

			color->matrix = load_ascii(*width, *height, f);

			*loaded = 1;

			select_all(color, cds, sel, *width, *height, loaded);

			fprintf(stdout, "Loaded %s\n", filename);

		} else if (strcmp(type, "P3") == 0) {
			// load an rgb image in ascii

			load_ascii_rgb(*width, *height, f, color);

			*loaded = 2;

			select_all(color, cds, sel, *width, *height, loaded);

			fprintf(stdout, "Loaded %s\n", filename);

		} else if (strcmp(type, "P5") == 0) {
			// load a grayscale image in binary

			color->matrix = load_binary(*width, *height, f);

			*loaded = 1;

			select_all(color, cds, sel, *width, *height, loaded);

			fprintf(stdout, "Loaded %s\n", filename);

		} else if (strcmp(type, "P6") == 0) {
			// load an rgb image in binary

			load_binary_rgb(*width, *height, f, color);

			*loaded = 2;

			select_all(color, cds, sel, *width, *height, loaded);

			fprintf(stdout, "Loaded %s\n", filename);

		} else {
			printf("Cannot load %s", filename);
		}
		fclose(f);
	}
}
