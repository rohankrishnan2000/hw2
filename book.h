#ifndef BOOK_H
#define BOOK_H


#include "product.h"
#include <string>
#include <set>


class Book : public Product
{
  public:
    Book(const std::string category,
        const std::string name,
        double price,
        int qty,
        const std::string isbn,
        const std::string author);
    virtual ~Book();
}