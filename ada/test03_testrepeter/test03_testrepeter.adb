with Ada.Text_IO, Ada.Integer_Text_IO;
use Ada.Text_IO, Ada.Integer_Text_IO;

procedure test03_testrepeter is
    test1 : integer;
begin
    test1 := 0;
    loop 
        test1 := test1 + 1;
        Put("Test1 après incrementation : ");
        Put(test1);
        New_Line(1);
        exit when test1 = 10;
    end loop;
    Put("Valeur de test1 finproc : ");
    Put(test1);
    New_Line(1);
end test03_testrepeter;