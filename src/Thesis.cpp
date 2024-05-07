// Thesis class implementation
// Author: Leo Feasby
// Date: 13/04/2024

#include "../include/Thesis.h"
#include <iostream>

Thesis::Thesis(int id, std::string title, std::string author, std::string supervisor, std::string university)
  : Literature(id, title), author(author), supervisor(supervisor), university(university)
{
}

void Thesis::display() const
{
  std::cout<<"Thesis ID: "<<id<<"\nTitle: "<<title<<"\nAuthor: "<<author
           <<"\nSupervisor: "<<supervisor<<"\nUniversity: "<<university<<std::endl;
}
