// Copyright 2020 Nikita Klimov nik179804@gmail.com

#ifndef INCLUDE_ANALYSIS_H_
#define INCLUDE_ANALYSIS_H_

#include <string>
#include <boost/filesystem.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <set>

namespace file = boost::filesystem;

class Analysis {

 private:
  file::path Path;
  std::set<std::string> AccountsNames;
  std::vector<file::path> MasPath;

 public:
  explicit Analysis(const std::string& path);
  const file::path& getPathToAccount(const size_t& n) const;
  std::stringstream printAccount(const file::path& elem, const size_t& n) const;
  friend std::ostream& operator <<(std::ostream& out, const Analysis& A);
  ~Analysis();

  void printData(const std::string& path);
};

#endif  // INCLUDE_ANALYSIS_H_
