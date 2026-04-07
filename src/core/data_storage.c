#include "data_storage.h"
#include "inventory.h"
#include <stdlib.h>



static FILE* save_path = NULL;

static void write_product(void *data) {
    fwrite(data, sizeof(Product), 1, save_path);
} 

void load_bin_data() {
    save_path = fopen(DEFAULT_DAT_SAVE_PATH, "r");
    Product* buffer = malloc(sizeof(Product));

    if (buffer == NULL) {
        perror("Failed to allocate memory");
        return;
    };

    while (fread(buffer, sizeof(Product), 1, save_path) == 1) {
        add_to_inventory(buffer);
        buffer = malloc(sizeof(Product));
        if (buffer == NULL) {
            perror("Failed to allocate memory");
            return;
        }
    }
    fclose(save_path);
}


void save_bin_data() {
    save_path = fopen(DEFAULT_DAT_SAVE_PATH, "w");
    if (save_path == NULL) {
        perror("Unable to open file!!!");
        return;
    }
    for_every_item(write_product);
    fclose(save_path);
}
