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
  std::cout << "3. Add New Journal\n";
  std::cout << "4. Add New Thesis\n";
  std::cout << "5. Add New Book\n";
  std::cout << "6. Remove / Burn Entry\n";
  std::cout << "7. Edit Entry\n";
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
        case 3:
        {
          std::cout << "Adding new journal...\n";
          std::string title;
          float impactFactor;
          int volumes;
          std::vector<std::string> editors; // Assume you have a way to capture this
          std::string scope;
          std::cout << "Enter journal title: ";
          getline(std::cin, title);
          impactFactor = validateUserInput<float>("Enter impact factor: ", 0.0, std::numeric_limits<float>::max(), "Error reading impact factor. Please enter a valid number.\n");
          volumes = validateUserInput<int>("Enter volumes: ", 1, std::numeric_limits<int>::max(), "Error reading volumes. Please enter a valid number.\n");
          std::cout << "Enter scope: ";
          getline(std::cin, scope);
          dbManager.add_journal(Journal(0, title, impactFactor, volumes, editors, scope)); // Corrected to match the constructor signature
          std::cout << "Journal added successfully.\n";
          break;
        }
        case 4:
        {
          std::cout << "Adding new thesis...\n";
          std::string title;
          std::string author;
          std::string supervisor;
          std::string university;
          std::cout << "Enter thesis title: ";
          getline(std::cin, title);
          std::cout << "Enter author: ";
          getline(std::cin, author);
          std::cout << "Enter supervisor: ";
          getline(std::cin, supervisor);
          std::cout << "Enter university: ";
          getline(std::cin, university);
          dbManager.add_thesis(Thesis(0, title, author, supervisor, university)); // Assuming ID is auto-incremented or not needed
          std::cout << "Thesis added successfully.\n";
          break;
        }

        case 5:
        {
          std::cout << "Adding new book...\n";
          std::string title;
          std::vector<std::string> authors;
          std::string publisher;
          std::string subject;
          std::cout << "Enter book title: ";
          getline(std::cin, title);
          std::cout << "Enter author: ";
          std::string author;
          getline(std::cin, author);
          authors.push_back(author); 
          std::cout << "Enter publisher: ";
          getline(std::cin, publisher);
          std::cout << "Enter subject: ";
          getline(std::cin, subject);
          dbManager.add_book(Book(0, title, authors, publisher, subject)); // Assuming ID is auto-incremented or not needed
          std::cout << "Book added successfully.\n";
          break;
        }
        case 6:
        {
          std::cout << "Enter the type of literature to remove (book, thesis, journal): ";
          std::string type;
          getline(std::cin, type);
          std::cout << "Enter the ID of the " << type << " to remove: ";
          int id;
          std::cin >> id;
          if(type == "book") {
            dbManager.remove_book_by_id(id);
          } else if(type == "thesis") {
            dbManager.remove_thesis_by_id(id);
          } else if(type == "journal") {
            dbManager.remove_journal_by_id(id);
          } else {
            std::cout << "Invalid type entered.\n";
         }
          break;
      }
      case 7:
      {
        std::cout << "Enter the type of literature to edit (book, thesis, journal): ";
        std::string type;
        getline(std::cin, type);
        if(type == "book")
        {
          std::cout << "Available Book IDs: ";
          dbManager.display_book_ids();
          std::cout << "\nEnter the ID of the book to edit: ";
          int id;
          std::cin >> id;
          if(dbManager.edit_book_by_id(id))
            displayMenu();
        }
        else if(type == "thesis")
        {
          std::cout << "Available Thesis IDs: ";
          dbManager.display_thesis_ids();
          std::cout << "\nEnter the ID of the thesis to edit: ";
          int id;
          std::cin >> id;
          if(dbManager.edit_thesis_by_id(id))
            displayMenu();
        }
        else if(type == "journal")
        {
          std::cout << "Available Journal IDs: ";
          dbManager.display_journal_ids();
          std::cout << "\nEnter the ID of the journal to edit: ";
          int id;
          std::cin >> id;
          if(dbManager.edit_journal_by_id(id))
            displayMenu();
        }
        else
        {
          std::cout << "Invalid type entered.\n";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Flush the newline character out of the buffer
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
