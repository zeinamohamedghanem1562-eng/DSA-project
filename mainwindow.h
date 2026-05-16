#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QGroupBox>

#include "DSA_Storage_System.h"
#include "DSA_Ordering_System.h"
#include "DSA_Shopping_System.h"
#include "DSA_File_Manager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void signUpUser();
    void loginUser();
    void logoutUser();
    void placeOrder();
    void addToCart();
    void cancelOrder();
    void processOrders();
    void saveAllData();
    void loadAllData();

private:
    // helpers
    void buildUsersTab(QTabWidget *tabs);
    void buildShopsTab(QTabWidget *tabs);
    void buildProductsTab(QTabWidget *tabs);
    void buildOrdersTab(QTabWidget *tabs);
    void buildFileTab(QTabWidget *tabs);

    void refreshUsersTable();
    void refreshShopsTable();
    void refreshProductsTable();
    void refreshOrderQueue();
    void refreshCartTable();
    void populateShopBox();
    void populateProductBox();
    void setStatus(const QString &msg, bool error = false);

    User *currentUser = nullptr;

    // Users tab
    QLineEdit    *suName, *suCity, *suAddress, *suPhone, *suPass;
    QLineEdit    *liID,   *liPass;
    QLabel       *loginStatus;
    QTableWidget *usersTable;

    // Shops tab
    QTableWidget *shopsTable;

    // Products tab
    QTableWidget *productsTable;
    QComboBox    *filterShop;

    // Orders tab
    QComboBox    *shopBox;
    QComboBox    *productBox;
    QComboBox    *shippingBox;
    QTableWidget *cartTable;
    QTextEdit    *queueDisplay;
    QLineEdit    *cancelInput;
    QLabel       *orderStatus;

    // cart uses YOUR Vector, not a Qt container
    Vector<Product*> cart;

    // File tab
    QTextEdit *fileLog;

    // bottom status bar
    QLabel *statusBar;
};

#endif
