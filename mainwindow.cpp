#include "mainwindow.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QFont>
#include <QSplitter>
#include <QFrame>
#include <QString>
#include <QStringList>

// ═══════════════════════════════════════════════════════════════
//  Constructor
// ═══════════════════════════════════════════════════════════════
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("DSA Shopping System");
    setMinimumSize(1000, 650);

    // central widget
    QWidget     *central = new QWidget(this);
    QVBoxLayout *root    = new QVBoxLayout(central);
    root->setContentsMargins(8, 8, 8, 4);
    root->setSpacing(6);
    setCentralWidget(central);

    // tab widget
    QTabWidget *tabs = new QTabWidget();
    tabs->setTabPosition(QTabWidget::North);
    root->addWidget(tabs);

    buildUsersTab(tabs);
    buildShopsTab(tabs);
    buildProductsTab(tabs);
    buildOrdersTab(tabs);
    buildFileTab(tabs);

    // global status bar
    statusBar = new QLabel("Ready.");
    statusBar->setStyleSheet("color: green; font-weight: bold; padding: 2px 6px;");
    root->addWidget(statusBar);
}

// ═══════════════════════════════════════════════════════════════
//  TAB 1 — USERS
// ═══════════════════════════════════════════════════════════════
void MainWindow::buildUsersTab(QTabWidget *tabs)
{
    QWidget     *page   = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(page);

    // ── LEFT: Sign Up ──
    QGroupBox   *suBox = new QGroupBox("Sign Up");
    QVBoxLayout *suL   = new QVBoxLayout(suBox);
    suBox->setMaximumWidth(230);

    suName    = new QLineEdit(); suName->setPlaceholderText("Full name");
    suCity    = new QLineEdit(); suCity->setPlaceholderText("City");
    suAddress = new QLineEdit(); suAddress->setPlaceholderText("Address");
    suPhone   = new QLineEdit(); suPhone->setPlaceholderText("Phone number");
    suPass    = new QLineEdit(); suPass->setPlaceholderText("Password");
    suPass->setEchoMode(QLineEdit::Password);

    QPushButton *suBtn = new QPushButton("Register");
    connect(suBtn, &QPushButton::clicked, this, &MainWindow::signUpUser);

    suL->addWidget(new QLabel("Name:"));    suL->addWidget(suName);
    suL->addWidget(new QLabel("City:"));    suL->addWidget(suCity);
    suL->addWidget(new QLabel("Address:")); suL->addWidget(suAddress);
    suL->addWidget(new QLabel("Phone:"));   suL->addWidget(suPhone);
    suL->addWidget(new QLabel("Password:")); suL->addWidget(suPass);
    suL->addWidget(suBtn);

    // ── MIDDLE: Login ──
    QGroupBox   *liBox = new QGroupBox("Login");
    QVBoxLayout *liL   = new QVBoxLayout(liBox);
    liBox->setMaximumWidth(200);

    liID   = new QLineEdit(); liID->setPlaceholderText("User ID");
    liPass = new QLineEdit(); liPass->setPlaceholderText("Password");
    liPass->setEchoMode(QLineEdit::Password);
    loginStatus = new QLabel("Not logged in.");
    loginStatus->setStyleSheet("color: gray;");

    QPushButton *liBtn  = new QPushButton("Login");
    QPushButton *loBtn  = new QPushButton("Logout");
    connect(liBtn, &QPushButton::clicked, this, &MainWindow::loginUser);
    connect(loBtn, &QPushButton::clicked, this, &MainWindow::logoutUser);

    liL->addWidget(new QLabel("User ID:")); liL->addWidget(liID);
    liL->addWidget(new QLabel("Password:")); liL->addWidget(liPass);
    liL->addWidget(liBtn);
    liL->addWidget(loBtn);
    liL->addWidget(loginStatus);
    liL->addStretch();

    // ── RIGHT: Users table ──
    QGroupBox   *tBox = new QGroupBox("All Users");
    QVBoxLayout *tL   = new QVBoxLayout(tBox);

    usersTable = new QTableWidget();
    usersTable->setColumnCount(5);
    usersTable->setHorizontalHeaderLabels({"ID","Name","City","Address","Phone"});
    usersTable->horizontalHeader()->setStretchLastSection(true);
    usersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    usersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    usersTable->setAlternatingRowColors(true);
    tL->addWidget(usersTable);

    layout->addWidget(suBox);
    layout->addWidget(liBox);
    layout->addWidget(tBox);

    tabs->addTab(page, "👤 Users");
    refreshUsersTable();
}

