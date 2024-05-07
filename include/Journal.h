// Description: Header file for the Journal class, inheriting from Literature, to manage journal-related information.
// Author: Leo Feasby
// Date: 13/04/2024

#ifndef JOURNAL_H
#define JOURNAL_H

#include<iostream>
#include "Literature.h"
#include <string>
#include <vector>

class Journal : public Literature 
{
public:
  float impact_factor;
  int volumes;
  std::vector<std::string> editors;
  std::string scope;

  Journal(int id, std::string title, float impact_factor, int volumes, std::vector<std::string> editors, std::string scope);
  void display() const override;
  bool operator==(const Journal& other) const 
  {
    return id == other.id; // Assuming 'id' uniquely identifies a journal
  }
};

#endif
