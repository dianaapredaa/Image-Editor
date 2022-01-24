// Copyright 2021 - 2022 Preda Diana 314CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "photo.h"
#include "utils.h"
#include "load_action.h"
#include "save_action.h"
#include "select_action.h"
#include "exit_action.h"
#include "crop_action.h"
#include "rotate_action.h"
#include "apply_action.h"

#define AMAX 3
#define BMAX 20
#define CMAX 200
#define DMAX 4

int main(void)
{
	photo color;
	char action[BMAX], where[BMAX], type[AMAX];
	int height, width, maxvalue, loaded = 0;
	int coords[DMAX];
		// x1
		coords[0] = 0;
		// y1
		coords[1] = 0;
		// x2
		coords[2] = 0;
		// y2
		coords[3] = 0;
	// array of matrices
	double ***sel;
	sel = malloc(AMAX * sizeof(double **));

	if (!sel) {
		fprintf(stderr, "malloc() failed\n");
		free(sel);
	}

	do {
		scanf("%s", action);

		if (strcmp(action, "LOAD") == 0) {
			scanf("%s", where);
			load_action(&color, where, &width, &height, &loaded, &maxvalue,
						type, sel, coords);

		} else if (strcmp(action, "SELECT") == 0 && loaded != 0) {
			select_action(&color, width, height, coords, sel, &loaded);

		} else if (strcmp(action, "ROTATE") == 0 && loaded != 0) {
			rotate_action(&color, sel, loaded, coords, &height, &
			width);
		} else if (strcmp(action, "CROP") == 0 && loaded != 0) {
			crop_action(&color, sel, loaded, &width, &height, coords);

		} else if (strcmp(action, "APPLY") == 0 && loaded != 0) {
			apply_action(&color, sel, coords, loaded, height, width);

		} else if (strcmp(action, "SAVE") == 0 && loaded != 0) {
			save_action(&color, width, height, maxvalue, type);

		} else if (strcmp(action, "EXIT") == 0) {
			if (loaded == 0)
				printf("No image loaded\n");
			else
				exit_action(&color, height, loaded, sel, coords);

		} else if (loaded != 0) {
			wrong_arg();
			fprintf(stdout, "Invalid command\n");

		} else if (loaded == 0) {
			wrong_arg();
			fprintf(stdout, "No image loaded\n");
		}
	} while (strcmp(action, "EXIT") != 0);

	free(sel);

	return 0;
}