// ═══════════════════════════════════════════════════════════════
//  TAB 2 — SHOPS
// ═══════════════════════════════════════════════════════════════
void MainWindow::buildShopsTab(QTabWidget *tabs)
{
    QWidget     *page = new QWidget();
    QVBoxLayout *l    = new QVBoxLayout(page);

    QGroupBox   *box = new QGroupBox("All Shops");
    QVBoxLayout *bl  = new QVBoxLayout(box);

    shopsTable = new QTableWidget();
    shopsTable->setColumnCount(4);
    shopsTable->setHorizontalHeaderLabels({"ID","Name","Location","Phone"});
    shopsTable->horizontalHeader()->setStretchLastSection(true);
    shopsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    shopsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    shopsTable->setAlternatingRowColors(true);

    bl->addWidget(shopsTable);
    l->addWidget(box);

    tabs->addTab(page, "🏪 Shops");
    refreshShopsTable();
}

// ═══════════════════════════════════════════════════════════════
//  TAB 3 — PRODUCTS
// ═══════════════════════════════════════════════════════════════
void MainWindow::buildProductsTab(QTabWidget *tabs)
{
    QWidget     *page = new QWidget();
    QVBoxLayout *l    = new QVBoxLayout(page);

    // filter row
    QHBoxLayout *filterRow = new QHBoxLayout();
    filterShop = new QComboBox();
    filterShop->addItem("All Shops");
    Vector<Shop*> shops = Shop::getShopsInSystem();
    for (int i = 0; i < shops.vectorSize(); i++)
        filterShop->addItem(QString::fromStdString(shops[i]->getShopName()));

    connect(filterShop, &QComboBox::currentTextChanged,
            this, &MainWindow::refreshProductsTable);

    filterRow->addWidget(new QLabel("Filter by Shop:"));
    filterRow->addWidget(filterShop);
    filterRow->addStretch();
    l->addLayout(filterRow);

    productsTable = new QTableWidget();
    productsTable->setColumnCount(6);
    productsTable->setHorizontalHeaderLabels({"ID","Name","Shop","Category","Price","Stock"});
    productsTable->horizontalHeader()->setStretchLastSection(true);
    productsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    productsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    productsTable->setAlternatingRowColors(true);
    l->addWidget(productsTable);

    tabs->addTab(page, "📦 Products");
    refreshProductsTable();
}

