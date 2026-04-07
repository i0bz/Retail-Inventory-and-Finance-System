#include "inventory_handling.h"

#define HEADER_LINES "================================================================================================\n"

enum {
    NAME,
    PRICE,
    CATEGORY,
    QUANTITY,
    EXIT
};


static void update_category(Product* product) {
    printf("Enter Category: ");
    char* category = string_input();
    strcpy(product->category, category);
    free(category);
}
static void update_quantity(Product* product) {
    printf("Enter Quantity: ");
    size_t quantity = positive_integer_input();
    product->quantity = quantity;
}
static void update_price(Product* product) {
    printf("Enter price: ");
    size_t price = positive_integer_input();
    product->price = price;
}
static void update_name(Product* product) {
    printf("Enter Product Name: ");
    char* name = string_input();
    strcpy(product->name, name);
    free(name);
}

static void product_stats_header() {
    printf(HEADER_LINES);
    printf("ID\t\tName\t\tCategory\t\tPrice\t\tStock\t\tSold\n");
    printf(HEADER_LINES);
}
static void product_stats(void *data) {
    Product* product = data;
    printf("%llu\t\t%s\t\t%s\t\t%.2f\t\t%llu\t\t%llu\n", product->id, product->name, product->category, product->price, product->quantity, product->sold);
}
static void exit_prompt() {
    printf("Enter any to exit: ");
    char temp[5];
    fgets(temp, 5,stdin);
}

void main_menu() {
    printf(HEADER_LINES);
    printf("RETAIL STORE SYSTEM\n");
    printf(HEADER_LINES);
    printf("1. Add Product\n");
    printf("2. Display Products\n");
    printf("3. Search Product\n");
    printf("4. Update Product\n");
    printf("5. Delete Product\n");
    printf("6. Process Sale\n");
    printf("7. Save Records\n");
    printf("8. Exit\n");
}

void add_product() {
    printf(HEADER_LINES);
    printf("Add Product\n");
    printf(HEADER_LINES);

    size_t id;
    char* name;
    char* category;
    float price;
    size_t quantity;
    size_t sold;

    
    printf("ID: ");
    id = positive_integer_input();
    while (retrieve_from_inventory(id) != NULL) {
        printf("ID already exists! Enter again: ");
        id = positive_integer_input();
    }
    
    printf("Name: ");
    name = string_input();
    
    printf("Category: ");
    category = string_input();
    
    printf("Price: ");
    price = positive_float_input();
    
    printf("Quantity: ");
    quantity = positive_integer_input();
    
    add_to_inventory(create_product(id, name, category, price, quantity));

    printf(HEADER_LINES);
    exit_prompt();
}

void display_products() {
    product_stats_header();
    for_every_item(product_stats);
    printf(HEADER_LINES);
    exit_prompt();
}

void search_product() {
    printf(HEADER_LINES);
    printf("Product Search\n");
    printf(HEADER_LINES);

    size_t id;
    printf("Enter ID: ");
    id = positive_integer_input();
    Product* product = retrieve_from_inventory(id);
    if (product == NULL) {
        printf("Product not found.\n");
        exit_prompt();
        return;
    }
    product_stats_header();
    product_stats(product);
    printf(HEADER_LINES);
    exit_prompt();
    
}

void update_product() {
    printf(HEADER_LINES);
    printf("Product Update\n");
    printf(HEADER_LINES);
    
    size_t id;
    printf("Enter ID: ");
    id = positive_integer_input();
    Product* product = retrieve_from_inventory(id);
    if (product == NULL) {
        printf("Product not found.\n");
        exit_prompt();
        return;
    }
    
    int option;
    while (1) {
        printf(HEADER_LINES);
        printf("1. Product Name\n");
        printf("2. Price\n");
        printf("3. Category\n");
        printf("4. Quantity\n");
        printf("5. Exit\n");
        printf("Choose which to update: ");
        option = (int) positive_integer_input();
        

        switch (option)
        {
        case NAME:
            update_name(product);
            break;
        case PRICE:
            update_price(product);
            break;
        case CATEGORY:
            update_category(product);
            break;
        case QUANTITY:
            update_quantity(product);
            break;
        case EXIT:
            return;
        default:
            printf("Choose from 1-5: ");
            option = (int) positive_integer_input();
            break;
        }
    }

}

void process_sale() {
    printf(HEADER_LINES);
    printf("Process Sale\n");
    printf(HEADER_LINES);

    size_t id;
    printf("Enter ID: ");
    id = positive_integer_input();
    Product* product = retrieve_from_inventory(id);
    if (product == NULL) {
        printf("Product not found.\n");
        exit_prompt();
        return;
    }

    size_t sold;
    printf("Enter quantity sold: ");
    sold = positive_integer_input();

    while(sold > product->quantity) {
        printf("Insufficient Stock!!\n");
        printf("Try again: ");
        sold = positive_integer_input();
    }
    product->quantity -= sold;
    product->sold += sold;
}

void delete_product() {
    printf(HEADER_LINES);
    printf("Delete Product\n");
    printf(HEADER_LINES);

    size_t id;
    printf("Enter ID: ");
    id = positive_integer_input();
    Product* product = retrieve_from_inventory(id);
    if (product == NULL) {
        printf("Product not found.\n");
        exit_prompt();
        return;
    }

    remove_from_inventory((ID)id);
    printf(HEADER_LINES);
    exit_prompt();
}

