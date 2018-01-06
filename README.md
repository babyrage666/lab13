## Laboratory work XIII

## Tasks
Написать программы на **C++** для сериализации и десериализации структуры `Person`.

Структура `Person` определяется следующим образом:

```cpp
struct Email {
  std::string nickname;
  std::string server;
};

struct Person {
  std::string  first_name;
  std::string  last_name;
  Email        email;
  size_t       age;
  std::string  phone;
};
```

## Tutorial
Определяем глобальные переменные.
```ShellSession
$ export GITHUB_USERNAME=babyrage666
$ alias edit=subl
```
Подготовка к выполнению **Лабораторной работы №13**.
```ShellSession
$ git clone https://github.com/${GITHUB_USERNAME}/lab12 projects/lab13
$ cd projects/lab12
$ git remote remove origin
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab12
$ rm -R sources # удаляем лишние каталоги
```
Редактируем **CMakeLists.txt**
```ShellSession
$ edit CMakeList.txt
# Подключаем пакет nlohmann_json
# Добавляем таргеты pack/unpack.cpp
```
Создаем **pack/unpack.cpp**
```ShellSession
$ mkdir sources && cd sources
$ edit pack.cpp
$ edit unpack.cpp
```
Редактируем **.travis.yml**
```ShellSession
$ edit .travis.yml
```
Собираем проект в **CMake**
```ShellSession
$ cmake -H. -B_build
$ cmake --build _build
```

Отправляем данные на удаленный репозиторий в **GitHub**
```ShellSession
$ git add .
$ git commit -m"added everythg"
$ git push origin master
```

Подключаем **TravisCI**
```ShellSession
$ travis login --auto
$ travis enable
```

## Result
$jsonlint file.json
Вывод:
{
  "first_name": "Georgy",
  "last_name": "Kapotyuk",
  "email_nickname": "kapotyuk0901@yandex.ru",
  "age": 20,
  "phone": "+79661286844"
}
