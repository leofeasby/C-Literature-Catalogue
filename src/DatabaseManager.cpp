// src/DatabaseManager.cpp
#include "../include/DatabaseManager.h"
#include "../include/Thesis.h"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <limits>
#include <map>
#include <unordered_map>
#include <cctype> // Added to resolve the "qualified name is not allowed" error

std::string join(const std::vector<std::string>& vec, const std::string& delim)
{
  std::ostringstream result;
  for (auto it = vec.begin(); it != vec.end(); ++it)
  {
    if (it != vec.begin())
      result << delim;
    result << *it;
  }
  return result.str();
}

// Function to split a string by a delimiter and return a vector of strings
std::vector<std::string> splitString(const std::string& str, char delim)
{
  std::vector<std::string> tokens;
  std::stringstream ss(str);
  std::string token;
  while (getline(ss, token, delim))
    tokens.push_back(token);
  return tokens;
}

// New function to split author names by comma
std::vector<std::string> splitAuthors(const std::string& authorStr)
{
  std::vector<std::string> authors;
  std::istringstream iss(authorStr);
  std::string author;
  while (getline(iss, author, ','))
    authors.push_back(author);
  return authors;
}
DatabaseManager::DatabaseManager()
: next_book_id(0), next_thesis_id(0), next_journal_id(0) 
{
}

DatabaseManager::~DatabaseManager() 
{
}

void DatabaseManager::add_book(const Book& book)
{
  Book new_book = book;
  new_book.id = next_book_id++; // Set the book ID and increment the counter
  books.push_back(new_book);
  book_map[new_book.id] = &books.back(); // Add to map for quick access
  literature_title_map[{new_book.id, 'B'}] = new_book.title; // Update literatureTitleMap
  std::cout << "Book added. Total books: " << books.size() << std::endl;
  write_all_to_file();
}

void DatabaseManager::append_book_to_file(const Book& book)
{
  std::ofstream file("./literature_catalogue.dat", std::ios_base::app);
  if (!file.is_open())
    std::cerr << "Unable to open file for appending.\n";
  else
  {
    file << book.id << "|" << book.title << "|" << join(book.authors, ";") << "|" 
         << book.publisher << "|" << book.subject << "|" << book.price << "\n";
    file.close();
  }
}

void DatabaseManager::search_literature_by_title(const std::string& title)
{
  std::string lower_title = title;
  std::transform(lower_title.begin(), lower_title.end(), lower_title.begin(), tolower);
  bool found = false;
  for (const auto& book : books)
  {
    std::string lower_book_title = book.title;
    std::transform(lower_book_title.begin(), lower_book_title.end(), lower_book_title.begin(), tolower);
    if (lower_book_title.find(lower_title) != std::string::npos)
    {
      std::cout << R"(
  _________
 /         \
 |   ID    |   )" << book.id << R"(
 |  Title  |   )" << book.title << R"(
 |  Author |   )" << join(book.authors, ", ") << R"(
 |Publisher|   )" << book.publisher << R"(
 |  Price  |   $)" << book.price << R"(
 \_________/
      )" << std::endl;
      found = true;
    }
  }
  for (const auto& thesis : theses)
  {
    std::string lower_thesis_title = thesis.title;
    std::transform(lower_thesis_title.begin(), lower_thesis_title.end(), lower_thesis_title.begin(), tolower);
    if (lower_thesis_title.find(lower_title) != std::string::npos)
    {
      std::cout << R"(
  _________
 /         \
 |   ID    |   )" << thesis.id << R"(
 |  Title  |   )" << thesis.title << R"(
 | Author  |   )" << thesis.author << R"(
 |Supervisor|  )" << thesis.supervisor << R"(
 |University|  )" << thesis.university << R"(
 \_________/
      )" << std::endl;
      found = true;
    }
  }
  for (const auto& journal : journals)
  {
    std::string lower_journal_title = journal.title;
    std::transform(lower_journal_title.begin(), lower_journal_title.end(), lower_journal_title.begin(), tolower);
    if (lower_journal_title.find(lower_title) != std::string::npos)
    {
      std::cout << R"(
  _________
 /         \
 |   ID    |   )" << journal.id << R"(
 |  Title  |   )" << journal.title << R"(
 | Impact  |   )" << journal.impact_factor << R"(
 | Volumes |   )" << journal.volumes << R"(
 | Editors |   )" << join(journal.editors, ", ") << R"(
 |  Scope  |   )" << journal.scope << R"(
 \_________/
      )" << std::endl;
      found = true;
    }
  }
  if (!found)
    std::cout << "No literature found with title containing: " << title << std::endl;
}
void DatabaseManager::list_all_books() {
  if (books.empty()) {
    std::cout << "No books available." << std::endl;
    return;
  }

  int count = 0; // Counter to track the number of books processed
  for (const auto& book : books) {
    std::cout << R"(
     _________
    /         \
    |   ID    |   )" << book.id << R"(
    |  Title  |   )" << book.title << R"(
    |  Author |   )" << join(book.authors, ", ") << R"(
    |Publisher|   )" << book.publisher << R"(
    |  Price  |   $)" << book.price << R"(
    \_________/
        )" << std::endl;
    count++;
  }
}
// Add a thesis to the database
void DatabaseManager::add_thesis(const Thesis& thesis)
{
  Thesis new_thesis = thesis;
  new_thesis.id = next_thesis_id++; // Set the thesis ID and increment the counter
  theses.push_back(new_thesis);
  thesis_map[new_thesis.id] = &theses.back(); // Add to map for quick access
  literature_title_map[{new_thesis.id, 'T'}] = new_thesis.title; // Update literatureTitleMap
  std::cout << "Thesis added. Total theses: " << theses.size() << std::endl;
  write_all_to_file();
}

