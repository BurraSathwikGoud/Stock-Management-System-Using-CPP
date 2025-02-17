///////////*******STOCK MANAGEMENT SYSTEM***********///////////


#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm> // For std::remove_if

using namespace std;

// Structure to represent a product
struct Product {
    int id;
    string name;
    int quantity;
    double price;
};

// Function prototypes
void addProduct(vector<Product>& inventory);
void displayProducts(const vector<Product>& inventory);
void saveToFile(const vector<Product>& inventory);
void loadFromFile(vector<Product>& inventory);
void deleteProduct(vector<Product>& inventory);

// Main function
int main() {
    vector<Product> inventory;
    int choice;

    // Load inventory from file
    loadFromFile(inventory);

    cout << "===== Stock Management System =====" << endl;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Product\n";
        cout << "2. Display Products\n";
        cout << "3. Delete Product\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addProduct(inventory);
                saveToFile(inventory);
                break;
            case 2:
                displayProducts(inventory);
                break;
            case 3:
                deleteProduct(inventory);
                saveToFile(inventory);
                break;
            case 4:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

// Add a new product
void addProduct(vector<Product>& inventory) {
    Product p;
    cout << "Enter product ID: ";
    cin >> p.id;
    cout << "Enter product name: ";
    cin.ignore(); // To clear input buffer
    getline(cin, p.name);
    cout << "Enter quantity: ";
    cin >> p.quantity;
    cout << "Enter price: ";
    cin >> p.price;

    inventory.push_back(p);
    cout << "Product added successfully!\n";
}

// Display all products
void displayProducts(const vector<Product>& inventory) {
    if (inventory.empty()) {
        cout << "No products in inventory.\n";
        return;
    }

    cout << "\nID\tName\t\tQuantity\tPrice\n";
    cout << "---------------------------------------------\n";
    for (const auto& p : inventory) {
        cout << p.id << "\t" << p.name << "\t\t" << p.quantity << "\t\t" << p.price << endl;
    }
}

// Save inventory to a file
void saveToFile(const vector<Product>& inventory) {
    ofstream file("inventory.txt");
    if (!file) {
        cerr << "Error saving to file.\n";
        return;
    }

    for (const auto& p : inventory) {
        file << p.id << "," << p.name << "," << p.quantity << "," << p.price << endl;
    }
    file.close();
    cout << "Inventory saved successfully!\n";
}

// Load inventory from a file
void loadFromFile(vector<Product>& inventory) {
    ifstream file("inventory.txt");
    if (!file) {
        return; // No file exists yet, so no action needed
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Product p;
        string temp;

        getline(ss, temp, ',');
        p.id = stoi(temp);
        getline(ss, p.name, ',');
        getline(ss, temp, ',');
        p.quantity = stoi(temp);
        getline(ss, temp, ',');
        p.price = stod(temp);

        inventory.push_back(p);
    }
    file.close();
}

// Delete a product
void deleteProduct(vector<Product>& inventory) {
    int id;
    cout << "Enter the product ID to delete: ";
    cin >> id;

    auto it = remove_if(inventory.begin(), inventory.end(), [id](const Product& p) {
        return p.id == id;
    });

    if (it != inventory.end()) {
        inventory.erase(it, inventory.end());
        cout << "Product deleted successfully!\n";
    } else {
        cout << "Product with ID " << id << " not found.\n";
    }
}
