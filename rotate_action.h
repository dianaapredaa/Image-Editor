// Copyright 2021 - 2022 Preda Diana 314CA
#ifndef ROTATE_ACTION_H
#define ROTATE_ACTION_H

#include <stdio.h>
#include "photo.h"

int is_select_all(int *cds, int ht, int wd);

void change_cds(int *cds, int ht, int wd);

int how_many_rotations(int angle);

void swap(int *a, int *b);

void rotate_grayscale(photo *col, double ***sel, int *cds);

void rotate_rgb(photo *col, double ***sel, int *cds);

void rotate_grayscale_all(photo *col, double ***sel, int ht, int wd);

void rotate_rgb_all(photo *col, double ***sel, int ht, int wd);

void rotate_action(photo *color, double ***sel, int loaded, int *cds,
				   int *ht, int *wd);

#endif
