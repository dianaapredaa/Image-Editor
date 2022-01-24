// Copyright 2021 - 2022 Preda Diana 314CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"
#include "photo.h"

#define AMAX 3
#define BMAX 20
#define CMAX 200
#define DMAX 4

int validate_and_swap_coordinates(int wd, int ht,
								  char tmp_cds[4][10], int cds[4])
{
	for (int i = 0; i < 4; i++)
		for (unsigned int j = 0; j < strlen(tmp_cds[i]); j++)
			if (isdigit(tmp_cds[i][j]) == 0 && tmp_cds[i][j] != '-') {
				printf("Invalid command\n");
				return 0;
			}

	for (int i = 0; i < 4; i++)
		cds[i] = atoi(tmp_cds[i]);

	if (cds[0] > cds[2]) {
		int aux = cds[0];
		cds[0] = cds[2];
		cds[2] = aux;
	}
	if (cds[1] > cds[3]) {
		int aux = cds[1];
		cds[1] = cds[3];
		cds[3] = aux;
	}

	if (cds[0] > wd) {
		printf("Invalid set of coordinates\n");
		return 0;
	} else if (cds[1] > ht) {
		printf("Invalid set of coordinates\n");
		return 0;
	} else if (cds[2] > wd) {
		printf("Invalid set of coordinates\n");
		return 0;
	} else if (cds[3] > ht) {
		printf("Invalid set of coordinates\n");
		return 0;
	} else if (cds[0] < 0 || cds[1] < 0 || cds[2] < 0 || cds[3] < 0) {
		printf("Invalid set of coordinates\n");
		return 0;
	} else if (cds[2] - cds[0] == 0) {
		printf("Invalid set of coordinates\n");
		return 0;
	} else if (cds[3] - cds[1] == 0) {
		printf("Invalid set of coordinates\n");
		return 0;
	} else {
		return 1;
	}
}

void select_all(photo *color, int *cds, double ***sel, int wd, int ht,
				int *loaded)
{
	// selecting all of the image
	// x1
	cds[0] = 0;
	// y1
	cds[1] = 0;
	// x2
	cds[2] = wd;
	// y2
	cds[3] = ht;

	// get the selection matrix
	if (*loaded == 1) {
		double **gr = alloc_matrix(ht, wd);

		if (!gr) {
			fprintf(stderr, "malloc() failed\n");
			return;
		}

		for (int i = 0; i < ht; i++)
			for (int j = 0; j < wd; j++)
				gr[i][j] = color->matrix[i][j];
		// o stands for grayscale
		sel[0] = gr;

	} else if (*loaded == 2) {
		double **red = alloc_matrix(ht, wd);
		double **green = alloc_matrix(ht, wd);
		double **blue = alloc_matrix(ht, wd);

		if (!red || !green || !blue) {
			fprintf(stderr, "malloc() failed\n");
			return;
		}

		for (int i = 0; i < ht; i++)
			for (int j = 0; j < wd; j++)
				red[i][j] = color->R[i][j];
		for (int i = 0; i < ht; i++)
			for (int j = 0; j < wd; j++)
				green[i][j] = color->G[i][j];
		for (int i = 0; i < ht; i++)
			for (int j = 0; j < wd; j++)
				blue[i][j] = color->B[i][j];
		// 0 stands for red
		// 1 stands for green
		// 2 stands for blue
		sel[0] = red;
		sel[1] = green;
		sel[2] = blue;
	}
}

void select_action(photo *color, int wd, int ht, int cds[4],
				   double ***sel, int *loaded)
{
	char first_arg[BMAX];
	scanf("%s", first_arg);
	if (strcmp(first_arg, "ALL") == 0) {
		// free previously allocated selection matrix
		free_loaded(sel, cds, *loaded);
		// select the entire image
		select_all(color, cds, sel, wd, ht, loaded);
		printf("Selected ALL\n");

	} else {
		char tmp_cds[4][10], string[20], *delim = " ", *tokens;
		strcpy(tmp_cds[0], first_arg);
		int k = 1, cds_num[4];
		// check to see if the rest of the arguments are present and integers
		fgets(string, BMAX, stdin);
		tokens = strtok(string, delim);
		strcpy(tmp_cds[1], tokens);
		while (tokens[strlen(tokens) - 1] != '\n') {
			k++;
			tokens = strtok(NULL, delim); strcpy(tmp_cds[k], tokens);
			if (k > 3)
				break;
		}
		if (k < 3) {
			printf("Invalid command\n"); return;
		}
		tmp_cds[3][strlen(tmp_cds[3]) - 1] = '\0';
		// validating coordinates
		int good = validate_and_swap_coordinates(wd, ht, tmp_cds, cds_num);
		// if the coordinates are good we can start
		if (good == 1) {
			// free previously allocated selection matrix
			free_loaded(sel, cds, *loaded);
			cds[0] = cds_num[0];
			cds[1] = cds_num[1];
			cds[2] = cds_num[2];
			cds[3] = cds_num[3];
			// copy the area we need in an auxiliary matrix,
			//then put it in the selection array of matrices
			if (*loaded == 1) {
				double **gr = alloc_matrix(cds[3] - cds[1],
												  cds[2] - cds[0]);
				if (!gr) {
					fprintf(stderr, "malloc() failed\n");
					return;
				}
				for (int i = cds[1]; i < cds[3]; i++)
					for (int j = cds[0]; j < cds[2]; j++)
						gr[i - cds[1]][j - cds[0]] = color->matrix[i][j];
				sel[0] = gr;
			} else if (*loaded == 2) {
				double **red =
				alloc_matrix(cds[3] - cds[1], cds[2] - cds[0]);
				double **green =
				alloc_matrix(cds[3] - cds[1], cds[2] - cds[0]);
				double **blue =
				alloc_matrix(cds[3] - cds[1], cds[2] - cds[0]);
				if (!red || !green || !blue) {
					fprintf(stderr, "malloc() failed\n");
					return;
				}
				for (int i = cds[1]; i < cds[3]; i++)
					for (int j = cds[0]; j < cds[2]; j++)
						red[i - cds[1]][j - cds[0]] = color->R[i][j];
				for (int i = cds[1]; i < cds[3]; i++)
					for (int j = cds[0]; j < cds[2]; j++)
						green[i - cds[1]][j - cds[0]] = color->G[i][j];
				for (int i = cds[1]; i < cds[3]; i++)
					for (int j = cds[0]; j < cds[2]; j++)
						blue[i - cds[1]][j - cds[0]] = color->B[i][j];
				sel[0] = red;
				sel[1] = green;
				sel[2] = blue;
			}
			printf("Selected %d %d %d %d\n", cds[0], cds[1], cds[2], cds[3]);
		}
	}
}
