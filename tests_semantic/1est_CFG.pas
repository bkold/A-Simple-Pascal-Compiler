program CFG3;

class CFG3

BEGIN
	VAR aa, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14,
		  a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26,
	a27, a28, a29 : integer;

FUNCTION testIfThenElseNested;
BEGIN

	WHILE aa > 0 DO
		IF a1 = 1 THEN
			a2 := 2
		ELSE
		BEGIN
					a3 := 3;
					WHILE a4 < 5 DO
						IF a5 = 5 THEN
							IF a6 = 6 THEN
									IF a7 = 7 THEN
											a8 := 8
									ELSE
											a9 := 9
							ELSE
									IF a10 = 10 THEN
											a11 := 11
									ELSE
											a12 := 12
						ELSE
							a13 := 13;
					a14 := 14
			END;

	IF a15 = 15 THEN
		a16 := 16
	ELSE
	BEGIN
			a17 := 17;
			WHILE a18 < 18 DO
				IF a19 = 19 THEN
					IF a20 = 20 THEN
				WHILE a21 > 21 DO
								IF a22 = 22 THEN
										a23 := 23
								ELSE
										a24 := 24
					ELSE
							IF a25 = 25 THEN
									a26 := 26
							ELSE
									a27 := 27
				ELSE
					a28 := 28;
			a29 := 29
	END

END

END
.
