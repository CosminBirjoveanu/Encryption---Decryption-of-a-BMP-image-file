#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H
#include "DataStructures.h"

liniarized_image loadImage(unsigned char* image_path) {
    liniarized_image image;
    unsigned char* memory_test1 = NULL;
    pixel* memory_test2 = NULL;
    unsigned long int i, j, padding_counter, c = 0;

    FILE *f = fopen ((void*) image_path, "rb");
    if (f == NULL) {
        printf("\nThe file did not load correctly!\n");
        exit(0);
    }

    fseek(f, 2, SEEK_SET);
    fread(&image.image_dimensions, sizeof(unsigned int), 1, f);
    fseek(f, 18, SEEK_SET);
    fread(&image.width, sizeof(unsigned int), 1, f);
    fread(&image.height, sizeof(unsigned int), 1, f);

    memory_test1 = (unsigned char*) malloc(54 * 1);
    if (memory_test1 != NULL) {
        image.header = memory_test1;
        memory_test1 = NULL;
    }
    else {
        printf("The memory did not allocate correctly!");
        exit(0);
    }

    fseek(f, 0, SEEK_SET);
    for (i = 0; i < 54; i++) {
        fread( &image.header[i], sizeof(unsigned char), 1, f);
    }

    if( image.width % 4 != 0) {
        image.padding = 4 - (3 * image.width) % 4;
    }
    else {
        image.padding = 0;
    }

    memory_test2 = (pixel*) malloc(((image.image_dimensions - 54) * 1));
    if (memory_test2 != NULL) {
        image.v = memory_test2;
        memory_test2 = NULL;
    }
    else {
        printf("The memory did not allocate correctly!");
        exit(0);
    }

    for(i = 0; i < image.height; i++) {
	    c = image.width * (image.height - i - 1);
		for(j = 0; j < image.width; j++) {
            fread( &image.v[c].b, 1, 1, f);
            fread( &image.v[c].g, 1, 1, f);
            fread( &image.v[c].r, 1, 1, f);
            c++;
		}
		for (padding_counter = 0; padding_counter < image.padding; padding_counter++) {
            fseek(f, image.padding, SEEK_CUR);
        }
	}
    fclose(f);

    return image;
}

void saveImage(unsigned char* image_destination_path, liniarized_image* image)
{
    unsigned long int i, j, padding_counter, c = 0;
    unsigned char a = 0;

    FILE *f = fopen ((const char*) image_destination_path, "wb");
    if (f == NULL) {
        printf("\nThe file did not load correctly!\n");
        exit(0);
    }

    for (i = 0; i < 54; i++) {
        fwrite((const void*) &image->header[i], sizeof(unsigned char), 1, f);
    }

	for(i = 0; i < image->height; i++) {
	    c = image->width * (image->height - i - 1);
		for(j = 0; j < image->width; j++) {
            fwrite((const void*) &image->v[c].b, 1, 1, f);
            fwrite((const void*) &image->v[c].g, 1, 1, f);
            fwrite((const void*) &image->v[c].r, 1, 1, f);
            c++;
		}
		for (padding_counter = 0; padding_counter < image->padding; padding_counter++) {
            fwrite(&a, 1, 1, f);
        }
	}
    fclose(f);
}

#endif // SAVE_LOAD_H
