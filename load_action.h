// Copyright 2021 - 2022 Preda Diana 314CA
#ifndef LOAD_ACTION_H
#define LOAD_ACTION_H

#include <stdio.h>
#include "photo.h"

double **load_ascii(int width, int height, FILE * filename);

double **load_binary(int width, int height, FILE *filename);

void load_ascii_rgb(int width, int height, FILE *filename, photo *color);

void load_binary_rgb(int width, int height, FILE *filename, photo *color);

void load_action(photo *color, char *filename, int *width, int *height,
				 int *loaded, int *maxvalue, char *type,
				 double ***sel, int *cds);

#endif
