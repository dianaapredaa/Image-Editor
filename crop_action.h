// Copyright 2021 - 2022 Preda Diana 314CA
#ifndef CROP_H
#define CROP_H

#include <stdio.h>
#include "photo.h"

void crop_action(photo * color, double ***sel, int selected, int *width,
				 int *height, int coords[4]);

#endif
