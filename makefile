FLAGS=-std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2

diccionario: main.c src/*.c
	gcc $(FLAGS) main.c src/*.c -o diccionario

pruebas_diccionario: pruebas/pruebas_alumno.c src/*.c 
	gcc $(FLAGS) pruebas/pruebas_alumno.c src/*.c -o pruebas_diccionario

