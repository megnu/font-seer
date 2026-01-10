CC = gcc
CFLAGS = -Wall -Wextra -O2
LIBS = $(shell pkg-config --cflags --libs gtk+-3.0 fontconfig pangofc)

font_seer: font_seer.c
	$(CC) $(CFLAGS) font_seer.c -o font_seer $(LIBS)

clean:
	rm -f font_seer
