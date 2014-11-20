# Fel på matriser

## Matrix01.o
* `operator>>` verkar inte ställa om storleken så att den matchar storleken på input.  När vi frågade en asse så sa han att storleken på det man matar in ALLTID ska motsvara storleken på resultatet. Det är inte fallet. Om man matar in en 3x3-matris till en 4x4 matris så blir resultatet en 4x4-matris med resterna av 4x4-matrisen kvar.

* Fel på `operator-`

## Matrix02.o
* Samma som tidigare på `operator>>`

* Fel på `operator*` som verkar returnera 1 för mycket

## Matrix03.o
* Samma som tidigare på `operator>>`

* Många fel i våra tester. Det verkar som att copy konstruktorn kan vara tokigt implementerad.

## Matrix04.o
* Samma som tidigare på `operator>>`

* Fel på `operator<<` som verkar göra ändringar (0-sätta) på matrisen

## Matrix05.o
* Samma som tidigare på `operator>>`

Från labbpeket: "Tillståndsfel efter utksrift/tilldelning"

* TODO (svåra att hitta enligt labbpeket)

## Matrix06.o
* Transponeringen verkar ändra formatet till transponerat format, men också sätta alla element till 0 på något sätt.

## Matrix07.o
* Samma som tidigare på `operator>>`

* Addition verkar inte fungera korrekt. Den nollställer vissa index (t.ex. blir i våra tester alltid resulterande index `[0][2]` nollställt).

## Matrix08.o
* Vi får exakt samma fel som för `Matrix07.o`

## Matrix09.o
"Tillståndsfel efter utksrift/tilldelning"

* Får ett fel på `operator*` som verkar returnera 1 för högt ibland. Kan också ha med `operator>>` eller `operator=` att göra. Se test `testmatrix_mult_test`.
* Fel på `operator+` som verkar returnera 7 för lite ibland. Kan också ha med `operator>>` eller `operator=` att göra. Se `testmatrix_addition_test`.
* Fel på `operator-`. Kan också ha med `operator>>` eller `operator=` att göra. Se `testmatrix_subtraction_test`.
