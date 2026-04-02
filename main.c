#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 300     //Maximum number of books in inventory
#define MAX_ORDERS 250    //Maximum number of orders of the customer

// Declaring Global Arrays to store Book data
char bookTitles[MAX_BOOKS][200];       // Titles of books
char bookAuthors[MAX_BOOKS][180];      // Authors of books
float bookPrices[MAX_BOOKS];           // Prices of books
int bookQty[MAX_BOOKS];                // Quantity available for each book
int totalBooks = 0;                    // Current number of books

// Declaring Global Arrays to store Order data
char orderTitles[MAX_ORDERS][100];       // Titles of ordered books
int orderQty[MAX_ORDERS];                // Quantity ordered for each book
int totalOrders = 0;                     // Current total number of orders

// ---------- STAFF PANEL FUNCTIONS ----------
// Add a new book to inventory
int addBook()
{
// Check if inventory has space
    if (totalBooks < MAX_BOOKS)
   {
        printf("\nEnter Book Title: ");
        scanf(" %[^\n]", bookTitles[totalBooks]);
        printf("Enter Author Name: ");
        scanf(" %[^\n]", bookAuthors[totalBooks]);
        printf("Enter Price: ");
        scanf("%f", &bookPrices[totalBooks]);
        printf("Enter Quantity: ");
        scanf("%d", &bookQty[totalBooks]);
        totalBooks++;                              // Increment total books count
        printf("\nBook Added Successfully!\n");
    }
else
   {
        printf("\nInventory Full!\n");
    }
    return 0;
}

// Update details of an existing book in the inventory
int updateBook()
{
    char title[100];
    int found = -1;
    printf("\nEnter Book Title to Update: ");
    scanf(" %[^\n]", title);

// Search for the book in inventory
    for (int i = 0; i < totalBooks; i++)
   {
        if (strcmp(bookTitles[i], title) == 0)
       {
            found = i;
            break;
        }
    }

// If book found in the inventory
    if (found != -1)
{
        printf("Enter New Author Name: ");
        scanf(" %[^\n]", bookAuthors[found]);
        printf("Enter New Price: ");
        scanf("%f", &bookPrices[found]);
        printf("Enter New Quantity: ");
        scanf("%d", &bookQty[found]);
        printf("\nBook Updated Successfully!\n");
    }
 else
   {
        printf("\nBook Not Found!\n");
    }
    return 0;
}

// Remove a book from inventory
int removeBook()
{
    char title[50];
    int found = -1;
    printf("\nEnter Book Title to Remove: ");
    scanf(" %[^\n]", title);

//Search for the book in the inventory
    for (int i = 0; i < totalBooks; i++)
{
        if (strcmp(bookTitles[i], title) == 0)
       {
            found = i;
            break;
        }
}

 // If book found in the inventory
    if (found != -1) {
        for (int i = found; i < totalBooks - 1; i++) {
            strcpy(bookTitles[i], bookTitles[i + 1]);
            strcpy(bookAuthors[i], bookAuthors[i + 1]);
            bookPrices[i] = bookPrices[i + 1];
            bookQty[i] = bookQty[i + 1];
        }
        totalBooks--;              // Decrement total books count
        printf("\nBook Removed Successfully!\n");
    } else {
        printf("\nBook Not Found!\n");
    }
    return 0;
}

// Display all books in the inventory
int displayBooks() {
 // If no books available
    if (totalBooks == 0) {
        printf("\nNo Books in Inventory!\n");
        return 0;
    }
    printf("\n--- Book Inventory ---\n");
    for (int i = 0; i < totalBooks; i++) {
        printf("%d. %s by %s | Price: %.3f | Qty: %d\n", i + 1, bookTitles[i], bookAuthors[i], bookPrices[i], bookQty[i]);
    }
    return 0;
}

