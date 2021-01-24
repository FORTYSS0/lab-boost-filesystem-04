// Copyright 2021 by FORTYSS

#include <FTPFile.hpp>

int main (int argc, char* argv[]){
  try{
    path path_to_ftp;
    if(argc == 1){
      std::cout<< "Scanning parent directory, because don't enter arguments"
          <<std::endl;
      path_to_ftp = ".";
    } else {
      path_to_ftp = argv[1];
    }
    FTPFile scan(path_to_ftp);
    std::cout<<scan;
    return 0;
  } catch (filesystem_error& e) {
    std::cout << e.what() << std::endl;
    return  1;
  }
}