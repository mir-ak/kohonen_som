CC=gcc
HEADER=include/
CFLAGS=-Wall -I$(HEADER)
LBIS = -lm
SDL = `sdl2-config --cflags --libs`
OUT= output/
SRCDIR=src/
SRC=map.c free.c window.c iris_data.c
ECHO=echo
OBJ=$(SRC:.c=.o)
PROGNAME=Iris
tm = time
RM=rm -rf
MKDIR=mkdir -p

all:	$(OUT) $(OUT)$(PROGNAME)

$(OUT):
	$(MKDIR) $@

$(OUT)$(PROGNAME):	$(addprefix $(OUT), $(OBJ))
	$(CC) $(CFLAGS) $^ $(LBIS) $(SDL) -o $@

$(OUT)iris_data.o:	$(addprefix $(SRCDIR), iris_data.c)
	$(CC) $(CFLAGS) -c $< $(LBIS) $(SDL) -o $@

$(OUT)free.o:	$(addprefix $(SRCDIR), free.c) $(HEADER)iris_data.h
	$(CC) $(CFLAGS) -c $< $(LBIS) $(SDL) -o $@

$(OUT)map.o:	$(addprefix $(SRCDIR), map.c) $(HEADER)iris_data.h
	$(CC) $(CFLAGS) -c $< $(LBIS) $(SDL) -o $@

$(OUT)window.o:	$(addprefix $(SRCDIR), window.c) $(HEADER)iris_data.h
	$(CC) $(CFLAGS) -c $< $(LBIS) $(SDL) -o $@


clean:
	$(RM) $(OUT)*.o $(OUT)$(PROGNAME) 
	

run:   
	  $(OUT)$(PROGNAME) 
