Feature: Source file must be present, compilable and output correct information

	Scenario: Makefile and git.log must be present
		When I run `rm ../../bin/Makefile`
		Then I run `rm ../../bin/git.log`
		Then I run `cp ../../Makefile ../../bin/`
		Then I run `cp ../../git.log ../../bin/`
		Then I run `cp ../../addr.c ../../bin/`
		Then I run `cp ../../addr.h ../../bin/`
		Then I run `cp ../../db.c ../../bin/`
		Then I run `cp ../../screen.c ../../bin/`
		Then a file named "../../bin/Makefile" should exist
		And a file named "../../bin/git.log" should exist
		Then 10 points are awarded

	Scenario: the Makefile should create a working addr
		Then I run `cp ../../addr.c .`
		Then I run `cp ../../addr.h .`
		Then I run `cp ../../db.c .`
		Then I run `cp ../../screen.c .`
		When I run `make -f ../../bin/Makefile`
		Then the exit status should be 0
		And a file named "addr" should exist
		Then 10 points are awarded
		And I run `./addr`
		Then the output should contain:
		"""
		I am addr.c
		I am db.c
		I am screen.c
		"""
		Then 10 points are awarded
	
	Scenario: the Makefile delete .o files only
		Then I run `cp ../../addr.c .`
		Then I run `cp ../../addr.h .`
		Then I run `cp ../../db.c .`
		Then I run `cp ../../screen.c .`
		When I run `make -f ../../bin/Makefile`
		Then the exit status should be 0
		And a file named "addr" should exist
		And a file named "addr.o" should exist
		And a file named "db.o" should exist
		And a file named "screen.o" should exist
		Then 10 points are awarded
		When I run `make -f ../../bin/Makefile clean`
		Then a file named "addr" should not exist
		And a file named "addr.o" should not exist
		And a file named "db.o" should not exist
		And a file named "screen.o" should not exist
		And a file named "addr.c" should exist
		And a file named "addr.h" should exist
		And a file named "db.c" should exist
		And a file named "screen.c" should exist
		Then 20 points are awarded
	
	Scenario: Makefile should not explicitly call gcc
		When I run `rm Makefile`
		Then I run `cp ../../bin/Makefile .`
		Then a file named "Makefile" should exist
		And the file "Makefile" should not contain "\tgcc"
		Then 20 points are awarded
			
	Scenario: git.log contains a record of two commits
		When I run `rm git.log`
		Then I run `cp ../../bin/git.log .`
		Then a file named "git.log" should exist
		And the file "git.log" should contain "Added clean rule to Makefile"
		And the file "git.log" should contain "Initial commit"
		Then 20 points are awarded
