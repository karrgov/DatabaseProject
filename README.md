The project represents a program that supports operations with simple databases. The databases consist of a series of tables, with each table stored in its own file. The database itself is recorded in a main file (catalog), which contains a list of the tables in the database. Each table entry specifies the table's name and the file where the table is stored.
Each column in a database table has a specific type, and a single table can have columns of different types. The application supports the following data types:
- Integer number: A sequence of digits without any other symbols between them. The number may have a '+' or '-' sign at the beginning.
- Floating-point number: A sequence of digits followed by a dot symbol and another sequence of digits. The number may have a '+' or '-' sign at the beginning.
- String: A sequence of arbitrary characters enclosed in quotation marks. Similar to std::string in C++, if you want to include a quotation mark in a string, you must escape it as ", and if you want to include a backslash, you must escape it as \. For example:
"Hello world!"
"C:\temp\"
""This is a quotation""
In addition to specific values, a singular cell in a table can be "empty." Such cells should be specially marked and displayed as "NULL."
Once the application opens a certain database file (catalogue), it is able to perform the following operations, in addition to common operations like close, save, save as, help, and exit:

- open *filename* - Opens a file, provided by the user.

- close *filename* - Closes the opened file.

- save - Saves to the opened file.

- saveas *filename* - Saves the already opened file to a specific one, provided by the user.

- help - Displays all of the available commands.

- exit - Exits the program.

- import *tablename* *filename* - Imports a new table into the database by table name and file name.

- showtables - Displays a list of all loaded tables.

- describe *tablename* - Shows all the types of the columns of the provided table.

- print *tablename* - Prints the provided table.

- export *tablename* *filename* - Exports the provided table to a specific file.

- select *columnIndex* *value* *tablename* - Prints all rows which match the provided value.

- addcolumn *tablename* *columnname* *columntype* - Adds a new column to the provided table.

- update *tablename* *searchColumnIndex* *searchValue* *targetColumnIndex* *targetValue* - Updates the provided table.

- delete *tablename* *searchColumnIndex* *searchValue* - Deletes the rows matching the provided value.

- insert *tablename* *value1* *value2* ... *valueN* - Inserts the provided values.

- innerjoin *tablename1* *columnIndex1* *tablename2* *columnIndex2* - Performs the inner join operation on the provided tables.

- rename *tablename* *newTablename* - Changes the name of the provided table.

- count *tablename* *searchColumnIndex* *searchValue* - Counts the rows having this specific value in the provided table.

- aggregate *tablename* *searchColumnIndex* *searchValue* *targetColumnIndex* *mathOperation* - Performs a given operation (sum, product, maximum, or minimum) on the values in the target column index of all rows whose columns with number search column index contain the value search value. Returns an error if the columns are not numeric.

FOR THE PROJECT ARCHITECTURE (Bulgarian and English version): 

Цялата архитектура на програмата започва с CellInterface класът, който темплейтен interface бива наследен от всички типове клетки, които има и които може да има евентуално, и ги задължава да имат в себе си определени член методи. Видовете клетки в нашия случай са три - Int, Double и String. За тях има направен темплейтния клас Cell, който да улеснява бъдещето разширение на програмата, а както и моментната разработка. Всеки един обект от Cell има две полета в себе си - стойност от тип Т и булева стойност, която да служи за определянето на това дали една клетка е празна (в този случай false) или съдържа стойност (в този случай true).

Следващата стъпка от разработката е това да бъде направен интерфейс за отделните колони, тъй като една таблица трябва да позволява това да има в себе си колони от различен тип, т.е. таблицата ще бъде хетерогенен контейнер. Това е класът ColumnInterface, който бива наследен от всички типове колони, които има и които може да има евентуално, и ги задължава да имат в себе си определени член методи. Видовете колони в нашия случай са три - IntColumn, DoubleColumn и StringColumn, като всяка колона в себе си има име, което да бъде показвано при принтирането на таблицата, както и вектор от указатели към интерфейса на клетките, което решава проблема с object slicing и също така прави възможен runtime polymorphism.

Класовете на колоните няма да имат оператор =, както и конструктор за копиране, защото те ще бъдат ненужни.Ще има базовите нужни методи за удобната реализация на цялата функционалност на програмата - метод, който да връща типа на колоната, метод за достъпване на някоя клетка от вектора, тъй като той е private, метод, който да запазва индексите на клетките, на които се среща някаква определена стойност в колоната, метод, който да променя някаква стойност от колоната, при подаден индекс и нова стойност, метод за триене на клетка, отново по подаден индекс, както и метод за добавяне на нова клетка в колоната.

