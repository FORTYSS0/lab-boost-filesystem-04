// Copyright 2021 by FORTYSS

#include "FTPFile.hpp"

FTPFile::FTPFile(const path& pat) {
  for(auto && item : directory_iterator(pat))
  {
    Check(item);
  }
  Unique(AcName());
}
std::vector<string>FTPFile::AcName() {
  std::vector<string> acname;
  for(auto & ac : all_ac){
    if(!ac.get_ac_name().empty()){
      acname.push_back(ac.get_ac_name());
    }
  }
  std::sort(acname.begin(), acname.end());
  return acname;
}
void FTPFile::Check(const path& pat) {
  try {
    if (exists(pat)) {
      if (is_directory(pat)) {
        for (auto&& item : directory_iterator(pat)) {
          Check(item);
        }
      } else if(is_regular_file(pat)){
        all_ac.emplace_back(pat);
      } else if (is_symlink(pat)) {
        Check(read_symlink(pat));
      } else {
        throw std::runtime_error("It's not a regular file or directory");
      }
    } else {
      throw std::runtime_error("Doesn't exists");
    }
  } catch (const filesystem_error& e) {
    std::cout << e.what() << "\n";
  }
}
void FTPFile::Unique(std::vector<string> ac_name) {
  unic_ac.emplace_back(ac_name[0]);
  count_ac.push_back(1);
  for(size_t i = 1; i<ac_name.size(); ++i) {
    if (ac_name[i] != ac_name[i - 1]) {
      unic_ac.emplace_back(ac_name[i]);
      count_ac.push_back(1);
    } else {
      ++count_ac.back();
    }
  }
    int t_data =0;
    string t_br;
    for(auto & unic_acc : unic_ac) {
      for(auto & ac : all_ac) {
        if(ac.get_ac_name() == unic_acc.get_ac_name()) {
          if(ac.get_data() > t_data) {
            t_br = ac.get_br_name();
            t_data = ac.get_data();
          }
        }
      }
      unic_acc.inp_data(t_data);
      t_data = 0;
      unic_acc.inp_br_name(t_br);
      t_br = "";
    }
  }
void FTPFile::OutAll(std::ostream& str) const {
    str << "Finanse file info: \n";
    for (Account ac : all_ac) {
      if (ac.get_type()) {
        ac.print(str);
      }
    }
  }
void FTPFile::OutUnique(std::ostream& str) const {
  str << "Broker info: \n";
  for (size_t i = 0; i<unic_ac.size();++i){
   str << "Broker: " << unic_ac[i].get_br_name() << " "
        << "Account: " << unic_ac[i].get_ac_name() << " "
   << "Files: " << count_ac[i] << " "
   << "Last data: " << unic_ac[i].get_data() << "\n";
  }
}
  std::ostream& operator << (std::ostream& str, const FTPFile& scanner) {
    scanner.OutAll(str);
    scanner.OutUnique(str);
    return str;
  }

  Account::Account(const path& pat) {
    if(cor_file(pat)){
      type = true;
      string stem_str = pat.stem().string();
      setter(cutter(stem_str), cutter(stem_str.substr(0,
                                                      stem_str.size()-
                                                      cutter(stem_str).size())),
pat.parent_path().filename().string());
    } else {

    }
  }
  bool Account::cor_file(const path& pat) {
    string input = pat.stem().string();
    size_t coun = 0;
    bool flag_type = false;
    for(const auto& charr : input){
      if (charr == '_'){
        ++coun;
      }
      switch (coun) {
        case 0:
          if(charr<65||charr>90||charr<97||charr>122) {
            flag_type = false;
          } else {
            flag_type = true;
          }
          break;
        case 1: case 2:
          if(charr< 49|| charr>57) {
            flag_type = false;
          } else {
            flag_type = true;
          }
          break;
        default:
          flag_type = false;
      }
    }
    if (coun !=2) {
      flag_type = false;
    }
    if (pat.extension() == ".txt" && pat.stem().extension() != ".old"&&
                                                                 flag_type ) {
      return true;
    } else {
      return false;
    }
  }
  string Account::cutter(const string& input) {
    string out;
    for(int i = input.length(); i>0; --i) {
      if(input[i] == '_') {
        break;
      }
      out += input[i];
    }
    int length = out.length();
    int n = length-1;
    for(int i=0; i<(length/2); ++i){
      std::swap(out[i], out[n]);
      --n;
    }
    return  out;
  }
  void Account::setter(const string& input_data, const string& input_ac_name, const string& input_br_name) {
    data = atoi(input_data.c_str());
    ac_name = input_ac_name;
    br_name = input_br_name;
  }
void Account::print(std::ostream& str) {
  str << get_br_name() << "\t" << "balance_" << get_ac_name() << "_" << get_data() << ".txt\n";
}
int Account::get_data() const { return  data;}
string Account::get_ac_name() const { return  ac_name;}
string Account::get_br_name() const {return  br_name;}
bool Account::get_type() {return  type;}
void Account::inp_data(int dat) {data = dat;}
void Account::inp_br_name(string brok_name) { br_name = std::move(brok_name);}
Account::Account(string acc_name, int dat, string brok_name, bool typ) {
  ac_name = acc_name;
  data = dat;
  br_name = brok_name;
  type = typ;
}
