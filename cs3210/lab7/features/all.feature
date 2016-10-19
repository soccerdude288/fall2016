Feature: Source file must be present, compilable and output correct information

	Scenario: sql.c must be compilable with no errors
		When I run `rm ../../bin/sql.c`
		Then I run `rm ../../bin/sql`
		Then I run `rm ../../bin/Makefile`
		Then I run `cp ../../sql.c ../../bin/`
		Then I run `cp ../../sqlite3.c ../../bin/`
		Then I run `cp ../../sqlite3.h ../../bin/`
		Then I run `cp ../../Makefile ../../bin/`
		Then a file named "../../bin/sql.c" should exist
		And a file named "../../bin/sqlite3.c" should exist
		And a file named "../../bin/sqlite3.h" should exist
		And a file named "../../bin/Makefile" should exist
		Then 10 points are awarded
		When I run `gcc -Wall -Werror -o ../../bin/sql ../../bin/sql.c ../../bin/sqlite3.c -lpthread -ldl` 
		Then the exit status should be 0
		Then a file named "../../bin/sql" should exist
		Then 10 points are awarded

	Scenario: sql with improper parameters should print a proper USAGE statement and exit nonzero
		When I run `sql -?`
		Then the exit status should not be 0
		And the output should match /Usage/
		When I run `sql -c`
		Then the exit status should not be 0
		And the output should match /Usage/
		When I run `sql -a db_only`
		Then the exit status should not be 0
		And the output should match /Usage/
		When I run `sql -d db_only`
		Then the exit status should not be 0
		And the output should match /Usage/
		When I run `sql -g db_only`
		Then the exit status should not be 0
		And the output should match /Usage/
		When I run `sql -l`
		Then the exit status should not be 0
		And the output should match /Usage/
		Then 10 points are awarded
	
	Scenario: sql -c should properly create a database
		When I run `sql -c test.db`
		Then the exit status should be 0
		And a file named "test.db" should exist
		And the stdout should not contain anything
		And the stderr should not contain anything
		Then 10 points are awarded
			
	Scenario: sql -a DATABASE NAME ROLE should add items to the database
		When I run `sql -c jetsons.db`
		When I run `sql -a jetsons.db George Hubby`
		Then the exit status should be 0
		And the stdout should not contain anything
		And the stderr should not contain anything
		When I run `sql -a jetsons.db Jane Wife`
		Then the exit status should be 0
		And the stdout should not contain anything
		And the stderr should not contain anything
		When I run `sql -a jetsons.db Judy Daughter`
		Then the exit status should be 0
		And the stdout should not contain anything
		And the stderr should not contain anything
		Then 10 points are awarded
		When I run `sql -a jetsons.db Judy Daughter`
		Then the exit status should not be 0
		And the output should contain "UNIQUE constraint failed"
		Then 10 points are awarded
			
	Scenario: sql -l should list all records in the database
		When I run `sql -c flintstones.db`
		When I run `sql -a flintstones.db George Hubby`
		When I run `sql -a flintstones.db Jane Wife`
		When I run `sql -a flintstones.db Judy Daughter`
		When I run `sql -l flintstones.db`
		Then the exit status should be 0
		And the output should contain:
		"""
		George = Hubby
		Jane = Wife
		Judy = Daughter
		"""
		And the stderr should not contain anything
		Then 20 points are awarded
			
	Scenario: sql -g and sql -d should work properly
		When I run `sql -c beatles.db`
		When I run `sql -a beatles.db John Guitarist`
		When I run `sql -a beatles.db Paul Songwriter`
		When I run `sql -a beatles.db George Vocalist`
		When I run `sql -a beatles.db Ringo Drummer`
		When I run `sql -g beatles.db Ringo`
		Then the exit status should be 0
		And the output should contain:
		"""
		Ringo = Drummer
		"""
		And the exit status should be 0
		And the stderr should not contain anything
		Then 10 points are awarded
		When I run `sql -d beatles.db Paul`
		Then the exit status should be 0
		Then I run `sql -l beatles.db`
		And the output should contain:
		"""
		George = Vocalist
		John = Guitarist
		Ringo = Drummer
		"""
		Then 10 points are awarded
			
