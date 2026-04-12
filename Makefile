CC = gcc
CFLAGS = -Wall -Wextra -O2
LIBS = $(shell pkg-config --cflags --libs gtk+-3.0 fontconfig pangofc)

font_seer: main.c
	$(CC) $(CFLAGS) main.c -o font_seer $(LIBS)

clean:
	rm -f font_seer
