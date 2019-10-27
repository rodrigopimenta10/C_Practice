/*
 * enee140_hashtable.c
 *
 *  Created on: Apr 27, 2015
 *      Author: rodrigopimenta
 */

#include "enee140_hashtable.h"
#include <string.h>
/*
 * Hashtable main storage
 */
static char keys[NBUCKETS][MAX_STRING];
static int values[NBUCKETS];
static int used_buckets;
/*
 * Internal library functions
 */
unsigned hash_function(char s[]) {

unsigned hashval, i;
for (hashval=0, i=0; s[i] != '\0'; i++) {
hashval += s[i] + 31*hashval;
}
return hashval % NBUCKETS;
}

/*
 * Main hashtable API
 */

//Returns the load factor as a float. Load factor is the used_buckets/NBUCKETS-used_buckets.
//If NBUCKETS==used_buckets then the load factor is 1.
float hash_load_factor()
{
	if(NBUCKETS == used_buckets){
		return 1;
	}
	return (float)(used_buckets/(NBUCKETS-used_buckets));
}


/*
 * Initialize the hash table by clearing its content.
 */
void hash_initialize()
{
	int i;
	for(i=0; i<NBUCKETS; i++){
	values[i] = 0;
	keys[i][0] = 0;
	}


}

/*
 * Insert a <key, value> pair in the hash table.
 * Return 1 if the insert was successful, and 0 if
 * the key could not be inserted because the hash
 * table if full.
 */
int hash_put(char key[], int value) {
	int hash_index;
	int flag, start;
	hash_index=hash_function(key);

	if(keys[hash_index]!=0){
		flag=0;
		start = hash_index;
		while(hash_index<NBUCKETS){
			hash_index++;
			if(keys[hash_index]==0){
				strcpy(keys[hash_index], key);
				values[hash_index]=value;
				used_buckets++;
				flag=1;
			}
		}
			if(flag==0){
				hash_index=0;
				while(hash_index<start){
				if(keys[hash_index]==0){
					strcpy(keys[hash_index], key);
					values[hash_index]=value;
					used_buckets++;
					flag=1;
				}
					hash_index++;

				}
			}
		}
	else{
		strcpy(keys[hash_index], key);
		values[hash_index]=value;
		used_buckets++;
	}
	if(flag==0){
		return 0;
	}
	else{
		return 1;
	}

}
/*
 * If key is stored in the hashtable, return the corresponding
 * value. Otherwise, return 0.
 */
int hash_get(char key[]) {
	int hash_index;
	int flag, start;
	hash_index=hash_function(key);

	if(keys[hash_index]!=key){
		flag=0;
		start = hash_index;
		while(hash_index<NBUCKETS){
			hash_index++;
			if(keys[hash_index]==key){
				return values[hash_index];
						flag=1;
					}
				}
					if(flag==0){
						hash_index=0;
						while(hash_index<start){
						if(keys[hash_index]==key){
							return values[hash_index];
							flag=1;
						}
							hash_index++;

						}
					}
				}
			else{
				return values[hash_index];
			}
			if(flag==0){
				return 0;
			}
			else{
				return 1;
			}
	}
/*
 * Returns 1 if key is stored in the hashtable, and 0 otherwise.
 */
int hash_lookup(char key[]) {
	int hash_index;
		int flag, start;
		hash_index=hash_function(key);

		if(keys[hash_index]!=key){
			flag=0;
			start = hash_index;
			while(hash_index<NBUCKETS){
				hash_index++;
				if(keys[hash_index]==key){
					flag=1;
				}
			}
				if(flag==0){
					hash_index=0;
					while(hash_index<start){
					if(keys[hash_index]==key){
						flag=1;
					}
						hash_index++;

					}
				}
			}
		else{
			return 1;
		}
		if(flag==0){
			return 0;
		}
		else{
			return 1;
		}
}
