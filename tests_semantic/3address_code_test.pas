run
program testExpressionSimple;

	class testExpressionSimple
	BEGIN

		VAR dd, ee, ff: integer;

		FUNCTION testExpressionSimple;
		BEGIN 
			dd := 550;
			print dd;

			ee := 4;
			print ee;

			dd := (dd / 2) - 300;
			print dd;

			WHILE dd < 7 DO	BEGIN
				dd := dd + 1;
				print dd
			END;

			dd := 56;
			ee := 23;
			ff := ee + -dd;
			print ff;
			ee := dd;
			IF ee = dd THEN
				ff := -99
			ELSE
				ff := -ee;
			print ff;

			IF ee = 4 THEN
				ee := 1
			ELSE
				ee := 5;
			print ee

		END

	END
.
