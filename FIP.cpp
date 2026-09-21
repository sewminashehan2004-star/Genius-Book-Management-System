#include<iostream>
#include<string>
#include<fstream>
using namespace std;

// ============================= FUNCTION PROTOTYPES =============================
void logpage();
void availablebooks();
void MainMenu();
void userinterface();
void addbook();
void latestbook();
void buyermenu();
void searchbookbuyID();
void searchbookname();
void buyerCart();
void buyerlog();
void latestbookbuyer();
void buybook();
void availablebuy();
void geussavailablebooks();
void salesManagement();
void company();
void Deletebook();
void updatebook();
void Deletecartbook();
void guesscateagories();

// ============================= HELPER FUNCTIONS =============================

// Reads a book record from availablebook.txt.
// Format: CATEGORY|ID|TITLE|PRICE|AUTHOR
bool readAvailableBook(string line, string &category, int &id, string &title, double &price, string &author)
{
    int p1 = line.find("|");
    int p2 = line.find("|", p1 + 1);
    int p3 = line.find("|", p2 + 1);
    int p4 = line.find("|", p3 + 1);

    if (p1 == -1 || p2 == -1 || p3 == -1 || p4 == -1)
        return false;

    category = line.substr(0, p1);
    id = stoi(line.substr(p1 + 1, p2 - p1 - 1));
    title = line.substr(p2 + 1, p3 - p2 - 1);
    price = stod(line.substr(p3 + 1, p4 - p3 - 1));
    author = line.substr(p4 + 1);

    return true;
}

// Reads a book record from addbook.txt or cart.txt.
// Format: ID|TITLE|PRICE|AUTHOR
bool readSimpleBook(string line, int &id, string &title, double &price, string &author)
{
    int p1 = line.find("|");
    int p2 = line.find("|", p1 + 1);
    int p3 = line.find("|", p2 + 1);

    if (p1 == -1 || p2 == -1 || p3 == -1)
        return false;

    id = stoi(line.substr(0, p1));
    title = line.substr(p1 + 1, p2 - p1 - 1);
    price = stod(line.substr(p2 + 1, p3 - p2 - 1));
    author = line.substr(p3 + 1);

    return true;
}

// Displays the main book categories used by seller, buyer and guest modes.
void showCategoryMenu()
{
    cout << "(01) MARTIN WICKRAMASINGHE" << endl;
    cout << "(02) J.K. ROWLING" << endl;
    cout << "(03) GUNADASA AMARASEKARA" << endl;
    cout << "(04) EDIRIWEERA SARACHCHANDRA" << endl;
    cout << "(05) T.B. ILANGARATHNE" << endl;
    cout << "(06) EDUCATIONAL BOOKS" << endl;
    cout << "(07) CHILDREN BOOKS" << endl;
    cout << "(08) LATEST BOOKS" << endl;
    cout << "(09) EXIT" << endl;
}

// Converts the selected menu number into the category stored in the TXT file.
string getCategoryName(int choice)
{
    if (choice == 1) return "MARTIN WICKRAMASINGHE";
    if (choice == 2) return "J.K. ROWLING";
    if (choice == 3) return "GUNADASA AMARASEKARA";
    if (choice == 4) return "EDIRIWEERA SARACHCHANDRA";
    if (choice == 5) return "T.B. ILANGARATHNE";
    if (choice == 6) return "EDUCATIONAL";
    if (choice == 7) return "CHILDREN";
    return "";
}

// Displays books from the TXT file according to the selected category.
void displayCategoryBooks(int choice, bool showPrice)
{
    ifstream infile("availablebook.txt");

    string line;
    string category;
    string selectedCategory = getCategoryName(choice);

    int id;
    string title;
    string author;
    double price;

    bool found = false;

    if (!infile.is_open())
    {
        cout << "Error: availablebook.txt could not be opened." << endl;
        return;
    }

    while (getline(infile, line))
    {
        if (line.empty())
            continue;

        if (readAvailableBook(line, category, id, title, price, author))
        {
            if (category == selectedCategory)
            {
                found = true;

                cout << "Book ID : " << id << endl;
                cout << "Title   : " << title << endl;

                if (showPrice)
                    cout << "Price   : Rs. " << price << endl;

                cout << "Author  : " << author << endl;
                cout << "--------------------------------------------" << endl;
            }
        }
    }

    infile.close();

    if (!found)
        cout << "No books available in this category." << endl;
}

