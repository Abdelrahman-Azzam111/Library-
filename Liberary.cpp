#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <ctime>

using namespace std;

// Class for Book

class Book {
public:
    string id;
    string title;
    string author;
    int publicationYear;
    bool isAvailable;
    double price;
    vector<string> reviews;
    double ratingSum = 0;
    int ratingCount = 0;

    Book(string id, string title, string author, int publicationYear, bool isAvailable, double price)
        : id(id), title(title), author(author), publicationYear(publicationYear), isAvailable(isAvailable), price(price) {}

    void addReview(const string& review, int rating) {
        if (rating < 1 || rating > 5) throw invalid_argument("Rating must be between 1 and 5.");
        reviews.push_back(review);
        ratingSum += rating;
        ratingCount++;
        cout << "Review added successfully!" << endl;
    }

    void displayReviewsAndRating() const {
        if (ratingCount > 0) {
            cout << "Average Rating: " << fixed << setprecision(1) << ratingSum / ratingCount << "/5" << endl;
        } else {
            cout << "No ratings yet." << endl;
        }
        if (!reviews.empty()) {
            cout << "Reviews:" << endl;
            for (const auto& review : reviews) {
                cout << "- " << review << endl;
            }
        } else {
            cout << "No reviews available." << endl;
        }
    }
};

// Class for Library

class Library {
private:
    vector<Book> books; // المتغير الخاص بتخزين الكتب

public:
void markBookUnavailable(const string& bookId) {
    Book* book = findBookById(bookId); // البحث عن الكتاب باستخدام bookId
    if (book) {
        book->isAvailable = false;
        cout << "Book marked as unavailable!" << endl;
    } else {
        cout << "Book not found!" << endl;
    }
}

void updateBookDetails(const string& bookId) {
    Book* book = findBookById(bookId); // البحث عن الكتاب باستخدام bookId
    if (book) {
        cout << "Enter new details for the book (leave blank to keep current values):" << endl;
        
        string title, author;
        int year;
        double price;

        // تعديل العنوان
        cout << "New Title (current: " << book->title << "): ";
        cin.ignore(); // لتجنب أي مشاكل في قراءة السطر التالي
        getline(cin, title);
        if (!title.empty()) {
            book->title = title;
        }

        // تعديل المؤلف
        cout << "New Author (current: " << book->author << "): ";
        getline(cin, author);
        if (!author.empty()) {
            book->author = author;
        }

        // تعديل سنة النشر
        cout << "New Publication Year (current: " << book->publicationYear << "): ";
        string yearInput;
        getline(cin, yearInput);
        if (!yearInput.empty()) {
            try {
                year = stoi(yearInput);
                book->publicationYear = year;
            } catch (exception&) {
                cout << "Invalid input. Keeping the current year." << endl;
            }
        }

        // تعديل السعر
        cout << "New Price (current: " << fixed << setprecision(2) << book->price << "): ";
        string priceInput;
        getline(cin, priceInput);
        if (!priceInput.empty()) {
            try {
                price = stod(priceInput);
                book->price = price;
            } catch (exception&) {
                cout << "Invalid input. Keeping the current price." << endl;
            }
        }

        cout << "Book details updated successfully!" << endl;
    } else {
        cout << "Book not found!" << endl;
    }
}

    void addBook(const Book& book) {
        books.push_back(book);
    }

    Book* findBookById(const string& bookId) {
        for (auto& book : books) {
            if (book.id == bookId) {
                return &book;
            }
        }
        return nullptr;
    }

    void removeBook(const string& bookId) {
        auto it = remove_if(books.begin(), books.end(), [&](const Book& book) { return book.id == bookId; });
        if (it != books.end()) {
            books.erase(it, books.end());
            cout << "Book removed successfully!" << endl;
        } else {
            cout << "Book not found!" << endl;
        }
    }

    void displayAvailableBooks() const {
        cout << "Available Books:" << endl;
        for (const auto& book : books) {
            if (book.isAvailable) {
                cout << "ID: " << book.id << ", Title: " << book.title
                     << ", Author: " << book.author << ", Year: " << book.publicationYear
                     << ", Price: $" << fixed << setprecision(2) << book.price << endl;
            }
        }
    }

