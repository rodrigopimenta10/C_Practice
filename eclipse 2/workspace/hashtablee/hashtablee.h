/*
 * enee140_hashtablee.h
 *
 *  Created on: May 20, 2015
 *      Author: rodrigopimenta
 */

#ifndef ENEE140_HASHTABLEE_H_
#define ENEE140_HASHTABLEE_H_

/*
 * define the paramerters of a hashtable that will store English words.
 * Provision the capacity of the hashtable considering the fact that
 * Shakespeare's works include about 30,000 unique words and that the
 * Lookup performance tends to decrease with a load factor > 0.7.
 */
#define NBUCKETS	50021 // prime number, for better hash uniformity
#define MAX_STRING	80

// Function prototypes for the public hashtable API.
void hash_initialize();
float hash_load_factor();
int hash_put(char key[], int value);
int hash_get(char key[]);
int hash_lookup(char key[]);
int maximum_length();
float collision_average();


#endif /* ENEE140_HASHTABLEE_H_ */

