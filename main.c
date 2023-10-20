#include <stdio.h>
#include <strings.h>
#include <malloc.h>

#define MAX_BOOKS 5
#define MAX_CHAR_LENGTH 40

typedef struct {
    int bookID;
    char title[MAX_CHAR_LENGTH];
    char author[MAX_CHAR_LENGTH];
    double price;
    int quantity;
} Book;

void listBooks();

void addBook();

void removeBook();

void findBook();

void updateBook();

Book** books;
int totalBooks;

int main() {
    setbuf(stdout, 0);
    books = (Book**)malloc(MAX_BOOKS * sizeof(Book*));
    for(int i = 0; i < MAX_BOOKS; ++i)books[i] = malloc(sizeof(Book));

    printf("NTU BOOKSHOP MANAGEMENT PROGRAM:\n");
    printf("1: listBooks()\n");
    printf("2: addBook()\n");
    printf("3: removeBook()\n");
    printf("4: findBook()\n");
    printf("5: updateBook()\n");
    printf("6: quit\n");
    int choice;
    int run = 1;
    while (run) {
        printf("Enter your choice:\n");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                listBooks();
                break;
            case 2:
                addBook();
                break;
            case 3:
                removeBook();
                break;
            case 4:
                findBook();
                break;
            case 5:
                updateBook();
                break;
            case 6:
                run = 0;
                break;
        }
    }

    for(int i = 0; i < MAX_BOOKS; ++i)free(books[i]);
    free(books);
    return 0;
}



/////////////////////////////
//     UTILITY FUNCTIONS  ///
//                        ///
/////////////////////////////

/**
 * Read a line of input from stdin until the newline character '\n'.
 * @param buf The input buffer to store the input.
 */
void readline(char *buf) {
    fgets(buf, MAX_CHAR_LENGTH, stdin);
    // Remove the '\n' character
    buf[strcspn(buf, "\n")] = 0;
}

/**
 * Swap two elements in the [books] array.
 * @param i The index of the first element to be swapped.
 * @param j the index of the second element to be swapped.
 */
void swapBook(int i, int j) {
    Book* tmp = books[i];
    books[i] = books[j];
    books[j] = tmp;
}


int partition(int start, int end) {
    int pivot = end;
    int i = start - 1;
    for (int j = start; j < end; ++j) {
        if (books[j]->bookID <= books[pivot]->bookID) {
            i++;
            if (j != i) {
                swapBook(i, j);
            }
        }
    }
    swapBook(i + 1, pivot);
    return i + 1;
}

/**
 * Perform a quicksort on the [books] array using the bookID.
 * @param start The starting index of the array to be sorted.
 * @param end The ending index of the array to be sorted.
 */
void quicksortBooks(int start, int end) {
    if (start < end) {
        int pivot = partition(start, end);
        quicksortBooks(start, pivot - 1);
        quicksortBooks(pivot + 1, end);
    }
}

/**
 * Display the details of the book at the specified index in the [books] array.
 * @param index The index of the book to be displayed.
 */
void displayBook(int index) {
    Book *book = books[index];
    printf("BookID: %d\n", book->bookID);
    printf("Book title: %s\n", book->title);
    printf("Author name: %s\n", book->author);
    printf("Book price: %.2f\n", book->price);
    printf("Quantity: %d\n", book->quantity);
}

/**
 * Check if the given bookID exists in the books array.
 * @param bookID The ID of the book to be checked.
 * @return 1 if the bookID exists in the [books] array, 0 otherwise.
 */
int containBookID(int bookID) {
    for (int i = 0; i < totalBooks; ++i) {
        if (books[i]->bookID == bookID) return 1;
    }
    return 0;
}

/**
 * Find a book in the [books] array by its title and author.
 * @param title The title of the book to be searched.
 * @param author The author of the book to be searched.
 * @return Index of the book in the [books] array if found, -1 otherwise.
 */
int findBookByTitleAndAuthor(char const *title, char const *author) {
    for (int i = 0; i < totalBooks; ++i) {
        if (strcasecmp(title, books[i]->title) == 0 &&
            strcasecmp(author, books[i]->author) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * Remove a book from the [books] array at the specified index.
 * @param index The index of the book to be removed.
 */
void removeBookIndex(int index) {
    // Shift books back one element to remove the book at the given index
    for (int i = index; i < totalBooks - 1; ++i) {
        swapBook(i, i + 1);
    }
    totalBooks--;
}

/////////////////////////////
//      FUNCTION          ///
//                        ///
/////////////////////////////

void listBooks() {
    printf("listBooks():\n");
    if (totalBooks == 0) printf("The bookshop is empty\n");

    for (int i = 0; i < totalBooks; ++i) {
        displayBook(i);
    }
}


void addBook() {
    Book* book = books[totalBooks];
    printf("addBook():\n");
    printf("Enter bookID:\n");
    scanf("%d", &(book->bookID));
    getchar();

    printf("Enter book title:\n");
    readline(book->title);

    printf("Enter author name:\n");
    readline(book->author);

    printf("Enter price:\n");
    scanf("%lf", &(book->price));
    getchar();

    printf("Enter quantity:\n");
    scanf("%d", &(book->quantity));
    getchar();

    if (totalBooks >= MAX_BOOKS) {
        printf("The bookshop is full! Unable to addBook()\n");
        return;
    }

    if (containBookID(book->bookID)) {
        printf("The bookID has already existed! Unable to addBook()\n");
        return;
    }

//    books[totalBooks] = book;
    totalBooks++;

    if (totalBooks > 1)quicksortBooks(0, totalBooks - 1);
    printf("The book has been added successfully\n");

}

void removeBook() {
    printf("removeBook():\n");

    printf("Enter the target book title:\n");
    char title[MAX_CHAR_LENGTH];
    readline(title);

    printf("Enter the target author name:\n");
    char author[MAX_CHAR_LENGTH];
    readline(author);

    if (totalBooks == 0) {
        printf("The bookshop is empty\n");
        return;
    }

    int index = findBookByTitleAndAuthor(title, author);

    if (index != -1) {
        printf("The target book is removed\n");
        displayBook(index);
        removeBookIndex(index);
    } else {
        printf("The target book is not in the bookshop\n");
    }

}

void findBook() {
    printf("findBook():\n");

    printf("Enter the target book title:\n");
    char title[MAX_CHAR_LENGTH];
    readline(title);

    printf("Enter the target author name:\n");
    char author[MAX_CHAR_LENGTH];
    readline(author);

    int index = findBookByTitleAndAuthor(title, author);
    if (index != -1) {
        printf("The target book is found\n");
        displayBook(index);
    } else {
        printf("The target book is not found\n");
    }
}

void updateBook() {
    printf("updateBook():\n");

    printf("Enter the target book title:\n");
    char title[MAX_CHAR_LENGTH];
    readline(title);

    printf("Enter the target author name:\n");
    char author[MAX_CHAR_LENGTH];
    readline(author);

    int index = findBookByTitleAndAuthor(title, author);

    if (index != -1) {
        Book *book = books[index];
        printf("Enter updated book price:\n");
        scanf("%lf", &(book->price));

        printf("Enter updated quantity:\n");
        scanf("%d", &(book->quantity));

        printf("The target book is updated\n");
        displayBook(index);
    } else {
        printf("The target book is not in the bookshop\n");
    }


}

