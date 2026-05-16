#ifndef DSA_SHOPPING_SYSTEM_H_INCLUDED
#define DSA_SHOPPING_SYSTEM_H_INCLUDED
#include <iostream>
#include <string>
#include "DSA_Storage_System.h"
#include "DSA_Ordering_System.h"

using namespace std;

class Shop;
class OrderDeque;
class Order;
class OrderNode;

class Product //class to store all products in the system and their relevant information
{string productName;
 int productID;
 int productShopID;
 string productShopName;
 string productCategory;
 float productPrice;
 int availableProductItems;
 static Vector<Product*> allProducts;

 public:

 Product(const int& ID,const string& name, const string& sellerName, const int& sellerID, const string& category, float price, int availableItems);

 int getProductID();
 string getProductName();
 int getProductShopID();
 string getProductShopName();
 string getProductCategory();
 float getProductPrice();
 int getAvailableProductItems();
 static Vector<Product*> getProductsInSystem();
 int getProductsSize();

 void setProductID(int ID);
 void setProductName(string name);
 void setProductCategory (string category);
 void setAvailableProductItems(int items);

 bool isProductsListEmpty();
 bool checkProductAvailability();

 static Product * searchForProductInSystem(const int&ID);
 static Product * searchForProductInSystem(const string&name);
Vector <Product*> searchForProductsofCategory(string category);

 static void productPrinter();
};



class Shop //class to store all shops in the system and their relevant information
{string shopName;
 int shopID;
 string shopLocation;
 string shopContactNumber;
 Vector<Product*> shopProducts;
 OrderDeque* shopDeque;
 static Vector<Shop*> allShops;

 public:

 Shop(const int& ID,const string& name, const string& location, const string& contactNumber);
 void addShopProduct(Product* newProduct);

 int getShopID();
 string getShopName();
 string getShopLocation();
 string getShopContactNumber();
 Vector<Product*> getShopProducts();
 static Vector<Shop*> getShopsInSystem();
 OrderDeque* getShopDeque();

 void setShopID(int ID);
 void setShopName(string name);
 void setShopContactNumber(string number);

 bool isShopEmpty();
 bool areNoProductsInShop();
 void addShop(Shop* shop);

 static Shop * searchForShop(const int&ID);
 static Shop * searchForShop(const string&name);
 Product * searchForProductInShop(const int& ID);
 Product * searchForProductInShop(const string& name);

 static void shopPrinter();
 void shopProductsPrinter();

};

class User
{ string userName;
  int userID;
  string userContactNumber;
  string userCity;
  string userAddress;
  string userPassword;
  Vector<Order*> userOrders;
  static Vector <User*> allUsers;
  static int allUsersCount;

  public:
  string getUserName();
  int getUserID();
  string getUserCity();
  string getUserAddress();
  string getUserContactNumber();
  string getUserPassword();
  Vector <Order*> getUserOrders();
  static Vector<User*> getUsersInSystem();

  User(const string& name,const string& city, const string& address,const string& contactNumber, const string& password);

  void setUserName(string name);
  void setUserID(int ID);
  void setUserAddress(string address);
  void setUserCity(string city);
  void setUserContactNumber(string contactNumber);
  void setUserPassword(string password);

  User*userLogIn(int ID, string password);
  User* userSignUp(string name, string city, string address, string contactNumber, string password);
  int userIDGenerator();


  void addUserOrder(Order* info);
  static User * searchForUser(const int&ID);
  Order* searchforUserOrder(const int& ID);

  static void userPrinter();
  void userOrdersPrinter();
};
#endif // DSA_SHOPPING_SYSTEM_H_INCLUDED
