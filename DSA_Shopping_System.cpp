#include "DSA_Shopping_System.h"


using namespace std;

Vector<Product*> Product::allProducts;
Vector<Shop*> Shop::allShops;
Vector <User*> User::allUsers;
int User::allUsersCount = 0;


Product::Product(const int& ID,const string& name, const string& sellerName,const int& sellerID, const string& category, float price, int availableItems)
{ productID = ID;
  productName = name;
  productShopName = sellerName;
  productShopID = sellerID;
  productCategory = category;
  productPrice = price;
  availableProductItems = availableItems;
  allProducts.pushBack(this);
  Shop* shop = Shop::searchForShop(sellerID);
  shop->addShopProduct(this);
}


int Product::getProductID()
{ return productID; }

string Product::getProductName()
{ return productName; }

int Product::getProductShopID()
{ return productShopID; }

string Product::getProductShopName()
{ return productShopName; }

string Product::getProductCategory()
{ return productCategory; }

Vector<Product*> Product::getProductsInSystem()
{ return allProducts; }

int Product:: getProductsSize()
{ return allProducts.vectorSize(); }

float Product:: getProductPrice()
{ return productPrice; }

int Product :: getAvailableProductItems()
{ return availableProductItems; }

void Product::setProductID(int ID)
{ productID = ID; }

void Product::setProductName (string name)
{ productName = name; }

void Product::setProductCategory (string category)
{ productCategory = category; }

void Product::setAvailableProductItems(int items)
{ availableProductItems = items; }

bool Product:: isProductsListEmpty()
{ if(allProducts.isVectorEmpty()==1)
 { return 1;}
  else return 0;
}

bool Product:: checkProductAvailability()
{ if(availableProductItems==0)
  {return false;}
  else return true;
}

Product* Product::searchForProductInSystem(const int& ID)
{ for(int i = 0 ; i < allProducts.vectorSize() ; i++)
  {if(ID==(allProducts[i]->productID))
   {return allProducts[i];}
  }
  return nullptr;
}

Product* Product::searchForProductInSystem(const string& name)
{ for(int i = 0 ; i < allProducts.vectorSize() ; i++)
  {if(name==(allProducts[i]->productName))
   {return allProducts[i];}
  }
  return nullptr;
}

Vector <Product*> Product::searchForProductsofCategory(string category)
{Vector<Product*> categoryProducts;
 for(int i = 0 ; i < allProducts.vectorSize() ; i++)
 {if(category == allProducts[i]->productCategory)
  {categoryProducts.pushBack(allProducts[i]);} }
  return categoryProducts;
}

void Product::productPrinter()
{ for(int i = 0 ; i < allProducts.vectorSize() ; i++)
  {cout<<"Products:"<<endl;
   cout<<"("<<i+1<<")"<<allProducts[i]->productID << "  "<<allProducts[i]->productName << "  "<<allProducts[i]->productShopID << "  "<<allProducts[i]->productPrice << "  "<<allProducts[i]->availableProductItems << endl;
  }
}


Shop::Shop(const int& ID,const string& name, const string& location, const string& contactNumber)
{ shopName = name;
  shopID = ID;
  shopLocation = location;
  shopContactNumber = contactNumber;
  shopDeque = new OrderDeque;
  allShops.pushBack(this);
}

void Shop::addShopProduct(Product* newProduct)
{ if(newProduct!= nullptr)
  {shopProducts.pushBack(newProduct);}
}

int Shop::getShopID()
{ return shopID; }

string Shop::getShopName()
{ return shopName; }

string Shop::getShopContactNumber()
{ return shopContactNumber; }

string Shop::getShopLocation()
{ return shopLocation; }

Vector<Shop*> Shop::getShopsInSystem()
{ return allShops; }

Vector<Product*> Shop::getShopProducts()
{ return shopProducts; }

OrderDeque* Shop::getShopDeque()
{ return shopDeque;
}

void Shop::setShopContactNumber(string number)
{ shopContactNumber = number; }

void Shop::setShopID(int ID)
{ shopID = ID; }

void Shop::setShopName(string name)
{ shopName = name; }

bool Shop::isShopEmpty()
{ if(allShops.isVectorEmpty()==1)
  return 1;
  else return 0;
}

bool Shop::areNoProductsInShop()
{ if(shopProducts.isVectorEmpty()==1)
  return 1;
  else return 0;
}

Shop * Shop::searchForShop(const int& ID)
{
  int IDholder = ID;
  for(int i = 0 ; i < allShops.vectorSize() ; i++)
  {int IDver = allShops[i]->getShopID();
   if(IDholder == IDver)
   {return allShops[i];}
  }
  return nullptr;
}

