// Copyright 2021 by FORTYSS

#ifndef INCLUDE_FTPFILE_HPP_
#define INCLUDE_FTPFILE_HPP_

#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
#include <utility>
#include <vector>
#include <sstream>

using path = boost::filesystem::path;
using directory_iterator = boost::filesystem::directory_iterator;
using filesystem_error = boost::filesystem::filesystem_error;
using string = std::string;

struct Account {
 private:
  int data;
  string ac_name;
  string br_name;
  bool type;

 public:
  explicit Account(const path&);
  explicit Account(
      string acc_name, int dat = 0, string brok_name ="", bool typ = true);
  static string cutter(const string&);

  static inline bool cor_file(const path&);

  void setter(const string&, const string&, const string&);

  int get_data();

  string get_ac_name();

  string get_br_name();

  void inp_data(int);

  void inp_br_name(string);

  bool get_type();

  void print(std::ostream&);
};


class FTPFile {
 public:
  explicit FTPFile(const path&);
  void Check(const path& pat);
  void Unique(std::vector<string>);
  std::vector<string> AcName();
  friend std::ostream& operator << (std::ostream&, const FTPFile& scanner);
  void OutAll (std::ostream&);
  void OutUnique(std::ostream&);
 protected:
  std::vector<Account> all_ac;
  std::vector<Account> unic_ac;
  std::vector<int> count_ac;
};

#endif // INCLUDE_FTPFILE_HPP_
