#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// This class stores the details for one book.
class Book {
private:
    string title;
    string author;
    int pages;
    string id;
    bool borrowed;

public:
    Book(string t, string a, int p, string i, bool b)
        : title{t}, author{a}, pages{p}, id{i}, borrowed{b} {}

    string getID() const { return id; }
    bool getBorrowed() const { return borrowed; }
    void setBorrowed(bool value) { borrowed = value; }

    // This displays all information about a book.
    void displayBook() const {
        cout << "ID: " << id << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Pages: " << pages << endl;
        cout << "Status: " << (borrowed ? "Borrowed" : "Available") << endl;
    }

    // This prepares the book data for saving to the file.
    string getFileData() const {
        return title + "," + author + "," + to_string(pages) + "," + id + "," +
               (borrowed ? "true" : "false");
    }
};

// This reads the file and creates the Book objects.
vector<Book> loadBooks() {
    ifstream inFile{"bookData.txt"};
    vector<Book> books;
    string line;

    if (!inFile.is_open()) {
        cout << "The book file could not be opened." << endl;
        return books;
    }

    while (getline(inFile, line)) {
        string title, author, pagesText, id, borrowedText;
        stringstream stream{line};

        if (!getline(stream, title, ',') || !getline(stream, author, ',') ||
            !getline(stream, pagesText, ',') || !getline(stream, id, ',') ||
            !getline(stream, borrowedText)) {
            continue;
        }

        try {
            int pages = stoi(pagesText);
            bool borrowed = borrowedText == "true";
            books.push_back(Book{title, author, pages, id, borrowed});
        } catch (...) {
            // Skip a row if the page number is not valid.
        }
    }
    return books;
}

// This saves any changes back to the same file.
bool saveBooks(const vector<Book>& books) {
    ofstream outFile{"bookData.txt"};
    if (!outFile.is_open()) return false;

    for (const Book& book : books) {
        outFile << book.getFileData() << endl;
    }
    return true;
}

// This searches for a book by its ID.
int findBook(const vector<Book>& books, const string& id) {
    for (size_t i = 0; i < books.size(); i++) {
        if (books[i].getID() == id) return static_cast<int>(i);
    }
    return -1;
}

int main() {
    vector<Book> books = loadBooks();
    if (books.empty()) {
        cout << "No book data was loaded." << endl;
        return 1;
    }

    int choice = 0;
    while (choice != 5) {
        // Show the main menu.
        cout << "\nBOOK MANAGER" << endl;
        cout << "1. View all books" << endl;
        cout << "2. View one book" << endl;
        cout << "3. Borrow a book" << endl;
        cout << "4. Return a book" << endl;
        cout << "5. Quit" << endl;
        cout << "Choose an option: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number from 1 to 5." << endl;
            continue;
        }

        if (choice == 1) {
            // Display every book in the vector.
            for (const Book& book : books) {
                cout << endl;
                book.displayBook();
            }
        } else if (choice >= 2 && choice <= 4) {
            string id;
            cout << "Enter book ID: ";
            cin >> id;
            int position = findBook(books, id);

            if (position == -1) {
                cout << "Book not found." << endl;
            } else if (choice == 2) {
                books[position].displayBook();
            } else if (choice == 3 && !books[position].getBorrowed()) {
                books[position].setBorrowed(true);
                cout << "Book borrowed." << endl;
            } else if (choice == 4 && books[position].getBorrowed()) {
                books[position].setBorrowed(false);
                cout << "Book returned." << endl;
            } else {
                cout << "That action cannot be completed." << endl;
            }
        } else if (choice != 5) {
            cout << "Invalid choice." << endl;
        }
    }

    // Save the latest availability before closing.
    if (!saveBooks(books)) {
        cout << "The changes could not be saved." << endl;
        return 1;
    }

    cout << "Goodbye!" << endl;
    return 0;
}
