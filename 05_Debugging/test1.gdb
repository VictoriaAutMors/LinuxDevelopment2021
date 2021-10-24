set pagination off
set logging on

break 17 if i % 5 == 0
	command 1
	printf "@@@%d, %d, %d, %d\n", N, M, S, i
	continue
end

run 1 12 > /dev/null

set logging off
quit