void DatabaseManager::append_thesis_to_file(const Thesis& thesis)
{
  std::ofstream file("./literature_catalogue.dat", std::ios_base::app);
  if (!file.is_open())
    std::cerr << "Unable to open file for appending.\n";
  else
  {
    file << thesis.id << "|" << thesis.title << "|" << thesis.author << "|" 
         << thesis.supervisor << "|" << thesis.university << "\n";
    file.close();
  }
}

// List all theses in the database
void DatabaseManager::list_all_theses()
{
  if (theses.empty())
    std::cout << "No theses available." << std::endl;
  else
  {
    for (const auto& thesis : theses)
    {
      std::cout << R"(
  _________
 /         \
 |   ID    |   )" << thesis.id << R"(
 |  Title  |   )" << thesis.title << R"(
 | Author   |   )" << thesis.author << R"(
 |Supervisor|  )" << thesis.supervisor << R"(
 |University|  )" << thesis.university << R"(
 \_________/
      )" << std::endl;
    }
  }
}

// Add a journal to the database
void DatabaseManager::add_journal(const Journal& journal)
{
  Journal new_journal = journal;
  new_journal.id = next_journal_id++; // Set the journal ID and increment the counter
  journals.push_back(new_journal);
  journal_map[new_journal.id] = &journals.back(); // Add to map for quick access
  literature_title_map[{new_journal.id, 'J'}] = new_journal.title; // Update literatureTitleMap
  std::cout << "Journal added. Total journals: " << journals.size() << std::endl;
  write_all_to_file();
}

// Method to append a journal to the literature_catalogue.dat file
void DatabaseManager::append_journal_to_file(const Journal& journal)
{
  std::ofstream file("./literature_catalogue.dat", std::ios_base::app); // Open in append mode
  if (!file.is_open())
    std::cerr << "Unable to open file for appending.\n";
  else
  {
    // Assuming the journal details are to be written in a specific format
    file << journal.id << "|" << journal.title << "|" << journal.impact_factor << "|" 
         << journal.volumes << "|" << join(journal.editors, ";") << "|" << journal.scope << "\n";
    file.close();
  }
}
// List all journals in the database
void DatabaseManager::list_all_journals() 
{
  std::cout << "Total journals: " << journals.size() << std::endl; // Debug statement to print the size of the journals vector
  if (journals.empty())
    std::cout << "No journals available." << std::endl;
  else
  {
    for (const auto& journal : journals)
    {
      std::cout << R"(
  _________
 /         \
 |    ID   |   )" << journal.id << R"(
 |  Title  |   )" << journal.title << R"(
 | Impact  |   )" << journal.impact_factor << R"(
 | Volumes |   )" << journal.volumes << R"(
 | Editors |   )" << join(journal.editors, ", ") << R"(
 |  Scope  |   )" << journal.scope << R"(
 \_________/
      )" << std::endl;
    }
  }
}

