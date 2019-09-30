CC       := gcc
OBJ      := main.o crc32.o do_env.o
LINKOBJ  := main.o crc32.o do_env.o
BIN      := uboot-env-tool

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LINKOBJ) -o $(BIN) $(LIBS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

crc32.o: crc32.c
	$(CC) -c crc32.c -o crc32.o $(CFLAGS)

do_env.o: do_env.c
	$(CC) -c do_env.c -o do_env.o $(CFLAGS)
