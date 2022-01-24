// Copyright 2021 - 2022 Preda Diana 314CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "utils.h"
#include "photo.h"

#define AMAX 3
#define BMAX 20
#define CMAX 200
#define DMAX 4

void save_as_ascii(photo *color, FILE *out, int width, int height)
{
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			unsigned char tmp = round(color->matrix[i][j]);
			fprintf(out, "%hhu ", (unsigned char)tmp);
		}
		fprintf(out, "\n");
	}
}

void save_as_binary(photo *color, FILE *out, int width, int height)
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			unsigned char tmp = (unsigned char)round(color->matrix[i][j]);
			fwrite(&tmp, sizeof(unsigned char), 1, out);
		}
}

void save_as_ascii_colored(photo *color, FILE *out, int width, int height)
{
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			unsigned char tmp1 = (unsigned char)round(color->R[i][j]);
			unsigned char tmp2 = (unsigned char)round(color->G[i][j]);
			unsigned char tmp3 = (unsigned char)round(color->B[i][j]);
			fprintf(out, "%hhu %hhu %hhu ", tmp1, tmp2, tmp3);
			}
		fprintf(out, "\n");
	}
}

void save_as_binary_colored(photo *color, FILE *out, int width, int height)
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			unsigned char tmp1 = (unsigned char)round(color->R[i][j]);
			unsigned char tmp2 = (unsigned char)round(color->G[i][j]);
			unsigned char tmp3 = (unsigned char)round(color->B[i][j]);
			fwrite(&tmp1, sizeof(unsigned char), 1, out);
			fwrite(&tmp2, sizeof(unsigned char), 1, out);
			fwrite(&tmp3, sizeof(unsigned char), 1, out);
		}
}

void save_action(photo *color, int width, int height, int maxvalue, char *type)
{
	char arguments[CMAX];
	fgets(arguments, CMAX, stdin);

	// get saving type
	int save_ascii = 0;
	if (strstr(arguments, "ascii"))
		save_ascii = 1;

	// get saving name
	char output[200];
	strcpy(output, strtok(arguments, " "));

	if ((strcmp(type, "P2") == 0 || strcmp(type, "P5") == 0) &&
		save_ascii == 1) {
		// saving a grayscale image in ascii

		FILE *out = fopen(output, "wt");
		fprintf(out, "P2\n%d %d\n%d\n", width, height, maxvalue);
		// save matrix
		save_as_ascii(color, out, width, height);
		fclose(out);

	} else if ((strcmp(type, "P2") == 0 || strcmp(type, "P5") == 0) &&
				save_ascii == 0) {
		// saving a grayscale image in binary
		if (output[strlen(output) - 1] != 'm')
			output[strlen(output) - 1] = '\0';

		FILE *out = fopen(output, "w");
		fprintf(out, "P5\n%d %d\n%d\n", width, height, maxvalue);
		// save matrix
		save_as_binary(color, out, width, height);
		fclose(out);

	} else if ((strcmp(type, "P3") == 0 || strcmp(type, "P6") == 0) &&
				save_ascii == 1) {
		// saving an rgb image in ascii

		FILE *out = fopen(output, "wt");
		fprintf(out, "P3\n%d %d\n%d\n", width, height, maxvalue);
		// save matrix
		save_as_ascii_colored(color, out, width, height);
		fclose(out);

	} else if ((strcmp(type, "P3") == 0 || strcmp(type, "P6") == 0) &&
				save_ascii == 0) {
		// saving an rgb image in binary
		if (output[strlen(output) - 1] != 'm')
			output[strlen(output) - 1] = '\0';

		FILE *out = fopen(output, "w");
		fprintf(out, "P6\n%d %d\n%d\n", width, height, maxvalue);
		// save matrix
		save_as_binary_colored(color, out, width, height);
		fclose(out);
	}
	printf("Saved %s\n", output);
}
