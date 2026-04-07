#include "inventory_handling.h"

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
    printf("=================================================\n");
    printf("ID\tProduct Name\tCategory\tPrice\tStock\tSold\n");
    printf("=================================================\n");
}
static void product_stats(void *data) {
    Product* product = data;
    printf("%llu\t%s\t%s\t%.2f\t%llu\t%llu\n", product->id, product->name, product->category, product->price, product->quantity, product->sold);
}
static void exit_prompt() {
    printf("Enter any to exit: ");
    char temp[5];
    fgets(temp, 5,stdin);
}

void main_menu() {
    printf("============================\n");
    printf("RETAIL STORE SYSTEM\n");
    printf("============================\n");
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
    printf("============================\n");
    printf("Add Product\n");
    printf("============================\n");

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

    printf("============================\n");
    exit_prompt();
}

void display_products() {
    product_stats_header();
    for_every_item(product_stats);
    printf("=================================================\n");
    exit_prompt();
}

void search_product() {
    printf("=================================================\n");
    printf("Product Search\n");
    printf("=================================================\n");

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
    printf("=================================================\n");
    exit_prompt();
    
}

void update_product() {
    printf("=================================================\n");
    printf("Product Update\n");
    printf("=================================================\n");
    
    size_t id;
    printf("Enter ID: ");
    id = positive_integer_input();
    Product* product = retrieve_from_inventory(id);
    if (product == NULL) {
        printf("Product not found.\n");
        exit_prompt();
        return;
    }
    int option = 0;
    while (option != 5) {
        if (option > 5) {
            printf("Choose from 1-5: ");
            option = (int) positive_integer_input();
            continue;
        }
        printf("=================================================\n");
        printf("1. Product Name\n");
        printf("2. Price\n");
        printf("3. Category\n");
        printf("4. Quantity\n");
        printf("5. Exit\n");
        printf("Choose which to update: ");
        option = (int) positive_integer_input();
        

        switch (option)
        {
        case 1:
            update_name(product);
            break;
        case 2:
            update_price(product);
            break;
        case 3:
            update_category(product);
            break;
        case 4:
            update_quantity(product);
            break;
        }
    }

}

void process_sale() {
    printf("=================================================\n");
    printf("Process Sale\n");
    printf("=================================================\n");

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
    printf("=================================================\n");
    printf("Delete Product\n");
    printf("=================================================\n");

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
}

