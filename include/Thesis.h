// Thesis class header file
// Author: Leo Feasby
// Date: 13/04/2024

#ifndef THESIS_H
#define THESIS_H

#include "Literature.h"
#include <string>

class Thesis : public Literature
{
public:
  std::string author;
  std::string supervisor;
  std::string university;

  Thesis(int id, std::string title, std::string author, std::string supervisor, std::string university);
  void display() const override;
  bool operator==(const Thesis& other) const
  {
    return id == other.id; // Assuming 'id' uniquely identifies a thesis
  }
};

#endif
