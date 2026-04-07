#include "inventory.h"
#include "cli.h"



int main() {
    open_inventory();
    load_bin_data();
    init_cli();
    save_bin_data();
    close_inventory();
    return 0;
}