F = -std=c++17 -ggdb -Wall -Wextra -Werror -pedantic -Wfatal-errors
P = process-numbers mapset compute_grades

def: $P

process_numbers: process_numbers.cpp
	g++ $F process_numbers.cpp -o process_numbers

mapset: mapset.cpp
	g++ $F mapset.cpp -o mapset

compute_grades: compute_grades.cpp
	g++ $F compute_grades.cpp -o compute_grades

clean: 
	/bin/rm -rf $P course_grades.txt odds.txt evens.txt frequency.txt *.dSYM txt.zip $Z

mem_linux: $P
	valgrind -s process_numbers
	valgrind -s mapset
	valgrind -s compute_grades

mem_mac: $P
	leaks --atExit -- process_numbers
	leaks --atExit -- mapset
	leaks --atExit -- compute_grades