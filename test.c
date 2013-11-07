#include "map.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	map m;
	int items_number = 10;
	map_item items[items_number];

	char *keys[] = {"aaa", "bbb", "ccc", "ddd", "eee", "fff", "ggg", "hhh", "iii", "jjj"};
	char *values[] = {"foo", "bar", "toto", "tata", "something", "10", "truc", "3.14", "moi", "vous"};

	int i;
	for (i = 0; i < items_number; ++i) {
		//~items[i] = (map_item) calloc(1, sizeof(map_item));
		items[i].index = i;
		items[i].key = keys[i];
		items[i].item = values[i];
	}

	//~m = (map) calloc(1, sizeof(map));
	m.items = items;
	m.items_number = items_number;

	printf("%s\n", (char *) map_get_entry("aaa", &m));
	printf("%s %s\n", m.items[0].key, (char *) m.items[0].item);
	printf("%s\n", (char *) map_get_entry("bbb", &m));
	printf("%s\n", (char *) map_get_entry("uuu", &m));

	return 0;
}