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
- open <filename>
Opens a file, provided by the user.

- close
Closes the opened file.

- save
Saves to the opened file.

- saveas <filename>
Saves the already opened file to a specific one, provided by the user.

- help
Displays all of the available commands.

- exit
Exits the program.

- import <tablename> <filename>
Imports a new table into the database by table name and file name.

- showtables
Displays a list of all loaded tables.

- describe <tablename>
Shows all the types of the columns of the provided table.

- print <tablename>
Prints the provided table.

- export <tablename> <filename>
Exports the provided table to a specific file.

- select <columnIndex> <value> <tablename>
Prints all rows which match the provided value.

- addcolumn <tablename> <columnname> <columntype>
Adds a new column to the provided table.

- update <tablename> <searchColumnIndex> <searchValue> <targetColumnIndex> <targetValue>
Updates the provided table.

- delete <tablename> <searchColumnIndex> <searchValue>
Deletes the rows matching the provided value.

- insert <tablename> <value1> <value2> ... <valueN>
Inserts the provided values.

- innerjoin <tablename1> <columnIndex1> <tablename2> <columnIndex2>
Performs the inner join operation on the provided tables.

- rename <tablename> <newTablename>
Changes the name of the provided table.

- count <tablename> <searchColumnIndex> <searchValue>
Counts the rows having this specific value in the provided table.

- aggregate <tablename> <searchColumnIndex> <searchValue> <targetColumnIndex> <mathOperation>
Performs a given operation (sum, product, maximum, or minimum) on the values in the target column index of all rows whose columns with number search column index contain the value search value. Returns an error if the columns are not numeric.
