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
  int next_book_id;
  int next_thesis_id;
  int next_journal_id;
public:
  DatabaseManager();
  ~DatabaseManager();
  void add_book(const Book& book);  void add_thesis(const Thesis& thesis);
  void list_all_theses();
  void add_journal(const Journal& journal);
  void list_all_journals();
  void search_thesis_by_title(const std::string& title);
  void search_journal_by_title(const std::string& title);

