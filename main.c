#include <stdio.h>

#define MAX_BOOKS 10

typedef struct
{
    int bookID;
    char title[40];
    char author[40];
    double price;
    int quantity;
} Book;

void listBooks();
void addBook();
void removeBook();
void findBook();
void updateBook();

Book books[MAX_BOOKS];
int totalBooks;

void listBooks() {
    printf("listBooks() :\n");
    if(totalBooks == 0) printf("The bookshop is empty\n");

    for(int i = 0; i < totalBooks; ++i){
        Book* book = &books[i];
        printf("BookID: %d\n", book->bookID);
        printf("Book title: %s\n", book->title);
        printf("Author name: %s\n", book->author);
        printf("Book price: %.2f\n", book->price);
        printf("Quantity: %d\n", book->quantity);
    }
}

void addBook(){
    Book book;
    printf("addBook():\n");
    printf("Enter bookID:\n");
    scanf("%d", &book.bookID);
    printf("Enter book title:\n");
    scanf("%s", &book.title);
    printf("Enter author name:\n");
    scanf("%d", &book.author);
    printf("Enter price:\n");
    scanf("%lf", &book.price);
    books[totalBooks] = book;
    totalBooks++;

    printf("The book has been added successfully\n");

}


int main(){

    int choice;
    int run = 1;
    while(run){
        printf("NTU BOOKSHOP MANAGEMENT PROGRAM:\n");
        printf("1: listBooks()\n");
        printf("2: addBook()\n");
        printf("3: removeBook()\n");
        printf("4: findBook()\n");
        printf("5: updateBook()\n");
        printf("6: quit\n");
        printf("Enter your choice:\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                listBooks();
                break;
            case 2:
                addBook();
                break;
            case 6:
                run = 0;
                break;
        }
    }

  return 0;
}

