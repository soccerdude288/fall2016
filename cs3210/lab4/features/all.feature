Feature: Source file must be present, compilable and output correct information

	Scenario: userinfo.c must be compilable with no errors
		When I run `rm ../../bin/userinfo.c`
		Then I run `rm ../../bin/userinfo`
		Then I run `cp ../../userinfo.c ../../bin/`
		Then a file named "../../bin/userinfo.c" should exist
		Then 10 points are awarded
		When I run `gcc -Wall -Werror -o ../../bin/userinfo ../../bin/userinfo.c` 
		Then the exit status should be 0
		Then a file named "../../bin/userinfo" should exist
		Then 10 points are awarded

	Scenario: userinfo -? should print a proper USAGE statement
		When I run `userinfo -?`
		Then the exit status should not be 0
		And the output should match /-h.*show hostname/
		And the output should match /-t.*show time and date/
		And the output should match /-u.*show username, uid, gid, home dir, shell and GECOS/
		And the output should match /-?.*show usage/
		Then 20 points are awarded
	
	Scenario: userinfo -h should properly print the system hostname
		When I run `userinfo -h`
		Then the exit status should be 0
		And the output should match /hostname:/
		And the output should contain the host name
		Then 20 points are awarded
			
	Scenario: userinfo -u USERNAME should properly print the data from getpwnam()
		When I run `userinfo -u daemon`
		Then the exit status should be 0
		And the output should match that from getpwnam for daemon 
		When I run `userinfo -u root`
		Then the exit status should be 0
		And the output should match that from getpwnam for root 
		Then 20 points are awarded
			
	Scenario: userinfo -t should properly print the current date and time
		When I run `userinfo -t`
		Then the exit status should be 0
		And the output should contain the current date and time
		Then 20 points are awarded
			