// Checks whether the selected book is already in the cart.
bool bookInCart(int searchID)
{
    ifstream infile("cart.txt");

    string line;
    int id;
    string title;
    string author;
    double price;

    while (getline(infile, line))
    {
        if (line.empty())
            continue;

        if (readSimpleBook(line, id, title, price, author))
        {
            if (id == searchID)
            {
                infile.close();
                return true;
            }
        }
    }

    infile.close();
    return false;
}

// Searches both the main catalog and seller-added books using Book ID.
bool findBookByID(int searchID, int &id, string &title, double &price, string &author)
{
    ifstream infile("availablebook.txt");

    string line;
    string category;

    while (getline(infile, line))
    {
        if (line.empty())
            continue;

        if (readAvailableBook(line, category, id, title, price, author))
        {
            if (id == searchID)
            {
                infile.close();
                return true;
            }
        }
    }

    infile.close();

    infile.open("addbook.txt");

    while (getline(infile, line))
    {
        if (line.empty())
            continue;

        if (readSimpleBook(line, id, title, price, author))
        {
            if (id == searchID)
            {
                infile.close();
                return true;
            }
        }
    }

    infile.close();

    return false;
}

// Searches both catalogs using the complete book title.
bool findBookByName(string searchName, int &id, string &title, double &price, string &author)
{
    ifstream infile("availablebook.txt");

    string line;
    string category;

    while (getline(infile, line))
    {
        if (line.empty())
            continue;

        if (readAvailableBook(line, category, id, title, price, author))
        {
            if (title == searchName)
            {
                infile.close();
                return true;
            }
        }
    }

    infile.close();

    infile.open("addbook.txt");

    while (getline(infile, line))
    {
        if (line.empty())
            continue;

        if (readSimpleBook(line, id, title, price, author))
        {
            if (title == searchName)
            {
                infile.close();
                return true;
            }
        }
    }

    infile.close();

    return false;
}

// Stores a selected book in cart.txt.
void addBookToCart(int id, string title, double price, string author)
{
    ofstream outfile("cart.txt", ios::app);

    if (outfile.is_open())
    {
        outfile << id << "|" << title << "|" << price << "|" << author << endl;

        outfile.close();

        cout << "Book added to cart successfully." << endl;
    }
    else
    {
        cout << "Error: Could not open cart.txt." << endl;
    }
}

// ============================= CART MANAGEMENT =============================

// Deletes a selected book from the buyer cart.
void Deletecartbook()
{
    int deleteID;
    int id;

    string title;
    string author;
    string line;

    double price;

    bool found = false;

    string newData = "";

    cout << "Enter the Book ID you want to delete: ";
    cin >> deleteID;

    ifstream infile("cart.txt");

    while (getline(infile, line))
    {
        if (line.empty())
            continue;

        if (!readSimpleBook(line, id, title, price, author))
            continue;

        if (id == deleteID)
        {
            found = true;
            continue;
        }

        newData += line + "\n";
    }

    infile.close();

    ofstream outfile("cart.txt", ios::trunc);

    outfile << newData;

    outfile.close();

    if (found)
        cout << "Book deleted from cart successfully!" << endl;
    else
        cout << "Book ID not found in cart!" << endl;
}

