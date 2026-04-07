#include "inventory.h"
#include "cli.h"



int main() {
    open_inventory();
    init_cli();
    close_inventory();
    return 0;
}