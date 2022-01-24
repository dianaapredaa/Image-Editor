// Copyright 2021 - 2022 Preda Diana 314CA
#ifndef SELECT_ACTION_H
#define SELECT_ACTION_H

#include <stdio.h>
#include "photo.h"

int validate_and_swap_coordinates(int wd, int ht, int coords[4]);

void select_all(photo *col, int *cds, double ***sel, int wd, int ht,
				int *loaded);

void select_action(photo *col, int wd, int ht, int cds[4],
				   double ***sel, int *loaded);

#endif
