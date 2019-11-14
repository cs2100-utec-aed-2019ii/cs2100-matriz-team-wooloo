run: compile
	@./matrix.o

compile:
	@clang++ -o matrix.o main.cpp -L/usr/X11R6/lib -lm -lX11 -O2

clean:
	@rm matrix.o