// ---------- CUSTOMER PANEL FUNCTIONS ----------
// Search for a book by title
int searchBook() {
    char title[50];
    int found = 0;
    printf("\nEnter Book Title to Search: ");
    scanf(" %[^\n]", title);

    for (int i = 0; i < totalBooks; i++) {
        if (strcmp(bookTitles[i], title) == 0) {
            printf("Found: %s by %s | Price: %.3f | Qty: %d\n", bookTitles[i], bookAuthors[i], bookPrices[i], bookQty[i]);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("\nBook Not Found!\n");
    }
    return 0;
}

// Place an order for a book
int placeOrder() {
    char title[50];
    int qty;
    printf("\nEnter Book Title to Order: ");
    scanf(" %[^\n]", title);
    printf("Enter Quantity: ");
    scanf("%d", &qty);

    for (int i = 0; i < totalBooks; i++) {
        if (strcmp(bookTitles[i], title) == 0) {
            if (bookQty[i] >= qty) {             // Check quantity
                strcpy(orderTitles[totalOrders], title);
                orderQty[totalOrders] = qty;
                totalOrders++;                   // Increment total orders
                bookQty[i] -= qty;               // Reduce quantity
                printf("\nOrder Placed Successfully!\n");
            } else {
                printf("\nNot Enough Stock!\n");
            }
            return 0;
        }
    }
    printf("\nBook Not Found!\n");
    return 0;
}

// Cancel a customer's exiting order
int cancelOrder() {
    char title[50];
    int found = -1;
    printf("\nEnter Book Title to Cancel Order: ");
    scanf(" %[^\n]", title);

// Search for an order
    for (int i = 0; i < totalOrders; i++) {
        if (strcmp(orderTitles[i], title) == 0) {
            found = i;
            break;
        }
    }
    if (found != -1) {
// Restore stock
        for (int j = 0; j < totalBooks; j++) {
            if (strcmp(bookTitles[j], title) == 0) {
                bookQty[j] += orderQty[found];
                break;
            }
        }
        for (int i = found; i < totalOrders - 1; i++) {
            strcpy(orderTitles[i], orderTitles[i + 1]);
            orderQty[i] = orderQty[i + 1];
        }
        totalOrders--;            // Decrease total orders
        printf("\nOrder Cancelled!\n");
    } else {
        printf("\nOrder Not Found!\n");
    }
    return 0;
}

// Display all customer orders
int displayOrders() {
    if (totalOrders == 0) {
        printf("\nNo Orders Placed!\n");
        return 0;
    }
    printf("\n--- Customer Orders ---\n");
    for (int i = 0; i < totalOrders; i++) {
        printf("%d. %s | Qty: %d\n", i + 1, orderTitles[i], orderQty[i]);
    }
    return 0;
}

// ---------- MAIN MENU OF STAFF AND CUSTOMER PANEL ----------
int main() {
    int choice, staffChoice, customerChoice;

    while (1) {
        printf("\n--- Bookstore Management System ---\n");     // Main menu
        printf("1. Staff Panel\n");
        printf("2. Customer Panel\n");
        printf("3. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

// Staff Panel Menu
        if (choice == 1) {
            while (1) {
                printf("\n--- Staff Panel ---\n");
                printf("1. Add New Book\n");
                printf("2. Update Book\n");
                printf("3. Remove Book\n");
                printf("4. Display All Books\n");
                printf("5. Back to Main Menu\n");
                printf("Enter Choice: ");
                scanf("%d", &staffChoice);

                if (staffChoice == 1) addBook();
                else if (staffChoice == 2) updateBook();
                else if (staffChoice == 3) removeBook();
                else if (staffChoice == 4) displayBooks();
                else if (staffChoice == 5) break;
                else printf("\nInvalid Choice!\n");
            }
        }
// Customer Panel Menu
        else if (choice == 2) {
            while (1) {
                printf("\n--- Customer Panel ---\n");
                printf("1. Search Book\n");
                printf("2. Place Order\n");
                printf("3. Cancel Order\n");
                printf("4. Display All Orders\n");
                printf("5. Back to Main Menu\n");
                printf("Enter Choice: ");
                scanf("%d", &customerChoice);

                if (customerChoice == 1) searchBook();
                else if (customerChoice == 2) placeOrder();
                else if (customerChoice == 3) cancelOrder();
                else if (customerChoice == 4) displayOrders();
                else if (customerChoice == 5) break;
                else printf("\nInvalid Choice!\n");
            }
        }
// Exit Program
        else if (choice == 3) {
            printf("\nExiting Program...\n");
            break;
        }
        else {
            printf("\nInvalid Choice!\n");
        }
    }
    return 0;
}