Shop * Shop::searchForShop(const string& name)
{
  string nameHolder = name;
  for(int i = 0 ; i < allShops.vectorSize() ; i++)
  {string nameVer = allShops[i]->getShopName();
   if(nameHolder == nameVer)
   {return allShops[i];}
  }
  return nullptr;
}

Product * Shop::searchForProductInShop(const int& ID)
{ for(int i = 0 ; i < shopProducts.vectorSize() ; i++)
  {if(ID==(shopProducts[i]->getProductID()))
   {return shopProducts[i];}
  }
  return nullptr;
}

Product * Shop::searchForProductInShop(const string& name)
{ for(int i = 0 ; i < shopProducts.vectorSize() ; i++)
  {if(name==(shopProducts[i]->getProductName()))
   {return shopProducts[i];}
  }
  return nullptr;
}

void Shop::shopPrinter()
{ for(int i = 0 ; i < allShops.vectorSize() ; i++)
  {cout<<"Shops:"<<endl;
   cout<<"("<<i+1<<")"<<allShops[i]->shopID << "  "<<allShops[i]->shopName << "  "<<allShops[i]->shopLocation << "  "<<allShops[i]->shopContactNumber <<endl;
  }
}

void Shop::shopProductsPrinter()
{ for(int i = 0 ; i < shopProducts.vectorSize() ; i++)
  {cout<<"Products:"<<endl;
   cout<<"("<<i+1<<")"<<shopProducts[i]->getProductID() << "  "<<shopProducts[i]->getProductName() << "  "<<shopProducts[i]->getProductShopID() << "  "<<shopProducts[i]->getProductPrice() << "  "<<shopProducts[i]->getAvailableProductItems() << endl;
  }

}

User::User(const string& name, const string& city,const string& address, const string& contactNumber, const string& password)
{User::allUsersCount++;
 userName = name;
 userID = userIDGenerator();
 userCity = city;
 userAddress = address;
 userContactNumber = contactNumber;
 userPassword = password;
 allUsers.pushBack(this);
}

string User::getUserName()
{return userName;}

int User::getUserID()
{return userID;}

string User::getUserCity()
{return userCity; }

string User::getUserAddress()
{return userAddress; }

string User::getUserContactNumber()
{return userContactNumber; }

string User::getUserPassword()
{return userPassword; }

Vector<Order*> User::getUserOrders()
{return userOrders; }

Vector<User*> User::getUsersInSystem()
{return allUsers;}

void User::setUserName(string name)
{userName = name;}

void User::setUserID(int ID)
{userID = ID;}

void User::setUserCity(string city)
{userCity = city;}


void User::setUserAddress(string address)
{userAddress = address;}

void User::setUserContactNumber(string contactNumber)
{userContactNumber = contactNumber;}

void User::setUserPassword(string password)
{userPassword = password;}

void User::addUserOrder(Order* info)
{userOrders.pushBack(info);}

int User::userIDGenerator()
{ int ID = allUsersCount;
  return ID;
}



User* User::userLogIn(int ID, string password)
{ User* user = User::searchForUser(ID);
  if(user!= nullptr && user->getUserPassword() == password)
  {return user;}
  else return nullptr;
}

User* User::userSignUp(string name, string city, string address, string contactNumber, string password)
{ User* user = new User(name,city, address,contactNumber,password);
  return user;
}


User * User::searchForUser(const int&ID)
{ for(int i = 0 ; i < allUsers.vectorSize() ; i++)
  {if(ID==(allUsers[i]->userID))
   {return allUsers[i];}
  }
  return nullptr;
}

Order* User::searchforUserOrder(const int& ID)
{ for(int i = 0 ; i < userOrders.vectorSize() ; i++)
  {if(ID==(userOrders[i]->orderID))
   {return userOrders[i];}
  }
  return nullptr;
}

void User::userPrinter()
{ for(int i = 0 ; i < allUsers.vectorSize() ; i++)
  {cout<<"Users:"<<endl;
   cout<<"("<<i+1<<")"<<allUsers[i]->userID << "  "<<allUsers[i]->userName << "  "<<allUsers[i]->userAddress << "  "<<allUsers[i]->userContactNumber <<endl;
  }
}

void User::userOrdersPrinter()
{ for(int i = 0 ; i < userOrders.vectorSize() ; i++)
  {cout<<"Orders of user:"<<endl;
   cout<<"("<<i+1<<")"<<userOrders[i]->orderID << "  "<<userOrders[i]->shopID << "  "<<userOrders[i]->orderPrice << "  "<<endl;
   for(int j = 0; j<userOrders[i]->orderedProducts.vectorSize(); j++)
   {cout<<"("<<i+1<<")"<<userOrders[i]->orderedProducts[j]->getProductID() << "  "<<userOrders[i]->orderedProducts[j]->getProductName()<< "  "<<userOrders[i]->orderedProducts[j]->getAvailableProductItems() << "  "<<endl;
   }
  }
}
