run
program codeTest;

	class AA
	BEGIN
		VAR row : integer;
			AAArray : ARRAY[1 .. 4] OF integer;
	END 

	class BB
	BEGIN
		VAR BBArray : ARRAY[1 .. 4] OF integer;
			AAObject : AA;
			Thing : integer;
	END 

	class codeTest
	BEGIN
		VAR XRay : ARRAY[1 .. 4] OF integer;
			YRay : ARRAY[9 .. 12] OF integer;
			ZRay : ARRAY[20 .. 40] OF ARRAY[1 .. 4] OF integer;
			BObject : BB;

		FUNCTION codeTest;
		BEGIN
			BObject := new BB;
			BObject.AAObject := new AA;
			BObject.Thing := 5;
			print BObject.Thing;

			BObject.AAObject.AAArray[2] := 4;
			print BObject.AAObject.AAArray[2]
		END

	END
.
