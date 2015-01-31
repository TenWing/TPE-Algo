CC=gcc
CFLAG=-Wall -g
LIBS=-L
OBJ=main.o image.o image_util.o
OUTPUT=testimage

$(OUTPUT): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS) -limage32 

clean:
	rm -f $(OUTPUT) $(OBJ)

main.o: main.c image.h objet.h exit_if.h classe.h point.h move_type.h \
  type_obj.h 
	$(CC) $(CFLAG) -c main.c

image.o: image.c image.h objet.h exit_if.h classe.h point.h move_type.h \
  type_obj.h
		 $(CC) $(CFLAG) -c image.c

image_util.o: image.c image_util.c image.h objet.h exit_if.h classe.h point.h move_type.h \
  type_obj.h
			$(CC) $(CFLAG) -c image_util.c image.c