// Displays the buyer cart and completes the purchase process.
void buyerCart()
{
    while (true)
    {
        system("cls");

        cout << "\t\t\t  ----------------------------------------------------" << endl;
        cout << "\t\t\t                    -- YOUR CART --" << endl;
        cout << "\t\t\t  ----------------------------------------------------" << endl;

        ifstream cartfile("cart.txt");

        string line;

        int id;

        string title;
        string author;

        double price;

        bool hasBook = false;

        while (getline(cartfile, line))
        {
            if (line.empty())
                continue;

            if (readSimpleBook(line, id, title, price, author))
            {
                hasBook = true;

                cout << "Book ID : " << id << endl;
                cout << "Title   : " << title << endl;
                cout << "Price   : Rs. " << price << endl;
                cout << "Author  : " << author << endl;
                cout << "--------------------------------------------" << endl;
            }
        }

        cartfile.close();

        if (!hasBook)
        {
            cout << "Cart is empty!" << endl;
            system("pause");
            return;
        }

        int choice;

        cout << endl;
        cout << "01. Purchase books" << endl;
        cout << "02. Delete a book" << endl;
        cout << "03. Continue shopping" << endl;
        cout << "04. Go back" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            double grandTotal = 0;

            string salesData = "";

            bool validPurchase = true;

            ifstream buyfile("cart.txt");

            while (getline(buyfile, line))
            {
                if (line.empty())
                    continue;

                if (readSimpleBook(line, id, title, price, author))
                {
                    int quantity;
                    double lineTotal;

                    cout << "\nBook: " << title << endl;
                    cout << "Enter quantity: ";
                    cin >> quantity;

                    if (quantity <= 0)
                    {
                        cout << "Invalid quantity." << endl;
                        validPurchase = false;
                        break;
                    }

                    lineTotal = price * quantity;

                    grandTotal += lineTotal;

                    salesData += to_string(id) + "|" +
                                 title + "|" +
                                 to_string(price) + "|" +
                                 author + "|" +
                                 to_string(quantity) + "|" +
                                 to_string(lineTotal) + "\n";
                }
            }

            buyfile.close();

            if (!validPurchase)
            {
                system("pause");
                continue;
            }

            cout << "\n--------------------------------------------" << endl;
            cout << "Total Amount: Rs. " << grandTotal << endl;
            cout << "--------------------------------------------" << endl;

            char confirm;

            cout << "Confirm purchase? (y/n): ";
            cin >> confirm;

            if (confirm == 'y' || confirm == 'Y')
            {
                ofstream salesfile("sales.txt", ios::app);

                salesfile << salesData;

                salesfile.close();

                ofstream clearCart("cart.txt", ios::trunc);

                clearCart.close();

                cout << "Purchase completed successfully!" << endl;

                system("pause");

                return;
            }
            else
            {
                cout << "Purchase cancelled. Cart was not changed." << endl;
                system("pause");
            }
        }

        else if (choice == 2)
        {
            Deletecartbook();

            system("pause");
        }

        else if (choice == 3)
        {
            buybook();
            return;
        }

        else if (choice == 4)
        {
            return;
        }

        else
        {
            cout << "Invalid choice!" << endl;
            system("pause");
        }
    }
}

// ============================= BUYER SEARCH =============================

// Searches a book by ID and adds it to the cart.
void searchbookbuyID()
{
    int searchID;

    int id;

    string title;
    string author;

    double price;

    system("cls");

    cout << "\t\t\t  ----------------------------------------------------" << endl;
    cout << "\t\t\t                 -- SEARCH BOOK BY ID --" << endl;
    cout << "\t\t\t  ----------------------------------------------------" << endl;

    cout << "Enter the Book ID to search: ";
    cin >> searchID;

    if (bookInCart(searchID))
    {
        cout << "This book is already in the cart." << endl;

        system("pause");

        return;
    }

    if (findBookByID(searchID, id, title, price, author))
    {
        cout << "\nBook Found" << endl;

        cout << "----------------------------" << endl;

        cout << "Book ID : " << id << endl;
        cout << "Title   : " << title << endl;
        cout << "Price   : Rs. " << price << endl;
        cout << "Author  : " << author << endl;

        char choice;

        cout << "\nAdd to cart? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y')
            addBookToCart(id, title, price, author);
        else
            cout << "Book was not added to cart." << endl;
    }
    else
    {
        cout << "Book ID not found in the system!" << endl;
    }

    system("pause");
}

// Searches a book by its complete name and adds it to the cart.
void searchbookname()
{
    string bookName;

    int id;

    string title;
    string author;

    double price;

    system("cls");

    cout << "\t\t\t  ----------------------------------------------------" << endl;
    cout << "\t\t\t                -- SEARCH BOOK BY NAME --" << endl;
    cout << "\t\t\t  ----------------------------------------------------" << endl;

    cin.ignore();

    cout << "Enter the complete Book Name: ";
    getline(cin, bookName);

    if (findBookByName(bookName, id, title, price, author))
    {
        if (bookInCart(id))
        {
            cout << "This book is already in the cart." << endl;

            system("pause");

            return;
        }

        cout << "\nBook Found" << endl;

        cout << "----------------------------" << endl;

        cout << "Book ID : " << id << endl;
        cout << "Title   : " << title << endl;
        cout << "Price   : Rs. " << price << endl;
        cout << "Author  : " << author << endl;

        char choice;

        cout << "\nAdd to cart? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y')
            addBookToCart(id, title, price, author);
        else
            cout << "Book was not added to cart." << endl;
    }
    else
    {
        cout << "Book name not found in the system!" << endl;
    }

    system("pause");
}

