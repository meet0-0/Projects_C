#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct item 
{
    char itemName[30];
    int quantity;
    int price;
    struct item *next;
};

struct invoice 
{
    char customerName[30];
    char date[20];
    int totalAmount;
    char paymentMode[10];
    int receivedAmount;
    struct item *items;
    struct invoice *next;
};

struct invoice *head = NULL;

void addItem(struct item **head, char name[], int quantity, int price) 
{
    struct item *newItem = (struct item *)malloc(sizeof(struct item));
    if (newItem == NULL) 
    {
        printf("Memory allocation failed.\n");
        return;
    }

    strcpy(newItem->itemName, name);
    newItem->quantity = quantity;
    newItem->price = price;
    newItem->next = NULL;

    if (*head == NULL) 
    {
        *head = newItem;
    } 
    else 
    {
        struct item *current = *head;
        while (current->next != NULL) 
        {
            current = current->next;
        }
        current->next = newItem;
    }
}

void addInvoice() 
{
    struct invoice *newInvoice = (struct invoice *)malloc(sizeof(struct invoice));
    if (newInvoice == NULL) 
    {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter customer name: ");
    scanf("%s", newInvoice->customerName);

    printf("Enter date (dd-mm-yyyy): ");
    scanf("%s", newInvoice->date);

    printf("Enter payment mode (cash, card, or cheque): ");
    scanf("%s", newInvoice->paymentMode);

    newInvoice->totalAmount = 0;
    newInvoice->receivedAmount = 0;
    newInvoice->items = NULL;

    int itemCount;
    printf("Enter number of items: ");
    scanf("%d", &itemCount);

    for (int i = 0; i < itemCount; i++) 
    {
        char itemName[30];
        int quantity, price;
        printf("\nEnter item name: ");
        scanf("%s", itemName);

        printf("Enter quantity: ");
        scanf("%d", &quantity);

        printf("Enter price: ₹");
        scanf("%d", &price);

        addItem(&(newInvoice->items), itemName, quantity, price);
        newInvoice->totalAmount += quantity * price;
    }
    
    printf("Total Amount: ₹%d\n", newInvoice->totalAmount);
    
    printf("Enter amount received: ₹");
    scanf("%d", &newInvoice->receivedAmount);

    if (head == NULL) 
    {
        head = newInvoice;
        newInvoice->next = head;
    } 
    else 
    {
        struct invoice *temp = head;
        while (temp->next != head)
        {
            temp = temp->next;
        }
        temp->next = newInvoice;
        newInvoice->next = head;
    }

    FILE *file = fopen("C:\\Users\\marsg\\OneDrive\\Desktop\\CP\\CP_PROJECT\\Project.txt", "a");
    if (file != NULL) 
    {
        fprintf(file, "%s %s %d %s %d %d\n", newInvoice->customerName, newInvoice->date, newInvoice->totalAmount, newInvoice->paymentMode, newInvoice->receivedAmount, itemCount);
        struct item *item = newInvoice->items;
        while (item != NULL) 
        {
            fprintf(file, "%s %d %d\n", item->itemName, item->quantity, item->price);
            item = item->next;
        }
        fclose(file);
    } 
    else 
    {
        printf("Failed to open file for writing.\n");
    }
}

void loadInvoices() 
{
    FILE *file = fopen("invoices.txt", "r");
    if (file != NULL) 
    {
        while (!feof(file)) 
        {
            struct invoice *newInvoice = (struct invoice *)malloc(sizeof(struct invoice));
            if (newInvoice == NULL) 
            {
                printf("Memory allocation failed.\n");
                fclose(file);
                return;
            }

            int itemCount;
            fscanf(file, "%s %s %d %s %d %d", newInvoice->customerName, newInvoice->date, &newInvoice->totalAmount, newInvoice->paymentMode, &newInvoice->receivedAmount, &itemCount);
            newInvoice->items = NULL;

            for (int i = 0; i < itemCount; i++) 
            {
                char itemName[30];
                int quantity, price;
                fscanf(file, "%s %d %d", itemName, &quantity, &price);
                addItem(&(newInvoice->items), itemName, quantity, price);
            }

            if (head == NULL) 
            {
                head = newInvoice;
                newInvoice->next = head;
            } 
            else 
            {
                struct invoice *temp = head;
                while (temp->next != head) 
                {
                    temp = temp->next;
                }
                temp->next = newInvoice;
                newInvoice->next = head;
            }
        }
        fclose(file);
    }
}

void searchInvoice(char name[]) 
{
    if (head == NULL) 
    {
        printf("No invoices available.\n");
        return;
    }

    struct invoice *current = head;
    int found = 0;
    do 
    {
        if (strcmp(current->customerName, name) == 0) 
        {
            printf("--------------------------------\n");
            printf("\n\t\t  Patel's Kitchen.");
            printf("--------------------------------\n");
            printf("Customer Name\t %s\n", current->customerName);
            printf("Date\t  %s\n", current->date);
            printf("Payment Mode\t  %s\n", current->paymentMode);
            printf("Total Amount\t  ₹%d\n", current->totalAmount);
            printf("Items:\n");
            struct item *item = current->items;
            printf("--------------------------------\n");
            while (item != NULL) 
            {
                printf("\tItem Name\t\t %s\n", item->itemName);
                printf("\tQuantity\t\t  %d\n", item->quantity);
                printf("\tPrice:\t\t    ₹%d\n", item->price);
                printf("--------------------------------\n");
                item = item->next;
            }
            printf("Amount Received: ₹%d\n", current->receivedAmount);
            printf("Change: ₹%d\n", current->receivedAmount - current->totalAmount);
            printf("--------------------------------\n");
            found = 1;
        }
        current = current->next;
    } while (current != head);

    if (!found) 
    {
        printf("Invoice not found.\n");
    }
}

void deleteInvoice(char name[]) 
{
    if (head == NULL) 
    {
        printf("No invoices to delete.\n");
        return;
    }

    struct invoice *current = head;
    struct invoice *prev = NULL;
    do 
    {
        if (strcmp(current->customerName, name) == 0) 
        {
            if (current == head) 
            {
                struct invoice *temp = head;
                while (temp->next != head) 
                {
                    temp = temp->next;
                }
                if (head->next == head) 
                {
                    free(head);
                    head = NULL;
                } 
                else 
                {
                    temp->next = head->next;
                    free(head);
                    head = temp->next;
                }
                printf("Invoice deleted.\n");
                return;
            } 
            else 
            {
                prev->next = current->next;
                free(current);
                printf("Invoice deleted.\n");
                return;
            }
        }
        prev = current;
        current = current->next;
    } 
    while (current != head);
    printf("Invoice not found.\n");
}

void displayInvoices()
{
    if (head == NULL) 
    {
        printf("No invoices available.\n");
        return;
    }

    struct invoice *current = head;
    do 
    {
        printf("Customer Name\t %s\n", current->customerName);
        printf("Date\t\t  %s\n", current->date);
        printf("Payment Mode\t %s\n", current->paymentMode);
        printf("Total Amount\t ₹%d\n", current->totalAmount);
        printf("Items:\n");
        struct item *item = current->items;
        while (item != NULL) 
        {
            printf("\tItem Name\t   %s\n", item->itemName);
            printf("\tQuantity\t    %d\n", item->quantity);
            printf("\tPrice\t\t     ₹%d\n", item->price);
            printf("--------------------------------\n");
            item = item->next;
        }
        printf("\n");
        printf("Amount Received\t   ₹%d\n", current->receivedAmount);
        printf("Change\t\t    ₹%d\n", current->receivedAmount - current->totalAmount);
        printf("--------------------------------\n");
        printf("\t\t  Come Back Soon.\n");
        current = current->next;
    } 
    while (current != head);
}

void freeItems(struct item *head) 
{
    struct item *current = head;
    while (current != NULL) 
    {
        struct item *temp = current;
        current = current->next;
        free(temp);
    }
}

void freeList() 
{
    if (head == NULL) 
    {
        return;
    }

    struct invoice *current = head;
    struct invoice *next;
    do 
    {
        next = current->next;
        freeItems(current->items);
        free(current);
        current = next;
    }
    while (current != head);
}

int main() 
{
    loadInvoices();
    int choice;
    char name[30];
    do 
    {
        printf("1. Add Invoice\n");
        printf("2. Search Invoice by Customer Name\n");
        printf("3. Delete Invoice\n");
        printf("4. Display All Invoices\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                addInvoice();
                break;
            case 2:
                printf("Search customer name: ");
                scanf("%s", name);
                searchInvoice(name);
                break;
            case 3:
                printf("Delete customer name: ");
                scanf("%s", name);
                deleteInvoice(name);
                break;
            case 4:
                displayInvoices();
                break;
            case 5:
                freeList();
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter again.\n");
        }
    } 
    while (choice != 5);
    return 0;
}