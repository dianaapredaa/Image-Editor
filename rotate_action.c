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

int is_select_all(int *cds, int ht, int wd)
{
	if (cds[0] == 0 && cds[1] == 0 && cds[2] == wd && cds[3] == ht)
		return 1;
	else
		return 0;
}

void change_cds(int *cds, int ht, int wd)
{
	cds[0] = 0;
	cds[1] = 0;
	cds[2] = wd;
	cds[3] = ht;
}

int how_many_rotations(int angle)
{
	// reduce the angle using the 360 degrees period
	int actual_angle = angle % 360;
	// if the angle is negative, calculate the positive complementary angle
	if (actual_angle < 0)
		actual_angle = 360 + actual_angle;
	// calculate the number of rotation necessary to reach the rotation angle
	int rotations = actual_angle / 90;
	return rotations;
}

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void rotate_grayscale(photo *col, double ***sel, int *cds)
{
	for (int i = 0; i < cds[3] - cds[1]; i++)
		for (int j = cds[2] - cds[0] - 1; j >= 0; j--)
			col->matrix[i + cds[1]][cds[2] - j - 1] = sel[0][j][i];
	for (int i = cds[1]; i < cds[3]; i++)
		for (int j = cds[0]; j < cds[2]; j++)
			sel[0][i - cds[1]][j - cds[0]] = col->matrix[i][j];
}

void rotate_rgb(photo *col, double ***sel, int *cds)
{
	for (int i = 0; i < cds[3] - cds[1]; i++)
		for (int j = cds[2] - cds[0] - 1; j >= 0; j--)
			col->R[i + cds[1]][cds[2] - j - 1] = sel[0][j][i];

	for (int i = 0; i < cds[3] - cds[1]; i++)
		for (int j = cds[2] - cds[0] - 1; j >= 0; j--)
			col->G[i + cds[1]][cds[2] - j - 1] = sel[1][j][i];

	for (int i = 0; i < cds[3] - cds[1]; i++)
		for (int j = cds[2] - cds[0] - 1; j >= 0; j--)
			col->B[i + cds[1]][cds[2] - j - 1] = sel[2][j][i];

	for (int i = cds[1]; i < cds[3]; i++)
		for (int j = cds[0]; j < cds[2]; j++)
			sel[0][i - cds[1]][j - cds[0]] = col->R[i][j];

	for (int i = cds[1]; i < cds[3]; i++)
		for (int j = cds[0]; j < cds[2]; j++)
			sel[1][i - cds[1]][j - cds[0]] = col->G[i][j];

	for (int i = cds[1]; i < cds[3]; i++)
		for (int j = cds[0]; j < cds[2]; j++)
			sel[2][i - cds[1]][j - cds[0]] = col->B[i][j];
}

void rotate_grayscale_all(photo *col, double ***sel, int ht, int wd)
{
	for (int i = 0; i < wd; i++)
		for (int j = ht - 1; j >= 0; j--)
			col->matrix[i][ht - j - 1] = sel[0][j][i];
}

void rotate_rgb_all(photo *col, double ***sel, int ht, int wd)
{
	for (int i = 0; i < wd; i++)
		for (int j = ht - 1; j >= 0; j--)
			col->R[i][ht - j - 1] = sel[0][j][i];
	for (int i = 0; i < wd; i++)
		for (int j = ht - 1; j >= 0; j--)
			col->G[i][ht - j - 1] = sel[1][j][i];
	for (int i = 0; i < wd; i++)
		for (int j = ht - 1; j >= 0; j--)
			col->B[i][ht - j - 1] = sel[2][j][i];
}

void rotate_action(photo *col, double ***sel, int loaded, int *cds,
				   int *ht, int *wd)
{
	int angle;
	// check if the image is fully selected
	int good = is_select_all(cds, *ht, *wd);

	scanf("%d", &angle);
	// calculate the number of rotations of 90 degrees that needs to be done
	int rotations = how_many_rotations(angle);

	if (angle % 90 != 0) {
		printf("Unsupported rotation angle\n");
	// check if the selection is square
	} else if (cds[2] - cds[0] != cds[3] - cds[1] && good != 1) {
		printf("The selection must be square\n");

	} else if (good == 1) {
		for (int x = 0; x < rotations; x++) {
			free_action(col, *ht, loaded);
			// free the image
			if (loaded == 1) {
				col->matrix = alloc_matrix(*wd, *ht);
				// alocate the matrix with the new dimensions
				if (!col->matrix) {
					printf("malloc() failed\n");
					return;
				}
				// we use the selection array to rotate the picture
				rotate_grayscale_all(col, sel, *ht, *wd);

			} else if (loaded == 2) {
				col->R = alloc_matrix(*wd, *ht);
				col->G = alloc_matrix(*wd, *ht);
				col->B = alloc_matrix(*wd, *ht);

				if (!col->R || !col->G || !col->B) {
					printf("malloc() failed\n");
					return;
				}
				// we use the selection array to rotate the picture
				rotate_rgb_all(col, sel, *ht, *wd);
			}
				// swap the height and width values
				swap(ht, wd);
				// free the previous matrix
				free_loaded(sel, cds, loaded);
				// change the coordonates
				change_cds(cds, *ht, *wd);
				// after rotating, select the new area
				select_all(col, cds, sel, *wd, *ht, &loaded);
		}
		printf("Rotated %d\n", angle);

	} else if (good == 0) {
		for (int x = 0; x < rotations; x++) {
			if (loaded == 1)
				// we use the selection array to rotate the picture
				rotate_grayscale(col, sel, cds);
			else if (loaded == 2)
				// we use the selection array to rotate the picture
				rotate_rgb(col, sel, cds);
		}
		printf("Rotated %d\n", angle);
	}
}
