sources = sorter.c print.c mergesort.c
headers = sorter.h
objects = $(patsubst %.c, %.o, $(sources))

all: sorter submission.tar

sorter: $(objects)
	$(CC) -lm $(LDFLAGS) -o sorter $(objects)

$(objects): %.o: %.c $(headers)
	$(CC) -c $(CPPFLAGS) -Wall -g -O2 $(CFLAGS) $<

submission.tar: $(sources) $(headers) Makefile readme.txt
	mkdir --parents submission
	$(foreach file, $(sources) $(headers) Makefile readme.txt, cp $(file) submission;)
	tar cvf submission.tar submission

.PHONY: clean
clean:
	rm --recursive --force --verbose sorter $(objects) submission.tar submission
