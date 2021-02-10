#include <stdio.h>
#include "sqlite3.h"
 
const char* SQL = "CREATE TABLE IF NOT EXISTS foo(a,b,c); INSERT INTO FOO VALUES(1,2,3); INSERT INTO FOO SELECT * FROM FOO;";
 
int main(int argc, char **argv){
 
sqlite3 *db = 0; // хэндл объекта соединение к БД
char *err = 0;
 
// открываем соединение
if( sqlite3_open("my_cosy_database.dblite", &db) )
fprintf(stderr, "Ошибка открытия/создания БД: %s\n", sqlite3_errmsg(db));
// выполняем SQL
else if (sqlite3_exec(db, SQL, 0, 0, &err))
{
fprintf(stderr, "Ошибка SQL: %sn", err);
sqlite3_free(err);
}
// закрываем соединение
sqlite3_close(db);
return 0;
}