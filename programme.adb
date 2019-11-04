with Ada.Text_IO, Ada.Integer_Text_IO;
use Ada.Text_IO, Ada.Integer_Text_IO;

procedure programme is
    i : integer;
    j : integer;
begin
    j := 0;
    i := 1;
    while i < 8 loop
        j := j + i;
        i := i + 1;
    end loop;
    Put("bonjour !");
    Put(i + 2);
    Put("blabla");
    New_Line(1);
    Get(i);
    Get(i);
    Get(j);
end programme;