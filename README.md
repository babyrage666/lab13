[![Build Status](https://travis-ci.org/babyrage666/lab10.svg?branch=master)](https://travis-ci.org/babyrage666/lab10)
the demo application redirects data from stdin to a file **log.txt** using a package **print**.
## Laboratory work X

Данная лабораторная работа посвещена изучению систем управления пакетами на примере **Hunter**

```ShellSession
$ open https://github.com/ruslo/hunter
```

## Tasks

- [X] 1. Создать публичный репозиторий с названием **lab10** на сервисе **GitHub**
- [X] 2. Сгенирировать токен для доступа к сервису **GitHub** с правами **repo**
- [X] 3. Выполнить инструкцию учебного материала
- [X] 4. Ознакомиться со ссылками учебного материала
- [X] 5. Составить отчет и отправить ссылку личным сообщением в **Slack**

## Tutorial
Определяем глобальные переменные.
```ShellSession
$ export GITHUB_USERNAME=babyrage666
$ export GITHUB_TOKEN=9d6a8f37edae157754bbdb03f5db21f456504bff
```
Подготовка к выполнению **Лабораторной работы №10**.
```ShellSession
$ cd ${GITHUB_USERNAME}/workspace
$ pushd .
$ source scripts/activate
$ # Скачиваем и устанавливаем дополнительные пакеты.
$ go get github.com/github/hub
```
Настраиваем конфигурационный файл для утилиты **hub**.
```ShellSession
$ mkdir ~/.config
$ cat > ~/.config/hub <<EOF
github.com:
- user: ${GITHUB_USERNAME}
  oauth_token: ${GITHUB_TOKEN}
  protocol: https
EOF
$ git config --global hub.protocol https
```
Скачиваем пакет **lab09** и копируем его **SHA1-ключ**.
```ShellSession
$ wget https://github.com/${GITHUB_USERNAME}/lab09/archive/v0.1.0.0.tar.gz
$ export PRINT_SHA1=`openssl sha1 v0.1.0.0.tar.gz | cut -d'=' -f2 | cut -c2-41`
$ echo $PRINT_SHA1
$ rm -rf v0.1.0.0.tar.gz
```
Делаем fork репозитория **hunter**.
```ShellSession
$ git clone https://github.com/ruslo/hunter projects/hunter
$ cd projects/hunter && git checkout v0.19.137
$ git remote show
$ hub fork
$ git remote show
$ git remote show ${GITHUB_USERNAME}
```
Настраиваем конфигурационный файл утилиты **hunter** для пакета **print**.
```ShellSession
$ mkdir cmake/projects/print
$ cat > cmake/projects/print/hunter.cmake <<EOF
include(hunter_add_version)
include(hunter_cacheable)
include(hunter_cmake_args)
include(hunter_download)
include(hunter_pick_scheme)

hunter_add_version(
    PACKAGE_NAME
    print
    VERSION
    "0.1.0.0"
    URL
    "https://github.com/${GITHUB_USERNAME}/lab09/archive/v0.1.0.0.tar.gz"
    SHA1
    ${PRINT_SHA1}
)

hunter_pick_scheme(DEFAULT url_sha1_cmake)

hunter_cmake_args(
    print
    CMAKE_ARGS
    BUILD_EXAMPLES=NO
    BUILD_TESTS=NO
)
hunter_cacheable(print)
hunter_download(PACKAGE_NAME print)
EOF
```
Редактируем конфигурационный файл **cmake**.
```ShellSession
$ cat >> cmake/configs/default.cmake <<EOF
hunter_config(print VERSION 0.1.0.0)
EOF

```
Отправляем данные в репозиторий на **GitHub**.
```ShellSession
$ git add .
$ git commit -m"added print package"
$ git push ${GIHUB_USERNAME} master
$ git tag v0.19.137.1
$ git push ${GIHUB_USERNAME} master --tags
$ cd ..
```
Копируем абсолютный адрес утилиты **hunter**.
```ShellSession
$ export HUNTER_ROOT=`pwd`/hunter
$ mkdir lab10 && cd lab10
$ git init
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab10
```
Создаем файл **demo.cpp** и добавляем в него код программы.
```ShellSession
$ mkdir sources
$ cat > sources/demo.cpp <<EOF
#include <print.hpp>

int main(int argc, char** argv) {
	std::string text;
	while(std::cin >> text) {
		std::ofstream out("log.txt", std::ios_base::app);
		print(text, out);
		out << std::endl;
	}
}
EOF
```
Настраиваем шлюз для утилиты **hunter**.
```ShellSession
$ wget https://github.com/hunter-packages/gate/archive/v0.8.1.tar.gz 
$ tar -xzvf v0.8.1.tar.gz gate-0.8.1/cmake/HunterGate.cmake
$ mkdir cmake
$ mv gate-0.8.1/cmake/HunterGate.cmake cmake
$ rm -rf gate*/
$ rm *.tar.gz
```
Вносим изменения в **CMakeLists.txt**.
```ShellSession
$ cat > CMakeLists.txt <<EOF
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
EOF
```
Копируем **SHA1-ключ** на модифицированный **hunter** с добавленным print-ом.
```
$ wget https://github.com/${GITHUB_USERNAME}/hunter/archive/v0.19.137.1.tar.gz
$ export HUNTER_SHA1=`openssl sha1 v0.19.137.1.tar.gz | cut -d'=' -f2 | cut -c2-41`
$ echo $HUNTER_SHA1
$ rm -rf v0.19.137.1.tar.gz
```
Добавляем данные для верификации с **hunter**.
```ShellSession
$ cat >> CMakeLists.txt <<EOF

include(cmake/HunterGate.cmake)

HunterGate(
    URL "https://github.com/${GITHUB_USERNAME}/hunter/archive/v0.19.137.1.tar.gz"
    SHA1 "${HUNTER_SHA1}"
)
EOF
```
Настраиваем **CMakeLists.txt** для работы с **hunter**.
```ShellSession
$ cat >> CMakeLists.txt <<EOF

project(demo)

hunter_add_package(print)
find_package(print)

add_executable(demo \${CMAKE_CURRENT_SOURCE_DIR}/sources/demo.cpp)
target_link_libraries(demo print)

install(TARGETS demo RUNTIME DESTINATION bin)
EOF
```
Создаем **.gitignore** файл.
```ShellSession
$ cat > .gitignore <<EOF
*build*/
*install*/
*.swp
EOF
```
Создаем **README.md** файл.
```ShellSession
$ cat > README.md <<EOF
[![Build Status](https://travis-ci.org/${GITHUB_USERNAME}/lab10.svg?branch=master)](https://travis-ci.org/${GITHUB_USERNAME}/lab10)
the demo application redirects data from stdin to a file **log.txt** using a package **print**.
EOF
```
Создаем **.travis.yml** файл.
```ShellSession
$ cat > .travis.yml <<EOF
language: cpp

script:   
- cmake -H. -B_build
- cmake --build _build
EOF
```
Проверяем файл **.travis.yml** на ошибки.
```ShellSession
$ travis lint
```
Отправляем изменения на **GitHub**.
```ShellSession
$ git add .
$ git commit -m"first commit"
$ git push origin master
```
Подключаем **Travis CI**.
```ShellSession
$ travis login --auto
$ travis enable
```
Собираем проект утилитой **hunter** и проверяем работу программы.
```ShellSession
$ cmake -H. -B_build -DCMAKE_INSTALL_PREFIX=_install
$ cmake --build _build --target install
$ mkdir artifacts && cd artifacts
$ echo "text1 text2 text3" | ../_install/bin/demo
$ cat log.txt
```

## Report

```ShellSession
$ popd
$ export LAB_NUMBER=10
$ git clone https://github.com/tp-labs/lab${LAB_NUMBER} tasks/lab${LAB_NUMBER}
$ mkdir reports/lab${LAB_NUMBER}
$ cp tasks/lab${LAB_NUMBER}/README.md reports/lab${LAB_NUMBER}/REPORT.md
$ cd reports/lab${LAB_NUMBER}
$ edit REPORT.md
$ gistup -m "lab${LAB_NUMBER}"
```

## Links

- [hub](https://hub.github.com/)
- [polly](https://github.com/ruslo/polly)
- [conan](https://conan.io)

```
Copyright (c) 2017 Братья Вершинины
```
