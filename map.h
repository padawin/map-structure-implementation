#define ENTRY_UPDATED 1
#define ENTRY_ADDED 2

typedef struct {
	int index;
	char *key;
	void *item;
} map_item;

typedef struct {
	int items_number;
	map_item *items;
} map;

void *map_get_entry(const char *key, map *collection);
int map_add_entry(const char *key, void *entry, map *collection);
int map_remove_entry(const char *key, map *collection);
