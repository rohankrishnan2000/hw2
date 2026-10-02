class Movie : public Product
{
  public:
    Movie(const std::string category,
          const std::string name,
          double price,
          int qty,
          const std::string genre,
          const std::string rating);

    virtual ~Movie();


    std::set<std::string> keywords() const;
    std::striing displayString() const;
    void dump(std::ostream& os) const;

    private:
      std::string genre_;
      std::string rating_;
}

#endif