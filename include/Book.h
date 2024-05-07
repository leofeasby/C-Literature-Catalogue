// Description: Header file for the Book class, inheriting from Literature, to manage book-related information.
// Author: Leo Feasby
// Date: 13/04/2024

#ifndef BOOK_H
#define BOOK_H

#include "Literature.h"
#include <string>
#include <vector>

// Book class definition
class Book : public Literature 
{
public:
  std::vector<std::string> authors;
  std::string publisher;
  std::string subject;
  float price;

  Book(int id, std::string title, std::vector<std::string> authors, std::string publisher, std::string subject, float price, float rating = 0.0);
  void display() const override;
  void setRating(float new_rating); // New method to update rating
  bool operator==(const Book& other) const 
  {
    return id == other.id; // Assuming 'id' uniquely identifies a book
  }
};

#endif
