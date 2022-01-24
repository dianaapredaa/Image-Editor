// Copyright 2021 - 2022 Preda Diana 314CA
#ifndef SAVE_ACTION_H
#define SAVE_ACTION_H

#include <stdio.h>
#include "photo.h"

void save_as_ascii(photo * color, FILE * out, int width, int height);

void save_as_binary(photo *color, FILE *out, int width, int height);

void save_as_ascii_colored(photo *color, FILE *out, int width, int height);

void save_as_binary_colored(photo *color, FILE *out, int width, int height);

void save_action(photo *color, int width, int height, int maxvalue,
				 char *type);

#endif