void DatabaseManager::search_thesis_by_title(const std::string& title) 
{
  for (const auto& thesis : theses)
  {
    if (thesis.title.find(title) != std::string::npos)
    {
      std::cout << "Thesis ID: " << thesis.id << std::endl;
      std::cout << "Thesis Title: " << thesis.title << std::endl;
      // Print other thesis details
    }
  }
}

void DatabaseManager::search_journal_by_title(const std::string& title) 
{
  for (const auto& journal : journals)
  {
    if (journal.title.find(title) != std::string::npos)
    {
      std::cout << "Journal ID: " << journal.id << std::endl;
      std::cout << "Journal Title: " << journal.title << std::endl;
      std::cout << "Volume: " << journal.volumes << std::endl;
      std::cout << "Impact Factor: " << journal.impact_factor << std::endl;
      std::cout << "Volumes: " << journal.volumes << std::endl;
      std::cout << "Editors: " << join(journal.editors, ", ") << std::endl;
      std::cout << "Scope: " << journal.scope << std::endl;
    }
  }
}
void DatabaseManager::load_data_from_file(const std::string& file_path) 
{
  std::ifstream file(file_path);
  if (!file.is_open())
  {
    std::cerr << "Unable to open file: " << file_path << std::endl;
    return;
  }
  books.clear(); // Clear books at the start of the loading function
  theses.clear(); // Clear theses at the start of the loading function
  journals.clear(); // Clear journals at the start of the loading function
  book_map.clear(); // Clear book_map at the start of the loading function
  thesis_map.clear(); // Clear thesis_map at the start of the loading function
  journal_map.clear(); // Clear journal_map at the start of the loading function
  literature_title_map.clear(); // Clear literature_title_map at the start of the loading function
  int max_book_id = 0, max_thesis_id = 0, max_journal_id = 0;

  std::string line;
  enum class ReadingMode { None, Books, Theses, Journals } mode = ReadingMode::None;

  try 
  {
    while (getline(file, line)) 
    {
      if(line.empty()) 
        continue; // Skip empty lines
      if (line == "== BOOKS ==") 
      {
        mode = ReadingMode::Books;
        continue;
      } 
      else if (line == "== THESIS ==") 
      {
        mode = ReadingMode::Theses;
        continue;
      } 
      else if (line == "== JOURNALS ==") 
      {
        mode = ReadingMode::Journals;
        continue;
      }

      std::istringstream iss(line);
      std::vector<std::string> tokens;
      std::string token;
      while (getline(iss, token, '|')) // Changed ',' to '|'
      {
        tokens.push_back(token);
      }

      switch (mode) 
      {
        case ReadingMode::Books:
        {
          if (tokens.size() >= 6) 
          {
            int id = std::stoi(tokens[0]);
            if (id < 0) 
              throw std::invalid_argument("Negative ID is not valid.");
            max_book_id = std::max(max_book_id, id);
            std::string title = tokens[1];
            std::vector<std::string> authors = splitAuthors(tokens[2]); // New function to handle multiple authors
            std::string publisher = tokens[3];
            std::string subject = tokens[4];
            float price = std::stof(tokens[5]);
            Book book(id, title, authors, publisher, subject, price);
            books.push_back(book);
            book_map[book.id] = &books.back(); // Add to map for quick access
            literature_title_map[{book.id, 'B'}] = book.title; // Update literature_title_map
          }
        }
        break;
        case ReadingMode::Theses:
        {
          if (tokens.size() >= 5) 
          {
            int id = std::stoi(tokens[0]);
            max_thesis_id = std::max(max_thesis_id, id);
            std::string title = tokens[1];
            std::string author = tokens[2];
            std::string supervisor = tokens[3]; // Assuming 'supervisor' is the 4th token
            std::string university = tokens[4];
            Thesis thesis(id, title, author, supervisor, university);
            theses.push_back(thesis);
            thesis_map[thesis.id] = &theses.back(); // Add to map for quick access
            literature_title_map[{thesis.id, 'T'}] = thesis.title; // Update literature_title_map
          }
        }
        break;
        case ReadingMode::Journals:
        {
          try 
          {
            int id = std::stoi(tokens[0]);
            max_journal_id = std::max(max_journal_id, id);
            std::string title = tokens[1];
            float impact_factor;
            try 
            {
              impact_factor = std::stof(tokens[2]);
            } 
            catch (const std::invalid_argument& e) 
            {
              std::cerr << "Invalid argument: " << e.what() << " for Journal Impact Factor\n";
              continue;
            } 
            catch (const std::out_of_range& e) 
            {
              std::cerr << "Out of range: " << e.what() << " for Journal Impact Factor\n";
              continue;
            }
            int volumes;
            try 
            {
              volumes = std::stoi(tokens[3]);
            } 
            catch (const std::invalid_argument& e) 
            {
              std::cerr << "Invalid argument: " << e.what() << " for Journal Volumes\n";
              volumes = 0; // Default value or handle differently
            }
            std::vector<std::string> editors = splitString(tokens[4], ';');
            std::string scope = tokens[5];
            Journal journal(id, title, impact_factor, volumes, editors, scope);
            journals.push_back(journal);
            journal_map[journal.id] = &journals.back(); // Add to map for quick access
            literature_title_map[{journal.id, 'J'}] = journal.title; // Update literature_title_map
          } 
          catch (const std::exception& e) 
          {
            std::cerr << "Exception caught while creating or adding a Journal: " << e.what() << std::endl;
          }
        }
        break;
        default:
        break;
      }
    }
  } 
  catch (const std::ios_base::failure& e) 
  {
    if (!file.eof()) 
    {
      std::cerr << "Exception caught while reading file: " << e.what() << std::endl;
    }
  }

  next_book_id = max_book_id + 1;
  next_thesis_id = max_thesis_id + 1;
  next_journal_id = max_journal_id + 1;

  file.close();
}
void DatabaseManager::search_by_author(const std::string& author_query)
{
  bool found = false;
  std::string lower_author_query = author_query;
  std::transform(lower_author_query.begin(), lower_author_query.end(), lower_author_query.begin(), tolower);
  for (const auto& book : books)
  {
    for (const auto& author : book.authors)
    {
      std::string lower_author = author;
      std::transform(lower_author.begin(), lower_author.end(), lower_author.begin(), tolower);
      if (lower_author.find(lower_author_query) != std::string::npos)
      {
        std::cout << R"(
    _________
   /         \
   |   ID    |   )" << book.id << R"(
   |  Title  |   )" << book.title << R"(
   |  Author |   )" << join(book.authors, ", ") << R"(
   |Publisher|   )" << book.publisher << R"(
   |  Price  |   $)" << book.price << R"(
   \_________/
        )" << std::endl;
        found = true;
      }
    }
  }
  for (const auto& thesis : theses)
  {
    std::string lower_thesis_author = thesis.author;
    std::transform(lower_thesis_author.begin(), lower_thesis_author.end(), lower_thesis_author.begin(), tolower);
    if (lower_thesis_author.find(lower_author_query) != std::string::npos)
    {
      std::cout << R"(
    _________
   /         \
   |   ID    |   )" << thesis.id << R"(
   |  Title  |   )" << thesis.title << R"(
   | Author   |   )" << thesis.author << R"(
   |Supervisor|  )" << thesis.supervisor << R"(
   |University|  )" << thesis.university << R"(
   \_________/
        )" << std::endl;
      found = true;
    }
  }
  for (const auto& journal : journals)
  {
    for (const auto& editor : journal.editors)
    {
      std::string lower_editor = editor;
      std::transform(lower_editor.begin(), lower_editor.end(), lower_editor.begin(), tolower);
      if (lower_editor.find(lower_author_query) != std::string::npos)
      {
        std::cout << R"(
    _________
   /         \
   |   ID    |   )" << journal.id << R"(
   |  Title  |   )" << journal.title << R"(
   | Impact  |   )" << journal.impact_factor << R"(
   | Volumes |   )" << journal.volumes << R"(
   | Editors |   )" << join(journal.editors, ", ") << R"(
   |  Scope  |   )" << journal.scope << R"(
   \_________/
        )" << std::endl;
        found = true;
      }
    }
  }
  if (!found)
    std::cout << "No literature found by author: " << author_query << std::endl;
}

