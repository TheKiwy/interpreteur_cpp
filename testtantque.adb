with Ada.Text_IO, Ada.Integer_Text_IO;
use Ada.Text_IO, Ada.Integer_Text_IO;

procedure testtantque is
    iterateur : integer;
    nb : integer;
begin
    iterateur := 1;
    nb := 0;
    Put("Entrez un nb à multiplier : ");
    New_Line(1);
    Get(nb);
    while iterateur <= 10 loop
        Put(iterateur);
        Put(" x ");
        Put(nb);
        Put(" = ");
        Put(iterateur * nb);
        New_Line(1);
        iterateur := iterateur + 1;
    end loop;
end testtantque;
