#include "mydatastore.h"
#include "util.h"
#include <iostream>

using namespace std;

MyDataStore::MyDataStore()
{
}
MyDataStore::~MyDataStore()
{
  for(vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it){
    delete *it;
  }

  for(map<string, User*>::iterator it = users_.begin();
        it != users_.end();
        ++it) {
        delete it->second;
    }
  
}

void MyDataStore::addProduct(Product* p)
{
  products_.push_back(p);

  set<string> keys = p->keywords();

  for(set<string>::iterator it= keys.begin(); it!= keys.end(); ++it){
    keywordMap_[convToLower(*it)].insert(p);

  }
}

void MyDataStore::addUser(User* u)
{
  string username = convToLower(u->getName());

  if(users_.find(username) == users_.end()){
    users_[username] = u;
    carts_[username] = vector<Product*>();

  }
  else{
    delete u;
  }
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type){
  vector<Product*> result;

  if(terms.size() == 0){
    return result;
  }
  set<Product*> matches;
  
  if(type == 0){
    string firstTerm = convToLower(terms[0]);

    map<string, set<Product*>::iterator first = keywordMap_.find(firstTerm);

    if(first == keywordMap_.end()){
      return result;
    }

    matches = first->second;
    for(unsigned int i = 1; i <terms.size(); i++){
      string term = convToLower(terms[i]);
      map<string, set<Product*>::iterator it = keywordMap_.find(term);

      if(it == keywordMap_.end()){
        matches.clear();
        break;
      }
      matches = setIntersection(matches, it->second);
    }
  }
  else{
    for(unsigned int i = 0; i < terms.size(); i++){
      string term = convToLower(terms[i]);

      map<string, set<Product*>::iterator it = keywordMap_.find(term);

      if(it != keywordMap_.end()){
        matches = setUnion(matches, it->second);
      }
    }
  }
  for(set<Product*>::iterator it = matches.begin; it != matches.end(); ++it){
  result.push_back(*it)
  }
  return result;
}


bool MyDataStore::addToCart(string username, Product* product)
{
    username = convToLower(username);

    map<string, User*>::iterator userIt = users_.find(username);

    if(userIt == users_.end()) {
        return false;
    }

    carts_[username].push_back(product);
    return true;
}


bool MyDataStore::viewCart(string username)
{
  username = convToLower(username);

  map<string, User*>::iterator userIt = users_.find(username);

  if(userIt == users_.end()){
    return false;
  }

  vector<Product*>& cart = carts_[username];

  for(unsigned int i = 0; i < cart.size(); i++){
    cout <<"Item " << (i + 1) << endl;
    cout << cart[i]->displayString() << endl;

  }
  return true;
}

bool MyDataStore::buyCart(string username)
{
  username = convToLower(username);
  map<string, User*>::iterator userIt = users_.find(username);

  if(userIt == users_.end()){
    return false;}

    User* user = userIt->second;
    vector<Product*>& cart = carts_[username];

    vector<Product*> remaining;

    for(vector<Product*>::iterator it = cart.begin();
    it != cart.end(); ++it){
      Product* product = *it;

      if(product->getQty() > 0 && user->getBalance() >= product->getPrice()){
        product->subtractQty(1);
        user->deductAmount(product->getPrice());
      
      }else{
        remaining.push_back(product);
      } 
      cart = remaining;
      return true;  
    }

  }


void MyDataStore::dump(ostream& ofile)
{
    ofile << "<products>" << endl;

    for(vector<Product*>::iterator it = products_.begin();
        it != products_.end();
        ++it) {
        (*it)->dump(ofile);
    }

    ofile << "</products>" << endl;

    ofile << "<users>" << endl;

    for(map<string, User*>::iterator it = users_.begin();
        it != users_.end();
        ++it) {
        it->second->dump(ofile);
    }

    ofile << "</users>" << endl;
}