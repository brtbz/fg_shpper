/*
Fantasy General SHP-file extractor v1.0 by brtbz

GCC: (tested with GCC 7.4.0)
cc -std=c99 shpper.c -lm -o fg_shpper

MSVC: (tested with MSVC 2015 (cl.exe version 19.00.24210 for x64))
cl.exe /TC /Fefg_shpper shpper.c /link /subsystem:console
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

typedef struct fgcolor
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} fgcolor;

fgcolor palette[256];

// these are from a screenshot taken in dosbox at the game's main menu
uint8_t color_values_alt[768] = {
	0, 0, 0,
	4, 4, 0,
	0, 0, 0,
	8, 4, 0,
	16, 4, 4,
	8, 12, 4,
	4, 8, 8,
	4, 4, 8,
	16, 12, 16,
	12, 24, 20,
	24, 20, 28,
	24, 28, 32,
	20, 40, 28,
	32, 40, 12,
	40, 48, 16,
	48, 60, 20,
	52, 69, 24,
	48, 77, 28,
	60, 77, 28,
	69, 85, 28,
	77, 93, 32,
	81, 97, 28,
	81, 105, 36,
	89, 113, 40,
	97, 121, 44,
	105, 130, 48,
	113, 142, 52,
	121, 146, 56,
	130, 154, 60,
	142, 162, 65,
	154, 166, 69,
	162, 170, 77,
	170, 178, 81,
	182, 186, 89,
	195, 195, 97,
	207, 199, 101,
	215, 203, 113,
	223, 207, 121,
	235, 211, 130,
	243, 215, 138,
	255, 219, 150,
	247, 215, 150,
	239, 215, 150,
	231, 211, 146,
	223, 207, 146,
	215, 203, 146,
	207, 199, 146,
	199, 195, 142,
	190, 186, 142,
	178, 182, 138,
	170, 174, 134,
	162, 166, 134,
	154, 158, 130,
	134, 154, 125,
	121, 150, 125,
	117, 150, 142,
	113, 138, 146,
	113, 121, 146,
	105, 105, 134,
	97, 97, 125,
	93, 89, 117,
	77, 77, 109,
	65, 65, 101,
	52, 52, 97,
	44, 44, 89,
	32, 40, 81,
	24, 36, 77,
	16, 28, 69,
	12, 24, 60,
	4, 24, 56,
	4, 20, 48,
	0, 16, 40,
	0, 16, 36,
	0, 24, 36,
	0, 36, 40,
	0, 40, 36,
	0, 44, 28,
	0, 44, 20,
	4, 48, 16,
	4, 48, 8,
	8, 52, 4,
	20, 52, 4,
	32, 56, 8,
	44, 56, 8,
	56, 60, 12,
	69, 69, 16,
	81, 77, 20,
	93, 85, 24,
	105, 89, 28,
	113, 97, 32,
	125, 97, 40,
	138, 101, 44,
	146, 105, 52,
	158, 109, 56,
	170, 109, 65,
	182, 113, 73,
	195, 125, 85,
	199, 138, 93,
	207, 150, 105,
	211, 166, 117,
	219, 178, 125,
	223, 190, 138,
	231, 203, 150,
	235, 215, 162,
	243, 223, 178,
	247, 235, 190,
	255, 247, 207,
	255, 247, 166,
	255, 255, 130,
	255, 247, 117,
	251, 235, 109,
	251, 227, 101,
	251, 215, 89,
	251, 199, 81,
	251, 186, 73,
	251, 170, 60,
	251, 154, 52,
	251, 138, 44,
	251, 121, 36,
	251, 101, 24,
	251, 81, 16,
	251, 60, 8,
	243, 56, 4,
	235, 56, 4,
	231, 52, 4,
	223, 52, 4,
	215, 48, 4,
	211, 48, 0,
	203, 44, 0,
	199, 44, 0,
	190, 44, 0,
	182, 40, 0,
	178, 40, 0,
	162, 36, 0,
	142, 32, 0,
	125, 32, 0,
	105, 28, 0,
	89, 24, 0,
	73, 20, 0,
	69, 20, 0,
	65, 20, 0,
	81, 28, 0,
	97, 44, 4,
	113, 60, 12,
	130, 77, 20,
	146, 93, 32,
	162, 113, 44,
	178, 134, 60,
	190, 146, 77,
	203, 158, 89,
	211, 170, 101,
	235, 239, 255,
	215, 215, 235,
	203, 195, 215,
	195, 174, 199,
	182, 158, 186,
	170, 146, 174,
	158, 130, 166,
	150, 117, 154,
	138, 105, 142,
	130, 93, 134,
	121, 85, 125,
	117, 81, 117,
	109, 73, 109,
	105, 69, 105,
	97, 60, 97,
	89, 56, 85,
	77, 48, 73,
	69, 40, 65,
	56, 36, 52,
	48, 28, 44,
	40, 24, 36,
	52, 28, 60,
	60, 36, 73,
	65, 44, 85,
	69, 56, 93,
	77, 65, 105,
	81, 73, 117,
	85, 85, 125,
	97, 101, 138,
	109, 117, 150,
	121, 138, 158,
	134, 162, 170,
	146, 182, 178,
	162, 195, 178,
	174, 207, 182,
	195, 219, 190,
	219, 231, 207,
	231, 239, 215,
	223, 235, 211,
	215, 235, 207,
	207, 235, 203,
	182, 219, 199,
	174, 211, 195,
	166, 207, 195,
	158, 199, 195,
	154, 190, 190,
	146, 178, 186,
	142, 166, 178,
	134, 158, 174,
	125, 146, 166,
	121, 130, 162,
	113, 121, 154,
	109, 109, 150,
	101, 109, 138,
	93, 109, 125,
	89, 109, 113,
	81, 101, 101,
	73, 89, 85,
	65, 77, 73,
	56, 69, 60,
	48, 56, 48,
	56, 65, 56,
	65, 77, 65,
	77, 85, 73,
	85, 97, 81,
	97, 109, 89,
	109, 117, 97,
	121, 130, 105,
	134, 138, 113,
	138, 150, 121,
	142, 166, 134,
	142, 182, 142,
	150, 199, 162,
	162, 215, 190,
	170, 219, 207,
	178, 223, 223,
	186, 219, 227,
	199, 219, 231,
	207, 215, 235,
	215, 219, 239,
	227, 227, 243,
	239, 235, 251,
	251, 247, 255,
	239, 231, 243,
	227, 219, 235,
	211, 207, 227,
	199, 190, 215,
	182, 178, 207,
	170, 166, 195,
	158, 154, 182,
	146, 142, 174,
	138, 130, 162,
	125, 117, 154,
	113, 105, 142,
	105, 97, 134,
	0, 255, 255,
	0, 255, 255,
	0, 255, 255,
	0, 255, 255,
	0, 255, 255,
	0, 255, 255,
	48, 48, 93,
	146, 36, 0,
	0, 0, 0,
	255, 125, 125,
};

// these are from FGPAL01.LBM file
uint8_t color_values[768] = {
	0, 0, 0,
	0, 0, 0,
	7, 7, 0,
	11, 7, 0,
	19, 7, 7,
	11, 15, 7,
	7, 11, 11,
	7, 7, 11,
	19, 15, 19,
	15, 27, 23,
	27, 23, 31,
	27, 31, 35,
	23, 43, 31,
	35, 43, 15,
	43, 51, 19,
	51, 63, 23,
	55, 71, 27,
	51, 79, 31,
	63, 79, 31,
	71, 87, 31,
	79, 95, 35,
	83, 99, 31,
	83, 107, 39,
	91, 115, 43,
	99, 123, 47,
	107, 131, 51,
	115, 143, 55,
	123, 147, 59,
	131, 155, 63,
	143, 163, 67,
	155, 167, 71,
	163, 171, 79,
	171, 179, 83,
	183, 187, 91,
	195, 195, 99,
	207, 199, 103,
	215, 203, 115,
	223, 207, 123,
	235, 211, 131,
	243, 215, 139,
	255, 219, 151,
	247, 215, 151,
	239, 215, 151,
	231, 211, 147,
	223, 207, 147,
	215, 203, 147,
	207, 199, 147,
	199, 195, 143,
	191, 187, 143,
	179, 183, 139,
	171, 175, 135,
	163, 167, 135,
	155, 159, 131,
	135, 155, 127,
	123, 151, 127,
	119, 151, 143,
	115, 139, 147,
	115, 123, 147,
	107, 107, 135,
	99, 99, 127,
	95, 91, 119,
	79, 79, 111,
	67, 67, 103,
	55, 55, 99,
	47, 47, 91,
	35, 43, 83,
	27, 39, 79,
	19, 31, 71,
	15, 27, 63,
	7, 27, 59,
	7, 23, 51,
	0, 19, 43,
	0, 19, 39,
	0, 27, 39,
	0, 39, 43,
	0, 43, 39,
	0, 47, 31,
	0, 47, 23,
	7, 51, 19,
	7, 51, 11,
	11, 55, 7,
	23, 55, 7,
	35, 59, 11,
	47, 59, 11,
	59, 63, 15,
	71, 71, 19,
	83, 79, 23,
	95, 87, 27,
	107, 91, 31,
	115, 99, 35,
	127, 99, 43,
	139, 103, 47,
	147, 107, 55,
	159, 111, 59,
	171, 111, 67,
	183, 115, 75,
	195, 127, 87,
	199, 139, 95,
	207, 151, 107,
	211, 167, 119,
	219, 179, 127,
	223, 191, 139,
	231, 203, 151,
	235, 215, 163,
	243, 223, 179,
	247, 235, 191,
	255, 247, 207,
	255, 247, 167,
	255, 255, 131,
	255, 247, 119,
	251, 235, 111,
	251, 227, 103,
	251, 215, 91,
	251, 199, 83,
	251, 187, 75,
	251, 171, 63,
	251, 155, 55,
	251, 139, 47,
	251, 123, 39,
	251, 103, 27,
	251, 83, 19,
	251, 63, 11,
	243, 59, 7,
	235, 59, 7,
	231, 55, 7,
	223, 55, 7,
	215, 51, 7,
	211, 51, 0,
	203, 47, 0,
	199, 47, 0,
	191, 47, 0,
	183, 43, 0,
	179, 43, 0,
	163, 39, 0,
	143, 35, 0,
	127, 35, 0,
	107, 31, 0,
	91, 27, 0,
	75, 23, 0,
	71, 23, 0,
	67, 23, 0,
	83, 31, 0,
	99, 47, 7,
	115, 63, 15,
	131, 79, 23,
	147, 95, 35,
	163, 115, 47,
	179, 135, 63,
	191, 147, 79,
	203, 159, 91,
	211, 171, 103,
	235, 239, 255,
	215, 215, 235,
	203, 195, 215,
	195, 175, 199,
	183, 159, 187,
	171, 147, 175,
	159, 131, 167,
	151, 119, 155,
	139, 107, 143,
	131, 95, 135,
	123, 87, 127,
	119, 83, 119,
	111, 75, 111,
	107, 71, 107,
	99, 63, 99,
	91, 59, 87,
	79, 51, 75,
	71, 43, 67,
	59, 39, 55,
	51, 31, 47,
	43, 27, 39,
	55, 31, 63,
	63, 39, 75,
	67, 47, 87,
	71, 59, 95,
	79, 67, 107,
	83, 75, 119,
	87, 87, 127,
	99, 103, 139,
	111, 119, 151,
	123, 139, 159,
	135, 163, 171,
	147, 183, 179,
	163, 195, 179,
	175, 207, 183,
	195, 219, 191,
	219, 231, 207,
	231, 239, 215,
	223, 235, 211,
	215, 235, 207,
	207, 235, 203,
	183, 219, 199,
	175, 211, 195,
	167, 207, 195,
	159, 199, 195,
	155, 191, 191,
	147, 179, 187,
	143, 167, 179,
	135, 159, 175,
	127, 147, 167,
	123, 131, 163,
	115, 123, 155,
	111, 111, 151,
	103, 111, 139,
	95, 111, 127,
	91, 111, 115,
	83, 103, 103,
	75, 91, 87,
	67, 79, 75,
	59, 71, 63,
	51, 59, 51,
	59, 67, 59,
	67, 79, 67,
	79, 87, 75,
	87, 99, 83,
	99, 111, 91,
	111, 119, 99,
	123, 131, 107,
	135, 139, 115,
	139, 151, 123,
	143, 167, 135,
	143, 183, 143,
	151, 199, 163,
	163, 215, 191,
	171, 219, 207,
	179, 223, 223,
	187, 219, 227,
	199, 219, 231,
	207, 215, 235,
	215, 219, 239,
	227, 227, 243,
	239, 235, 251,
	251, 247, 255,
	239, 231, 243,
	227, 219, 235,
	211, 207, 227,
	199, 191, 215,
	183, 179, 207,
	171, 167, 195,
	159, 155, 183,
	147, 143, 175,
	139, 131, 163,
	127, 119, 155,
	115, 107, 143,
	107, 99, 135,
	0, 255, 255,
	0, 255, 255,
	0, 255, 255,
	0, 255, 255,
	0, 255, 255,
	0, 255, 255,
	0, 255, 255,
	0, 255, 255,
	0, 255, 255,
	255, 127, 127
};

// color_values_alt seems to be the more correct palette, but I can't say for sure
void LoadPalette()
{
	// memcpy(&palette[0], &color_values[0], 768);
	memcpy(&palette[0], &color_values_alt[0], 768);
}

void LoadPaletteFromFile()
{
	FILE *fp = fopen("FGPAL01.LBM", "rb");
	if (fp == NULL)
	{
		printf("Couldn't open palette file FGPAL01.LBM\n");
		exit(-1);
	}
	else
	{
		fpos_t begin;
		fgetpos(fp, &begin);
		fseek(fp, 0, SEEK_END);
		int file_size = ftell(fp);
		fsetpos(fp, &begin);
		uint8_t *data = (uint8_t*)malloc(file_size);
		int rc = fread(data, file_size, 1, fp);
		fclose(fp);

		memcpy(&palette[0], &data[48], 256*3);

		free(data);
	}
}

uint8_t debug_red = 0;
uint8_t debug_green = 0;
uint8_t debug_blue = 0;

typedef enum
{
	WAITING,
	START_NEW_ROW,
	SKIP_NUMBER_OF_PIXELS,
	DRAW_LINE_OF_PIXELS,
	DRAW_SINGLE_PIXELS,
	ICON_READY,
} ParseCommand;

void GetCommand(uint8_t code, ParseCommand *pc, uint8_t *parse_parameter)
{
	if (code == 0) { *pc = START_NEW_ROW; }
	else if (code == 1) { *pc = SKIP_NUMBER_OF_PIXELS; }
	else if (code % 2 == 0)
	{
		*pc = DRAW_LINE_OF_PIXELS;
		*parse_parameter = code / 2;
	}
	else if (code % 2 == 1)
	{
		*pc = DRAW_SINGLE_PIXELS;
		*parse_parameter = (code-1) / 2;
	}
}

bool ValueWithinRange(int value, int min, int max)
{
	if (value < min || value > max) 
	{
		return false;
	}
	return true;
};

int ProcessIcon(const char* shp_name, uint32_t offset, uint32_t icon_number, uint8_t *data, uint8_t alpha)
{
	int start_x = *(uint32_t*)(&data[offset+8]);
	int start_y = *(uint32_t*)(&data[offset+12]);
	int end_x = *(uint32_t*)(&data[offset+16]);
	int end_y = *(uint32_t*)(&data[offset+20]);

	int row_width = *(uint16_t*)(&data[offset+2]) + 1;
	int column_height = *(uint16_t*)(&data[offset]) + 1;

	fprintf(stderr, "%u\n", icon_number);
	fprintf(stderr, "lines: %d, pixels in line %d\n", column_height, row_width );
	fprintf(stderr, "start x %d ", start_x);
	fprintf(stderr, "y %d\n", start_y);
	fprintf(stderr, "end x %d ", end_x);
	fprintf(stderr, "y %d\n", end_y);

	if (!ValueWithinRange(start_x, 0, row_width)
		|| !ValueWithinRange(start_y, 0, column_height)
		|| !ValueWithinRange(end_x, 0, row_width)
		|| !ValueWithinRange(end_y, 0, column_height))
	{
		return -1;
	}

	char png_name[64] = { 0 };
	char png_number[13] = { 0 };
	char png_extension[5] = ".png";
	strcat(&png_name[0], shp_name);
	snprintf(&png_number[0], 12, "_%03u", icon_number);
	strcat(png_name, png_number);
	strcat(png_name, png_extension);

	fprintf(stderr, "%s\n", png_name);

	uint8_t *png_data = (uint8_t*)malloc( row_width * column_height * 4 );

	int read_head = offset + 24; // icon header
	int skip_pixels = 0;
	int draw_line_pixels = 0;
	uint8_t draw_line_pixels_color = 0;
	int draw_single_pixels = 0;
	bool waiting_orders = true;

	ParseCommand pc = WAITING;
	uint8_t pp = 0; // parse parameter
	int x = start_x;
	int y = start_y;

	for ( int j = 0; j < column_height; j++)
	{
		for (int i = 0; i < row_width; i++)
		{
			png_data[ (j * row_width + i) * 4     ] = debug_red;
			png_data[ (j * row_width + i) * 4 + 1 ] = 0;
			png_data[ (j * row_width + i) * 4 + 2 ] = debug_blue;
			png_data[ (j * row_width + i) * 4 + 3 ] = alpha;
		}
	}

	while (pc != ICON_READY)
	{
		if (pc == WAITING)
		{
			GetCommand( data[read_head], &pc, &pp );
		}

		if (pc == START_NEW_ROW)
		{
			while( x < row_width)
			{
				png_data[ (y * row_width + x) * 4     ] = 0;
				png_data[ (y * row_width + x) * 4 + 1 ] = debug_green;
				png_data[ (y * row_width + x) * 4 + 2 ] = 0;
				png_data[ (y * row_width + x) * 4 + 3 ] = alpha;

				x++;
			}

			y++;
			x = start_x;
			read_head++;
			pc = WAITING;
		}
		else if ( pc == SKIP_NUMBER_OF_PIXELS)
		{
			read_head++;
			pp = data[read_head];

			while(pp > 0)
			{
				png_data[ (y * row_width + x) * 4     ] = debug_red;
				png_data[ (y * row_width + x) * 4 + 1 ] = debug_green;
				png_data[ (y * row_width + x) * 4 + 2 ] = 0;
				png_data[ (y * row_width + x) * 4 + 3 ] = alpha;

				x++;
				pp--;
			}

			read_head++;
			pc = WAITING;
		}
		else if ( pc == DRAW_LINE_OF_PIXELS )
		{
			read_head++;
			uint8_t color_parameter = data[read_head];

			while( pp > 0 )
			{
				png_data[ (y * row_width + x) * 4     ] = palette[color_parameter].r;
				png_data[ (y * row_width + x) * 4 + 1 ] = palette[color_parameter].g;
				png_data[ (y * row_width + x) * 4 + 2 ] = palette[color_parameter].b;
				png_data[ (y * row_width + x) * 4 + 3 ] = 255;

				x++;
				pp--;
			}

			read_head++;
			pc = WAITING;
		}
		else if ( pc == DRAW_SINGLE_PIXELS )
		{
			while ( pp > 0)
			{
				read_head++;

				uint8_t color = data[read_head];

				png_data[ (y * row_width + x) * 4     ] = palette[color].r;
				png_data[ (y * row_width + x) * 4 + 1 ] = palette[color].g;
				png_data[ (y * row_width + x) * 4 + 2 ] = palette[color].b;
				png_data[ (y * row_width + x) * 4 + 3 ] = 255;

				x++;
				pp--;
			}

			read_head++;
			pc = WAITING;
		}

		if (y > column_height || y > end_y )
		{
			pc = ICON_READY;
		}
	}

	stbi_write_png(png_name, row_width, column_height, 4, png_data, 0);
	free(png_data);

	return 0;
}

int main(int argc, char** argv)
{
	bool debug = false; // debug is full opaque alpha so you can see the debug colors

	uint8_t alpha = 0;

	LoadPalette();
	//LoadPaletteFromFile();

	if ( argc < 2 || argc > 3 )
	{
		fprintf(stderr, "Fantasy General SHP-file extractor v1.0 by brtbz\n");
		fprintf(stderr, "Extracts images from SHP-files and saves them as PNG-files (32-bit RGBA)\n");
		fprintf(stderr, "Usage: fg_shpper <SHP_FILE>\n\n");
		fprintf(stderr, "Options (not required):\n-x\textract PNG(s) from SHP-file (same as no option)\n");
		fprintf(stderr, "-d\tdebug extract (replaces transparent pixels with debug colors in the output png)\n");
		fprintf(stderr, "Example: fg_shpper -d UIF0.SHP\n");
		exit(0);
	}

	int file_name_arg = 0;

	if ( argc == 3 )
	{
		if (strncmp(argv[1], "-x", 2) == 0) { debug = false; }
		else if (strncmp(argv[1], "-d", 2) == 0) { debug = true; }
		else { printf("Unknown command: %s\n", argv[1]); exit(1); }

		file_name_arg = 2;
	}

	if ( argc == 2 )
	{
		debug = false;
		file_name_arg = 1;
	}

	if (debug)
	{
		alpha = 255;
		debug_red = 255;
		debug_green = 255;
		debug_blue = 255;
	}

	FILE *fp = fopen(argv[file_name_arg], "rb");

	if (fp != NULL)
	{
		fpos_t begin;
		fgetpos(fp, &begin);
		fseek(fp, 0, SEEK_END);
		int file_size = ftell(fp);
		fsetpos( fp, &begin );
		uint8_t *data = (uint8_t*)malloc(file_size);
		int rc = fread(data, file_size, 1, fp);
		fclose(fp);

		fprintf(stderr, "Processing %s...\n", argv[file_name_arg]);

		fprintf(stderr, "File size: %d\n", file_size);

		int number_of_icons = *(uint32_t*)(&data[4]);
		fprintf(stderr, "Number of icons: %d\n", number_of_icons);

		uint32_t *icon_header_offsets;
		icon_header_offsets = (uint32_t*)malloc(number_of_icons * sizeof(uint32_t));

		for (int i = 0; i < number_of_icons; i++)
		{
			icon_header_offsets[i] = *(uint32_t*)(&data[8 + i * 8]);
		}

		char basename[64];
		strncpy(&basename[0], argv[file_name_arg], 64);
		char *last_dot = strrchr(basename, '.');
		if (last_dot) { *last_dot = '\0'; }

		for (int i = 0; i < number_of_icons; i++)
		{
			ProcessIcon(basename, icon_header_offsets[i], i, &data[0], alpha);
		}

		free(data);
		free(icon_header_offsets);
	}
	else
	{
		fprintf(stderr, "Couldn't open file%s\n", argv[file_name_arg]);
	}

	return 0;
}