// Buyer search menu.
void buybook()
{
    int choice;

    while (true)
    {
        system("cls");

        cout << "\t\t\t  ----------------------------------------------------" << endl;
        cout << "\t\t\t                     -- BUY BOOKS --" << endl;
        cout << "\t\t\t  ----------------------------------------------------" << endl;

        cout << "01. Search from Book ID" << endl;
        cout << "02. Search from Book Name" << endl;
        cout << "03. View Cart" << endl;
        cout << "04. Go Back" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            searchbookbuyID();
            break;

        case 2:
            searchbookname();
            break;

        case 3:
            buyerCart();
            break;

        case 4:
            return;

        default:
            cout << "Invalid choice!" << endl;
            system("pause");
            break;
        }
    }
}

// ============================= BUYER BOOK DISPLAY =============================

// Displays available books to buyers using data stored in availablebook.txt.
void availablebuy()
{
    int choice;

    while (true)
    {
        system("cls");

        cout << ".............................................." << endl;
        cout << "           -- AVAILABLE BOOKS --" << endl;
        cout << ".............................................." << endl;
        cout << endl;

        showCategoryMenu();

        cout << "\nEnter your category number: ";
        cin >> choice;

        if (choice >= 1 && choice <= 7)
        {
            system("cls");

            cout << "-- " << getCategoryName(choice) << " --" << endl;
            cout << "--------------------------------------------" << endl;

            displayCategoryBooks(choice, true);

            cout << endl;

            system("pause");
        }

        else if (choice == 8)
        {
            latestbookbuyer();
            return;
        }

        else if (choice == 9)
        {
            return;
        }

        else
        {
            cout << "Invalid choice!" << endl;
            system("pause");
        }
    }
}

// Displays seller-added books to buyers.
void latestbookbuyer()
{
    ifstream infile("addbook.txt");

    string line;

    int id;

    string title;
    string author;

    double price;

    bool found = false;

    system("cls");

    cout << "....................................................." << endl;
    cout << "                 -- LATEST ADDED BOOKS --" << endl;
    cout << "....................................................." << endl;

    while (getline(infile, line))
    {
        if (line.empty())
            continue;

        if (readSimpleBook(line, id, title, price, author))
        {
            found = true;

            cout << "Book ID : " << id << endl;
            cout << "Title   : " << title << endl;
            cout << "Price   : Rs. " << price << endl;
            cout << "Author  : " << author << endl;

            cout << "--------------------------------------------" << endl;
        }
    }

    infile.close();

    if (!found)
        cout << "No latest books are available." << endl;

    system("pause");
}

// Buyer main menu.
void buyermenu()
{
    int choice;

    while (true)
    {
        system("cls");

        cout << "\t\t\t  ----------------------------------------------------" << endl;
        cout << "\t\t\t              -- GENIUS BOOKSHOP BUYER MENU --" << endl;
        cout << "\t\t\t  ----------------------------------------------------" << endl;
        cout << endl;

        cout << "01. Available Books" << endl;
        cout << "02. Go to Buy" << endl;
        cout << "03. Cart" << endl;
        cout << "04. Log out" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            availablebuy();
            break;

        case 2:
            buybook();
            break;

        case 3:
            buyerCart();
            break;

        case 4:
            return;

        default:
            cout << "Invalid choice!" << endl;
            system("pause");
            break;
        }
    }
}

// ============================= BUYER LOGIN =============================

// Handles buyer login using the original project credentials.
void buyerlog()
{
    while (true)
    {
        string username;
        string password;

        system("cls");

        cout << "\t\t\t****************************************************************" << endl;
        cout << "\t\t\t              ~~ WELCOME TO THE GENIUS BOOKSHOP ~~" << endl;
        cout << "\t\t\t****************************************************************" << endl;
        cout << endl;

        cout << "Enter your username: ";
        cin >> username;

        if (username == "shehan")
        {
            cout << "Enter your password: ";
            cin >> password;

            if (password == "1234")
            {
                buyermenu();
                return;
            }

            else
            {
                cout << "Incorrect password. Please try again." << endl;
                system("pause");
            }
        }

        else
        {
            cout << "Incorrect username. Please try again." << endl;
            system("pause");
        }
    }
}

