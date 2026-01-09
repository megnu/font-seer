CC = gcc
CFLAGS = -Wall -Wextra -O2
LIBS = $(shell pkg-config --cflags --libs gtk+-3.0 fontconfig pangofc)

font_viewer: font_viewer.c
	$(CC) $(CFLAGS) font_viewer.c -o font_viewer $(LIBS)

clean:
	rm -f font_viewer
