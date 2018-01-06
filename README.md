## Laboratory work XIII

Данная лабораторная работа посвещена изучению работы программы СURL.

## Tasks

## Tutorial
Определяем глобальные переменные.
```ShellSession
$ export GITHUB_USERNAME=babyrage666
$ alias edit=subl
```
Подготовка к выполнению **Лабораторной работы №12**.
```ShellSession
$ git clone https://github.com/${GITHUB_USERNAME}/lab10 projects/lab12
$ cd projects/lab12
$ git remote remove origin
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab12
$ rm -R sources # удаляем лишние каталоги
```
Редактируем **CMakeLists.txt**
```ShellSession
$ edit CMakeList.txt
# Подключаем пакеты CURl и OpenSSl.
# Добавляем таргет main.cpp
```
Создаем **main.cpp**
```ShellSession
$ edit main.cpp
```
Редактируем **.travis.yml**
```ShellSession
$ cat >> .travis.yml <<EOF
- cd _build
- ./main
EOF
```
Собираем проект в **CMake**
```ShellSession
$ cmake -H. -B_build
$ cmake --build _build
```

Отправляем данные на удаленный репозиторий в **GitHub**
```ShellSession
$ git add .
$ git commit -m"done"
$ git push origin master
```

Подключаем **TravisCI**
```ShellSession
$ travis login --auto
$ travis enable
```

## Links
- [Libcurl](https://curl.haxx.se/libcurl/c/)
- [HTTP](https://ru.wikipedia.org/wiki/HTTP)
- [Curlcpp](https://github.com/JosephP91/curlcpp)
- [Boost_Asio](http://www.boost.org/doc/libs/1_65_0/doc/html/boost_asio.html)
