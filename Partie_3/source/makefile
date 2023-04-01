CC=gcc
CFLAGS=-ansi -Wall
OBJ1=correcteur_1.o Listes.o ATR.o Levenshtein.o ArbreBK.o Lecture.o
OBJ2=correcteur_2.o Listes.o ATR.o Levenshtein.o ArbreBK.o Lecture.o

correcteur_1: $(OBJ1)
	$(CC) -o $@ $^ $(CFLAGS)

correcteur_2: $(OBJ2)
	$(CC) -o $@ $^ $(CFLAGS)

correcteur_1.o: correcteur_1.c Listes.h ATR.h Lecture.h

correcteur_2.o: correcteur_2.c Listes.h ATR.h ArbreBK.h Lecture.h

Listes.o: Listes.c Listes.h

ATR.o: ATR.c ATR.h

Levenshtein.o: Levenshtein.c Levenshtein.h

ArbreBK.o : ArbreBK.c ArbreBK.h Listes.h Levenshtein.h

Lecture.o: Lecture.c Lecture.h ATR.h Listes.h Levenshtein.h ArbreBK.h

%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o