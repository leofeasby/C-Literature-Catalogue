// src/main.cpp
#include "../include/DatabaseManager.h"
#include <iostream>
#include <limits>
#include <vector>
#include <thread>
#include <chrono>


void displayMenu() 
{
  std::cout << "Academic Literature Catalogue\n";
  std::cout << "========================================\n";
  std::cout << "1. Show all by type\n";
  std::cout << "8. Exit\n";
  std::cout << "========================================\n";
  std::cout << "Enter your choice: ";
}
template<typename T>
T validateUserInput(const std::string& prompt, T min, T max, const std::string& errorMessage) 
{
  T input;
  while (true) 
  {
    std::cout << prompt;
    std::cin >> input;
    if (std::cin.fail() || input < min || input > max) 
    {
      std::cerr << errorMessage;
      std::cin.clear(); // Clear error flag
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip to the next newline
    } 
    else 
    {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer
      return input;
    }
  }
}

int main() 
{
  try
  {
    std::cout << "Initializing Database Manager...\n";
    DatabaseManager dbManager; // Updated to reflect the new constructor
    int choice = 0;
    std::cout << "Loading data from file...\n";
    dbManager.load_data_from_file("./literature_catalogue.dat");
    while (choice != 8) 
    {
      displayMenu();
      choice = validateUserInput<int>("Enter your choice: ", 1, 8, "Error: Invalid choice. Please enter a number between 1 and 8.\n");

      switch (choice) 
      {
        case 1:
        {
          bool continueSearch = true;
          while (continueSearch) 
          {
            std::cout << "Enter type (book, thesis, journal): ";
            std::string type;
            getline(std::cin, type);
            dbManager.search_by_type(type);
            
            std::cout << "Do you want to search another type? (yes/no): ";
            std::string answer;
            getline(std::cin, answer);
            if (answer != "yes") 
              continueSearch = false;
          }
          break;
        }
        case 8:
          std::cout << "Exiting program.\n";
          break;
        default:
          std::cout << "Invalid choice. Please try again.\n";
      }
    }
  } 
  catch (const std::runtime_error& e) 
  {
    std::cerr << "Failed to initialize the Database Manager: " << e.what() << std::endl;
    return -1;
  }
  return 0;
}


