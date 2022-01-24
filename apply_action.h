// Copyright 2021 - 2022 Preda Diana 314CA
#ifndef APPLY_H
#define APPLY_H

#include <stdio.h>
#include "photo.h"

int clamp(int x);

void apply_edge(photo *color, double ***sel, int *cds, int wd, int ht);

void apply_sharpen(photo *color, double ***sel, int *cds,
				   int wd, int ht);

void apply_blur(photo *color, double ***sel, int *cds, int wd, int ht);

void apply_gaussian_blur(void);

void apply_action(photo *color, double ***sel, int *cds, int loaded,
				  int ht, int wd);

#endif