// ============================= SELLER FUNCTIONS =============================

// Displays seller-added books.
void latestbook()
{
    ifstream infile("addbook.txt");

    string line;

    int id;

    string title;
    string author;

    double price;

    bool found = false;

    system("cls");

    cout << "....................................................." << endl;
    cout << "                 -- LATEST ADDED BOOKS --" << endl;
    cout << "....................................................." << endl;

    while (getline(infile, line))
    {
        if (line.empty())
            continue;

        if (readSimpleBook(line, id, title, price, author))
        {
            found = true;

            cout << "Book ID : " << id << endl;
            cout << "Title   : " << title << endl;
            cout << "Price   : Rs. " << price << endl;
            cout << "Author  : " << author << endl;

            cout << "--------------------------------------------" << endl;
        }
    }

    infile.close();

    if (!found)
        cout << "No latest books available." << endl;

    cout << endl;

    system("pause");
}

// Adds a new seller book to addbook.txt.
void addbook()
{
    int id;

    string title;
    string author;

    double price;

    int choice;

    system("cls");

    cout << "....................................................." << endl;
    cout << "                 -- ADD NEW BOOK --" << endl;
    cout << "....................................................." << endl;

    cout << "Enter Book ID: ";
    cin >> id;

    cin.ignore();

    cout << "Enter Book Title: ";
    getline(cin, title);

    cout << "Enter Book Price: ";
    cin >> price;

    cin.ignore();

    cout << "Enter Book Author: ";
    getline(cin, author);

    ofstream outfile("addbook.txt", ios::app);

    if (outfile.is_open())
    {
        outfile << id << "|" << title << "|" << price << "|" << author << endl;

        outfile.close();

        cout << "\nBook added successfully!" << endl;
    }

    else
    {
        cout << "Error: Could not open addbook.txt." << endl;
    }

    cout << "\n01. Add another book" << endl;
    cout << "02. Go back" << endl;

    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1)
        addbook();
}

// Updates a seller-added book in addbook.txt.
void updatebook()
{
    int searchID;

    int id;

    string title;
    string author;
    string line;

    double price;

    bool found = false;

    string newData = "";

    int choice;

    system("cls");

    cout << "....................................................." << endl;
    cout << "                 -- UPDATE BOOK --" << endl;
    cout << "....................................................." << endl;

    cout << "Enter the Book ID you want to update: ";
    cin >> searchID;

    ifstream infile("addbook.txt");

    while (getline(infile, line))
    {
        if (line.empty())
            continue;

        if (!readSimpleBook(line, id, title, price, author))
            continue;

        if (id == searchID)
        {
            found = true;

            cin.ignore();

            cout << "Enter new Book Title: ";
            getline(cin, title);

            cout << "Enter new Price: ";
            cin >> price;

            cin.ignore();

            cout << "Enter new Author: ";
            getline(cin, author);
        }

        newData += to_string(id) + "|" +
                   title + "|" +
                   to_string(price) + "|" +
                   author + "\n";
    }

    infile.close();

    ofstream outfile("addbook.txt", ios::trunc);

    outfile << newData;

    outfile.close();

    if (found)
        cout << "Book updated successfully!" << endl;
    else
        cout << "Book ID not found in seller-added books!" << endl;

    cout << "\n01. Update another book" << endl;
    cout << "02. Go back" << endl;

    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1)
        updatebook();
}

// Deletes a seller-added book from addbook.txt.
void Deletebook()
{
    int deleteID;

    int id;

    string title;
    string author;
    string line;

    double price;

    bool found = false;

    string newData = "";

    int choice;

    system("cls");

    cout << "....................................................." << endl;
    cout << "                 -- DELETE BOOK --" << endl;
    cout << "....................................................." << endl;

    cout << "Enter the Book ID you want to delete: ";
    cin >> deleteID;

    ifstream infile("addbook.txt");

    while (getline(infile, line))
    {
        if (line.empty())
            continue;

        if (!readSimpleBook(line, id, title, price, author))
            continue;

        if (id == deleteID)
        {
            found = true;
            continue;
        }

        newData += line + "\n";
    }

    infile.close();

    ofstream outfile("addbook.txt", ios::trunc);

    outfile << newData;

    outfile.close();

    if (found)
        cout << "Book deleted successfully!" << endl;
    else
        cout << "Book ID not found in seller-added books!" << endl;

    cout << "\n01. Delete another book" << endl;
    cout << "02. Go back" << endl;

    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1)
        Deletebook();
}

