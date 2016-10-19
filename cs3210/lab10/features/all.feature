Feature: Source file must be present and contain correct information

	Background:
		Then I run `cp ../../bin/gdb.txt .`

	Scenario: gdb.txt must be available
		When I run `rm ../../bin/gdb.txt`
		Then I run `cp ../../gdb.txt ../../bin/`
		Then a file named "../../bin/gdb.txt" should exist
		Then 10 points are awarded

	Scenario: gdb.txt includes breakpoint 1 and list 1,30
		Given a file named "gdb.txt" should exist
		Then the file "gdb.txt" should include:
		"""
		Breakpoint 1, main () at debug3.c:39
		"""
		Then 10 points are awarded
		And the file "gdb.txt" should include:
		"""
		Breakpoint 1, main () at debug3.c:39
		39              sort(array,5); 
		1       
		2       #include <stdio.h> 
		3       typedef struct {
		4           char data[4096];
		5           int key;
		6       } item;
		7       item array[] = {
		8           {"bill", 3},
		9           {"neil", 4},
		10          {"john", 2},
		11          {"rick", 5},
		12          {"alex", 1},
		13      };
		14      
		15      void sort(a,n)
		16      item *a; 
		17      int n;
		18      { 
		19          int i = 0, j = 0;
		20          int s = 1;
		21      
		22          for(; i < n && s != 0; i++) {
		23                  s = 0;
		24                  for(j = 0; j < n; j++) {
		25                          if(a[j].key > a[j+1].key) {
		26                                  item t = a[j];
		27                                  a[j] = a[j+1];
		28                                  a[j+1] = t;
		29                                  s++;
		30                          }
		"""
		Then 10 points are awarded

	Scenario: gdb.txt includes setting breakpoint 2 at sort() and stopping at sort()
		Given a file named "gdb.txt" should exist
		Then the file "gdb.txt" should match /Breakpoint 2 at 0x.*: file debug3.c, line 18/
		And the file "gdb.txt" should match /Breakpoint 2, sort \(a=0x.*, n=5\) at debug3.c:18/
		Then 10 points are awarded

	Scenario: gdb.txt includes a backtrace after hitting breakpoint 2
		Given a file named "gdb.txt" should exist
		Then the file "gdb.txt" should match /#0  sort \(a=0x.*, n=5\) at debug3.c:18/
		And the file "gdb.txt" should match /#1  0x.* in main \(\) at debug3.c:39/
		Then 10 points are awarded

	Scenario: gdb.txt includes a display of two breakpoints, main() and sort()
		Given a file named "gdb.txt" should exist
		Then the file "gdb.txt" should include:
		"""
		Num     Type           Disp Enb Address    What
		"""
		#And the file "gdb.txt" should match /breakpoint     keep y   0x.* in main at debug3.c:39/
		And the file "gdb.txt" should match /breakpoint.*in main at debug3.c:39/
		#And the file "gdb.txt" should match /breakpoint     keep y   0x.* in sort at debug3.c:18/
		And the file "gdb.txt" should match /breakpoint.*in sort at debug3.c:18/
		Then 10 points are awarded

	Scenario: gdb.txt includes the result of "print n" and data on breakpoints 2 and 3
		Given a file named "gdb.txt" should exist
		Then the file "gdb.txt" should contain "$1 = 5"
		And the file "gdb.txt" should match /2.*breakpoint     keep y   0x.* in sort at debug3.c:18/
		And the file "gdb.txt" should match /3.*breakpoint     keep y   0x.* in sort at debug3.c:23/
		Then 10 points are awarded

	Scenario: gdb.txt includes the results of setting commands on breakpoint 3
		Given a file named "gdb.txt" should exist
		Then the file "gdb.txt" should contain:
		"""
		End with a line saying just "end".
		"""
		Then 10 points are awarded


	Scenario: gdb.txt includes a display of five data items at breakpoint 3
		Given a file named "gdb.txt" should exist
		Then the file "gdb.txt" should match /Breakpoint 3, sort \(a=0x.*, n=5\) at debug3.c:23/
		And the file "gdb.txt" should include:
		"""
		23      s = 0;
		"""
		And the file "gdb.txt" should include:
		"""
		$2 = {{data = "bill", '\000' <repeats 4091 times>, key = 3}, {
			data = "neil", '\000' <repeats 4091 times>, key = 4}, {
			data = "john", '\000' <repeats 4091 times>, key = 2}, {
			data = "rick", '\000' <repeats 4091 times>, key = 5}, {
			data = "alex", '\000' <repeats 4091 times>, key = 1}}
		$3 = 0
		"""
		Then 10 points are awarded

	Scenario: gdb.txt includes a SIGSEGV and a backtrace
		Given a file named "gdb.txt" should exist

		Then the file "gdb.txt" should match /Program received signal SIGSEGV, Segmentation fault./
		Then the file "gdb.txt" should include:
		"""
		25                      if(a[j].key > a[j+1].key) {
		"""
		Then the file "gdb.txt" should match /#0 0x.* in sort \(a=0x.*, n=5\) at debug3.c:25/
		And the file "gdb.txt" should match /#1 0x.* in main \(\) at debug3.c:39/
		Then 10 points are awarded

