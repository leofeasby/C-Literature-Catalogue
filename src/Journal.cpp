// Description: Implementation of the Journal class, displaying journal details.
// Author: Leo Feasby
// Date: 11/05/2024

#include "../include/Journal.h"
#include<iostream>

Journal::Journal(int id, std::string title, float impact_factor, int volumes, std::vector<std::string> editors, std::string scope)
  : Literature(id, title), impact_factor(impact_factor), volumes(volumes), editors(editors), scope(scope) 
{
}

void Journal::display() const 
{
  std::cout << "Journal ID: " << id << "\nTitle: " << title << "\nImpact Factor: " << impact_factor
            << "\nVolumes: " << volumes << "\nEditors: ";
  for (const auto& editor : editors) 
  {
    std::cout << editor << "; ";
  }
  std::cout << "\nScope: " << scope << std::endl;
}
