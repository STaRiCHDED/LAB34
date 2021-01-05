// Copyright 2020 Nikita Klimov nik179804@gmail.com
#include "Analysis.hpp"

int main(int argc, char* argv[]) {
  std::string path;
  if (argc > 1) {
    path = argv[1];
  } else {
    path = "";
  }
  Analysis A("/home/starich/STARICHDED/SEM3/LAB34-REW/misc//ftp");
  A.printData("/home/starich/STARICHDED/SEM3/LAB34-REW/misc//ftp");
  return 0;
}
