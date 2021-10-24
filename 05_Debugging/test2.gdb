set pagination off
set logging on

set $var = 0

break 17 if $var >= 28 && $var <= 35
	command 1
	printf "@@@%d, %d, %d, %d\n", N, M, S, i
	continue
end

run -100 100 3 > /dev/null

set logging off
quit
