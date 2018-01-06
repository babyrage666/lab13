#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

struct Email 
{
  string nickname;
  string server;
};

struct Person 
{
  string first_name;
  string last_name;
  Email email;
  size_t age;
  string phone;
};

int main(int argc, char* argv[]) 
{
  string path = argv[1];
  Person pers
  json xxx;
  ifstream f;
  f.open(pers);
  f >> xxx;
  f.close();

  pers.first_name = xxx.at("first_name").get<string>();
  pers.last_name = xxx.at("last_name").get<string>();
  pers.email.nickname = xxx.at("email_nickname").get<string>();
  pers.age  = xxx.at("age").get<size_t>();
  pers.phone  = xxx.at("phone").get<string>();

  cout << "[Person]" << endl;
  cout << "First name: " << pers.first_name << endl;
  cout << "Last name: " << pers.last_name << endl;
  cout << "Email_nickname: " << pers.email.nickname << endl;
  cout << "Age: " << pers.age << endl;
  cout << "Phone: " << pers.phone << endl;

  return 0;
}
