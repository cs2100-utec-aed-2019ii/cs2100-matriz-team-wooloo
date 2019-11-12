run: compile
	@./matrix.o

compile:
	@clang++ -o matrix.o main.cpp

clean:
	@rm matrix.o
