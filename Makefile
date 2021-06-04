CC=gcc
EXE=CheetahMotor_can

$(EXE): main.c
	$(CC) -o $@ $^

clean:
	rm -rf $(EXE)
