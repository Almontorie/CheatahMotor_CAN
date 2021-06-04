CC=gcc
EXE=CheetahMotor_can.out

$(EXE): main.c commands.c
	$(CC) -o $@ $^

clean:
	rm -rf $(EXE)
