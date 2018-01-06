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

Person getInfo() 
{
	class Person file;
  file.first_name = "Georgy";
	file.last_name = "Kapotyuk";
	file.email.nickname = "kapotyuk0901@yandex.ru";
	file.age = 20;
	file.phone = "+79661286844";
	return file;
}


int main(int argc, char* argv[]) 
{
  string path = argv[1];
  Person pers;
  ofstream fout(path);

  pers = getInfo();
  json xxx;
  xxx["first_name"] = pers.first_name;
  xxx["last_name"] = pers.last_name;
  xxx["email_nickname"] = pers.email.nickname;
  xxx["age"] = pers.age;
  xxx["phone"] = pers.phone;
  fout << xxx;
  fout.close();
  return 0;
}