#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <limits>

using namespace std;

const int MAX_ENTRIES = 100;

class Entry {
private:
    string uniqueID, bookISBN, bookTitle, bookAuthor, bookEdition, bookPublisher, bookGenre;

public:
    void setData(string uniqueID, string bookISBN, string bookTitle, string bookAuthor, string bookEdition, string bookPublisher, string bookGenre) {
        this->uniqueID = uniqueID;
        this->bookISBN = bookISBN;
        this->bookTitle = bookTitle;
        this->bookAuthor = bookAuthor;
        this->bookEdition = bookEdition;
        this->bookPublisher = bookPublisher;
        this->bookGenre = bookGenre;
    }

    string getUniqueID() { return uniqueID; }
    string getGenre() { return bookGenre; }

    void displayEntry() {
        cout << uniqueID << "\t" << bookISBN << "\t" << bookTitle << "\t" << bookAuthor << "\t"
             << bookEdition << "\t" << bookPublisher << "\t" << bookGenre << endl;
    }

    void modify(string bookISBN, string bookTitle, string bookAuthor, string bookEdition, string bookPublisher, string bookGenre) {
        this->bookISBN = bookISBN;
        this->bookTitle = bookTitle;
        this->bookAuthor = bookAuthor;
        this->bookEdition = bookEdition;
        this->bookPublisher = bookPublisher;
        this->bookGenre = bookGenre;
    }
};

class Collection {
private:
    Entry entries[MAX_ENTRIES];
    int totalEntries = 0;

    int locateEntry(const string& uniqueID) {
        for (int i = 0; i < totalEntries; i++) {
            if (entries[i].getUniqueID() == uniqueID) return i;
        }
        return -1;
    }

    bool isValidGenre(const string& bookGenre) {
        return bookGenre == "Fiction" || bookGenre == "Non-fiction";
    }

    void wait() {
        cout << "Press any key to continue..."; cin.ignore(); cin.get();
    }

public:
    void addEntry();
    void modifyEntry();
    void locateBook();
    void removeEntry();
    void showEntriesByGenre();
    void showAllEntries();
};

void Collection::addEntry() {
    string bookGenre;
    do {
        cout << "Enter category (Fiction / Non-fiction): ";
        getline(cin, bookGenre);
        if (!isValidGenre(bookGenre)) cout << "Category not found!" << endl;
    } while (!isValidGenre(bookGenre));

    string uniqueID;
    cout << "Enter Book ID: "; getline(cin, uniqueID);
    if (locateEntry(uniqueID) != -1) {
        cout << "Duplicate ID!" << endl;
        return;
    }

    string bookISBN, bookTitle, bookAuthor, bookEdition, bookPublisher;
    cout << "Enter ISBN: "; getline(cin, bookISBN);
    cout << "Enter Title: "; getline(cin, bookTitle);
    cout << "Enter Author: "; getline(cin, bookAuthor);
    cout << "Enter Edition: "; getline(cin, bookEdition);
    cout << "Enter Publication: "; getline(cin, bookPublisher);

    entries[totalEntries++].setData(uniqueID, bookISBN, bookTitle, bookAuthor, bookEdition, bookPublisher, bookGenre);
    cout << "Book added successfully!" << endl;
    wait();
}

void Collection::modifyEntry() {
    string uniqueID;
    cout << "Enter Book ID to edit: ";
    getline(cin, uniqueID);

    int index = locateEntry(uniqueID);
    if (index == -1) {
        cout << "Book not found!" << endl;
        wait();
        return;
    }

    string bookISBN, bookTitle, bookAuthor, bookEdition, bookPublisher, bookGenre;
    cout << "Enter new ISBN: "; getline(cin, bookISBN);
    cout << "Enter new Title: "; getline(cin, bookTitle);
    cout << "Enter new Author: "; getline(cin, bookAuthor);
    cout << "Enter new Edition: "; getline(cin, bookEdition);
    cout << "Enter new Publication: "; getline(cin, bookPublisher);
    cout << "Enter new Category (Fiction / Non-fiction): "; getline(cin, bookGenre);
    
    entries[index].modify(bookISBN, bookTitle, bookAuthor, bookEdition, bookPublisher, bookGenre);
    cout << "Book edited successfully!" << endl;
    wait();
}

void Collection::locateBook() {
    string uniqueID;
    cout << "Enter Book ID to search: ";
    getline(cin, uniqueID);

    int index = locateEntry(uniqueID);
    if (index == -1) cout << "Book not found!" << endl;
    else entries[index].displayEntry();
    
    wait();
}

void Collection::removeEntry() {
    string uniqueID;
    cout << "Enter Book ID to delete: ";
    getline(cin, uniqueID);

    int index = locateEntry(uniqueID);
    if (index == -1) {
        cout << "Book not found!" << endl;
        wait();
        return;
    }
    
    entries[index].displayEntry();
    cout << "Confirm delete? (y/n): ";
    char confirm;
    cin >> confirm;
    cin.ignore();
    if (confirm == 'y' || confirm == 'Y') {
        entries[index] = entries[--totalEntries];
        cout << "Book deleted successfully!" << endl;
    }
    wait();
}

void Collection::showEntriesByGenre() {
    string bookGenre;
    cout << "Enter category (Fiction / Non-fiction): ";
    getline(cin, bookGenre);
    if (!isValidGenre(bookGenre)) {
        cout << "Category not found!" << endl;
        wait();
        return;
    }

    cout << "ID\tISBN\tTitle\tAuthor\tEdition\tPublication\tCategory\n";
    for (int i = 0; i < totalEntries; i++) {
        if (entries[i].getGenre() == bookGenre) entries[i].displayEntry();
    }
    wait();
}

void Collection::showAllEntries() {
    if (totalEntries == 0) cout << "No books available.\n";
    else {
        cout << "ID\tISBN\tTitle\tAuthor\tEdition\tPublication\tCategory\n";
        for (int i = 0; i < totalEntries; i++) entries[i].displayEntry();
    }
    wait();
}

int main() {
    Collection library;
    bool running = true;
    int selection;

    while (running) {
        cout << "\n====== Library Management System ======\n";
        cout << "1 - Add Book\n2 - Edit Book\n3 - Search Book\n4 - Delete Book\n5 - View Books by Category\n6 - View All Books\n7 - Exit\n";
        cout << "Enter your choice: ";
        cin >> selection;
        cin.ignore();

        switch (selection) {
            case 1: library.addEntry(); break;
            case 2: library.modifyEntry(); break;
            case 3: library.locateBook(); break;
            case 4: library.removeEntry(); break;
            case 5: library.showEntriesByGenre(); break;
            case 6: library.showAllEntries(); break;
            case 7: running = false; break;
            default: cout << "Invalid choice!" << endl; system("pause");
        }
    }
    return 0;
}