#include "DSA_File_Manager.h"
#include "DSA_Shopping_System.h"
#include "DSA_Ordering_System.h"
#include <sstream>
#include <iostream>
#include <string>


//SECTION 1: SAVING DATA TO FILES

// Save all registered Users
void FileManager::saveUsersToCSV(Vector<User*> users, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) return;

    // Header row for Excel columns
    outFile << "UserID,FirstName,Phone,City,Address,Password\n";
    for (int i = 0 ; i<users.vectorSize();i++)
    {User* u = users[i];
        outFile << u->getUserID() << ","
                << u->getUserName() << ","
                << u->getUserContactNumber() << ","
                << u->getUserCity() << ","
                << u->getUserAddress() << ","
                << u->getUserPassword() << "\n";
    }
    outFile.close();
}

// Save all Shops in system
void FileManager::saveShopsToCSV(Vector<Shop*> shops, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) return;

    outFile << "Name,ID,Location,Number\n";
    for (int i = 0 ; i<shops.vectorSize();i++) {
        Shop* s = shops[i];
        outFile << s->getShopName() << ","
                << s->getShopID() << ","
                << s->getShopLocation() << ","
                << s->getShopContactNumber() << "\n";
    }
    outFile.close();
}

// Save all Products
void FileManager::saveProductsToCSV(Vector<Product*> products, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) return;

    outFile << "ProductID,ShopName,ShopID,Name,Category,Price,Stock\n";
    for (int i = 0 ; i<products.vectorSize();i++) {
        Product* p = products[i];
        outFile << p->getProductID() << ","
                << p->getProductShopName() << ","
                << p->getProductShopID() << ","
                << p->getProductName() << ","
                << p->getProductCategory() << ","
                << p->getProductPrice() << ","
                << p->getAvailableProductItems() << "\n";
    }
    outFile.close();
}

// Save  Orders
void FileManager::saveOrdersToCSV(Vector<Order*> orders, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) return;

    outFile << "OrderID,UserID,ShopID,ShopName,Price\n";
    for (int i = 0 ; i<orders.vectorSize();i++) {
        Order*o = orders[i];
        outFile<< o->orderID     <<","
                << o->buyerID    << ","
                << o->shopID     << ","
                << o->shopName   << ","
                << o->orderPrice << "\n";
    }

    outFile.close();
}


// SECTION 2: REPORTING & ANALYTICS

// Show a quick summary of the whole system
void FileManager::generateSystemSummaryReport() {
    cout << "\n========== GLOBAL SYSTEM SUMMARY ==========\n";
    cout << "Total Users Registered : " << User::getUsersInSystem().vectorSize() << "\n";
    cout << "Total Shops Registered    : " << Shop::getShopsInSystem().vectorSize() << "\n";
    cout << "Total Products In System       : " << Product::getProductsInSystem().vectorSize() << "\n";
    cout << "Total Orders In System    : " << Order::allOrdersCount<< "\n";
    cout << "===========================================\n";
    Shop::shopPrinter();
    Product::productPrinter();
    User::userPrinter();
    Order::allOrderPrinter();
}

//SECTION 3: LOADING DATA FROM FILES


void FileManager::loadAllSystemData() {
    cout << "[FileManager] Loading data ...\n";

    // 1. Load Users from CSV
    ifstream uFile("Users.csv");
    if (uFile.is_open()) {
        string line;
        getline(uFile, line); // Skip Column Header
        while (getline(uFile, line)) {
            stringstream ss(line);
            string id, name, phone, city, address, password;
            getline(ss, id, ','); getline(ss, name, ','); getline(ss, phone, ','); getline(ss, city, ',');
            getline(ss, address, ','); getline(ss, password);
            if (!id.empty())
            {User* currentUser = new User(name,city,address,phone,password);
                currentUser->setUserID(stoi(id));}


        }
        uFile.close();

    }

    // 2. Load Shops from CSV
    ifstream sFile("Shops.csv");
    if (sFile.is_open()) {
        string line;
        getline(sFile, line);
        while (getline(sFile, line)) {
            stringstream ss(line);
            string name, id, location, number;
            getline(ss, name, ','); getline(ss, id, ','); getline(ss, location, ',');
            getline(ss, number);

            if (!id.empty())
                new Shop(stoi(id),name,location,number);
            //sys->addUser(new Admin(name, id, phone, email));
        }
        sFile.close();
    }

    // 3. Load Products from CSV
    ifstream pFile("Products.csv");
    if (pFile.is_open()) {
        string line;
        getline(pFile, line);
        while (getline(pFile, line))
        {stringstream ss(line);
            string id, shopid, shopname,name,category , items, price;
            getline(ss, id, ','); getline(ss, shopid, ','); getline(ss, shopname, ','); getline(ss, name, ',');
            getline(ss, category, ','); getline(ss, items, ','); getline(ss, price);
            if (!id.empty())
                new Product(stoi(id),name,shopname,stoi(shopid),category,stof(price),stoi(items));

            //sys->addUser(new Passenger(name, id, phone, email, pass));
        }
        pFile.close();
    }

    // 4. Load Orders from CSV

    ifstream oFile("Orders.csv");
    if (oFile.is_open()) {
        string line;
        // skip header
        getline(oFile, line);

        while (getline(oFile, line)) {
            stringstream ss(line);
            string userid, username,id, shopid, shopname, orderprice;
            Vector<int> orderedProducts;
            string productCell = "";
            char c;

            getline(ss, id, ',');
            getline(ss, userid, ',');
            getline(ss, username, ',');
            getline(ss, shopid, ',');
            getline(ss, shopname, ',');
            getline(ss, orderprice);

            if (!id.empty()) {
                Order* o = new Order();

                o->buyerID    = stoi(userid);
                o->shopID     = stoi(shopid);
                o->shopName   = shopname;
                o->orderPrice = stof (orderprice);
            }
        }
        oFile.close();
    }



    cout << "[FileManager] All data files successfully restored!\n";
}



// SECTION 4: UTILITY

// Factory Reset: Wipes the data but keeps the column headers for future loads
void FileManager::clearAllFiles() {
    cout << "\n[FileManager] Delete all data from files\n";

    ofstream uFile("Users.csv");
    if (uFile.is_open()) uFile << "UserID,FirstName,Phone,City,Address,Password\n";

    ofstream sFile("Shops.csv");
    if (sFile.is_open()) sFile <<"Name,ID,Location,Number\n" ;

    ofstream pFile("Products.csv");
    if (pFile.is_open()) pFile <<"ProductID,ShopName,ShopID,Name,Category,Price,Stock\n" ;

    ofstream oFile("Orders.csv");
    if (oFile.is_open()) oFile <<"UserID,ShopID,ShopName,ProductIDs,Price\n" ;

    cout << "[FileManager] All files have been successfully reset.\n";
}

// Master save — calls all individual save functions
void FileManager::saveAllSystemData() {
    saveUsersToCSV(User::getUsersInSystem(),       "Users.csv");
    saveShopsToCSV(Shop::getShopsInSystem(),       "Shops.csv");
    saveProductsToCSV(Product::getProductsInSystem(), "Products.csv");
    saveOrdersToCSV(Order::allOrders,             "Orders.csv");
    cout << "[FileManager] All data saved successfully.\n";
}
