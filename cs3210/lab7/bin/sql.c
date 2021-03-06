#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include <unistd.h>

static int
callback (void *NotUsed, int argc, char **argv, char **azColName)
{
  int i;
  for (i = 0; i < argc; i++)
    {
      printf ("%s%s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
  return 0;
}

void
usageMessage ()
{
  printf ("Usage: sql -c DATABASE (create DATABASE)\n");
  printf ("           -a DATABASE NAME ROLE (add a record to DATABASE)\n");
  printf ("           -d DATABASE NAME (delete a record from DATABASE)\n");
  printf ("           -g DATABASE NAME (retrieve a record from DATABASE)\n");
  printf ("           -l DATABASE (list all records in DATABASE)\n");

}


int
main (int argc, char **argv)
{
  char *zErrMsg = 0;
  int rc;
  int c;
  //char *sql;
  char sql[250];
  sqlite3 *db;

  if (argc == 1)
    {
      usageMessage ();
    }


  rc = sqlite3_open (argv[2], &db);
  if (rc)
    {
      fprintf (stderr, "%s\n", sqlite3_errmsg (db));
      sqlite3_close (db);
      return (1);
    }




  while ((c = getopt (argc, argv, "cadgl?")) != -1)
    {
      switch (c)
	{
	case 'c':
	  if (argc != 3)
	    {
	      usageMessage ();
	      return 1;
	    }
	  strcpy (sql,
		  "CREATE TABLE DATA(NAME VARCHAR(30) PRIMARY KEY,ROLE VARCHAR(30));\0");

	  //printf ("sql: %s", sql);
	  rc = sqlite3_exec (db, sql, callback, 0, &zErrMsg);
	  if (rc != SQLITE_OK)
	    {
	      fprintf (stderr, "SQL error: %s\n", zErrMsg);
	      sqlite3_free (zErrMsg);
	    }
	  sqlite3_close (db);
	  return 0;


	case 'a':
	  if (argc != 5)
	    {
	      usageMessage ();
	      return 1;
	    }
	  strcpy (sql, "INSERT INTO DATA (NAME,ROLE) VALUES ('");
	  strcat (sql, argv[3]);
	  strcat (sql, "', '");
	  strcat (sql, argv[4]);
	  strcat (sql, "');\0");

	  rc = sqlite3_exec (db, sql, callback, 0, &zErrMsg);
	  if (rc != SQLITE_OK)
	    {
	      fprintf (stderr, "SQL error: %s\n", zErrMsg);
	      sqlite3_free (zErrMsg);
	      return 1;
	    }
	  sqlite3_close (db);
	  return 0;


	case 'd':
	  if (argc != 4)
	    {
	      usageMessage ();
	      return 1;
	    }
	  strcpy (sql, "DELETE FROM DATA WHERE NAME like '");
	  strcat (sql, argv[3]);
	  strcat (sql, "';\0");

	  rc = sqlite3_exec (db, sql, callback, 0, &zErrMsg);
	  if (rc != SQLITE_OK)
	    {
	      fprintf (stderr, "SQL error: %s\n", zErrMsg);
	      sqlite3_free (zErrMsg);
	    }
	  sqlite3_close (db);
	  return 0;



	case 'g':
	  if (argc != 4)
	    {
	      usageMessage ();
	      return 1;
	    }

	  strcpy (sql,
		  "SELECT NAME || ' = ' || ROLE AS '' FROM DATA WHERE NAME like '");
	  strcat (sql, argv[3]);
	  strcat (sql, "';\0");
	  rc = sqlite3_exec (db, sql, callback, 0, &zErrMsg);
	  if (rc != SQLITE_OK)
	    {
	      fprintf (stderr, "SQL error: %s\n", zErrMsg);
	      sqlite3_free (zErrMsg);
	    }
	  sqlite3_close (db);
	  return 0;
	case 'l':
	  if (argc != 3)
	    {
	      usageMessage ();
	      return 1;
	    }

	  strcpy (sql,
		  "SELECT NAME || ' = ' || ROLE AS '' FROM DATA ORDER BY NAME;\0");
	  //printf ("sql: %s\n", sql);

	  rc = sqlite3_exec (db, sql, callback, 0, &zErrMsg);
	  sqlite3_close (db);
	  return 0;
	case '?':
	  usageMessage ();
	  return 1;
	}
    }

  return 0;
}