// Displays the available catalog to the seller.
void availablebooks()
{
    int choice;

    while (true)
    {
        system("cls");

        cout << ".............................................." << endl;
        cout << "           -- AVAILABLE BOOKS --" << endl;
        cout << ".............................................." << endl;
        cout << endl;

        showCategoryMenu();

        cout << "\nEnter your category number: ";
        cin >> choice;

        if (choice >= 1 && choice <= 7)
        {
            system("cls");

            cout << "-- " << getCategoryName(choice) << " --" << endl;
            cout << "--------------------------------------------" << endl;

            displayCategoryBooks(choice, true);

            cout << endl;

            system("pause");
        }

        else if (choice == 8)
        {
            latestbook();
        }

        else if (choice == 9)
        {
            return;
        }

        else
        {
            cout << "Invalid choice!" << endl;
            system("pause");
        }
    }
}

// Displays company information.
void company()
{
    system("cls");

    cout << "\t\t\t  ----------------------------------------------------" << endl;
    cout << "\t\t\t                -- COMPANY DETAILS --" << endl;
    cout << "\t\t\t  ----------------------------------------------------" << endl;
    cout << endl;

    cout << "Address : No 12, Kandy Road, Kandy" << endl;
    cout << "Contact : 0812500963 / 0740627239" << endl;
    cout << "Email   : GeniusBookshop@gmail.com" << endl;

    cout << endl;

    system("pause");
}

// Displays all completed sales from sales.txt.
void salesManagement()
{
    ifstream infile("sales.txt");

    string line;

    int id;
    int quantity;

    string title;
    string author;

    double price;
    double total;

    double totalSales = 0;

    bool found = false;

    system("cls");

    cout << "....................................................." << endl;
    cout << "                 -- SALES MANAGEMENT --" << endl;
    cout << "....................................................." << endl;

    while (getline(infile, line))
    {
        if (line.empty())
            continue;

        int p1 = line.find("|");
        int p2 = line.find("|", p1 + 1);
        int p3 = line.find("|", p2 + 1);
        int p4 = line.find("|", p3 + 1);
        int p5 = line.find("|", p4 + 1);

        if (p1 == -1 || p2 == -1 || p3 == -1 ||
            p4 == -1 || p5 == -1)
            continue;

        id = stoi(line.substr(0, p1));

        title = line.substr(
            p1 + 1,
            p2 - p1 - 1
        );

        price = stod(
            line.substr(
                p2 + 1,
                p3 - p2 - 1
            )
        );

        author = line.substr(
            p3 + 1,
            p4 - p3 - 1
        );

        quantity = stoi(
            line.substr(
                p4 + 1,
                p5 - p4 - 1
            )
        );

        total = stod(
            line.substr(p5 + 1)
        );

        found = true;

        cout << "Book ID  : " << id << endl;
        cout << "Title    : " << title << endl;
        cout << "Price    : Rs. " << price << endl;
        cout << "Author   : " << author << endl;
        cout << "Quantity : " << quantity << endl;
        cout << "Total    : Rs. " << total << endl;

        cout << "--------------------------------------------" << endl;

        totalSales += total;
    }

    infile.close();

    if (!found)
        cout << "No sales data found." << endl;
    else
        cout << "Total Sales: Rs. " << totalSales << endl;

    system("pause");
}

// ============================= SELLER LOGIN =============================

// Seller main menu after successful login.
void MainMenu()
{
    int choice;

    while (true)
    {
        system("cls");

        cout << "\t\t\t  ----------------------------------------------------" << endl;
        cout << "\t\t\t              -- GENIUS BOOKSHOP SELLER MENU --" << endl;
        cout << "\t\t\t  ----------------------------------------------------" << endl;
        cout << endl;

        cout << "01. Available Books Details" << endl;
        cout << "02. Add Books" << endl;
        cout << "03. Update Book Details" << endl;
        cout << "04. Delete Books" << endl;
        cout << "05. Company Details" << endl;
        cout << "06. Sales Management" << endl;
        cout << "07. Log out" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            availablebooks();
            break;

        case 2:
            addbook();
            break;

        case 3:
            updatebook();
            break;

        case 4:
            Deletebook();
            break;

        case 5:
            company();
            break;

        case 6:
            salesManagement();
            break;

        case 7:
            return;

        default:
            cout << "Invalid choice!" << endl;
            system("pause");
            break;
        }
    }
}

