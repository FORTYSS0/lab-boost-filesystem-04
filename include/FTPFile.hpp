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

};

class FTPFile {
 public:
  explicit FTPFile(const path&);
  //void
  friend std::ostream& operator << (std::ostream&, const FTPFile& scanner);
 protected:
  std::vector<Account> all_ac;
  std::vector<Account> unic_ac;
  std::vector<int> count_ac;
};

#endif // INCLUDE_FTPFILE_HPP_