// ═══════════════════════════════════════════════════════════════
//  TAB 4 — ORDERS
// ═══════════════════════════════════════════════════════════════
void MainWindow::buildOrdersTab(QTabWidget *tabs)
{
    QWidget     *page   = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(page);

    // ── LEFT: Place Order form ──
    QGroupBox   *formBox = new QGroupBox("Place Order");
    QVBoxLayout *formL   = new QVBoxLayout(formBox);
    formBox->setMaximumWidth(250);

    shopBox = new QComboBox();
    populateShopBox();
    connect(shopBox, &QComboBox::currentIndexChanged,
            this, &MainWindow::populateProductBox);

    productBox  = new QComboBox();
    populateProductBox();

    shippingBox = new QComboBox();
    shippingBox->addItem("Standard  (pushRear)");
    shippingBox->addItem("Express   (pushFront)");

    QPushButton *addBtn   = new QPushButton("Add to Cart");
    QPushButton *orderBtn = new QPushButton("Place Order ✓");
    orderBtn->setStyleSheet("background-color: #2d8a4e; color: white; font-weight: bold;");

    connect(addBtn,   &QPushButton::clicked, this, &MainWindow::addToCart);
    connect(orderBtn, &QPushButton::clicked, this, &MainWindow::placeOrder);

    // cart table
    cartTable = new QTableWidget();
    cartTable->setColumnCount(3);
    cartTable->setHorizontalHeaderLabels({"ID","Product","Price"});
    cartTable->horizontalHeader()->setStretchLastSection(true);
    cartTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    cartTable->setMaximumHeight(160);

    formL->addWidget(new QLabel("Shop:"));     formL->addWidget(shopBox);
    formL->addWidget(new QLabel("Product:")); formL->addWidget(productBox);
    formL->addWidget(new QLabel("Shipping:")); formL->addWidget(shippingBox);
    formL->addWidget(addBtn);
    formL->addWidget(new QLabel("Cart:"));
    formL->addWidget(cartTable);
    formL->addWidget(orderBtn);

    orderStatus = new QLabel("");
    orderStatus->setWordWrap(true);
    formL->addWidget(orderStatus);
    formL->addStretch();

    // ── RIGHT: Queue + Cancel + Process ──
    QGroupBox   *qBox = new QGroupBox("Order Queue  (front = highest priority)");
    QVBoxLayout *qL   = new QVBoxLayout(qBox);

    queueDisplay = new QTextEdit();
    queueDisplay->setReadOnly(true);
    queueDisplay->setFont(QFont("Courier New", 10));

    // cancel row
    QHBoxLayout *cancelRow = new QHBoxLayout();
    cancelInput = new QLineEdit(); cancelInput->setPlaceholderText("Order ID to cancel");
    QPushButton *cancelBtn  = new QPushButton("Cancel Order");
    cancelBtn->setStyleSheet("color: red; font-weight: bold;");
    connect(cancelBtn, &QPushButton::clicked, this, &MainWindow::cancelOrder);
    cancelRow->addWidget(cancelInput);
    cancelRow->addWidget(cancelBtn);

    QPushButton *processBtn = new QPushButton("⚙  Process Orders  (age → promote → sort → pop)");
    processBtn->setStyleSheet("background-color: #c47d00; color: white; font-weight: bold;");
    processBtn->setMinimumHeight(32);
    connect(processBtn, &QPushButton::clicked, this, &MainWindow::processOrders);

    qL->addWidget(queueDisplay);
    qL->addLayout(cancelRow);
    qL->addWidget(processBtn);

    layout->addWidget(formBox);
    layout->addWidget(qBox);

    tabs->addTab(page, "📋 Orders");
    refreshOrderQueue();
}

// ═══════════════════════════════════════════════════════════════
//  TAB 5 — FILE MANAGER
// ═══════════════════════════════════════════════════════════════
void MainWindow::buildFileTab(QTabWidget *tabs)
{
    QWidget     *page = new QWidget();
    QVBoxLayout *l    = new QVBoxLayout(page);

    QHBoxLayout *btnRow = new QHBoxLayout();
    QPushButton *saveBtn = new QPushButton("💾  Save All to CSV");
    QPushButton *loadBtn = new QPushButton("📂  Load All from CSV");
    saveBtn->setMinimumHeight(36);
    loadBtn->setMinimumHeight(36);
    saveBtn->setStyleSheet("font-weight: bold;");
    loadBtn->setStyleSheet("font-weight: bold;");
    connect(saveBtn, &QPushButton::clicked, this, &MainWindow::saveAllData);
    connect(loadBtn, &QPushButton::clicked, this, &MainWindow::loadAllData);
    btnRow->addWidget(saveBtn);
    btnRow->addWidget(loadBtn);

    fileLog = new QTextEdit();
    fileLog->setReadOnly(true);
    fileLog->setFont(QFont("Courier New", 10));
    fileLog->setPlaceholderText("File operation log will appear here...");

    l->addLayout(btnRow);
    l->addWidget(new QLabel("Log:"));
    l->addWidget(fileLog);

    tabs->addTab(page, "📁 Files");
}

