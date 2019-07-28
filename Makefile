CC=cc
CFLAGS:=-O3 -funroll-loops -Imruby/include $(CFLAGS)
LD=ld
LDFLAGS=
VPATH=mruby/src
OUTNAME=crc16-mrbuy
ASMS=benchmark.S sampledata.S bitwise.S bitcombine.S octet.S quartet.S duo.S parallelstride16.S crc.S

all: $(OUTNAME)

run: all
	./$(OUTNAME)

clean:
	-rm -f $(ASMS)

$(OUTNAME): $(ASMS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o$(OUTNAME) $(ASMS)

.c.S:
	$(CC) $(CFLAGS) -S -o$@ $<

benchmark.S: defs.h benchmark.c
sampledata.S: defs.h sampledata.c
bitwise.S: defs.h bitwise.c
bitcombine.S: defs.h bitcombine.c
octet.S: defs.h octet.c
quartet.S: defs.h quartet.c
duo.S: defs.h duo.c
parallelstride16.S: defs.h parallelstride16.c
crc.S: crc.c # <= mruby/src/crc.c
