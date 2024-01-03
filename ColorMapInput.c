/*********************
**  Color Map generator
** Skeleton by Justin Yokota
**********************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "ColorMapInput.h"


/**************
**This function reads in a file name colorfile.
**It then uses the information in colorfile to create a color array, with each color represented by an int[3].
***************/
uint8_t** FileToColorMap(char* colorfile, int* colorcount)
{
	//YOUR CODE HERE
	FILE* file = fopen(colorfile, "r");
	if (file == NULL) return NULL;
	
	fscanf(file, "%d", colorcount);
	
	uint8_t **point = (uint8_t **)malloc(sizeof(uint8_t *) * (*colorcount));
	int i = 0;
	for (i; i<*colorcount; i++) {
		uint8_t *color = (uint8_t *)malloc(sizeof(uint8_t) * 3);
		fscanf(file, "%d %d %d", color, color+1, color+2);
		*(point + i) = color;
	}
	fclose(file);
	
	if (i != *colorcount) {
		free(point);
		return NULL;
	}
	else {
		return point;
	}
}








