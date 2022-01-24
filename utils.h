// Copyright 2021 - 2022 Preda Diana 314CA
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include "photo.h"

double **alloc_matrix(int height, int width);

void free_matrix_grayscale(photo *color_aux, int height);

void free_matrix_colored(photo *color_aux, int height);

void free_action(photo *color, int height, int loaded);

void free_matrix(double ***matrix, int height);

void free_loaded(double ***sel, int *cds, int loaded);

void wrong_arg(void);

void check_comments(FILE *filename);

#endif