// ═══════════════════════════════════════════════════════════════
//  SLOTS
// ═══════════════════════════════════════════════════════════════

void MainWindow::signUpUser()
{
    QString name = suName->text().trimmed();
    QString city = suCity->text().trimmed();
    QString addr = suAddress->text().trimmed();
    QString phone= suPhone->text().trimmed();
    QString pass = suPass->text().trimmed();

    if (name.isEmpty() || pass.isEmpty()) {
        setStatus("Name and password are required.", true); return;
    }

    new User(name.toStdString(), city.toStdString(),
             addr.toStdString(), phone.toStdString(), pass.toStdString());

    suName->clear(); suCity->clear(); suAddress->clear();
    suPhone->clear(); suPass->clear();

    refreshUsersTable();
    setStatus("User registered successfully.");
}

void MainWindow::loginUser()
{
    bool ok;
    int id = liID->text().toInt(&ok);
    if (!ok) { setStatus("Enter a valid User ID.", true); return; }

    User *u = User::searchForUser(id);
    if (u && u->getUserPassword() == liPass->text().toStdString()) {
        currentUser = u;
        loginStatus->setText(QString("✔ Logged in: %1 (ID %2)")
                                 .arg(QString::fromStdString(u->getUserName()))
                                 .arg(u->getUserID()));
        loginStatus->setStyleSheet("color: green; font-weight: bold;");
        setStatus(QString("Welcome, %1!").arg(QString::fromStdString(u->getUserName())));
    } else {
        setStatus("Invalid ID or password.", true);
    }
}

void MainWindow::logoutUser()
{
    currentUser = nullptr;
    loginStatus->setText("Not logged in.");
    loginStatus->setStyleSheet("color: gray;");
    setStatus("Logged out.");
}

void MainWindow::addToCart()
{
    int idx = productBox->currentIndex();
    if (idx < 0) { setStatus("Select a product.", true); return; }

    // find product from selected shop
    int shopIdx = shopBox->currentIndex();
    Vector<Shop*> shops = Shop::getShopsInSystem();
    if (shopIdx < 0 || shopIdx >= shops.vectorSize()) return;

    Shop *shop = shops[shopIdx];
    Vector<Product*> prods = shop->getShopProducts();
    if (idx >= prods.vectorSize()) return;

    Product *p = prods[idx];
    if (!p->checkProductAvailability()) {
        setStatus("Product is out of stock.", true); return;
    }

    // check not already in cart
    for (int i = 0; i < cart.vectorSize(); i++)
        if (cart[i]->getProductID() == p->getProductID()) {
            setStatus("Already in cart.", true); return;
        }

    cart.pushBack(p);
    refreshCartTable();
    setStatus(QString("Added '%1' to cart.").arg(QString::fromStdString(p->getProductName())));
}

void MainWindow::placeOrder()
{
    if (!currentUser) { setStatus("Please login first.", true); return; }
    if (cart.vectorSize() == 0) { setStatus("Cart is empty.", true); return; }

    int shopIdx = shopBox->currentIndex();
    Vector<Shop*> shops = Shop::getShopsInSystem();
    if (shopIdx < 0 || shopIdx >= shops.vectorSize()) return;
    Shop *shop = shops[shopIdx];

    // build order
    Order *o       = new Order();
    o->buyerID     = currentUser->getUserID();
    o->shopID      = shop->getShopID();
    o->shopName    = shop->getShopName();
    o->shippingAddress = currentUser->getUserAddress();

    float total = 0;
    for (int i = 0; i < cart.vectorSize(); i++) {
        o->orderedProducts.pushBack(cart[i]);
        total += cart[i]->getProductPrice();
        // decrement stock
        int stock = cart[i]->getAvailableProductItems() - 1;
        cart[i]->setAvailableProductItems(stock);
    }
    o->orderPrice = total;
    o->age        = 0;

    currentUser->addUserOrder(o);

    OrderDeque *deque = shop->getShopDeque();
    if (shippingBox->currentIndex() == 1)
        deque->ExpressShipping(o);
    else
        deque->StandardShipping(o);

    // clear cart
    while (cart.vectorSize()) cart.popBack();
    refreshCartTable();
    refreshOrderQueue();
    refreshProductsTable();

    orderStatus->setText(QString("Order #%1 placed! Total: %2 EGP")
                             .arg(o->orderID).arg(total, 0, 'f', 2));
    orderStatus->setStyleSheet("color: green; font-weight: bold;");
    setStatus(QString("Order #%1 placed successfully.").arg(o->orderID));
}

