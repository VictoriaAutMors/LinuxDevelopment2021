TRASH = range *.gdbout *.output *.txt
GDB_FLAGS=-q --batch-silent

range: range.c
	cc $^ -O0 -g -o $@

test: range test1 test2

test1: test1.gdb
	gdb $(GDB_FLAGS) --command=$^ ./range | grep @@@ | cut -c 5- > test1.gdbout

test2: test2.gdb
	gdb $(GDB_FLAGS)  --command=$^ ./range | grep @@@ | cut -c 5- > test2.gdbout

clean:
	rm -f $(TRASH)
