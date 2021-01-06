// Copyright 2020 Nikita Klimov nik179804@gmail.com

#include "Analysis.hpp"

#include <iomanip>
#include <regex>

namespace file = boost::filesystem;

Analysis::Analysis(const std::string& path) {
  const std::regex re("^(balance)_\\d{8}_\\d{8}");
  if (!path.empty()) {
    if (file::exists(path)) {
      Path = path;
    }
  } else {
    Path = file::current_path();
  }
  for (const file::directory_entry& x : file::directory_iterator{Path}) {
    if (file::is_directory(x.path())) {
      for (const file::directory_entry& y :
           file::directory_iterator{x.path()}) {
        if ((y.path().stem().extension() == "") &&
            (y.path().extension() == ".txt") &&
            (std::regex_search(y.path().stem().string(), re))) {
          std::cout << std::left << std::setw(10)
                    << y.path().parent_path().filename().string() << " "
                    << y.path().filename().string() << '\n';

          MasPath.push_back(y.path());
          AccountsNames.insert(y.path().stem().string().substr(8, 8));
        }
      }
    }
  }
}

std::stringstream Analysis::printAccount(const file::path& elem,
                                         const size_t& n) const {
  std::stringstream ss;
  ss << "broker: " << std::left << std::setw(8)
     << elem.parent_path().filename().string()
     << " account: " << elem.stem().string().substr(8, 8)
     << " files: " << std::setw(3) << n
     << " lastdate: " << elem.stem().string().substr(17, 8);
  return ss;
}

std::ostream& operator<<(std::ostream& out, const Analysis& A) {
  for (const auto& el : A.AccountsNames) {
    std::vector<file::path> temp;
    for (const auto& i : A.MasPath) {
      if (el == i.stem().string().substr(8, 8)) {
        temp.push_back(i);
      }
    }
    file::path max = temp[0];
    size_t n = 0;
    for (const auto& j : temp) {
      if (max.stem().string().substr(17, 8) < j.stem().string().substr(17, 8)) {
        max = j;
      }
      n++;
    }
    out << A.printAccount(max, n).str() << std::endl;
  }
  return out;
}

Analysis::~Analysis() {}

const file::path& Analysis::getPathToAccount(const size_t& n) const {
  return MasPath[n];
}

void Analysis::printData(const std::string& path) {
  const std::regex re("^(balance)_\\d{8}_\\d{8}");
  if (!path.empty()) {
    if (file::exists(path)) {
      Path = path;
    }
    std::string parent = path.substr(46, 3);
    std::cout << parent << std::endl;
    for (const file::directory_entry& x : file::directory_iterator{Path}) {
      if (file::is_directory(x.path())) {
        int k = 0;
        for (const file::directory_entry& y :
             file::directory_iterator{x.path()}) {
          if ((y.path().extension() == ".txt") &&
              (std::regex_search(y.path().stem().string(), re))) {
            std::string dir = y.path().parent_path().filename().string();
            if (k == 0) {
              std::cout << " ├──" << dir << std::endl;
              k++;
            }
            std::cout << "     ├──" << y.path().filename().string()
                      << std::endl;
          }
        }
      }
    }
  }
}