void DatabaseManager::search_by_type(const std::string& type)
{
  if (type == "book")
    list_all_books();
  else if (type == "thesis")
    list_all_theses();
  else if (type == "journal")
    list_all_journals();
  else
    std::cout << "Invalid type. Please enter 'book', 'thesis', or 'journal'." << std::endl;
}

void DatabaseManager::remove_book_by_id(int id)
{
  display_book_ids();
  std::cout << "\nEnter the ID of the book to remove: ";
  auto it = book_map.find(id);
  if(it != book_map.end())
  {
    books.erase(std::remove(books.begin(), books.end(), *(it->second)), books.end());
    book_map.erase(it);
    literature_title_map.erase({id, 'B'}); // Update literatureTitleMap
    std::cout << "Book removed successfully.\n";
    write_all_to_file();
  }
  else
    std::cout << "Book with ID " << id << " not found.\n";
}

void DatabaseManager::remove_thesis_by_id(int id)
{
  display_thesis_ids();
  std::cout << "\nEnter the ID of the thesis to remove: ";
  auto it = thesis_map.find(id);
  if(it != thesis_map.end())
  {
    theses.erase(std::remove(theses.begin(), theses.end(), *(it->second)), theses.end());
    thesis_map.erase(it);
    literature_title_map.erase({id, 'T'}); // Update literatureTitleMap
    std::cout << "Thesis removed successfully.\n";
    write_all_to_file();
  }
  else
    std::cout << "Thesis with ID " << id << " not found.\n";
}
void DatabaseManager::remove_journal_by_id(int id)
{
  display_journal_ids();
  std::cout << "\nEnter the ID of the journal to remove: ";
  auto it = journal_map.find(id);
  if (it != journal_map.end())
  {
    journals.erase(std::remove(journals.begin(), journals.end(), *(it->second)), journals.end());
    journal_map.erase(it);
    literature_title_map.erase({id, 'J'}); // Update literatureTitleMap
    std::cout << "Journal removed successfully.\n";
    write_all_to_file();
  }
  else
    std::cout << "Journal with ID " << id << " not found.\n";
}