След като имаме всички тези методи, вече можем да определим, че една таблица, тоест клас Table ще има в себе си вектор от указатели към интерфейса на колоните, което решава проблема с object slicing и също така прави възможен runtime polymorphism, както и име на таблицата, име на файл, в който тя ще бъде записана и брой на редовете в таблицата. Тук отново няма да има оператор =, както и конструктор за копиране, защото те ще бъдат ненужни. Тъй като програмата поддържа три различни типа стойности, като те са малко специфични, т.е. могат да започват със символ, който не е число, а освен това могат и да бъдат някакъв низ, дали NULL за празна клетка или просто какъвто и да е израз, както и работа с команди, подавани от потребителя, които си имат различен брой съпътстващи аргументи, то трябва да имаме и клас, който да отговаря за преминаването от един тип към друг и за превръщането на тези специфични типове към C++ типове. Това е класът Converter, който има само статични методи, за да може те да бъдат използвани без съществуването на обекти от клас Converter. Те са метод, който да конвертира std::string стойност към int, метод, който да конвертира std::string стойност към double, метод, който да конвертира std::string низ, представляващ поредица от аргументи, към разделени аргументи тип std::string събрани за удобство във вектор. Освен това Converter има и булеви методи, за това дали клетка е string, защото по условие string трябва да бъде представян като поредица от символи в кавички, както и дали клетка е празна.

Тъй като имаме три типа колони, а те при разширение на програмата могат да станат повече, има шаблонът за дизайн Factory (клас ColumnFactory), който има в себе си статичен метод, приемащ колона с какво име и от какъв тип искаме и връщащ съответната колона, т.е. указател към интерфейса за колоните. Този шаблон улеснява разработката на програмата, както и нейната бъдеща поддръжка, и спомага за цялостната капсулация и ефективност.

Сега вече може да бъде направена и самата база от данни, най-просто казано няколко таблици събрани заедно. Клас Catalogue ще представлява базата от данни, като в себе си ще съдържа вектор от указатели към обект Table, правейки възможен runtime polymorphism и решавайки проблема с object slicing. Освен това в клас Catalogue ще има и името на файла, в който е записан този каталог от таблици. Тук отново няма да има оператор =, както и конструктор за копиране, защото те ще бъдат ненужни.

Стигаме до реализацията на командите, като за тях също ще бъде най-добре да имат някакъв общ интерфейс, който всички да наследяват, което ще помогне както и за бъдещо развитие на програмата, така и за яснотата за това какво се очаква да прави всяка една команда и какви методи трябва да има тя. Този интерфейс е CommandInterface и ще има само един pure virtual метод (приемащ std::string от параметрите, както и обект Catalogue), който ще трябва да пренапишат наследниците му, т.е. всяка една от командите. В такъв случай би било удобно да има клас, съдържащ всички съществуващи команди. Това ще бъде клас CommandController, който ще има в себе си вектор с указатели към интерфейса на командите, което решава проблема с object slicing и също така прави възможен runtime polymorphism. Тук отново няма да има оператор =, както и конструктор за копиране, защото те ще бъдат ненужни.

Вместо в самия main да правим обекти от всички нужни ни класове и той да бъде труден за четене, по-добрият вариант е някакъв клас, който да обвива всичко (wrapper). Този клас ще бъде Program и в себе си ще съдържа обект от тип Catalogue (базата данни), както и обект от тип CommandController (възможните команди). Тъй като този обект реално представлява цялата програма, а тя е само една, подходящо е да бъде използван шаблонът за дизайн Singleton. Какъвто е и стандарта например при правенето на една игра - нейните настройки са едни единствени и затова са Singleton. Използването на този шаблон води със себе си добавянето на още една член данна в класа Program, която да бъде указател към същия този Program. Освен това и конструкторът ще бъде private, за да не може да бъде извикван извън класа, и ще има един статичен метод, който да връща този единствен обект Program, когато и където ни потрябва. Трябва да имаме и метод, който да стартира цялата програма - това ще бъде execute().

Така в main ще трябва единствено да извикаме този единствен обект Program, и да изпълним метода execute() върху него, като така всичко за външния свят е скрито и разделено на удобни части, следвайки идеологията за разработка при обектно-ориентираното програмиране.

