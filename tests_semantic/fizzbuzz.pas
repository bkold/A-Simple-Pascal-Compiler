run
program codeTest;

	class codeTest
	BEGIN
		VAR PrintVars : ARRAY[1 .. 3] OF integer;
			Index : integer;

		FUNCTION codeTest;
		BEGIN
			PrintVars[1] := -1;
			PrintVars[2] := -2;
			PrintVars[3] := -3;

			Index := 1;
			WHILE Index < 101 DO BEGIN
				IF Index MOD 15 = 0 THEN
					print PrintVars[3]
				ELSE IF Index MOD 5 = 0 THEN
					print PrintVars[2]
				ELSE IF Index MOD 3 = 0 THEN
					print PrintVars[1]
				ELSE 
					print Index;

				Index := Index + 1

			END			
			
		END

	END
.