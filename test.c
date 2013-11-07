#include "map.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	map m;
	int items_number = 10;
	map_item items[items_number];
	char *unknown;

	const char *keys[] = {"aaa", "bbb", "ccc", "ddd", "eee", "fff", "ggg", "hhh", "iii", "jjj"};
	const char *values[] = {"foo", "bar", "toto", "tata", "something", "10", "truc", "3.14", "moi", "vous"};

	int i;
	for (i = 0; i < items_number; ++i) {
		items[i].index = i;
		items[i].key = (char *) keys[i];
		items[i].item = (char *) values[i];
	}

	m.items = items;
	m.items_number = items_number;

	printf("%s\n", (char *) map_get_entry("aaa", &m));
	printf("%s\n", (char *) map_get_entry("iii", &m));
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

	return 0;
}