ENGLISH TRANSLATION: 
The entire architecture of the program starts with the CellInterface class, which is a templated interface inherited by all cell types, both existing and potential, and requires them to include certain member methods. The types of cells in our case are three - Int, Double, and String. For these, a templated class Cell has been created to facilitate future expansion of the program as well as its current development. Each Cell object has two fields - a value of type T and a boolean value to determine whether a cell is empty (in this case, false) or contains a value (in this case, true).

The next step in the development is to create an interface for individual columns since a table must allow for columns of different types, i.e., the table will be a heterogeneous container. This is the ColumnInterface class, which is inherited by all column types, both existing and potential, and requires them to include certain member methods. The types of columns in our case are three - IntColumn, DoubleColumn, and StringColumn, with each column containing a name to be displayed when printing the table, as well as a vector of pointers to the cell interface, which solves the problem of object slicing and also enables runtime polymorphism.

The column classes will not have an assignment operator (=) or a copy constructor, as they will be unnecessary. There will be the basic required methods for the convenient implementation of the program's overall functionality - a method to return the type of the column, a method to access a cell from the vector since it is private, a method to save the indices of cells where a certain value is found in the column, a method to change a value in the column given an index and a new value, a method to delete a cell, again by a given index, and a method to add a new cell to the column.

After having all these methods, we can define that a table, i.e., the Table class, will contain a vector of pointers to the column interface, solving the problem of object slicing and enabling runtime polymorphism, as well as the table's name, the name of the file in which it will be saved, and the number of rows in the table. Here again, there will be no assignment operator (=) or a copy constructor, as they will be unnecessary. Since the program supports three different types of values, which are somewhat specific, i.e., they can start with a symbol that is not a number, and can also be some string, either NULL for an empty cell or just any expression, as well as working with commands provided by the user, which have a different number of accompanying arguments, we need a class responsible for transitioning from one type to another and for converting these specific types to C++ types. This is the Converter class, which has only static methods so they can be used without creating objects of the Converter class. These include a method to convert a std::string value to int, a method to convert a std::string value to double, and a method to convert a std::string string representing a sequence of arguments to separated std::string arguments conveniently collected in a vector. Additionally, the Converter has boolean methods to check if a cell is a string, as by convention, a string should be represented as a sequence of characters in quotes, and if a cell is empty.

Since we have three types of columns, which can increase with the program's expansion, there is the Factory design pattern (class ColumnFactory), which contains a static method accepting the column name and type we want and returning the respective column, i.e., a pointer to the column interface. This pattern facilitates the program's development and future maintenance, aiding overall encapsulation and efficiency.

Now, the actual database can be created, simply put as several tables combined together. The Catalogue class will represent the database, containing a vector of pointers to Table objects, enabling runtime polymorphism and solving the problem of object slicing. Additionally, the Catalogue class will have the file name in which this catalogue of tables is saved. Here again, there will be no assignment operator (=) or a copy constructor, as they will be unnecessary.

We reach the implementation of commands, which will also benefit from having a common interface that all commands inherit, aiding both the future development of the program and clarity regarding what each command is expected to do and what methods it should have. This interface is CommandInterface and will have only one pure virtual method (accepting a std::string from the parameters as well as a Catalogue object), which the inheritors will need to override, i.e., each command. In such a case, it would be convenient to have a class containing all existing commands. This will be the CommandController class, which will have a vector of pointers to the command interface, solving the problem of object slicing and enabling runtime polymorphism. Here again, there will be no assignment operator (=) or a copy constructor, as they will be unnecessary.

Instead of creating objects of all the necessary classes in main, making it difficult to read, a better option is a class that wraps everything. This class will be Program and will contain an object of type Catalogue (the database) as well as an object of type CommandController (the possible commands). Since this object essentially represents the entire program and there is only one, it is appropriate to use the Singleton design pattern, as is standard in game development, for example - the settings of a game are unique and hence Singleton. Using this pattern involves adding another member data in the Program class, which is a pointer to this same Program. Additionally, the constructor will be private to prevent it from being called outside the class, and there will be a static method to return this single Program object whenever needed. We also need a method to start the entire program - this will be execute().

Thus, in main, we will only need to call this single Program object and execute the execute() method on it, hiding everything from the external world and dividing it into convenient parts, following the object-oriented programming development ideology.