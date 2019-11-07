with Ada.Text_IO, Ada.Integer_Text_IO;
use Ada.Text_IO, Ada.Integer_Text_IO;

procedure test08_testpriorite is
    i : integer;
begin
    i := 12 + 5;
    Put(1 + 8 * 7 - 2 * 4);
    New_Line(1);
    Put(3 + 2 * 8);
    New_Line(1);
    Put(8 / 2 * 5);
    New_Line(1);
    if 2 * 7 * 5 + 4 = 5 + 2 * 8 + 3 or 7 /= 5 then 
        Put("2 * 7 * 5 + 4 = ");
        Put(2 * 7 * 5 + 4);
        Put(" comparé avec 5 + 2 * 8 + 3 = ");
        Put(5 + 2 * 8 + 3);
        New_Line(1);
    end if;
end test08_testpriorite;