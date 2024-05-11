// Description: Base class for managing literature-related information.
// Author: Leo Feasby
// Date: 11/05/2024

#ifndef LITERATURE_H
#define LITERATURE_H

#include <string>

class Literature 
{
public:
  int id;
  std::string title;

  Literature(int id, std::string title) : id(id), title(title) {}
  virtual void display() const = 0;
  virtual ~Literature() {}
};

#endif