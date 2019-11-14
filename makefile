run: compile
	@echo Ejecutando
	@./matrix.o

compile:
	@echo Compilando
	@clang++ -o matrix.o main.cpp -lpthread -L/usr/X11R6/lib -lm -lX11 -O2

clean:
	@rm matrix.o
