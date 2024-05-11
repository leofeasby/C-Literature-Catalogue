// Description: Main file including ASCII art and menu.
// Author: Leo Feasby
// Date: 11/05/2024

#include "../include/DatabaseManager.h"
#include <iostream>
#include <limits>
#include <vector>
#include <thread>
#include <chrono>
void displayBookOpeningAnimation() 
{
  const std::vector<std::string> frames = 
  {
        R"(
     __...--~~~~~-._       _.-~~~~~--...__
   //                 `V'                \\
  //                                      \\
 //__...--~~~~~~-._        _.-~~~~~~--...__\\
//__.....----~~~~._\   |  /_.~~~~----.....__\\
====================\\ | //====================
                     `---`
)",
        R"(
     __...--~~~~~-._       _.-~~~~~--...__
   //                 `V'                \\
  //   Welcome                             \\
 //__...--~~~~~~-._        _.-~~~~~~--...__\\
//__.....----~~~~._\   |  /_.~~~~----.....__\\
====================\\ | //====================
                     `---`
)",
        R"(
     __...--~~~~~-._       _.-~~~~~--...__
   //                 `V'                \\
  //   Welcome to                         \\
 //__...--~~~~~~-._        _.-~~~~~~--...__\\
//__.....----~~~~._\   |  /_.~~~~----.....__\\
====================\\ | //====================
                     `---`
)",
        R"(
     __...--~~~~~-._       _.-~~~~~--...__
   //                 `V'                \\
  //   Welcome to the                     \\
 //__...--~~~~~~-._        _.-~~~~~~--...__\\
//__.....----~~~~._\   |  /_.~~~~----.....__\\
====================\\ | //====================
                     `---`
)",
        R"(
     __...--~~~~~-._       _.-~~~~~--...__
   //                 `V'                \\
  //   Welcome to the Academic           \\
 //__...--~~~~~~-._        _.-~~~~~~--...__\\
//__.....----~~~~._\   |  /_.~~~~----.....__\\
====================\\ | //====================
                     `---`
)",
        R"(
     __...--~~~~~-._       _.-~~~~~--...__
   //                 `V'                \\
  //   Welcome to the Academic Literature\\
 //__...--~~~~~~-._        _.-~~~~~~--...__\\
//__.....----~~~~._\   |  /_.~~~~----.....__\\
====================\\ | //====================
                     `---`
)",
        R"(
     __...--~~~~~-._       _.-~~~~~--...__
   //                 `V'                \\
  //   Welcome to the Academic Literature\\
 //   Catalogue                           \\
//__...--~~~~~~-._        _.-~~~~~~--...__\\
//__.....----~~~~._\   |  /_.~~~~----.....__\\
====================\\ | //====================
                     `---`
)"
  };
  const std::string colorStart = "\033[1;36m"; // Cyan color start
  const std::string colorEnd = "\033[0m"; // Reset color
  for (const auto& frame : frames)
  {
    std::cout << "\033[2J\033[1;1H"; // Clear the screen and move cursor to home position
    std::cout << colorStart << frame << colorEnd << std::endl; // Apply cyan color to frame
    std::this_thread::sleep_for(std::chrono::milliseconds(250)); // Adjust time for each frame to control animation speed
  }
}

