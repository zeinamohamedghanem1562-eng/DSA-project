#ifndef DSA_ORDERING_SYSTEM_H_INCLUDED
#define DSA_ORDERING_SYSTEM_H_INCLUDED
#include<iostream>
#include<string>
#include "DSA_Storage_System.h"
#include "DSA_Shopping_System.h"

using namespace std;

enum orderType{Standard,Express,Late} ;

class Product;
class Shop;
class OrderNode;
class OrderDeque;

struct Order
{ int orderID;
  int buyerID;
  string shippingAddress;
  float orderPrice;

  Vector<Product*> orderedProducts;
  static Vector<Order*> allOrders;

  int shopID;
  string shopName;

  orderType priority;
  int age;

  static int allOrdersCount;   // declared here — defined ONCE in DSA_Ordering_System.cpp

  Order();
  Order(const int& ID, const string& Address, const float& Price,
        const int& sID, const string& Name);
  int   orderIDGenerator();
  float priceCalculator();
  void  orderPrinter();
  static void allOrderPrinter();
};

// ── DO NOT put "int Order::allOrdersCount = 0;" here ──
//    It lives in DSA_Ordering_System.cpp to avoid multiple-definition errors

class OrderNode
{public:
 Order* info;
 OrderNode* next;
 OrderNode* prev;

 OrderNode()
 {next = 0; prev = 0;}

 OrderNode(Order* orderInfo, OrderNode *ptrn = 0, OrderNode *ptrp = 0)
 { info = orderInfo; next = ptrn; prev = ptrp; }

 void ageOrder();
 void increasePriority();

 ~OrderNode(){};
};

class OrderDeque
{ OrderNode* head;
  OrderNode* tail;

  public:
  OrderDeque()
  {head = tail = 0;}

  // ── accessor for GUI to traverse the linked list ──
  OrderNode* getHead() const { return head; }

  int isEmpty()
  {return head == 0;}

  int   dequeSize();
  void  clearDeque();
  void  pushFront(Order* info);
  void  pushRear(Order* info);
  Order* popFront();
  Order* popRear();
  void StandardShipping(Order* info);
  void ExpressShipping(Order* info);
  void makeOrder(int buyerID, int shopID);
  void cancelOrder(int ID);
  void ageAllOrders();
  void organizePriority();
  OrderNode* divide();
  OrderNode* conquer(OrderNode* first, OrderNode* second);
  OrderNode* sortDeque(OrderNode* head);
  void processOrders();
  void printAll() const;
};

#endif // DSA_ORDERING_SYSTEM_H_INCLUDED
