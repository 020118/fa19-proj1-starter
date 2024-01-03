/*********************
**  Color Palette generator
** Skeleton by Justin Yokota
**********************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "ColorMapInput.h"

//You don't need to call this function but it helps you understand how the arguments are passed in 
void usage(char* argv[])
{
	printf("Incorrect usage: Expected arguments are %s <inputfile> <outputfolder> <width> <heightpercolor>", argv[0]);
}

//Creates a color palette image for the given colorfile in outputfile. Width and heightpercolor dictates the dimensions of each color. Output should be in P3 format
int P3colorpalette(char* colorfile, int width, int heightpercolor, char* outputfile)
{
	//YOUR CODE HERE
	int *colorcount = (int *) malloc(sizeof(int));
	uint8_t **p3p = FileToColorMap(colorfile, colorcount);
	if ((p3p == NULL)|| (width<1)|| (heightpercolor<1)) {
		free(colorcount);
		return 1;
	
	FILE *fp = fopen(outputfile, "w+");
	if (fp == NULL) return 1;
	
	fprintf(fp, "%s %d %d %d\n", "p3", width, (*colorcount)*heightpercolor, 255);
	uint8_t *temp;
	int i,j,k;
	for (i=0; i<*colorcount; i++) {
		temp = *(p3p+i);
		for (j=0; j<heightpercolor; j++) {
			for (k=0; k<width-1; k++) {
				fprintf(fp, "%hhu %hhu %hhu ", *temp, *(temp+1), *(temp+2));
			}
			fprintf(fp, "%hhu %hhu %hhu\n", *temp, *(temp+1), *(temp+2));
		}
	}
	fclose(fp);
	int x;
	for (x=0; x<*colorcount; x++) {
		free(*(p3p+x));
	}
	free(colorcount);
	free(p3p);
	return 0;
}

//Same as above, but with P6 format
int P6colorpalette(char* colorfile, int width, int heightpercolor, char* outputfile)
{
	//YOUR CODE HERE
	int *colorcount = (int *) malloc(sizeof(int));
	uint8_t **p6p = FileToColorMap(colorfile, colorcount);
	if (p6p == NULL || width<1 || heightpercolor<1) return 1;
	
	FILE *fp = fopen(outputfile, "w+");
	if (fp == NULL) return 1;
	
	fprintf(fp, "%s %d %d %d\n", "p6", width, (*colorcount)*heightpercolor, 255);
	uint8_t *temp;
	int i,j,k;
	for (i=0; i<*colorcount; i++) {
		temp = *(p6p+i);
		for (j=0; j<heightpercolor; j++) {
			for (k=0; k<width-1; k++) {
				fwrite(p6p, 1, 3, fp);
			}
		}
	}
	fclose(fp);
	int x;
	for(x = 0; i < *(colorcount); i++) {
		free(*(p6p + x));
	}
	free(colorcount);
	free(p6p);
	
	return 0;
}


//The one piece of c code you don't have to read or understand. Still, might as well read it, if you have time.
int main(int argc, char* argv[])
{
	/*
	if (argc != 5)
	{
		usage(argv);
		return 1;
	}*/
	int width = 4;//atoi(argv[3]);
	int height = 12;//atoi(argv[4]);
	char* P3end = "\\colorpaletteP3.ppm";
	char* P6end = "\\colorpaletteP6.ppm";
	char* g1 = "E:\\git-repo\\proj1-19fall\\defaultcolormap.txt";
	char* g2 = "E:\\git-repo\\proj1-19fall";
	char buffer[strlen(g2) + strlen(P3end)+1];
	sprintf(buffer, "%s%s", g2, P3end);
	int failed = P3colorpalette(g1, width, height, buffer);
	if (failed)
	{
		printf("Error in making P3colorpalette");
		return 1;
	}
	sprintf(buffer, "%s%s", g2, P6end);
	failed = P6colorpalette(g1, width, height, buffer);
	if (failed)
	{
		printf("Error in making P6colorpalette");
		return 1;
	}
	printf("P3colorpalette and P6colorpalette ran without error, output should be stored in %s%s, %s%s", g2, P3end, g2, P6end);
	return 0;
}




