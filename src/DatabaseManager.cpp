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
