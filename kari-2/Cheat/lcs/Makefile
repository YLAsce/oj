CFLAGS= -Wall -O2
PY_INCLUDE= -I/usr/include/python2.7

all: _lcs.so

lcs.o: lcs.c
	gcc ${CFLAGS} -c lcs.c

lcs_wrap.c lcs.py: lcs.i
	swig -python lcs.i

lcs_wrap.o: lcs_wrap.c
	gcc ${CFLAGS} -c $^ ${PY_INCLUDE} -o $@

_lcs.so: lcs.o lcs_wrap.o
	gcc ${CFLAGS} -shared -fPIC -o $@ $^

deploy:
	rm -f lcs.o lcs_wrap.o lcs_wrap.c lcs.pyc && mv lcs.py _lcs.so ../

clean:
	rm -f lcs.o lcs_wrap.o lcs_wrap.c lcs.py lcs.pyc _lcs.so
