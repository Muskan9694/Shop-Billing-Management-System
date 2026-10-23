
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

const int MAX_ITEMS = 50;
const float GST_RATE = 0.18f;
const float DISCOUNT_RATE = 0.05f;
const float DISCOUNT_LIMIT = 1000.0f;

struct Product {
    string name;
    float price;
    int quantity;
    float total;
};

int main() {
    string customerName, mobile;
    Product items[MAX_ITEMS];
    int itemCount = 0;
    char choice;
    float subtotal = 0.0f;
    float discount = 0.0f;
    float taxableAmount, gst, grandTotal;

    cout << "====================================\n";
    cout << "      SHOP BILLING MANAGEMENT\n";
    cout << "====================================\n";

    cout << "Enter customer name: ";
    getline(cin, customerName);

    cout << "Enter mobile number: ";
    getline(cin, mobile);

    do {
        if (itemCount >= MAX_ITEMS) {
            cout << "\nMaximum 50 items reached.\n";
            break;
        }

        cout << "\n--- Enter Product " << itemCount + 1 << " ---\n";
        cout << "Product name: ";
        getline(cin, items[itemCount].name);

        cout << "Price (Rs.): ";
        while (!(cin >> items[itemCount].price) ||
               items[itemCount].price < 0) {
            cout << "Enter a valid non-negative price: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Quantity: ";
        while (!(cin >> items[itemCount].quantity) ||
               items[itemCount].quantity <= 0) {
            cout << "Enter a valid quantity greater than 0: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        items[itemCount].total =
            items[itemCount].price * items[itemCount].quantity;

        subtotal += items[itemCount].total;
        itemCount++;

        cout << "Add another product? (y/n): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (choice == 'y' || choice == 'Y');

    if (itemCount == 0) {
        cout << "\nNo products added. Bill not created.\n";
        return 0;
    }

    if (subtotal >= DISCOUNT_LIMIT) {
        discount = subtotal * DISCOUNT_RATE;
    }

    taxableAmount = subtotal - discount;
    gst = taxableAmount * GST_RATE;
    grandTotal = taxableAmount + gst;

    cout << fixed << setprecision(2);

    cout << "\n\n============= CUSTOMER BILL =============\n";
    cout << "Customer Name : " << customerName << '\n';
    cout << "Mobile Number : " << mobile << '\n';
    cout << "-----------------------------------------\n";

    cout << left << setw(18) << "Product"
         << right << setw(8) << "Price"
         << setw(8) << "Qty"
         << setw(12) << "Total" << '\n';

    cout << "-----------------------------------------\n";

    for (int i = 0; i < itemCount; i++) {
        cout << left << setw(18) << items[i].name
             << right << setw(8) << items[i].price
             << setw(8) << items[i].quantity
             << setw(12) << items[i].total << '\n';
    }

    cout << "-----------------------------------------\n";
    cout << "Subtotal       : Rs. " << subtotal << '\n';
    cout << "Discount       : Rs. " << discount << '\n';
    cout << "Taxable Amount : Rs. " << taxableAmount << '\n';
    cout << "GST (18%)      : Rs. " << gst << '\n';
    cout << "GRAND TOTAL    : Rs. " << grandTotal << '\n';
    cout << "=========================================\n";
    cout << "        Thank you for shopping!\n";
    cout << "=========================================\n";

    // Save the bill in a text file
    ofstream file("bills.txt", ios::app);

    if (!file) {
        cout << "\nError: Bill could not be saved to file.\n";
        return 1;
    }

    file << fixed << setprecision(2);
    file << "\n============= CUSTOMER BILL =============\n";
    file << "Customer Name : " << customerName << '\n';
    file << "Mobile Number : " << mobile << '\n';
    file << "-----------------------------------------\n";

    file << left << setw(18) << "Product"
         << right << setw(8) << "Price"
         << setw(8) << "Qty"
         << setw(12) << "Total" << '\n';

    file << "-----------------------------------------\n";

    for (int i = 0; i < itemCount; i++) {
        file << left << setw(18) << items[i].name
             << right << setw(8) << items[i].price
             << setw(8) << items[i].quantity
             << setw(12) << items[i].total << '\n';
    }

    file << "-----------------------------------------\n";
    file << "Subtotal       : Rs. " << subtotal << '\n';
    file << "Discount       : Rs. " << discount << '\n';
    file << "Taxable Amount : Rs. " << taxableAmount << '\n';
    file << "GST (18%)      : Rs. " << gst << '\n';
    file << "GRAND TOTAL    : Rs. " << grandTotal << '\n';
    file << "=========================================\n";

    file.close();

    cout << "\nBill successfully saved in bills.txt\n";

    return 0;
}