void DatabaseManager::write_all_to_file()
{
  std::ofstream file("./literature_catalogue.dat", std::ios_base::trunc); // Open in truncate mode to overwrite

  if (!file.is_open())
  {
    std::cerr << "Unable to open file for writing.\n";
    return;
  }

  // Write books
  file << "== BOOKS ==\n";
  for (const auto& book : books)
  {
    file << book.id << "|" << book.title << "|" << join(book.authors, ";") << "|" 
         << book.publisher << "|" << book.subject << "|" << book.price << "\n";
  }

  // Write theses
  file << "\n== THESIS ==\n";
  for (const auto& thesis : theses)
  {
    file << thesis.id << "|" << thesis.title << "|" << thesis.author << "|" 
         << thesis.supervisor << "|" << thesis.university << "\n";
  }

  // Write journals
  file << "\n== JOURNALS ==\n";
  for (const auto& journal : journals)
  {
    file << journal.id << "|" << journal.title << "|" << journal.impact_factor << "|" 
         << journal.volumes << "|" << join(journal.editors, ";") << "|" << journal.scope << "\n";
  }

  file.close();
}
bool DatabaseManager::edit_book_by_id(int id) 
{
  auto it = std::find_if(books.begin(), books.end(), [id](const Book& book) { return book.id == id; });
  if (it != books.end())
  {
    std::cout << "Editing book: " << it->title << std::endl;
    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover newline character
    std::cout << "Enter new title (Leave blank to keep. Current: " << it->title << "): ";
    std::getline(std::cin, input);
    if (!input.empty()) it->title = input;
    std::cout << std::endl; // Ensure a line break here

    std::cout << "Enter new publisher (current: " << it->publisher << "): ";
    std::getline(std::cin, input);
    if (!input.empty()) it->publisher = input;
    std::cout << std::endl; // Added line break
    std::cout << "Enter new subject (current: " << it->subject << "): ";
    getline(std::cin, input);
    std::cout << std::endl; // Added line break
    if (!input.empty()) it->subject = input;

    std::cout << "Enter new price (current: $" << it->price << "): ";
    float price;
    if (std::cin >> price && price >= 0) // Check for valid price input
    {
      it->price = price;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
    }
    else
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input for price. Please enter a positive number.\n";
    }
    std::cout << std::endl; // Added line break

    write_all_to_file();
    std::cout << "Book updated successfully.\n";
    return true; // indicate success
  }
  else
  {
    std::cout << "Book with ID " << id << " not found.\n";
    return false; // indicate failure
  }
}

