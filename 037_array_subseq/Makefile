maxSeq: maxSeq.o test-subseq.o
	gcc -o maxSeq maxSeq.o test-subseq.o
maxSeq.o: maxSeq.c
	gcc -std=gnu99 -pedantic -Wall -Werror -c maxSeq.c
test-subseq.o: test-subseq.c
	gcc -std=gnu99 -pedantic -Wall -Werror -c test-subseq.c
