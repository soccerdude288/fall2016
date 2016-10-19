Feature: Source file must be present, compilable and output correct information

	Scenario: lab1.c must be compilable with no errors
		When I run `rm ../../bin/lab1.c`
		Then I run `rm ../../bin/lab1`
		Then I run `rm ../../bin/lab1renamed`
		Then I run `cp ../../lab1.c ../../bin/`
		Then a file named "../../bin/lab1.c" should exist
		When I run `gcc -Wall -Werror -o ../../bin/lab1 ../../bin/lab1.c` 
		Then a file named "../../bin/lab1" should exist
		Then 10 points are awarded

	Scenario: lab1 should issue no stderr messages if rc=0
		When I run `lab1 -n someoldstring`
		Then the exit status should be 0
		And the stderr should not contain anything 
		Then 10 points are awarded
		
	Scenario: lab1 should print the PID/PPID
		When I run `lab1 -n fozziebear`
		And the output should contain the pid/ppid
		Then 20 points are awarded

	Scenario: lab1 should print Welcome to Lab1, writen by USER
		When I run `lab1 -n fozziebear`
		And the output should match /Welcome to [Ll]ab 1, written by fozziebear/
		Then 20 points are awarded

	Scenario: lab1 should print the hostname
		When I run `lab1 -n fozziebear`
		And the output should contain the host name 
		Then 20 points are awarded

	Scenario: lab1 should correctly print its pgm name from argv[0]
		When I run `cp ../../bin/lab1 ../../bin/lab1renamed`
		Then a file named "../../bin/lab1renamed" should exist
		And I run `lab1renamed -n teddy`
		And the output should contain "Program: "
		And the output should contain "lab1renamed"
		Then 20 points are awarded

