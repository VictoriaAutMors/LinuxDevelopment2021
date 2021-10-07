GENERATES = prog prog-a prog-so *.so *.a README
TRASH = *.o *~ o.* *.a
CFLAGS = -Wall -fPIC -O2

all: README prog prog-a prog-so

README: prog
	./$< 2> $@

fun.o: outlib.h

liboutput_static.a: const.o fun.o
	ar -rcs $@ fun.o const.o

liboutput.so: fun.o const.o
	cc -shared fun.o const.o -o $@

prog: const.o fun.o prog.o

prog-a: prog.o liboutput_static.a
	cc -L. $< liboutput_static.a -o $@

prog-so: prog.o liboutput.so
	cc -L. $< liboutput.so -o $@

test: preg prog-a prog-so
	./prog > prog.a
	./prog-a > prog_a.a
	$LD_LIBRARY_PATH=. ./prog-so > prog_so.a
	cmp prog.a prog_so.a
	cmp prog.a prog_a.a
	cmp prog_a.a prog_so.a
	./prog 1 > prog.a
	./prog-a 1 > prog_a.a
	$LD_LIBRARY_PATH=. ./prog-so 1 > prog_so.a
	cmp prog.a prog_so.a
	cmp prog.a prog_a.a
	cmp prog_a.a prog_so.a
	./prog 1 2 3 > prog.a
	./prog-a 1 2 3 > prog_a.a
	$LD_LIBRARY_PATH=. ./prog-so 1 2 3 > prog_so.a
	cmp prog.a prog_so.a
	cmp prog.a prog_a.a
	cmp prog_a.a prog_so.a
	
clean:
	rm -f $(TRASH)

distclean:      clean
	rm -rf $(GENERATES)
