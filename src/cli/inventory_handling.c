#include "inventory_handling.h"

#define HEADER_LINES "=======================================================================================================\n"
#define SMALL_HEADER_LINES "========================\n"
#define MEDIUM_HEADER_LINES "=============================================\n"
enum {
    NAME = 1,
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
    printf("%-15s%-25s%-25s%-15s%-15s%-15s\n","ID", "Product Name", "Category", "Price", "Stock", "Sold");
    printf(HEADER_LINES);
}
static void product_stats(void* data) {
    Product* product = data;
    printf("%-15llu%-25s%-25s%-15.2f%-15llu%-15llu\n", product->id, product->name, product->category, product->price, product->quantity, product->sold);
}




static void exit_prompt() {
    printf("Enter any to exit: ");
    char temp[5];
    fgets(temp, 5,stdin);
}

void main_menu() {
    printf(SMALL_HEADER_LINES);
    printf("RETAIL STORE SYSTEM\n");
    printf(SMALL_HEADER_LINES);
    printf("1. Add Product\n");
    printf("2. Display Products\n");
    printf("3. Search Product\n");
    printf("4. Update Product\n");
    printf("5. Delete Product\n");
    printf("6. Process Sale\n");
    printf("7. Display Top Selling Product\n");
    printf("8. Display Total Inventory Amount\n");
    printf("9. Filter by Category\n");
    printf("10. Save Records\n");
    printf("11. Exit\n");
}

void add_product() {
    printf(SMALL_HEADER_LINES);
    printf("Add Product\n");
    printf(SMALL_HEADER_LINES);

    size_t id;
    printf("ID: ");
    id = positive_integer_input();
    while (retrieve_from_inventory(id) != NULL) {
        printf("ID already exists! Enter again: ");
        id = positive_integer_input();
    }
    
    printf("Name: ");
    char* name;
    name = string_input();
    
    printf("Category: ");
    char* category;
    category = string_input();
    
    printf("Price: ");
    float price;
    price = positive_float_input();
    
    printf("Quantity: ");
    size_t quantity;
    quantity = positive_integer_input();
    
    add_to_inventory(create_product(id, name, category, price, quantity));

    printf(SMALL_HEADER_LINES);
    exit_prompt();
}

void display_products() {
    product_stats_header();
    for_every_item(product_stats);
    printf(SMALL_HEADER_LINES);
    exit_prompt();
}

void search_product() {
    printf(SMALL_HEADER_LINES);
    printf("Product Search\n");
    printf(SMALL_HEADER_LINES);

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
    printf(SMALL_HEADER_LINES);
    exit_prompt();
    
}

void update_product() {
    printf(SMALL_HEADER_LINES);
    printf("Product Update\n");
    printf(SMALL_HEADER_LINES);
    
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
        printf(SMALL_HEADER_LINES);
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
    printf(SMALL_HEADER_LINES);
    printf("Process Sale\n");
    printf(SMALL_HEADER_LINES);

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
    printf(SMALL_HEADER_LINES);
    printf("Delete Product\n");
    printf(SMALL_HEADER_LINES);

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
    printf(SMALL_HEADER_LINES);
    exit_prompt();
}



static size_t total_inventory_amount = 0;

static void get_product_stocks(void* data) {
    Product* product = data;
    total_inventory_amount += product->quantity;
    printf("%-15llu%-25s%-15llu\n", product->id, product->name, product->quantity);
}

void display_total_inventory() {
    total_inventory_amount = 0;
    printf(MEDIUM_HEADER_LINES);
    printf("%-15s%-25s%-15s\n", "ID", "Product Name", "Stock");
    printf(MEDIUM_HEADER_LINES);
    for_every_item(get_product_stocks);
    printf(MEDIUM_HEADER_LINES);
    printf("%-15s%-15llu\n", "Total Stocks", total_inventory_amount);
    printf(MEDIUM_HEADER_LINES);

    exit_prompt();
}

static Product* top_seller = NULL;


void top_selling_product(void* data) {
    Product* product = data;
    if (top_seller == NULL) {
        top_seller = product;
        return;
    }
    if (product->sold > top_seller->sold) top_seller = product;
}

void display_top_seller() {
    top_seller = NULL;
    for_every_item(top_selling_product);

    printf(MEDIUM_HEADER_LINES);
    printf("%-15s%-25s%-15s\n", "ID", "Product Name", "Sold");
    printf(MEDIUM_HEADER_LINES);
    printf("%-15llu%-15s%15llu\n", top_seller->id, top_seller->name, top_seller->sold);
    printf(MEDIUM_HEADER_LINES);
    exit_prompt();
}



static char* category_filter = NULL;
static size_t array_iterator = 0;
static Product** products_array = NULL;

void get_filtered_products(void* data) {
    Product* product = data;
    if (strcmp(product->category, category_filter) == 0) 
        products_array[array_iterator++] = product;
}

void filter_by_category() {
    array_iterator = 0;
    size_t size = inventory_usage();
    products_array = calloc(size, sizeof(Product*));
    printf(MEDIUM_HEADER_LINES);
    printf("Filter by Category\n");
    printf(MEDIUM_HEADER_LINES);

    printf("Enter category: ");
    category_filter = string_input();

    for_every_item(get_filtered_products);

    if (products_array[0] != NULL) {
        product_stats_header();
        for (size_t i = 0; i < size; i++) {
            if (products_array[i] == NULL) break;
            product_stats(products_array[i]);
        }
        printf(MEDIUM_HEADER_LINES);
    } else {
        printf(MEDIUM_HEADER_LINES);
        printf("No product found with category: %s\n", category_filter);
        printf(MEDIUM_HEADER_LINES);
    }
    


    free(category_filter);
    category_filter = NULL;

    free(products_array);
    products_array = NULL;

    exit_prompt();
}