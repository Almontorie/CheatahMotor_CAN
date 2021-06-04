CC=gcc
EXE=CheetahMotor_can

$(EXE): main.c commands.c
	$(CC) -o $@ $^

clean:
	rm -rf $(EXE)
