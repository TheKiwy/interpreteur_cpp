with Ada.Text_IO, Ada.Integer_Text_IO;
use Ada.Text_IO, Ada.Integer_Text_IO;

procedure testpour is
    i : integer;
    j : integer;
    nb : integer;
    x : integer;
    y : integer;
begin
    Put("Entrez un nombre à multiplier : ");
    New_Line(1);
    Get(nb);
    Put("Test -Pour- avec la forme Affectation, Expression, Affectation : ");
    New_Line(1);
    i := 0;
    while i < 10 loop
        Put(nb);
        Put("x");
        Put(i);
        Put(" = ");
        Put(nb * i);
        New_Line(1);
        i := i + 1;
    end loop;
    Put("Test -Pour- avec la forme Expression, Affectation : ");
    New_Line(1);
    x := 0;
    while x < 10 loop
        Put(nb);
        Put("x");
        Put(x);
        Put(" = ");
        Put(nb * x);
        New_Line(1);
        x := x + 1;
    end loop;
    Put("Test -Pour- avec la forme Affectation, Expression : ");
    New_Line(1);
    y := 0;
    while y < 10 loop
        Put(nb);
        Put("x");
        Put(y);
        Put(" = ");
        Put(nb * y);
        New_Line(1);
        y := y + 1;
    end loop;
    Put("Test -Pour- avec la forme Expression : ");
    New_Line(1);
    j := 0;
    while j < 10 loop
        Put(nb);
        Put("x");
        Put(j);
        Put(" = ");
        Put(nb * j);
        New_Line(1);
        j := j + 1;
    end loop;
end testpour;