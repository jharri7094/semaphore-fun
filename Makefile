make:	pizzastudy.c votecountersem.c
	gcc -pthread -o pizzastudy pizzastudy.c
	gcc -pthread -o votecountersem votecountersem.c
	
