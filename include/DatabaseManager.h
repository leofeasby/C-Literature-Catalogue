// Description: Manages the database of literature including books, theses, and journals.
// Author: Leo Feasby
// Date: 13/04/2024

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include "../include/Thesis.h"
#include "../include/Book.h"
#include "../include/Journal.h"

struct LiteratureKey 
{
  int id;
  char type; // 'B' for Book, 'T' for Thesis, 'J' for Journal

  bool operator<(const LiteratureKey& other) const 
  {
    if (id == other.id) return type < other.type;
    return id < other.id;
  }
};

class DatabaseManager 
{
private:
  std::vector<Book> books; // Use a vector to store books in memory
  std::vector<Thesis> theses; // Use a vector to store theses
  std::vector<Journal> journals; // Use a vector to store journals
  std::unordered_map<int, Book*> book_map; // Map for quick ID-based access to books
  std::unordered_map<int, Thesis*> thesis_map; // Map for quick ID-based access to theses
  std::unordered_map<int, Journal*> journal_map; // Map for quick ID-based access to journals
  std::map<LiteratureKey, std::string> literature_title_map; // Map for searching titles by ID and type
  int next_book_id;
  int next_thesis_id;
  int next_journal_id;

public:
  DatabaseManager(); // Updated constructor without dbPath
  ~DatabaseManager();
  // Method declarations...
  void add_book(const Book& book); // Added method declaration
  void search_literature_by_title(const std::string& title); // Added method declaration
  void list_all_books(); // Add this line
  void add_thesis(const Thesis& thesis); // Add this line
  void list_all_theses(); // Add this line to declare the method
  void add_journal(const Journal& journal); // Add this line to declare the method
  void list_all_journals(); // Add this line to declare the method
  void search_thesis_by_title(const std::string& title); // Add this line
  void search_journal_by_title(const std::string& title); // Add this line
  void load_data_from_file(const std::string& file_path); // Add this line
  void append_journal_to_file(const Journal& journal); // Add this line to declare the method
  void append_book_to_file(const Book& book); // Add this line to declare the method
  void append_thesis_to_file(const Thesis& thesis); // Add this line to declare the method
  void search_by_author(const std::string& author); // Add this line
  void search_by_type(const std::string& type); // Add this line
  void remove_book_by_id(int id); // Add this line to declare the method
  void remove_thesis_by_id(int id); // Add this line to declare the method
  void remove_journal_by_id(int id); // Add this line to declare the method
  void write_all_to_file(); // Add this line to declare the method
  bool edit_book_by_id(int id); // Add this line
  bool edit_thesis_by_id(int id); // Add this line
  bool edit_journal_by_id(int id); // Change return type to bool
  int get_total_entries() const; // Add this line
  int get_total_books() const; // Add this line
  int get_total_theses() const; // Add this line
  int get_total_journals() const; // Add this line
  void display_book_ids() const; // Add this line to declare the method
  void display_thesis_ids() const; // Add this line to declare the method
  void display_journal_ids() const; // Add this line to declare the method
  int display_average_book_price() const; // Add this line
  void display_cheapest_book() const; // Add this line
  void display_most_expensive_book() const; // Add this line
  const std::vector<Book>& get_books() const { return books; } // Add this line
  const std::vector<Thesis>& get_theses() const { return theses; } // Add this line
  const std::vector<Journal>& get_journals() const { return journals; } // Add this line
  std::string get_title_by_id(int id, char type); // Add this line to declare the method
};

#endif

