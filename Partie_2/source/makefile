CC=gcc
OBJ=correcteur_1.o Listes.o ATR.o Levenshtein.o Lecture.o

correcteur_1: $(OBJ)
	$(CC) -o $@ $^

correcteur_1.o: correcteur_1.c Listes.h ATR.h Lecture.h

Listes.o: Listes.c Listes.h

ATR.o: ATR.c ATR.h

Levenshtein.o: Levenshtein.c Levenshtein.h

Lecture.o: Lecture.c Lecture.h ATR.h Listes.h Levenshtein.h

%.o: %.c
	$(CC) -c $<

clean:
	rm -f *.o