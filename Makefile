# 311CA_MihutMatei_Tema3
cc = gcc
CFLAGS = -Wall -lm -Wextra -g
SRC = *.c
EXE = image_editor

build:
	$(CC) -o $(EXE) $(SRC) $(CFLAGS)

.PHONY: clean build pack

clean:
	rm -f $(EXE)

pack:
	zip -FSr 311CA_MihutMatei_Tema3.zip README Makefile *.c *.h