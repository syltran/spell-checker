CC=gcc
OBJ=correcteur_0.o Listes.o ATR.o Lecture.o

correcteur_0: $(OBJ)
	$(CC) -o $@ $^

correcteur_0.o: correcteur_0.c Listes.h ATR.h Lecture.h

Listes.o: Listes.c Listes.h

ATR.o: ATR.c ATR.h

Lecture.o: Lecture.c Lecture.h ATR.h

%.o: %.c
	$(CC) -c $<

clean:
	rm -f *.o