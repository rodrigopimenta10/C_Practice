#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "photoalbum.h"

Photo *create_photo(int id, const char *description) {
	if (description != NULL) {
		Photo *a;
		a = malloc(sizeof(Photo));
		if (a == NULL) {
			return NULL;
		}
		a->id = id;
		a->description = malloc(sizeof(char) * (strlen(description) + 1));
		if (a->description == NULL) {
			return NULL;
		}
		strcpy(a->description, description);
		return a;
	} else {
		Photo *a;
		a = malloc(sizeof(Photo));
		if (a == NULL) {
			return NULL;
		}
		a->id = id;
		a->description = NULL;
		return a;
	}
}
void print_photo(Photo *photo) {
	if (photo == NULL) {
		return;
	}
	if (photo->description == NULL) {
		printf("Photo Id: %d, Description: None.\n", photo->id);
	} else {
		printf("Photo Id: %d, Description: %s\n", photo->id,
				photo->description);
	}
}
void destroy_photo(Photo *photo) {
	if (photo == NULL) {
		return;
	} else {
		free(photo->description);
		free(photo);
	}
}
void initialize_album(Album *album) {
	if (album == NULL) {
		return;
	} else {
		album->size = 0;
		return;
	}

}
void print_album(const Album *album) {
	if (album == NULL) {
		return;
	} else if (album->size == 0) {
		printf("Album has no photos.\n");
		return;
	} else {
		int j = 0;
		for (j = 0; j < album->size; j++) {
			print_photo(album->all_photos[j]);
		}
	}
	return;
}
void destroy_album(Album *album) {
	if (album == NULL) {
		return;
	} else {
		int j = 0;
		for (j = 0; j < (album->size); j++) {
			destroy_photo(album->all_photos[j]);
		}
		album->size = 0;
	}
	return;
}
void add_photo_to_album(Album *album, int id, const char *description) {
	if (album == NULL) {
		return;
	} else if (album->size < MAX_ALBUM_SIZE) {
		album->all_photos[album->size] = create_photo(id, description);
		album->size = album->size + 1;
	}
	return;
}
