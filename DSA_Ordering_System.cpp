#include "DSA_Ordering_System.h"

using namespace std;

int Order::allOrdersCount = 0;
Vector<Order*> Order::allOrders;


Order::Order()
{orderID = orderIDGenerator();
 allOrders.pushBack(this);
}

Order::Order(const int& ID,const string& Address, const float& Price, const int& sID, const string& Name)
{orderID = orderIDGenerator();
 buyerID = ID;
 shippingAddress = Address;
 orderPrice = Price;
 shopID= sID;
 shopName = Name;
 allOrders.pushBack(this);}

int Order::orderIDGenerator()
{Order::allOrdersCount++;
 int ID = allOrdersCount;
 return ID;
}

float Order::priceCalculator()
{float price = 0;

 for(int i = 0; i<(orderedProducts.vectorSize()); i++)
 {Product* currentProduct = orderedProducts[i];
  float currentProductPrice = currentProduct->getProductPrice(); //finds price of every product ordered and adds it to the
  price = price + currentProductPrice;                           //total order price
 }

 return price; //returns total price of order
}


void Order::orderPrinter() //prints details of certain order
{
  cout<<"Order Details:"<<endl;
  for(int i = 0; i<orderedProducts.vectorSize();i++)
  {cout<<">Items:"<<endl;
   cout<<"("<<i+1<<")"<<orderedProducts[i]->getProductName()<<endl;}

  cout<<">Price: "<<endl;
  cout<<orderPrice<<endl;
  cout<<">Order ID: "<<endl;
  cout<<orderID<<endl;
}

void OrderNode::ageOrder()
{info->age = (info->age) + 1;}

void OrderDeque::ageAllOrders() //traverses list and increments age of all orders
{ OrderNode* tempNode = head;
  while(tempNode!=nullptr)
  {tempNode->ageOrder();
   tempNode = tempNode->next;}
}

void OrderNode::increasePriority()
{info->priority = Late;}

void OrderDeque::organizePriority() //checks for orders that have been in the system for more than 10 days
{ OrderNode* tempNode = head;

   while(tempNode!=nullptr)
   { if((tempNode->info->age)>=10)
    { tempNode->increasePriority();}
      tempNode = tempNode->next;}
}

OrderNode* OrderDeque::divide() //first helper func for merge sort deque
{ OrderNode* fast = head;
  OrderNode* slow = head;
  while(fast!=nullptr &&fast->next !=nullptr && fast->next->next!= nullptr) //fast pointer moves twice as much as slow pointer
  { fast = fast->next->next;
    slow = slow->next; }

  OrderNode* temp = slow->next; //splitting list in 2 sections
  slow->next = nullptr;
  if(temp!=nullptr)
  {temp->prev = nullptr;}
  return temp; //head will be head of first half of list and temp will be head of the second half of list
}

OrderNode* OrderDeque::conquer(OrderNode* first, OrderNode* second)
{ if(first==nullptr) //if either list is empty, return the other (nonempty) one
  {return second;}
  if(second==nullptr)
  {return first; }

  Order* orderTempFirst = first->info;
  Order* orderTempSecond = second->info;

  if(orderTempFirst->priority > orderTempSecond->priority) //recursively merge lists and assign result to current node
  { first->next = conquer(first->next,second);
   if(first->next!=nullptr)
   {first->next->prev = first;}
   first->prev = nullptr;
   return first;
  }

  else
  { second->next = conquer(first,second->next); //recursively merge lists and assign result to current node
   if(second->next!=nullptr)
   {second->next->prev = second;}
   second->prev = nullptr;
   return second;
  }
}


OrderNode* OrderDeque::sortDeque(OrderNode* head)
{ if(isEmpty()||head->next==nullptr) //empty list or only one element, list is technically sorted already
  { return head; }
  else
  { OrderNode* mid = divide();
    head = sortDeque(head); //sort each divided array alone
    mid = sortDeque(mid);
    return conquer(head,mid); //get them back together
  }
}

void OrderDeque::processOrders()
{ if(!isEmpty())
  { ageAllOrders();
    organizePriority();
    head = sortDeque(head);
    OrderNode* toPop = head;

     while(!isEmpty() && (head->info->priority == 1 || head->info->priority == 2)){
    popFront(); }
}

  else
  {cout<<"No orders to process."<<endl;
   exit(0);}
}


