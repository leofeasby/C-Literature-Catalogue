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
  DatabaseManager();
  ~DatabaseManager();
  void add_book(const Book& book);
  void search_literature_by_title(const std::string& title);
  void list_all_books();
  void add_thesis(const Thesis& thesis);
  void list_all_theses();
  void add_journal(const Journal& journal);
  void list_all_journals();
  void search_thesis_by_title(const std::string& title);
  void search_journal_by_title(const std::string& title);
  void load_data_from_file(const std::string& file_path);
  void append_journal_to_file(const Journal& journal);
  void append_book_to_file(const Book& book);
  void append_thesis_to_file(const Thesis& thesis);
  void search_by_author(const std::string& author);
  void search_by_type(const std::string& type);
  void remove_book_by_id(int id);
  void remove_thesis_by_id(int id);
  void remove_journal_by_id(int id);
  void write_all_to_file();
  bool edit_book_by_id(int id);
  bool edit_thesis_by_id(int id);
  bool edit_journal_by_id(int id);
  int get_total_entries() const;
  int get_total_books() const;
  int get_total_theses() const;
  int get_total_journals() const;
  void display_book_ids() const;
  void display_thesis_ids() const;
  void display_journal_ids() const;
  int display_average_book_price() const;
  void display_cheapest_book() const;
  void display_most_expensive_book() const;
  const std::vector<Book>& get_books() const;
  const std::vector<Thesis>& get_theses() const;
  const std::vector<Journal>& get_journals() const;
  std::string get_title_by_id(int id, char type);
