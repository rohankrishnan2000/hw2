#include "book.h"
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std;

Book::Book(const std::string category,
           const std::string name,
           double price,
           int qty,
           const std::string isbn,
           const std::string author) :
    Product(category, name, price, qty),
    isbn_(isbn),
    author_(author)
{
}

Book::~Book()
{
}

set<string> Book::keywords() const
{
    set<string> keys = parseStringToWords(name_);
    set<string> authorKeys = parseStringToWords(author_);

    keys = setUnion(keys, authorKeys);
    keys.insert(convToLower(isbn_));

    return keys;
}

string Book::displayString() const
{
    stringstream ss;

    ss << name_ << endl;
    ss << "Author: " << author_ << " ISBN: " << isbn_ << endl;
    ss << fixed << setprecision(2) << price_ << " " << qty_ << " left.";

    return ss.str();
}

void Book::dump(ostream& os) const
{
    Product::dump(os);
    os << isbn_ << endl;
    os << author_ << endl;
}
