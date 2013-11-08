#include "map.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	map m;
	int items_number = 10;
	int total_items_number = 10;
	char *unknown;

	//~const char *keys[] = {"aaa", "bbb", "ccc", "ddd", "eee", "fff", "ggg", "hhh", "iii", "jjj"};
	//~const char *values[] = {"foo", "bar", "toto", "tata", "something", "10", "truc", "3.14", "moi", "vous"};
	const char *keys[] = {"ddd", "aaa", "ggg", "ccc", "eee", "fff", "bbb", "jjj", "iii", "hhh"};
	const char *values[] = {"foo", "bar", "toto", "tata", "something", "10", "truc", "3.14", "moi", "vous"};

	m.items = (struct map_item*) calloc((size_t) total_items_number, sizeof(struct map_item));
	m.total_items_number = total_items_number;
	m.items_number = 0;

	int i;
	for (i = 0; i < items_number; i++) {
		map_add_entry(keys[i], (char *) values[i], &m);
		printf("map_get_entry access: key: %s, value %s\n", keys[i], (char *) map_get_entry(keys[i], &m));
	}

	// try to add an element in a full map
	if (map_add_entry("11th", (char *) "unwanted value", &m) == MAP_FULL) {
		printf("Map full while trying to insert %s\n", "11th");
	}

	// try to get an unexisting element
	unknown = (char *) map_get_entry("uuu", &m);
	if (unknown != NULL) {
		printf("%s\n", unknown);
	}
	else {
		printf("'uuu' is not in the map\n");
	}

	printf("before, for the key 'ddd', the value was '%s'\n", (char *) map_get_entry("ddd", &m));
	map_add_entry("ddd", (char *) "new ddd", &m);
	printf("and after, for the key 'ddd', the value is '%s'\n", (char *) map_get_entry("ddd", &m));

	free(m.items);
	return 0;
}
