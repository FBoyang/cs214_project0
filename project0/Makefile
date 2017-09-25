sources = csvio.c mergesort.c
headers = sorter.h
objects = $(patsubst %.c, %.o, $(sources))

sorter: $(objects)
	$(CC) -o sorter $(objects)

$(objects): %.o: %.c $(headers)
	$(CC) -c $(CPPFLAGS) -Wall -g $(CFLAGS) -o $@ $<

submission.tar: $(sources) $(headers)
	mkdir --parents submission
	$(foreach file, $(sources) $(headers), cp $(file) submission;)
	tar cvf submission.tar submission

.PHONY: clean
clean:
	rm --recursive --force --verbose sorter $(objects) sumbission.tar submission
