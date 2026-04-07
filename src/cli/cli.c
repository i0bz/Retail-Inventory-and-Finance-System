#include "cli.h"

enum {
    ADD = 1,
    DISPLAY,
    SEARCH,
    UPDATE,
    DELETE,
    PROCESS,
    SAVE,
    EXIT
};

void init_cli() {
    while(1) {
        size_t option;
        
        main_menu();
        printf("Choose an option: ");
        option = positive_integer_input();


        switch (option)
        {
        case ADD:
            add_product();
            break;
        case DISPLAY:
            display_products();
            break;
        case SEARCH:
            search_product();
            break;
        case UPDATE:
            update_product();
            break;
        case DELETE:
            delete_product();
            break;
        case PROCESS:
            process_sale();
            break;
        case SAVE:
            save_bin_data();
            break;
        case EXIT:
            return;
        default:
            printf("Choose from 1-8: ");
            option = positive_integer_input();
            break;
        }
    }
}