    void searchBooks(const string& query) const {
        bool found = false;
        for (const auto& book : books) {
            if (book.title.find(query) != string::npos || book.author.find(query) != string::npos) {
                cout << "Book Found - ID: " << book.id << ", Title: " << book.title
                     << ", Author: " << book.author << ", Year: " << book.publicationYear
                     << ", Price: $" << fixed << setprecision(2) << book.price << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No books found matching the query: " << query << endl;
        }
    }

    void listBooksByAuthor(const string& author) {
        bool found = false;
        for (const auto& book : books) {
            if (book.author == author) {
                cout << "ID: " << book.id << ", Title: " << book.title << ", Year: " << book.publicationYear << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No books found by the author: " << author << endl;
        }
    }

    void displayBooksByYear(int year) {
        bool found = false;
        for (const auto& book : books) {
            if (book.publicationYear == year) {
                cout << "ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No books found published in the year: " << year << endl;
        }
    }

    void sortBooksByPrice() {
        sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
            return a.price < b.price;
        });
        cout << "Books sorted by price!" << endl;
    }

    void displayBooksInPriceRange(double minPrice, double maxPrice) {
        bool found = false;
        for (const auto& book : books) {
            if (book.price >= minPrice && book.price <= maxPrice) {
                cout << "ID: " << book.id << ", Title: " << book.title << ", Price: $" << fixed << setprecision(2) << book.price << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No books found in the price range: $" << minPrice << " - $" << maxPrice << endl;
        }
    }

    int getTotalNumberOfBooks() const {
        return books.size();
    }

    double getTotalRevenueFromSoldBooks() const {
        double total = 0;
        for (const auto& book : books) {
            if (!book.isAvailable) {
                total += book.price;
            }
        }
        return total;
    }

    void saveBooksToFile(const string& filename) const {
        ofstream outFile(filename);
        if (!outFile) throw runtime_error("Could not open file for writing.");

        for (const auto& book : books) {
            outFile << book.id << "," << book.title << "," << book.author << "," << book.publicationYear << ","
                    << book.isAvailable << "," << book.price << endl;
        }
        outFile.close();
    }

    void loadBooksFromFile(const string& filename) {
        ifstream inFile(filename);
        if (!inFile) throw runtime_error("Could not open file for reading.");

        books.clear();
        string id, title, author, line;
        int publicationYear;
        bool isAvailable;
        double price;

        while (getline(inFile, line)) {
            stringstream ss(line);
            getline(ss, id, ',');
            getline(ss, title, ',');
            getline(ss, author, ',');
            ss >> publicationYear >> isAvailable >> price;
            books.emplace_back(id, title, author, publicationYear, isAvailable, price);
        }
        inFile.close();
    }
};


// Class for User
class User {
public:
    string username;
    string password;
    bool isOwner;

    User(string username, string password, bool isOwner)
        : username(username), password(password), isOwner(isOwner) {}
};

// Class for Borrower
class Borrower {
public:
    string id;
    string name;
    vector<string> transactions;

    Borrower(string id, string name) : id(id), name(name) {}
};

// Class for Transaction
class Transaction {
public:
    string bookId;
    string borrowerId;
    time_t borrowDate;
    time_t returnDate;

    Transaction(string bookId, string borrowerId, time_t borrowDate, time_t returnDate)
        : bookId(bookId), borrowerId(borrowerId), borrowDate(borrowDate), returnDate(returnDate) {}
};

// Class for Customer
class Customer {
public:
    string id;
    string name;
    vector<string> orderHistory;

    Customer(string id, string name) : id(id), name(name) {}

    void addOrder(const string& orderId) {
        orderHistory.push_back(orderId);
    }
};

// Class for Order
class Order {
public:
    string orderId;
    string bookId;
    int quantity;
    double totalPrice;

    Order(string orderId, string bookId, int quantity, double totalPrice)
        : orderId(orderId), bookId(bookId), quantity(quantity), totalPrice(totalPrice) {}
};

// Class for ShoppingCart
class ShoppingCart {
private:
    vector<Order> orders;

public:
    void addOrder(const Order& order) {
        orders.push_back(order);
    }

    void viewCart() {
        for (const auto& order : orders) {
            cout << "Order ID: " << order.orderId << ", Book ID: " << order.bookId
                 << ", Quantity: " << order.quantity << ", Total Price: " << order.totalPrice << endl;
        }
    }
};

// Function to authenticate user
User authenticateUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (username == "owner" && password == "owner123") {
        return User(username, password, true);
    } else {
        return User(username, password, false);
    }
}
int main() {
    Library library;
    ShoppingCart cart;
    Borrower borrower("B001", "John Doe");
    Customer customer("C001", "Jane Smith");
    vector<Transaction> transactions;
    string filename = "library_data.txt";

    try {
        library.loadBooksFromFile(filename);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    User user = authenticateUser();

    int choice;
    do {
        cout << "\nLibrary Management System - Main Menu" << endl;
        if (user.isOwner) {
            cout << "1. Add a new book" << endl;
            cout << "2. Display available books" << endl;
            cout << "3. Search for books" << endl;
            cout << "4. Add a new transaction" << endl;
            cout << "5. View all transactions" << endl;
            cout << "6. Add a customer order" << endl;
            cout << "7. View shopping cart" << endl;
            cout << "8. Add a review" << endl;
            cout << "9. View reviews" << endl;
            cout << "10. Remove a book" << endl;
            cout << "11. Update book details" << endl;
            cout << "12. Mark a book as unavailable" << endl;
            cout << "13. List all books by a specific author" << endl;
            cout << "14. Display books published in a specific year" << endl;
            cout << "15. Sort books by price" << endl;
            cout << "16. Display books within a price range" << endl;
            cout << "17. Display total number of books" << endl;
            cout << "18. Display total revenue from sold books" << endl;
            cout << "19. Add a new borrower" << endl;
            cout << "20. View all borrowers" << endl;
            cout << "21. Add a new customer" << endl;
            cout << "22. View customer order history" << endl;
            cout << "23. Save library data to file" << endl;
            cout << "24. Load library data from file" << endl;
            cout << "25. Logout" << endl;
        } else {
            cout << "2. Display available books" << endl;
            cout << "3. Search for books" << endl;
            cout << "8. Add a review" << endl;
            cout << "9. View reviews" << endl;
            cout << "13. List all books by a specific author" << endl;
            cout << "14. Display books published in a specific year" << endl;
            cout << "15. Sort books by price" << endl;
            cout << "16. Display books within a price range" << endl;
            cout << "25. Logout" << endl;
        }
        cout << "Enter your choice: ";
        cin >> choice;

        try {
            if (user.isOwner) {
                switch (choice) {
                case 1: {
                    string id, title, author;
                    int year;
                    double price;
                    bool isAvailable;
                    cout << "Enter Book ID: ";
                    cin >> id;
                    cout << "Enter Title: ";
                    cin.ignore();
                    getline(cin, title);
                    cout << "Enter Author: ";
                    getline(cin, author);
                    cout << "Enter Publication Year: ";
                    cin >> year;
                    cout << "Enter Price: ";
                    cin >> price;
                    cout << "Is available (1 for yes, 0 for no): ";
                    cin >> isAvailable;
                    library.addBook(Book(id, title, author, year, isAvailable, price));
                    break;
                }
                case 2:
                    library.displayAvailableBooks();
                    break;
                case 3: {
                    string query;
                    cout << "Enter search query: ";
                    cin.ignore();
                    getline(cin, query);
                    library.searchBooks(query);
                    break;
                }
                case 4: {
                    string bookId, borrowerId;
                    time_t now = time(0);
                    cout << "Enter Book ID: ";
                    cin >> bookId;
                    cout << "Enter Borrower ID: ";
                    cin >> borrowerId;
                    transactions.emplace_back(bookId, borrowerId, now, 0);
                    cout << "Transaction added successfully!" << endl;
                    break;
                }
                case 5:
                    for (const auto& transaction : transactions) {
                        cout << "Book ID: " << transaction.bookId
                             << ", Borrower ID: " << transaction.borrowerId
                             << ", Borrow Date: " << ctime(&transaction.borrowDate);
                    }
                    break;
                case 6: {
                    string orderId, bookId;
                    int quantity;
                    double price;
                    cout << "Enter Order ID: ";
                    cin >> orderId;
                    cout << "Enter Book ID: ";
                    cin >> bookId;
                    cout << "Enter Quantity: ";
                    cin >> quantity;
                    cout << "Enter Total Price: ";
                    cin >> price;
                    cart.addOrder(Order(orderId, bookId, quantity, price));
                    customer.addOrder(orderId);
                    break;
                }
                case 7:
                    cart.viewCart();
                    break;
                case 8: {
                    string bookId, review;
                    int rating;
                    cout << "Enter Book ID: ";
                    cin >> bookId;
                    Book* book = library.findBookById(bookId);
                    if (book) {
                        cout << "Enter your review: ";
                        cin.ignore();
                        getline(cin, review);
                        cout << "Enter your rating (1-5): ";
                        cin >> rating;
                        book->addReview(review, rating);
                    } else {
                        cout << "Book not found!" << endl;
                    }
                    break;
                }
                case 9: {
                    string bookId;
                    cout << "Enter Book ID: ";
                    cin >> bookId;
                    Book* book = library.findBookById(bookId);
                    if (book) {
                        book->displayReviewsAndRating();
                    } else {
                        cout << "Book not found!" << endl;
                    }
                    break;
                }
                case 10: {
                    string bookId;
                    cout << "Enter Book ID: ";
                    cin >> bookId;
                    library.removeBook(bookId);
                    break;
                }
                case 11: {
                    string bookId;
                    cout << "Enter Book ID: ";
                    cin >> bookId;
                    library.updateBookDetails(bookId);
                    break;
                }
                case 12: {
                    string bookId;
                    cout << "Enter Book ID: ";
                    cin >> bookId;
                    library.markBookUnavailable(bookId);
                    break;
                }
                case 13: {
                    string author;
                    cout << "Enter Author Name: ";
                    cin.ignore();
                    getline(cin, author);
                    library.listBooksByAuthor(author);
                    break;
                }
                case 14: {
                    int year;
                    cout << "Enter Publication Year: ";
                    cin >> year;
                    library.displayBooksByYear(year);
                    break;
                }
                case 15:
                    library.sortBooksByPrice();
                    library.displayAvailableBooks();
                    break;
                case 16: {
                    double minPrice, maxPrice;
                    cout << "Enter Min Price: ";
                    cin >> minPrice;
                    cout << "Enter Max Price: ";
                    cin >> maxPrice;
                    library.displayBooksInPriceRange(minPrice, maxPrice);
                    break;
                }
                case 17:
                    cout << "Total Number of Books: " << library.getTotalNumberOfBooks() << endl;
                    break;
                case 18:
                    cout << "Total Revenue from Sold Books: $" << fixed << setprecision(2) << library.getTotalRevenueFromSoldBooks() << endl;
                    break;
                case 19: {
                    string id, name;
                    cout << "Enter Borrower ID: ";
                    cin >> id;
                    cout << "Enter Borrower Name: ";
                    cin.ignore();
                    getline(cin, name);
                    Borrower newBorrower(id, name);
                    cout << "Borrower added successfully!" << endl;
                    break;
                }
                case 20:
                    cout << "Borrower: ID=" << borrower.id << ", Name=" << borrower.name << endl;
                    break;
                case 21: {
                    string id, name;
                    cout << "Enter Customer ID: ";
                    cin >> id;
                    cout << "Enter Customer Name: ";
                    cin.ignore();
                    getline(cin, name);
                    Customer newCustomer(id, name);
                    cout << "Customer added successfully!" << endl;
                    break;
                }
                case 22:
                    cout << "Order History for " << customer.name << ":" << endl;
                    for (const auto& order : customer.orderHistory) {
                        cout << "- Order ID: " << order << endl;
                    }
                    break;
                case 23:
                    library.saveBooksToFile(filename);
                    cout << "Library data saved successfully!" << endl;
                    break;
                case 24:
                    library.loadBooksFromFile(filename);
                    cout << "Library data loaded successfully!" << endl;
                    break;
                case 25:
                    cout << "Logging out..." << endl;
                    user = authenticateUser();
                    break;
                default:
                    cout << "Invalid choice. Try again." << endl;
                }
            } else {
                switch (choice) {
                case 2:
                    library.displayAvailableBooks();
                    break;
                case 3: {
                    string query;
                    cout << "Enter search query: ";
                    cin.ignore();
                    getline(cin, query);
                    library.searchBooks(query);
                    break;
                }
                case 8: {
                    string bookId, review;
                    int rating;
                    cout << "Enter Book ID: ";
                    cin >> bookId;
                    Book* book = library.findBookById(bookId);
                    if (book) {
                        cout << "Enter your review: ";
                        cin.ignore();
                        getline(cin, review);
                        cout << "Enter your rating (1-5): ";
                        cin >> rating;
                        book->addReview(review, rating);
                    } else {
                        cout << "Book not found!" << endl;
                    }
                    break;
                }                        
                        
                
                case 9: {
                    string bookId;
                    cout << "Enter Book ID: ";
                    cin >> bookId;
                    Book* book = library.findBookById(bookId);
                    if (book) {
                        book->displayReviewsAndRating();
                    } else {
                        cout << "Book not found!" << endl;
                    }
                    break;
                }
                case 13: {
                    string author;
                    cout << "Enter Author Name: ";
                    cin.ignore();
                    getline(cin, author);
                    library.listBooksByAuthor(author);
                    break;
                }
                case 14: {
                    int year;
                    cout << "Enter Publication Year: ";
                    cin >> year;
                    library.displayBooksByYear(year);
                    break;
                }
                case 15:
                    library.sortBooksByPrice();
                    library.displayAvailableBooks();
                    break;
                case 16: {
                    double minPrice, maxPrice;
                    cout << "Enter Min Price: ";
                    cin >> minPrice;
                    cout << "Enter Max Price: ";
                    cin >> maxPrice;
                    library.displayBooksInPriceRange(minPrice, maxPrice);
                    break;
                }
                case 25:
                    cout << "Logging out..." << endl;
                    user = authenticateUser();
                    break;
                default:
                    cout << "Invalid choice. Try again." << endl;
                }
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    } while (choice != 25);

    return 0;
}