// Seller login using the original project credentials.
void userinterface()
{
    while (true)
    {
        string username;
        string password;

        system("cls");

        cout << "\t\t\t****************************************************************" << endl;
        cout << "\t\t\t              ~~ WELCOME TO THE GENIUS BOOKSHOP ~~" << endl;
        cout << "\t\t\t****************************************************************" << endl;
        cout << endl;

        cout << "Enter your username: ";
        cin >> username;

        if (username == "shehan")
        {
            cout << "Enter your password: ";
            cin >> password;

            if (password == "1234")
            {
                MainMenu();
                return;
            }

            else
            {
                cout << "Incorrect password. Please try again." << endl;
                system("pause");
            }
        }

        else
        {
            cout << "Incorrect username. Please try again." << endl;
            system("pause");
        }
    }
}

// ============================= GUEST MODE =============================

// Displays book categories to guest users without prices.
void geussavailablebooks()
{
    int choice;

    while (true)
    {
        system("cls");

        cout << ".............................................." << endl;
        cout << "             -- GUEST BOOKS --" << endl;
        cout << ".............................................." << endl;
        cout << endl;

        showCategoryMenu();

        cout << "\nEnter your category number: ";
        cin >> choice;

        if (choice >= 1 && choice <= 7)
        {
            system("cls");

            cout << "-- " << getCategoryName(choice) << " --" << endl;
            cout << "--------------------------------------------" << endl;

            displayCategoryBooks(choice, false);

            cout << endl;

            system("pause");
        }

        else if (choice == 8)
        {
            latestbookbuyer();
            return;
        }

        else if (choice == 9)
        {
            return;
        }

        else
        {
            cout << "Invalid choice!" << endl;
            system("pause");
        }
    }
}

// Guest menu. Seller operations are protected by login.
void guesscateagories()
{
    int choice;

    while (true)
    {
        system("cls");

        cout << "\t\t\t  ----------------------------------------------------" << endl;
        cout << "\t\t\t                    -- GUEST MODE --" << endl;
        cout << "\t\t\t  ----------------------------------------------------" << endl;
        cout << endl;

        cout << "01. Available Books Details" << endl;
        cout << "02. Add Books" << endl;
        cout << "03. Update Book Details" << endl;
        cout << "04. Delete Books" << endl;
        cout << "05. Company Details" << endl;
        cout << "06. Log in" << endl;
        cout << "07. Back" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            geussavailablebooks();
            break;

        case 2:
            cout << "You must log in as a seller to add a book." << endl;
            system("pause");
            break;

        case 3:
            cout << "You must log in as a seller to update a book." << endl;
            system("pause");
            break;

        case 4:
            cout << "You must log in as a seller to delete a book." << endl;
            system("pause");
            break;

        case 5:
            company();
            break;

        case 6:
            userinterface();
            break;

        case 7:
            return;

        default:
            cout << "Invalid choice!" << endl;
            system("pause");
            break;
        }
    }
}

// ============================= LOGIN PAGE =============================

// Main application login and role selection page.
void logpage()
{
    int choice;

    while (true)
    {
        system("cls");

        cout << "\t\t\t****************************************************************" << endl;
        cout << "\t\t\t              ~~ WELCOME TO THE GENIUS BOOKSHOP ~~" << endl;
        cout << "\t\t\t****************************************************************" << endl;
        cout << endl;

        cout << "01. GUEST MODE" << endl;
        cout << "02. FOR SELLERS" << endl;
        cout << "03. FOR BUYERS" << endl;
        cout << "04. EXIT" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            guesscateagories();
            break;

        case 2:
            userinterface();
            break;

        case 3:
            buyerlog();
            break;

        case 4:
            system("cls");
            cout << "Thank you for using Genius Bookshop!" << endl;
            return;

        default:
            cout << "Invalid choice!" << endl;
            system("pause");
            break;
        }
    }
}

// ============================= PROGRAM START =============================

int main()
{
    // Start the Genius Bookshop application.
    logpage();

    return 0;
}