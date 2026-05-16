#ifndef DSA_FILE_MANAGER_H_INCLUDED
#define DSA_FILE_MANAGER_H_INCLUDED
#include <string>
#include "DSA_Storage_System.h"
#include <fstream>
#include <iostream>
#include "DSA_Ordering_System.h"
#include "DSA_Shopping_System.h"

using namespace std;

class FileManager {
public:
    // --- File Saving  ---
    static void saveUsersToCSV(Vector<User*> user, const string& filename);
    static void saveShopsToCSV(Vector<Shop*> shops, const string& filename);
    static void saveProductsToCSV(Vector<Product*> products, const string& filename);
    static void saveOrdersToCSV(Vector<Order*> orders, const string& filename);

    // --- Master Save Method ---
    static void saveAllSystemData();
    // --- Master Load Method ---
    static void loadAllSystemData();
    // --- Reporting Functions ---
    static void generateSystemSummaryReport();

    //Utility
    static void clearAllFiles();
};



#endif // DSA_FILE_MANAGER_H_INCLUDED
