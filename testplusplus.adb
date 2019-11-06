with Ada.Text_IO, Ada.Integer_Text_IO;
use Ada.Text_IO, Ada.Integer_Text_IO;

procedure testplusplus is
    i : integer;
begin
    i := 2;
    i := i + 1;
    Put(i);
    New_Line(1);
    i := i - 1;
    Put(i);
    New_Line(1);
end testplusplus;