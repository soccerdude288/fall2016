Feature: Source file must be present, compilable and output correct information

	Scenario: smallcalc must be found
		When I run `rm ../../bin/smallcalc`
		Then I run `cp ../../smallcalc ../../bin/`
		Then a file named "../../bin/smallcalc" should exist
		Then 20 points are awarded

	Scenario: smallcalc should issue the appropriate prompt
		When I run `smallcalc` interactively
		And I type "exit"
		Then the exit status should be 0
		And the stderr should not contain anything 
		And the stdout should contain "Enter an expression: "
		Then 20 points are awarded
		
	Scenario: smallcalc should exit without crashing
		When I run `smallcalc` interactively
		And I type "exit"
		Then the exit status should be 0
		And the stderr should not contain anything 
		Then 20 points are awarded

	Scenario: smallcalc with 1+1 should answer 2
		When I run `smallcalc` interactively
		And I type "1+1"
		And I type "exit"
		And the stdout should contain "Answer: 2"
		Then 10 points are awarded

	Scenario: smallcalc with 2*3 should answer 6
		When I run `smallcalc` interactively
		And I type "2*3"
		And I type "exit"
		And the stdout should contain "Answer: 6"
		Then 10 points are awarded

	Scenario: smallcalc with 1+1 should answer 2
		When I run `smallcalc` interactively
		And I type "12/3+1"
		And I type "exit"
		And the stdout should contain "Answer: 5"
		Then 10 points are awarded

	Scenario: smallcalc with 1+1 should answer 2
		When I run `smallcalc` interactively
		And I type "20/10-3"
		And I type "exit"
		And the stdout should contain "Answer: -1"
		Then 10 points are awarded

