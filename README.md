# ProjectExample
Пример организации проекта на С++, использующего библиотеку GogoleTest. Система сборки CMake.

## Зачем выделять функционал в библиотеки

1. __Повторное использование кода:__ Если у вас есть куски кода, которые вы используете в нескольких проектах или в разных частях одного проекта, вынесение их в библиотеку позволит вам переиспользовать этот код без необходимости копирования и вставки.
2. __Упрощение разработки:__ Разбиение вашего кода на маленькие независимые куски делает разработку более понятной и управляемой. Вы можете сосредотачиваться на одном аспекте функциональности в одной библиотеке, а затем использовать эту библиотеку в других местах вашего проекта.
3. __Тестирование:__ Каждую библиотеку можно тестировать отдельно. Это делает тестирование более простым и позволяет быстро выявить и устранить ошибки.
4. __Совместная работа:__ Если вы работаете в команде, вынесение функционала в библиотеки делает возможным параллельное выполнение задач разными членами команды. Каждый человек может работать над отдельной библиотекой без вмешательства в остальной код.
5. __Обновления и поддержка:__ Когда вы изменяете или улучшаете функциональность, находящуюся в библиотеке, вам не нужно вносить изменения во все места, где она используется. Это упрощает обновление кода и поддержку.

## Как понять, что функционал стоит вынести в библиотеку

1. __Логическая разделенность:__ Выносите функционал, который логически связан вместе. Например, все функции для работы с базой данных могут быть в одной библиотеке, а функции для работы с пользовательским интерфейсом - в другой, классы-контейнеры - в третьей.
2. __Повторное использование:__ Если код можно использовать в нескольких местах, это хороший признак для выноса его в библиотеку. (Если вам нужно включить какой-то .h файл в несколько cpp файлов, чтобы использовать функционал класса, а не написать реализацию методов - это хороший повод вынести класс в библиотеку)
3. __Сопровождаемость:__ Если вы видите, что ваш код становится сложным и трудным для сопровождения, это может быть признаком того, что стоит разделить его на более мелкие части.

## Структура проекта примера:

Основной проект состоит из 4-х подпроектов:

1. __Locker__ - библиотека, которая содержит один класс для работы с дверным замком.
2. __Utils__ - библиотека вспомогатальных функций, на данный момент содрежит шаблон функции `T getNum();`, но потенциально туда могут быть добавлены другие полезные фичи, используемые в различных проектах/заданиях.
3. __Dialogue__ - проект, который реализует простейшую программу, используя библиотеки _Locker_ и _Utils_.
4. __Tests__ - проект, который реализует программу тестирования библиотеки _Locker_ с помощью сторонней библиотеки _gtest_.

Далее будет рассмотрена структура каждого отдельного проекта, в составе основного.

### Locker

Иерархия файлов данного проекта имеет следующий вид:

    Locker/
    |-- CMakeLists.txt
    |-- include/
    |   |-- Locker/
    |   |   |-- Locker.h
    |-- source/
    |   |-- Locker.cpp

Все заголовочные файлы библиотеки удобно помещать в директории _include_. 

Внутри этой директории имеет смысл создать несколько папок с именами составных частей библиотеки или одну папку с именем библиотеки, чтобы можно было её использовать следующим образом:
`#include <Locker/Locker.h>` 
Из кода выше понятно, что Locker.h принадлежит библиотеке _Locker_. (В одной библиотеке может быть и несколько заголовочных файлов).

Все файлы, содержащие реализацию классов и функций содержатся в папке _source_. (Здесь - Locker.cpp). 

Описанная выше иерархия позволяет удобно ориентироваться в библиотеке и быстро находить нужные файлы и участки кода.

#### В основной папке библиотеки лежит файл, описывающий сборку данной библиотеки, рассмотрим его подробнее:

    cmake_minimum_required(VERSION 3.16)
    project(Locker)
    
    set(CMAKE_CXX_STANDARD 20)

    add_library(Locker STATIC source/Locker.cpp)

    target_include_directories(Locker PUBLIC include)

1. __cmake_minimum_required__ определяет минимальную версию _CMake_, которая требуется для сборки данного проекта
2.  __project__ позволяет объявить имя проекта. (Здесь - _Locker_)
3. __set(CMAKE_CXX_STANDARD 20)__ - задает используемый стандарт языка С++
4. __add_library(Locker STATIC source/Locker.cpp)__ - команда создаёт статическую библиотеку с именем Locker из перечисленных файлов исходного кода _(source/Locker.cpp)_.
5. __target_include_directories(Locker PUBLIC include)__ - команда задаёт папки, в которых ищутся заголовочные файлы, указанные в директиве `#include`. То есть, путь к заголовочным файлам можно найти по пути, который указан относительно папок, перечисленных в данной команде.