void OrderDeque::pushRear(Order* info) // adds a standard order to the back of the deque
{
    OrderNode* newNode = new OrderNode(info); // create a node for the new order
    if (isEmpty())
    {
        head = tail = newNode; //first node becomes head and tail
    }
    else
    {
        //linking the current tail to the new node
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void OrderDeque::pushFront(Order* info)
{
    OrderNode* newNode = new OrderNode(info);

    if(isEmpty())
    {
        head = tail = newNode;
    }
    else
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}


// popFront() to  remove the first order from the deque
Order* OrderDeque::popFront()
{
    if(isEmpty())  // check if deque is empty
    {
        cout << "No Orders Found.\n";
        return nullptr;
    }

    OrderNode* temp = head;  // to save first node temporary
    Order* removedOrder = temp->info; // save order data before deleting node

    if(head == tail)   // case 1 if there's only one node in deque
    {
        head = nullptr;
        tail = nullptr;
    }

    else  // case 2 if there are more than one node
    {
        head = head->next;
        head->prev = nullptr;
    }

    delete temp;
    return removedOrder;
}

// popRear() remove the last order from the deque

Order* OrderDeque::popRear()
{
    if(isEmpty())
    {
        cout << "No Orders Found.\n";
        return nullptr;
    }

    OrderNode* temp = tail; // to save last node temporary

    Order* removedOrder = temp->info; // save order data before removing
    if(head == tail) // case 1 only one node exist
    {
        head = nullptr;
        tail = nullptr;
    }
    else  // case 2  more than one node exist
    {

        tail = tail->prev;
        tail->next = nullptr;
    }

    delete temp;
    return removedOrder;
}

// cancelOrder() to remove a specific order using order id

void OrderDeque::cancelOrder(int targetID)
{
    if(isEmpty())
    {
        cout << "No Orders In System.\n";
        return;
    }
    OrderNode* current = head; // to start from head

    while(current != nullptr) // loop through all orders
    {
        // check if current order matches target ID
        if(current->info->orderID == targetID)
        {
            // case 1: node is the only node in deque
            if(current == head && current == tail)
            {
                head = nullptr;
                tail = nullptr;
            }
            // case 2:  node is first node
            else if(current == head)
            {
                head = head->next;
                head->prev = nullptr;
            }
            // case 3: node is last node

            else if(current == tail)
            {
                tail = tail->prev;
                tail->next = nullptr;
            }
            // case 4: node is in the middle
            else
            {
                // connect prev node to next node
                current->prev->next = current->next;

                // connect next node to prev node
                current->next->prev = current->prev;
            }
            delete current->info;
            delete current;
            cout << "Order Cancelled Successfully.\n";
            return;
        }
        current = current->next;    // move to next node
    }

    // if order id was not found
    cout << "Order Not Found.\n";
}


void OrderDeque:: makeOrder(int buyerID, int shopID)
{ // dynamically allocate new order
  Order* info = new Order;

  info->buyerID = buyerID;
  info->shopID = shopID;

  Shop* shop = Shop::searchForShop(shopID);
  OrderDeque* deque = shop->getShopDeque();


  int id;
  string choice;


do
{   cout<<"Add to cart:"<<endl;

    cin>>id; //collect products to be ordered

  Product* product = shop->searchForProductInShop(id);
  if(product->checkProductAvailability())
  {info->orderedProducts.pushBack(product);}
  else{cout<<"Product out of stock."<<endl;}


  cout<<"Want to add anything else? (Yes/No) "<<endl;
  getline(cin,choice);

}
  while(choice!="no"&& choice!="No");


  User* user = User::searchForUser(buyerID);

  user->addUserOrder(info);

  info->orderPrice = info->priceCalculator();

  info->orderPrinter();

  for(int i = 0; i<(info->orderedProducts.vectorSize());i++)
  {int available = info->orderedProducts[i]->getAvailableProductItems();
   --available;
   info->orderedProducts[i]->setAvailableProductItems(available);}

  cout<<"Please Choose Shipping Method."<<endl;
  cout<<"(1) Express"<<endl;
  cout<<"(2) Standard"<<endl;

  int pick;
  cin>>pick;
  cin.ignore();

  switch (pick)
{ case 1:
  deque->ExpressShipping(info);
  break;
  case 2:
  deque->StandardShipping(info);
  break;
} }

void OrderDeque::ExpressShipping(Order* info)
{   // express orders start with higher priority
    info->priority = Express;

    // new order age starts at 0
    info->age = 0;

    // express orders go to front
    pushFront(info);
    cout << "Express order " << info->orderID << " added successfully." << endl;

}


void OrderDeque::StandardShipping(Order* info)
{  // standard means priority = 0
    info->priority = Standard;

    // initializing age to 0 so it can be incremented later
    info->age = 0;

    // add it to the rear of the deque because it's a standard order
    pushRear(info);
    cout << "Standard order " << info->orderID << " added successfully." << endl;
}


void OrderDeque::printAll() const
{
    if(head == nullptr)
    {
        cout << "No orders in the system." << endl;
        return;
    }

    OrderNode* temp = head;

    cout << " ALL ORDERS " << endl;

    while(temp != nullptr)
    {
        Order* info = temp->info;

        cout << "Order ID: " << info->orderID << endl;
        cout << "Buyer ID: " << info->buyerID << endl;

        cout << "Shop ID: " << info->shopID << endl;

        cout << "Shop Name: " << info->shopName << endl;

        cout << "Shipping Address: " << info->shippingAddress << endl;

        cout << "Order Price: " << info->orderPrice << endl;

        cout << "Priority: " << info->priority << endl;

        cout << "Age: " << info->age << endl;

        cout << "....." << endl;

        temp = temp->next;
    }
}


// clear all orders.

void OrderDeque::clearDeque()
{
    while(head != nullptr)
    {
        OrderNode* temp = head;

        head = head->next;

        delete temp->info;
        delete temp;
    }

    tail = nullptr;
}


//deque size.
int OrderDeque::dequeSize()
{
    int count = 0;

    OrderNode* temp = head;

    while(temp != nullptr)
    {
        count++;
        temp = temp->next;
    }

    return count;
}

void Order::allOrderPrinter()
{ for(int i = 0 ; i < allOrders.vectorSize() ; i++)
  {cout<<"Orders:"<<endl;
   cout<<"("<<i+1<<")"<<allOrders[i]->orderID << "  "<<allOrders[i]->shopID << "  "<<allOrders[i]->shopName << "  "<<allOrders[i]->orderPrice << "  "<<endl;
   for(int j = 0; j<allOrders[i]->orderedProducts.vectorSize(); j++)
   {cout<<"("<<j+1<<")"<<allOrders[i]->orderedProducts[j]->getProductID() << "  "<<allOrders[i]->orderedProducts[j]->getProductName()<< "  "<<allOrders[i]->orderedProducts[j]->getAvailableProductItems() << "  "<<endl;
   }
  }}
