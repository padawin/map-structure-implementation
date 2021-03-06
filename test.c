#include "map.h"
#include <stdio.h>

int main()
{
	map m;
	int items_number = 10;
	int total_items_number = 10;
	char *unknown, *unknown_substring;

	//~const char *keys[] = {"aaa", "bbb", "ccc", "ddd", "eee", "fff", "ggg", "hhh", "iii", "jjj"};
	//~const char *values[] = {"foo", "bar", "toto", "tata", "something", "10", "truc", "3.14", "moi", "vous"};
	const char *keys[] = {"ddd", "aaa", "ggg", "ccc", "eee", "fff", "bbb", "jjj", "iii", "hhh"};
	const char *values[] = {"foo", "bar", "toto", "tata", "something", "10", "truc", "3.14", "moi", "vous"};

	map_init(&m, total_items_number);

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


	map_delete_entry("aaa", &m);
	unknown = (char *) map_get_entry("aaa", &m);
	if (unknown != NULL) {
		printf("\"aaa\" is still in the map\n");
	}
	else {
		printf("'aaa' is not in the map\n");
	}

	// e is the beginning of the key eee
	unknown_substring = (char *) map_get_entry("e", &m);
	if (unknown_substring != NULL) {
		printf("\"e\" is in the map\n");
	}
	else {
		printf("e' is not in the map\n");
	}

	map_free(&m);
	return 0;
}
