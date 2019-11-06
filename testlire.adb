with Ada.Text_IO, Ada.Integer_Text_IO;
use Ada.Text_IO, Ada.Integer_Text_IO;

procedure testlire is
    x : integer;
    y : integer;
begin
    x := 0;
    Put("Donnez une valeur de type entier à la variable x : ");
    New_Line(1);
    Get(x);
    Put("Est-ce bien ce que vous avez tapé au clavier ? : ");
    Put(x);
    New_Line(1);
    Put("Maintenant, rentrez deux nouvelles valeurs pour x et y: ");
    New_Line(1);
    Get(x);
    Get(y);
    Put("x est égal à ");
    Put(x);
    Put(" et y est égal à ");
    Put(y);
    New_Line(1);
end testlire;