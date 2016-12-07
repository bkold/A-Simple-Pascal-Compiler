run
program codeTest;

	class codeTest
	BEGIN
		VAR XRay : ARRAY[1 .. 4] OF integer;
			YRay : ARRAY[9 .. 19] OF integer;
			ZRay : ARRAY[20 .. 40] OF ARRAY[1 .. 4] OF integer;
			Index : integer;

		FUNCTION codeTest;
		BEGIN
			Index := 4;
			print Index;

			XRay[2] := 3;
			print XRay[2];

			XRay[Index] := XRay[2] * 999;
			print XRay[Index];

			Index := 9;
			WHILE Index < 20 DO BEGIN
				YRay[Index] := Index * 4;
				Index := Index + 1
			END;

			Index := 9;
			WHILE Index < 20 DO BEGIN
				print YRay[Index];
				Index := Index + 1
			END;

			Index := 1;
			WHILE Index < 5 DO BEGIN
				ZRay[23][Index] := Index * 9;
				Index := Index + 1
			END;

			Index := 1;
			WHILE Index < 5 DO BEGIN
				print ZRay[23][Index];
				Index := Index + 1
			END;

			Index := 1;
			WHILE Index < 5 DO BEGIN
				print ZRay[22][Index];
				Index := Index + 1
			END

		END

	END
.