bool DatabaseManager::edit_thesis_by_id(int id)
{
  auto it = std::find_if(theses.begin(), theses.end(), [id](const Thesis& thesis) { return thesis.id == id; });
  if (it != theses.end())
  {
    std::cout << "Editing thesis: " << it->title << std::endl;
    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover newline character
    std::cout << "Enter new title (Leave blank to keep. Current: " << it->title << "): ";
    getline(std::cin, input);
    std::cout << std::endl; // Added line break
    if (!input.empty()) it->title = input;

    std::cout << "Enter new author (current: " << it->author << "): ";
    getline(std::cin, input);
    std::cout << std::endl; // Added line break
    if (!input.empty()) it->author = input;

    std::cout << "Enter new supervisor (current: " << it->supervisor << "): ";
    getline(std::cin, input);
    std::cout << std::endl; // Added line break
    if (!input.empty()) it->supervisor = input;

    std::cout << "Enter new university (current: " << it->university << "): ";
    getline(std::cin, input);
    std::cout << std::endl; // Added line break
    if (!input.empty()) it->university = input;

    write_all_to_file();
    std::cout << "Thesis updated successfully.\n";
    return true; // indicate success
  }
  else
  {
    std::cout << "Thesis with ID " << id << " not found.\n";
    return false; // indicate failure
  }
}

bool DatabaseManager::edit_journal_by_id(int id)
{
  auto it = std::find_if(journals.begin(), journals.end(), [id](const Journal& journal) { return journal.id == id; });
  if (it != journals.end())
  {
    std::cout << "Editing journal: " << it->title << std::endl;
    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover newline character
    std::cout << "Enter new title (Leave blank to keep. Current: " << it->title << "): ";
    getline(std::cin, input);
    std::cout << std::endl; // Added line break
    if (!input.empty()) it->title = input;

    float impact_factor;
    std::cout << "Enter new impact factor (current: " << it->impact_factor << "): ";
    if (std::cin >> impact_factor && impact_factor > 0) // Validate positive impact factor
    {
      it->impact_factor = impact_factor;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
    }
    else
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input for impact factor. Please enter a positive number.\n";
    }
    std::cout << std::endl; // Added line break

    int volumes;
    std::cout << "Enter new volumes (current: " << it->volumes << "): ";
    if (std::cin >> volumes && volumes > 0) // Validate positive volumes
    {
      it->volumes = volumes;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
    }
    else
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input for volumes. Please enter a positive number.\n";
    }
    std::cout << std::endl; // Added line break

    std::cout << "Enter new editors (current: " << join(it->editors, ", ") << "): ";
    getline(std::cin, input);
    if (!input.empty()) it->editors = splitString(input, ',');

    std::cout << "Enter new scope (current: " << it->scope << "): ";
    getline(std::cin, input);
    std::cout << std::endl; // Added line break
    if (!input.empty()) it->scope = input;

    write_all_to_file();
    std::cout << "Journal updated successfully.\n";
    return true; // indicate success
  }
  else
  {
    std::cout << "Journal with ID " << id << " not found.\n";
    return false; // indicate failure
  }
}
int DatabaseManager::get_total_entries() const 
{
  return books.size() + theses.size() + journals.size();
}

int DatabaseManager::get_total_books() const 
{
  return books.size();
}

int DatabaseManager::get_total_theses() const 
{
  return theses.size();
}

int DatabaseManager::get_total_journals() const 
{
  return journals.size();
}

void DatabaseManager::display_book_ids() const 
{
  for (const auto& book : books)
    std::cout << book.id << " ";
}

void DatabaseManager::display_thesis_ids() const 
{
  for (const auto& thesis : theses)
    std::cout << thesis.id << " ";
}

void DatabaseManager::display_journal_ids() const 
{
  for (const auto& journal : journals)
    std::cout << journal.id << " ";
}