Например, с ипользованием этой команды внутри файла _Locker.cpp_ можно найти файл _Locker.h_ по пути _Locker/Locker.h_ (т.к. он относительно папки _include_). 

Если бы данная команда не использовалась, пришлось бы писать так: `#include "../include/Locker/Locker.h` (То есть пришлось бы прописывать путь к файлу относительно расположения _Locker.cpp_)

У _include_directories_ есть области видимости, упрощенно можно описать их так: 

1. Свойства библиотеки, указанные как __PRIVATE__, видны только внутри цели, к которой библиотека подключается. Другие цели, которые зависят от текущей цели, не унаследуют эти свойства. Пример использования __PRIVATE__ - когда библиотека используется для внутренних нужд данной цели и ее реализация не должна быть видна другим целям.

2. Свойства библиотеки, указанные как __PUBLIC__, видны как внутри цели, так и для всех целей, которые зависят от текущей цели. Это позволяет передавать свойства библиотеки целям, которые используют текущую цель. Пример использования __PUBLIC__ - когда библиотека предоставляет интерфейс, который должен быть видим для всех, кто использует эту цель.

### Utils
Иерархия файлов данного проекта имеет следующий вид:

    Utils/
    |-- CMakeLists.txt
    |-- include/
    |   |-- Utils/
    |   |   |-- getNum.h

Как видно из иерархии, данная библиотека не содержит никаких .cpp файлов, её можно назвать заголовочной или интерфейсной библиотекой. Такая библиотека не компилируется, её текст явно подставляется в другие файлы с помощью `#include`. 

Необходимость выносить даннный функционал в отдельную библиотеку в том, что он будет повторно использоваться в других проектах и не следует явно копировать файлы функции getNum в каждый проект отдельно. 
Подключение заголовочных библиотек к проекту выглядит так же, как и подключение статических библиотек.

Рассмотрим CMake файл данной библиотеки:

    cmake_minimum_required(VERSION 3.16)
    project(LibUtils)

    set(CMAKE_CXX_STANDARD 20)

    add_library(LibUtils INTERFACE)

    target_include_directories(LibUtils INTERFACE include)

Все команды отсюда нам знакомы, но некоторые из них используются по-другому, так как библиотека заголовочная:

1. __add_library(LibUtils INTERFACE)__ - добавляет данную библиотеку - ИНТЕРФЕЙС, делает видимой её для проектов, которые включили в себя проект этой библиотеки. Никаких файлов исходного кода здесь указывать не нужно, потому что их нет. Никакой компиляции не происходит, библиотека просто становится видимой для тех, кому она нужна.

2. __target_include_directories(LibUtils INTERFACE include)__ - работает аналогично тому, как в библиотеке _Locker_, но следует пояснить, что свойства библиотеки, указанные как __INTERFACE__, видны только для целей, которые зависят от текущей цели, но не видны внутри самой текущей цели. То есть это свойства, которые не используются внутри текущей цели, но предоставляются для других целей, которые используют текущую цель. У интерфейсных библиотек можно объявлять только интерфейсные свойства.

### Dialogue 

Проект, которые реализовывает прикладную программу, используя наши библиотеки, его структура:

     Dialogue/
     |-- CMakeLists.txt
     |-- source/
     |   |-- main.cpp
    
В данном случае он содержит только папку для файлов исходного кода (_source_), хотя в общем случае, может объявлять вспомогательные функции и классы в заголовочных файлах в папке _include_. (её тогда нужно будет добавить через __target_include_directories__).

Рассмотрим файл сборки этого проекта:

    cmake_minimum_required(VERSION 3.16)
    project(Dialogue)

    set(CMAKE_CXX_STANDARD 20)

    add_executable (Dialogue   source/main.cpp)

    target_link_libraries(Dialogue Locker
                                   LibUtils )

1. __add_executable (Dialogue   source/main.cpp)__ - создает исполняемый файл (Dialogue.exe для Windows и Dialogue для unix-систем) из файлов исходного кода (в данном случае source/main.cpp).

2. __target_link_libraries(Dialogue Locker LibUtils )__ - добавляет к проекту библиотеки, имена которых указаны после названия проекта, в данном случае это библиотеки, которые мы создавали выше. 

Имея такой CMake файл, мы можем в данном проекте использовать функционал нужных нам библиотек и подключать их заголовочные файлы, например:

    #include<Locker/Locker.h>
    #include<Utils/getNum.h>

(Обратите внимание, файлы библиотек в директиве инклуд следует подключать используя треугольные скобки, чтобы было понятно, что используется библиотека). 

### Tests 

