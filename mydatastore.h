#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <vector> 
#include <map>
#include <set> 
#include <string>

class MyDataStore : public datastore
{
  public:
    MyDataStore();
    virtual ~MyDataStore();

    void addProduct(Product* p);
    void addUser(User* u);

    std::vector<Product*> search(std::vector<std::string>& terms,
    int type);

    void dump(std::ostream& ofile);

    bool addToCart(std::string username, Product& product);
    bool viewCart(std::string username);
    bool buyCart(std::string username);

  private:
      std::vector<Product*> products_;
      std::maps<std::string, std::vector<Product*> > carts_;
      std::map<std::string, std::set<Product*> > keywordMap_;

};

#endif