void MainWindow::cancelOrder()
{
    bool ok;
    int id = cancelInput->text().toInt(&ok);
    if (!ok) { setStatus("Enter a valid Order ID.", true); return; }

    // cancel from every shop's deque
    Vector<Shop*> shops = Shop::getShopsInSystem();
    for (int i = 0; i < shops.vectorSize(); i++)
        shops[i]->getShopDeque()->cancelOrder(id);

    cancelInput->clear();
    refreshOrderQueue();
    setStatus(QString("Cancel request sent for Order #%1.").arg(id));
}

void MainWindow::processOrders()
{
    Vector<Shop*> shops = Shop::getShopsInSystem();
    int totalPopped = 0;

    for (int i = 0; i < shops.vectorSize(); i++) {
        OrderDeque *d = shops[i]->getShopDeque();
        if (!d->isEmpty()) {
            int before = d->dequeSize();
            d->processOrders();
            totalPopped += before - d->dequeSize();
        }
    }

    refreshOrderQueue();
    setStatus(QString("Processed %1 order(s) across all shops.").arg(totalPopped));
}

void MainWindow::saveAllData()
{
    FileManager::saveAllSystemData();
    fileLog->append("✔ All data saved to CSV files.");
    setStatus("Data saved.");
}

void MainWindow::loadAllData()
{
    FileManager::loadAllSystemData();
    refreshUsersTable();
    refreshShopsTable();
    refreshProductsTable();
    refreshOrderQueue();
    populateShopBox();
    fileLog->append("✔ All data loaded from CSV files.");
    setStatus("Data loaded.");
}

// ═══════════════════════════════════════════════════════════════
//  REFRESH HELPERS
// ═══════════════════════════════════════════════════════════════

void MainWindow::refreshUsersTable()
{
    Vector<User*> users = User::getUsersInSystem();
    usersTable->setRowCount(users.vectorSize());
    for (int i = 0; i < users.vectorSize(); i++) {
        User *u = users[i];
        usersTable->setItem(i, 0, new QTableWidgetItem(QString::number(u->getUserID())));
        usersTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(u->getUserName())));
        usersTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(u->getUserCity())));
        usersTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(u->getUserAddress())));
        usersTable->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(u->getUserContactNumber())));
    }
    usersTable->resizeColumnsToContents();
}

void MainWindow::refreshShopsTable()
{
    Vector<Shop*> shops = Shop::getShopsInSystem();
    shopsTable->setRowCount(shops.vectorSize());
    for (int i = 0; i < shops.vectorSize(); i++) {
        Shop *s = shops[i];
        shopsTable->setItem(i, 0, new QTableWidgetItem(QString::number(s->getShopID())));
        shopsTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(s->getShopName())));
        shopsTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(s->getShopLocation())));
        shopsTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(s->getShopContactNumber())));
    }
    shopsTable->resizeColumnsToContents();
}

