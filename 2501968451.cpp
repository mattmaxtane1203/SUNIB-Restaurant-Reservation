// II. Case

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int amountOfCustomers = 0;

struct Customer{

    char name[10];
    int membershipNumber;
    Customer *next, *prev;

} *head = NULL, *tail = NULL;

Customer *createCustomer(char name[], int membershipNumber){

    Customer *newCustomer = (Customer*)calloc(1, sizeof(Customer));

    strcpy(newCustomer->name, name);
    newCustomer->membershipNumber = membershipNumber;

    return newCustomer;
}

void pushHead(Customer *newCustomer){

    if(head == NULL){
        head = tail = newCustomer;
        return;
    }

    head->prev = newCustomer;
    newCustomer->next = head;
    head = head->prev;
}

void pushTail(Customer *newCustomer){

    if(tail == NULL){
        head = tail = newCustomer;
        return;
    }

    tail->next = newCustomer;
    newCustomer->prev = tail;
    tail = tail->next;
}

void insert(char name[], int membershipNumber){

    Customer *newCustomer = createCustomer(name, membershipNumber);

    amountOfCustomers++;

    if(head == NULL && tail == NULL){
        head = tail = newCustomer;
        return;
    }

    if(newCustomer->membershipNumber > head->membershipNumber){
        pushHead(newCustomer);
        return;
    }

    if(newCustomer->membershipNumber <= tail->membershipNumber){
        pushTail(newCustomer);
        return;
    }

    Customer *cursor = head;
    while(cursor->membershipNumber >= newCustomer->membershipNumber){
        cursor = cursor->next;
    }

    newCustomer->next = cursor;
    newCustomer->prev = cursor->prev;
    cursor->prev->next = newCustomer;
    cursor->prev = newCustomer;
}

void dequeue(){
    
    amountOfCustomers--;

    if(head == tail){
        free(head);
        head = tail = NULL;
        return;
    }

    head = head->next;
    free(head->prev);
    head->prev = NULL;
}

void printPriorityQueue(){

    int counter = 1;
    Customer *cursor = head;
    while(cursor != NULL){
        printf("%d. %s\n", counter, cursor->name);
        cursor = cursor->next;
        counter++;
    }
}

void mainMenu();

void printHeader(){

    puts("============================");
    puts("SUNIB Restaurant Reservation");
    puts("============================");
}

void printMenu(){

    puts("1. Add Customer to Queue");
    puts("2. Serve One");
    puts("3. Serve All");
    puts("4. Dismiss Queue");
    puts("0. Exit");
}

void addCustomerToQueuePage(){

    system("cls");

    char tempName[21];
    char tempMembership[7];
    int tempMembershipNumber;
    do{
        printf("Input name and membership [VVIP | VIP | Member | Guest] (case sensitive): ");
        scanf("%s %s", &tempMembership, &tempName); getchar();
    } while(strlen(tempName) < 3 || strlen(tempName) > 20);

    // printf("%s\n", tempName);
    // printf("%s\n", tempMembership);

    if(strcmp(tempMembership, "VVIP") == 0){
        tempMembershipNumber = 4;
    }
    
    else if(strcmp(tempMembership, "VIP") == 0){
        tempMembershipNumber = 3;
    }

    else if(strcmp(tempMembership, "Member") == 0){
        tempMembershipNumber = 2;
    }

    else if(strcmp(tempMembership, "Guest") == 0){
        tempMembershipNumber = 1;
    }

    else{
        printf("Invalid Membership Status!");
        getchar();
        mainMenu();
    }

    // printf("%d\n", tempMembershipNumber);

    insert(tempName, tempMembershipNumber);
    printf("Customer successfully added!");
    getchar();
    mainMenu();
}

void serveOnePage(){

    if(amountOfCustomers > 0){

        if(head->membershipNumber == 4){
            printf("Attention! %s is being served at VVIP table", head->name);
        }

        else if(head->membershipNumber == 3){
            printf("Attention! %s is being served at VIP table", head->name);
        }

        else if(head->membershipNumber == 2){
            printf("Attention! %s is being served at Member table", head->name);
        }

        else{
            printf("Attention! %s is being served at Guest table", head->name);
        }

        dequeue();
        getchar();
        mainMenu();
    }

    printf("No one in waiting line");
    getchar();
    mainMenu();
}

void serveAllPage(){

    if(amountOfCustomers > 0){

        while(head != NULL){
            if(head->membershipNumber == 4){
                printf("Attention! %s is being served at VVIP table\n", head->name);
            }
            else if(head->membershipNumber == 3){
                printf("Attention! %s is being served at VIP table\n", head->name);
            }
            else if(head->membershipNumber == 2){
                printf("Attention! %s is being served at Member table\n", head->name);
            }
            else{
                printf("Attention! %s is being served at Guest table\n", head->name);
            }
            
            dequeue();
        }

        getchar();
        mainMenu();
    }

    printf("No one in waiting line");
    getchar();
    mainMenu();
}

void dismissQueuePage(){

    if(amountOfCustomers > 0){

        while(head != NULL){
            dequeue();
        }
    }

    printf("End of the day!");
    getchar();
    mainMenu();
}

void mainMenu(){

    system("cls");
    printHeader();
    puts("");

    printf("Waiting Line:\n");
    printPriorityQueue();
    puts("");

    printMenu();

    int choice = -1;
    do{
        printf("Input Menu Number: ");
        scanf("%d", &choice); getchar();
    } while(choice < 0 || choice > 4);

    switch(choice){

        case 1:
            addCustomerToQueuePage();
            break;
        case 2:
            serveOnePage();
            break;
        case 3:
            serveAllPage();
            break;
        case 4:
            dismissQueuePage();
            break;
        case 0:
            exit(0);
            break;
    }
}

int main(){
    
    mainMenu();

    return 0;
}