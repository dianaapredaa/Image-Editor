// Copyright 2021 - 2022 Preda Diana 314CA
#include <stdlib.h>

#include "utils.h"

void crop_action(photo *color, double ***sel, int loaded, int *width,
				 int *height, int coords[4])
{
	if (loaded == 1) {
		free_action(color, *height, loaded);

		// select the new width and height
		int new_width = coords[2] - coords[0];
		int new_height = coords[3] - coords[1];

		// alloc using the new demensions
		color->matrix = alloc_matrix(new_height, new_width);

		if (!color->matrix) {
			printf("malloc() failed\n");
			return;
		}

		// copy the selection in the original matrix
		for (int i = 0; i < new_height; i++)
			for (int j = 0; j < new_width; j++)
				// tmp_mat[i][j] = sel[0][i][j];
				color->matrix[i][j] = sel[0][i][j];

		*width = new_width;
		*height = new_height;
		// save the new width and height
		coords[0] = 0;
		coords[1] = 0;
		coords[2] = new_width;
		coords[3] = new_height;

		printf("Image cropped\n");

	} else if (loaded == 2) {
		free_action(color, *height, loaded);

		int new_width = coords[2] - coords[0];
		int new_height = coords[3] - coords[1];

		// alloc using the new demensions
		color->R = alloc_matrix(new_height, new_width);
		color->G = alloc_matrix(new_height, new_width);
		color->B = alloc_matrix(new_height, new_width);

		if (!color->R || !color->G || !color->B) {
			printf("malloc() failed\n");
			return;
		}

		// copy the selection in the original matrix
		for (int i = 0; i < new_height; i++)
			for (int j = 0; j < new_width; j++)
				color->R[i][j] = sel[0][i][j];

		for (int i = 0; i < new_height; i++)
			for (int j = 0; j < new_width; j++)
				color->G[i][j] = sel[1][i][j];

		for (int i = 0; i < new_height; i++)
			for (int j = 0; j < new_width; j++)
				color->B[i][j] = sel[2][i][j];

		// save the new width and height
		*width = new_width;
		*height = new_height;
		coords[0] = 0;
		coords[1] = 0;
		coords[2] = new_width;
		coords[3] = new_height;

		printf("Image cropped\n");
	}
}