void MainWindow::refreshProductsTable()
{
    Vector<Product*> prods = Product::getProductsInSystem();
    QString filter = filterShop ? filterShop->currentText() : "All Shops";

    int row = 0;
    productsTable->setRowCount(prods.vectorSize());

    for (int i = 0; i < prods.vectorSize(); i++) {
        Product *p = prods[i];
        if (filter != "All Shops" &&
            QString::fromStdString(p->getProductShopName()) != filter) continue;

        productsTable->setItem(row, 0, new QTableWidgetItem(QString::number(p->getProductID())));
        productsTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(p->getProductName())));
        productsTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(p->getProductShopName())));
        productsTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(p->getProductCategory())));
        productsTable->setItem(row, 4, new QTableWidgetItem(QString::number(p->getProductPrice(), 'f', 2)));
        productsTable->setItem(row, 5, new QTableWidgetItem(QString::number(p->getAvailableProductItems())));

        // color out-of-stock rows red
        if (p->getAvailableProductItems() == 0)
            for (int c = 0; c < 6; c++)
                if (productsTable->item(row, c))
                    productsTable->item(row, c)->setForeground(Qt::red);
        row++;
    }
    productsTable->setRowCount(row);
    productsTable->resizeColumnsToContents();
}

void MainWindow::refreshOrderQueue()
{
    queueDisplay->clear();
    const char *PRIO[] = { "Standard", "Express", "LATE" };

    Vector<Shop*> shops = Shop::getShopsInSystem();
    bool anyOrder = false;

    for (int i = 0; i < shops.vectorSize(); i++) {
        Shop *shop = shops[i];
        OrderDeque *deque = shop->getShopDeque();
        if (deque->isEmpty()) continue;

        anyOrder = true;
        queueDisplay->append(QString("── %1 ──────────────────────")
                                 .arg(QString::fromStdString(shop->getShopName())));

        // traverse YOUR linked list via getHead()
        OrderNode *cur = deque->getHead();
        while (cur) {
            Order *o = cur->info;
            queueDisplay->append(
                QString("  #%1 | Buyer:%2 | %3 EGP | Age:%4d | %5")
                    .arg(o->orderID)
                    .arg(o->buyerID)
                    .arg(o->orderPrice, 0, 'f', 2)
                    .arg(o->age)
                    .arg(PRIO[o->priority]));
            cur = cur->next;
        }
        queueDisplay->append("");
    }

    if (!anyOrder)
        queueDisplay->setPlainText("No orders in any queue.");
}

void MainWindow::refreshCartTable()
{
    cartTable->setRowCount(cart.vectorSize());
    for (int i = 0; i < cart.vectorSize(); i++) {
        Product *p = cart[i];
        cartTable->setItem(i, 0, new QTableWidgetItem(QString::number(p->getProductID())));
        cartTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(p->getProductName())));
        cartTable->setItem(i, 2, new QTableWidgetItem(QString::number(p->getProductPrice(), 'f', 2)));
    }
}

void MainWindow::populateShopBox()
{
    shopBox->clear();
    Vector<Shop*> shops = Shop::getShopsInSystem();
    for (int i = 0; i < shops.vectorSize(); i++)
        shopBox->addItem(QString::fromStdString(shops[i]->getShopName()));
}

void MainWindow::populateProductBox()
{
    productBox->clear();
    int idx = shopBox->currentIndex();
    Vector<Shop*> shops = Shop::getShopsInSystem();
    if (idx < 0 || idx >= shops.vectorSize()) return;
    Vector<Product*> prods = shops[idx]->getShopProducts();
    for (int i = 0; i < prods.vectorSize(); i++)
        productBox->addItem(QString("[%1] %2 — %3 EGP")
                                .arg(prods[i]->getProductID())
                                .arg(QString::fromStdString(prods[i]->getProductName()))
                                .arg(prods[i]->getProductPrice(), 0, 'f', 2));
}

void MainWindow::setStatus(const QString &msg, bool error)
{
    statusBar->setText(msg);
    statusBar->setStyleSheet(
        error ? "color: red;   font-weight: bold; padding: 2px 6px;"
              : "color: green; font-weight: bold; padding: 2px 6px;");
}