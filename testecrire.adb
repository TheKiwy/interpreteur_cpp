with Ada.Text_IO, Ada.Integer_Text_IO;
use Ada.Text_IO, Ada.Integer_Text_IO;

procedure testecrire is
    a : integer;
    age : integer;
    b : integer;
begin
    Put("Bonjour, je suis un programme de test.");
    New_Line(1);
    Put("Comment allez-vous ? ");
    Put("Personnellement, je vais bien.");
    New_Line(1);
    age := 47;
    Put("Au fait, j'ai ");
    Put(age);
    Put(" ans.");
    New_Line(1);
    a := 1;
    b := 2;
    Put("a = ");
    Put(a);
    Put(", b = ");
    Put(b);
    Put(", a + b = ");
    Put(a + b);
    New_Line(1);
end testecrire;