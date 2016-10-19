Feature: Source file must be present, compilable and output correct information

	Scenario: zap.c must be compilable with no errors
		When I run `rm ../../bin/zap.c`
		Then I run `rm ../../bin/zap`
		Then I run `cp ../../zap.c ../../bin/`
		Then a file named "../../bin/zap.c" should exist
		Then 10 points are awarded
		When I run `gcc -Wall -Werror -o ../../bin/zap ../../bin/zap.c` 
		Then a file named "../../bin/zap" should exist
		Then 20 points are awarded

	Scenario: zap should update a test file properly
		Given a file named "testfile1" with:
		"""
		This is a test of the emergency broadcast system
		"""	
		When I run `zap testfile1 18 "THE"`
		And the file named "testfile1" should contain:
		"""
		This is a test of THE emergency broadcast system
		"""	
		Then the exit status should be 0
		And the stderr should not contain anything 
		Given a file named "testfile2" with:
		"""
		Four score and eight years ago
		"""	
		When I run `zap testfile2 15 "seven"`
		And the file named "testfile2" should contain:
		"""
		Four score and seven years ago
		"""	
		Then the exit status should be 0
		And the stderr should not contain anything 
		Given a file named "testfile3" with:
		"""
		These are the voyages of the      Ship Enterprise"
		"""	
		When I run `zap testfile3 29 "Star"`
		And the file named "testfile3" should contain:
		"""
		These are the voyages of the Star Ship Enterprise"
		"""	
		Then the exit status should be 0
		And the stderr should not contain anything 
		Then 70 points are awarded
		
