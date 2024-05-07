// Description: Implementation of the Book class, handling book details and display functionality.
// Author: Leo Feasby
// Date: 13/04/2024

#include "../include/Book.h"
#include <iostream>

Book::Book(int id, std::string title, std::vector<std::string> authors, std::string publisher, std::string subject, float price, float rating)
  : Literature(id, title), authors(authors), publisher(publisher), subject(subject), price(price) 
{
}

void Book::display() const 
{
  std::cout << "Book ID: " << id << "\nTitle: " << title << "\nAuthors: ";
  for (const auto& author : authors) 
  {
    std::cout << author << "; ";
  }
  std::cout << "\nPublisher: " << publisher << "\nSubject: " << subject << "\nPrice: $" << price << "\nRating: " << std::endl;
}