void displayMenu() 
{
  std::cout << R"(

    
     __...--~~~~~-._       _.-~~~~~--...__
   //                 `V'                \\
  //   Academic Literature Catalogue      \\
 //__...--~~~~~~-._        _.-~~~~~~--...__\\
//__.....----~~~~._\   |  /_.~~~~----.....__\\
====================\\ | //====================
                     `---`

                     

========================================
1. Show all by type
2. Search

3. Add New Journal
4. Add New Thesis
5. Add New Book

6. Display Total Number of Entries
7. Remove Entry
8. Edit Entry

9. Display average book price
10. Display cheapest book
11. Display most expensive book
12. Display All Entries

13. Exit
========================================
Enter your choice: )";
}
template<typename T>
void display_all_entries(const std::vector<T>& entries) 
{
  if (entries.empty()) 
  {
    std::cout << "No entries available." << std::endl;
    return;
  }
  for (const auto& entry : entries) 
    entry.display();
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
    displayBookOpeningAnimation();
    std::cout << "Initializing Database Manager...\n";
    DatabaseManager dbManager; 
    int choice = 0;
    std::cout << "Loading data from file...\n";
    dbManager.load_data_from_file("./literature_catalogue.dat");
    while (choice != 13) 
    {
      displayMenu();
      choice = validateUserInput<int>("Enter your choice: ", 1, 13, "Error: Invalid choice. Please enter a number between 1 and 13.\n");

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
        case 2:
        {
          std::cout << "Search Options:\n";
          std::cout << "1. By Title\n";
          std::cout << "2. By Author\n";
          std::cout << "3. By ID\n";
          int searchChoice = validateUserInput<int>("Enter your choice: ", 1, 3, "Invalid search option. Please try again.\n");

          switch (searchChoice) 
          {
            case 1:
            {
              std::cout << "Searching literature by title...\n";
              std::string title;
              std::cout << "Enter title to search: ";
              getline(std::cin, title);
              if (!title.empty()) 
                dbManager.search_literature_by_title(title);
              else 
                std::cout << "Invalid input. Title cannot be empty.\n";
              break;
            }
            case 2:
            {
              std::cout << "Enter author name: ";
              std::string author;
              getline(std::cin, author);
              if (!author.empty()) 
                dbManager.search_by_author(author);
              else 
                std::cout << "Invalid input. Author name cannot be empty.\n";
              break;
            }
            case 3:
            {
              std::cout << "Enter ID (number only): ";
              int id = validateUserInput<int>("", 1, std::numeric_limits<int>::max(), "Invalid ID. Please enter a valid number.\n");
              std::cout << "Enter type (B for Book, T for Thesis, J for Journal): ";
              char type;
              std::cin >> type;
              type = toupper(type); // Convert to uppercase to make capitalization not matter
              if (type == 'B' || type == 'T' || type == 'J') 
              {
                std::string title = dbManager.get_title_by_id(id, type);
                std::cout << "Title: " << title << std::endl;
              } 
              else 
                std::cout << "Invalid type. Please enter B, T, or J.\n";
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer after reading a single character
              break;
            }
            default:
              std::cout << "Invalid search option. Please try again.\n";
          }
        }
        break;
        case 3:
        {
          std::cout << "Adding new journal...\n";
          std::string title;
          float impactFactor;
          int volumes;
          std::vector<std::string> editors;
          std::string scope;
          std::cout << "Enter journal title: ";
          getline(std::cin, title);
          impactFactor = validateUserInput<float>("Enter impact factor: ", 0.0, std::numeric_limits<float>::max(), "Error reading impact factor. Please enter a valid number.\n");
          volumes = validateUserInput<int>("Enter volumes: ", 1, std::numeric_limits<int>::max(), "Error reading volumes. Please enter a valid number.\n");
          std::cout << "Enter scope: ";
          getline(std::cin, scope);
          dbManager.add_journal(Journal(0, title, impactFactor, volumes, editors, scope));
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
          dbManager.add_thesis(Thesis(0, title, author, supervisor, university));
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
          float price;
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
          price = validateUserInput<float>("Enter price: ", 0.0, std::numeric_limits<float>::max(), "Error reading price. Please enter a valid number.\n");
          dbManager.add_book(Book(0, title, authors, publisher, subject, price));
          std::cout << "Book added successfully.\n";
          break;
        }
        case 6:
        {
          std::cout << "Select type of data to display count:\n";
          std::cout << "1. All\n2. Books\n3. Theses\n4. Journals\nEnter choice: ";
          int countChoice;
          countChoice = validateUserInput<int>("Enter choice: ", 1, 4, "Invalid choice. Please enter a number between 1 and 4.\n");
          switch(countChoice) {
            case 1:
              std::cout << R"(
             ---------                     ---------             
           --     -       ----------------         --            
          -- -- - --                                --           
          - --   - -                                 -           
          - -    - -                                  -          
          -  - - - -                                  -          
          -     -  -                                  -          
           -   --  -                                  -          
             -     -                                 --          
                  --                                 -           
                  --      'Total entries: )" << dbManager.get_total_entries() << R"('       -           
                  -                                 --           
                  -                                 -            
                 --                                 -            
                 -                                 -             
                --                                 -             
               --                                 -              
               -                                  -              
              --  ---------                   --------           
             --  --  --                               -          
             -  --    -                               -          
             -  -   - -                               -          
             -  --  - -                               -          
             --  ---- -                              -           
              --     -     ----------------         --           
               ---  ----                       --- --            
                                                                 
                                                                                                                  
)" << std::endl;
              break;
            case 2:
              std::cout << R"(
             ---------                     ---------             
           --     -       ----------------         --            
          -- -- - --                                --           
          - --   - -                                 -           
          - -    - -                                  -          
          -  - - - -                                  -          
          -     -  -                                  -          
           -   --  -                                  -          
             -     -                                 --          
                  --                                 -           
                  --       'Total books: )" << dbManager.get_total_books() << R"('         -           
                  -                                 --           
                  -                                 -            
                 --                                 -            
                 -                                 -             
                --                                 -             
               --                                 -              
               -                                  -              
              --  ---------                   --------           
             --  --  --                               -          
             -  --    -                               -          
             -  -   - -                               -          
             -  --  - -                               -          
             --  ---- -                              -           
              --     -     ----------------         --           
               ---  ----                       --- --            
                                                                 
                                                         
)" << std::endl;
              break;
            case 3:
              std::cout << R"(
             ---------                     ---------             
           --     -       ----------------         --            
          -- -- - --                                --           
          - --   - -                                 -           
          - -    - -                                  -          
          -  - - - -                                  -          
          -     -  -                                  -          
           -   --  -                                  -          
             -     -                                 --          
                  --                                 -           
                  --     'Total theses: )" << dbManager.get_total_theses() << R"('             -           
                  -                                 --           
                  -                                 -            
                 --                                 -            
                 -                                 -             
                --                                 -             
               --                                 -              
               -                                  -              
              --  ---------                   --------           
             --  --  --                               -          
             -  --    -                               -          
             -  -   - -                               -          
             -  --  - -                               -          
             --  ---- -                              -           
              --     -     ----------------         --           
               ---  ----                       --- --            
                                                                 
                                                         
)" << std::endl;
              break;
            case 4:
              std::cout << R"(
             ---------                     ---------             
           --     -       ----------------         --            
          -- -- - --                                --           
          - --   - -                                 -           
          - -    - -                                  -          
          -  - - - -                                  -          
          -     -  -                                  -          
           -   --  -                                  -          
             -     -                                 --          
                  --                                 -           
                  --      'Total journals: )" << dbManager.get_total_journals() << R"('      -           
                  -                                 --           
                  -                                 -            
                 --                                 -            
                 -                                 -             
                --                                 -             
               --                                 -              
               -                                  -              
              --  ---------                   --------           
             --  --  --                               -          
             -  --    -                               -          
             -  -   - -                               -          
             -  --  - -                               -          
             --  ---- -                              -           
              --     -     ----------------         --           
               ---  ----                       --- --            
                                                                 
                                                         
)" << std::endl;
              break;
            default:
              std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
              break;
          }
          break;
      }
      case 7:
      {
        std::cout << "\033[31m"<< R"(
                                                     
                                                                               
                                                     
                        &&                           
           &          &&&& &                         
          &&&        &$X$&&&&             &          
    &     &&&       &$XX&&&&&        &&   &&         
   &&    &&&&     &&$XX$&&&$&       &&&&&  &&&       
   &&  &&&&$$&   &&&$XX$&&$$$&     &&&&$&&&&&&&      
& &&&&&&$&&$$&&&&&&$XXx$$$$$$&&    &&&$x$&&&$$&&    &
&&&&&&$$$&X$X$&&&&&$$XxX$$XX$&&&    &&$xx&&$$$&&&&&&&
&&&&&$X$&$X&$X$&&&&$Xx+X$XXxX$&&&  &&&$Xx$&&XX&&&&&&&
&&&&$XX$$xX&$X$$&&&$X++XX$X++X$&&&&&&$XXx$&$XX$$&&&&&
&&&&$Xxxx:$$x+X$&&&$X++XXX$+;+X$&&&&$XXXxX&&XXX$$$&&&
$&&$Xx+;.:$X+;X$$$&$X;+xXX$x:;xX$$$$X+XXxx$&XXXxX$$&&
$&&$X+:. ;$X;;X$$$$X+:++X$$x.:+X$$XX+;xX+xxXXxx;;xXX$
$&&$X+:  ;X+:+xX$XX+::;:X$X; :;xXXx+:.xXx+xxx++; :+xX
Xxx;.    ;:..;+XXx;:.. ;XX+  :;xXx+:  :+++;+x++;. ;++
; ..    .:  .;;+xx+;:..+xx:  .:+x+;.  ....:;;+++:.:;;
.        .   ..:;;;;  :;;:    .+x+:         ::;+;.:;:
               ...    .::.     :+;.          .:::... 
                                ..                   
)" << "\033[0m" << std::endl;
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
      case 8:
      {
        std::cout << "\033[32m" << R"(
                                                                                 

                                --   
                            -----    
                          ------     
                        -------      
                      --------       
                    ---------        
                  ---------          
                ----------           
               ----------            
             ----------              
            ----------               
           ---------                 
          --------                   
         ------                      
      ------                         
      ------                         
    ----------                       
   -----------                       
   -----------                       
   -----------                                                                                                
)" << "\033[0m" << "Enter the type of literature to edit (book, thesis, journal): ";
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
        case 9:
        {
          std::cout << "\n====================\n\n";
          dbManager.display_average_book_price();
          std::cout << "\n====================\n\n";
          break;
        }
        case 10:
        {
          std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
          dbManager.display_cheapest_book();
          std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
          break;
        }

        case 11:
          std::cout << "\n<> ~~~~~~~~~~~~~~~~~~~~~~~~ <>\n\n";
          dbManager.display_most_expensive_book();
          std::cout << "\n<> ~~~~~~~~~~~~~~~~~~~~~~~~ <>\n\n";
          break;
        case 12:
          std::cout << "Displaying all entries...\n";
          std::cout << "Books:\n";
          display_all_entries(dbManager.get_books());
          std::cout << "\nTheses:\n";
          display_all_entries(dbManager.get_theses());
          std::cout << "\nJournals:\n";
          display_all_entries(dbManager.get_journals());
          break;
        case 13:
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
