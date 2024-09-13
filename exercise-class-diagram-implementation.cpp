#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int maxProducts = 100;
const int maxCartItems = 100;
const int maxOrders = 100;

class Customer {
private:
    string customerName, username, password, confirm;
    string address, email;
    string contactNumber;
    int creditCardNumber;

public:
    Customer(const string& name, const string& add, string contact, int creditCard) :
        username(name), contactNumber(contact), creditCardNumber(creditCard), address(add) {}

    Customer() : username(""), address(""), contactNumber(""), creditCardNumber(0) {}

    void registerUser() {
        cin.ignore();
        cout << "\nInput your username: ";
        getline(cin, username);
        cout << "Input your password: ";
        getline(cin, password);
        cout << "\nPlease input your personal/contact details: " << endl;
        cout << "Address: ";
        getline(cin, address);
        cout << "Contact Number: ";
        getline(cin, contactNumber);
        cout << "Email: ";
        getline(cin, email);
        cout << "\nInput your credit card number: ";
        cin >> creditCardNumber;
        cout << "------------------------" << endl;
        cout << "Registered Successfully! " << endl;
        cout << "------------------------" << endl;
        cout << "\nHello " << username << "! " << "Welcome to Gitshop! " << endl;
    }
};

class Product {
public:
    string productID;
    string productName;
    double productPrice;

    Product(string id = "", string name = "", double price = 0.0)
        : productID(id), productName(name), productPrice(price) {}
};

class Order {
private:
    struct OrderDetails {
        Product items[maxCartItems];
        int quantities[maxCartItems];
        int size;
    };

    OrderDetails orders[maxOrders]; 
    int orderCount = 0; 

public:
    void addOrder(Product products[], int quantities[], int size) {
        if (orderCount < maxOrders) {
            orders[orderCount].size = size;
            for (int i = 0; i < size; ++i) {
                orders[orderCount].items[i] = products[i];
                orders[orderCount].quantities[i] = quantities[i];
            }
            orderCount++;
        } else {
            cout << "Order list is already full!" << endl;
        }
    }

    void viewOrders() {
        if (orderCount == 0) {
            cout << "No orders have been placed yet." << endl;
            return;
        }

        for (int i = 0; i < orderCount; ++i) {
            double total = 0.0;
            cout << "\nOrder ID: " << (i + 1) << endl;

            
            for (int j = 0; j < orders[i].size; ++j) {
                total += orders[i].items[j].productPrice * orders[i].quantities[j];
            }

            cout << "Total Amount: P" << total << endl;
            cout << "Order Details:\n";
            cout << left << setw(20) << "Product ID" << left << setw(20) << "Name" << left << setw(20) << "Price" << left << setw(20) << "Quantity" << endl;

            for (int j = 0; j < orders[i].size; ++j) {
                cout << left << setw(20) << orders[i].items[j].productID
                     << left << setw(20) << orders[i].items[j].productName
                     << left << setw(20) << orders[i].items[j].productPrice
                     << left << setw(20) << orders[i].quantities[j] << endl;
            }
        }
    }
};

class ShoppingCart {
private:
    Product cart[maxCartItems];
    int quantity[maxCartItems];
    int cartSize = 0;
    Order* orders;

public:
    ShoppingCart(Order* orders) : orders(orders) {}

    void addProduct(Product& product, int quantities = 1) {
        for (int i = 0; i < cartSize; ++i) {
            if (cart[i].productID == product.productID) {
                quantity[i] += quantities; 
            }
        }
        if (cartSize < maxCartItems) { 
            cart[cartSize] = product;
            quantity[cartSize] = quantities;
            cartSize++;
        }
        else {
            cout << "Cart is already full!" << endl;
        }
    }

    void viewCart() const {
        if (cartSize == 0) {
            cout << "Your shopping cart is empty." << endl;
            return;
        }
        cout << left << setw(20) << "\nProduct ID" << left << setw(20) << "Name"
             << left << setw(20) << "Price" << left << setw(20) << "Quantity" << endl;
        cout << "--------------------------------------------------------------------" << endl;

        for (int i = 0; i < cartSize; ++i) {
            cout << left << setw(19) << cart[i].productID << left << setw(20) << cart[i].productName << left << setw(20)
                 << cart[i].productPrice << left << setw(20) << quantity[i] << endl;
        }
    }

