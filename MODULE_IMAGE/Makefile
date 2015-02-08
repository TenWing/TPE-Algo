CC=gcc
CFLAG=-Wall -g
LIBS=-L
LDFLAGS= -lm
OBJ=main.o image.o image_util.o quadtree.o
OUTPUT=testimage

$(OUTPUT): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS) -limage32 $(LDFLAGS)

clean:
	rm -f $(OUTPUT) $(OBJ)

main.o: main.c image.h objet.h exit_if.h classe.h point.h move_type.h quadtree.h\
  type_obj.h 
	$(CC) $(CFLAG) -c main.c

image.o: image.c image.h objet.h exit_if.h classe.h point.h move_type.h \
  type_obj.h
		 $(CC) $(CFLAG) -c image.c

image_util.o: image.c image_util.c image.h objet.h exit_if.h classe.h point.h move_type.h \
  type_obj.h
			$(CC) $(CFLAG) -c image_util.c image.c

quadtree.o: image.c quadtree.c image_util.c  image.h objet.h exit_if.h classe.h point.h move_type.h \
  type_obj.h
			$(CC) $(CFLAG) -c image.c image_util.c quadtree.c 
