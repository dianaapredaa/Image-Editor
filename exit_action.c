// Copyright 2021 - 2022 Preda Diana 314CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "photo.h"

#define AMAX 3
#define BMAX 20
#define CMAX 200
#define DMAX 4

void exit_action(photo *color, int ht, int loaded, double ***sel,
				 int *cds)
{
	// free the memeory depending on the image type
	if (loaded == 1)
		free_matrix_grayscale(color, ht);
	if (loaded == 2)
		free_matrix_colored(color, ht);
	// free the selection array
	free_loaded(sel, cds, loaded);
}