    void checkout() {
    if (cartSize == 0) {
        cout << "Your shopping cart is empty." << endl;
        return;
    }

    double total = 0.0;
    cout << "Checking out the following products:" << endl;
    cout << left << setw(20) << "Product ID" << left << setw(20) << "Name" << left << setw(20) 
         << "Price" << left << setw(20) << "Quantity" << endl;
    cout << "--------------------------------------------------------------------" << endl;

    for (int i = 0; i < cartSize; ++i) {
        cout << left << setw(20) << cart[i].productID << left << setw(20) << cart[i].productName << left << setw(20)
             << cart[i].productPrice << left << setw(20) << quantity[i] << endl;
        total += cart[i].productPrice * quantity[i];
    }
    cout << "--------------------------------------------------------------------" << endl;
    cout << "Total Amount: P" << total << endl;
    cout << "You have successfully checked out the products!" << endl;

    orders->addOrder(cart, quantity, cartSize);
    cartSize = 0; 
}

    static void displayProducts(Product products[], int size) {
        cout << left << setw(20) << "\nProduct ID" << left << setw(20) << "Name" << left << setw(20) << "Price" << endl;
        cout << "----------------------------------------------" << endl;

        for (int i = 0; i < size; ++i) {
            cout << left << setw(20) << products[i].productID << left << setw(20)
                 << products[i].productName << left << setw(20) << products[i].productPrice << endl;
        }
    }
};

int main() {
    Customer customer;
    int choice;
    int option;
    char exit;
    bool lastChoice = true;

    int productCount = 6; 
    Order order;
    ShoppingCart Cart(&order);

    do {
        cout << "WELCOME TO GITSHOP! " << endl;
        cout << "1. Register " << endl;
        cout << "2. Continue as a guest " << endl;
        cout << "Enter your option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                customer.registerUser();
                break;
            case 2:
                cout << "--------------------------------" << endl;
                cout << "You are now browsing as a guest " << endl;
                cout << "--------------------------------" << endl;
                break;
            default:
                cout << "Invalid input! Please try again" << endl;
                break;
        }
    } while (choice != 1 && choice != 2);

    Product products[maxProducts] = {
        Product("ABC", "Paper", 20), // product 1
        Product("DEF", "Pencil", 10), // product 2
        Product("GHI", "Ballpen", 15), // product 3
        Product("JKL", "Correction Tape", 30), // product 4
        Product("MNO", "Eraser", 5), // product 5
        Product("PQR", "Crayons", 25), // product 6
    };

    do {
        cout << "\nMENU" << endl;
        cout << "1. View Products " << endl;
        cout << "2. View Shopping Cart " << endl;
        cout << "3. View Orders " << endl;
        cout << "4. Exit " << endl;
        cout << "Enter your option: ";
        cin >> option;

        switch (option) {
            case 1:
                ShoppingCart::displayProducts(products, productCount);

                while (true) {
                    cout << "\nEnter the ID of the product you want to add to the shopping cart: ";
                    string id;
                    cin >> id;
                    for (char& c : id) { 
                    c = std::toupper(c); 
                    } 
                    bool found = false;
                    for (int i = 0; i < productCount; ++i) {
                        if (products[i].productID == id) {
                            Cart.addProduct(products[i]);
                            cout << "Product added successfully!" << endl;
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        cout << "Invalid product ID!" << endl;
                    }

                    cout << "Do you want to add another product? (Y/N): ";
                    char addMore;
                    cin >> addMore;
                    if (addMore == 'N' || addMore == 'n') break;
                }
                break;

            case 2: { 
                Cart.viewCart();
                cout << "\nDo you want to check out all the products? (Y/N): ";
                char checkoutChoice;
                cin >> checkoutChoice;
                if (checkoutChoice == 'Y' || checkoutChoice == 'y') {
                    Cart.checkout();
                }
                break;
            }

            case 3: {
                order.viewOrders();
                break;
            }

            case 4: {
                cout << "Are you sure you want to Exit? (Y/N): ";
                cin >> exit;
                if (exit == 'Y' || exit == 'y') {
                    lastChoice = false;
                }
                break;
            }

            default:
                cout << "Invalid Input! Please Try Again. " << endl;
                break;
        }
    } while (lastChoice);

    return 0;
}