Проект, который реализует программу тестирования библиотеки Locker с помощью сторонней библиотеки Google Test. 

    Tests/
    |-- CMakeLists.txt
    |-- source/
    |   |-- main.cpp
    |   |-- TestCase1.cpp 

В файле main.cpp содержится функция, запускающая программу тестирования.
В файле TestCase1.cpp содержится объявление всех необходимых тестов. 
Подробнее про использоване библиотеки google test можно прочитать по [ссылке](https://habr.com/ru/articles/119090/) .

Рассмотрим файл сборки данного проекта, чтобы понять как очень просто, быстро, удобно и на любой операционной системе подключить библиотеку Google Test.

    cmake_minimum_required(VERSION 3.16)   
    project(Tests)

    set(CMAKE_CXX_STANDARD 20)

    // В зависимости от операционной системы объявляем переменную, в которой хранится текст ссылки на исходный код библиотеки на гитхабе.
    
    if(UNIX)
         set(gtest_source_url https://github.com/google/googletest/archive/release-1.11.0.tar.gz)
    elseif(WIN32)
        set(gtest_source_url https://github.com/google/googletest/archive/release-1.11.0.zip)
    else()
        message(FATAL_ERROR "Операционная система не поддерживается")
    endif()

    // Следующие несколько команд - приятная фишка CMake. Не вдаваясь в подробности, можно сказать,
    // использование FetchContent позволяет загрузить код библиотеки с удалённого репозитория и сделать частью проекта,
    // чтобы впоследствии компилировать и использовать эту библиотеку. Это значительно проще, чем скачивать и устанавливать её вручную.

    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL ${gtest_source_url}    // используем значение переменной, которую мы объявили в зависимости от ОС
    )
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_executable (Tests   source/main.cpp
                            source/TestCase1.cpp)

    // Добавляем библиотеки, первые две нужны для работы с google test, так же добавляем к проекту библиотеку Locker, которую будем тестировать
    target_link_libraries(Tests gtest
                                gtest_main
                                Locker)

### Основной проект. 

Рассмотрим CMake файл основного проекта. Его суть просто в том, чтобы включить в общий проект те 4 проекта, которые мы рассмотрели выше. Данный CMake файл является главным в проекте и интерпретация CMake программы начинается с него.

    cmake_minimum_required(VERSION 3.16)
    project(LabExample)

    add_subdirectory(Locker)
    add_subdirectory(Utils)
    add_subdirectory(Dialogue)
    add_subdirectory(Tests)

Функция __add_subdirectory__ - это команда в CMake, которая используется для включения другого CMake-проекта (расположенного в отдельной директории) в текущий проект. Это полезно, когда у вас есть главный проект, который включает в себя несколько подпроектов, и вы хотите собирать их всех вместе.

Основная задача __add_subdirectory__ - это добавление подпроекта в процесс сборки и создание целей для этого подпроекта, которые могут быть затем использованы в главном проекте. Это позволяет собирать и управлять зависимостями между разными частями проекта.

## Сборка

Проект может быть собран любой IDE, которая поддерживает работу с системой сборки CMake. (СMake должен быть установлен на вашем компьютере). 
Внутри IDE можно выбрать, какую цель компилировать: Библиотеку Locker, исполняемый файл с прикладной программой или исполняемый файл с тестами. 

С помощью командной строки linux можно скомпилировать проект следующим образом:

Скачать проект и перейти в его корневую папку. После этого выполнить следующий скрипт:

    mkdir build
    cd build
    cmake .. // Эта команда сгенерирует make-файлы для каждой цели в нашем проекте внутри папки build. Сам проект при этом лежит на одну папку выше
    make Dialogue  // Скомпилирует программу Dialogue
    make Tests     // Скомпилирует программу Tests
    make Locker    // Скомпилирует библиотеку Locker

(Очевидно, что необходимо, чтобы были установлены CMake и компилятор С++)
#### P.S. Если ваш компилятор не поддерживает С++20, измените версию С++ в CMake файлах проекта на С++17 или С++14.

## Заключение

Приведенная выше структура проекта и способ организации CMake файлов являются лишь примерным и упрощенным представлением того, как следует делать "по-хорошему". Это не четкая инструкция от которой нельзя отступать, структуру проекта можно менять, главное чтобы она была удобной и адекватной, а не набором перемешанных .h и .cpp файлов совершенно разных несвязанных классов, валяющихся в одной папке. 

Имеет смысл немного поковыряться в данном проекте, понять его суть, попробовать скомпилировать самостоятельно. Такая иерархия будет вполне достаточной и удобной для сдачи большинства (или даже всех) лабораторных данного курса, да и для организации собственных проектов.
