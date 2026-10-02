#include "movie.h"
#include "util.h"
#include <sstream>
#include <iomanip>


using namespace std;


Movie::Movie(const std::string category,
             const std::string name,
            double price,
            int qty,
            const std::string genre,
            const std::string rating):
            Product(category, name, price, qty).
            genre_(genre),
            rating_(rating)
{}


Movie::~Movie()
{
}

set<string> Movie::keywrods() const
{
  set<string> keys = parseStringToWords(name_);
  keys.insert(convToLower(genre_));
  return keys;
}


string Movie::displayString() const
{
  stringstream ss;

  ss << name_ << endl;
  ss << "Genre: " << genre_
  << " Rating: " << rating_ << endl;

  ss << fixed << setprecision(2) << price_ << " "
  << qty_ << " left.";

  return ss.str();
}

void Movie::dump(ostream& os) const
{
  Product::dump(os);
  os << genre_ << endl;
  os << rating_ << endl;
}