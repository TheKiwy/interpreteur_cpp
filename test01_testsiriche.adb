with Ada.Text_IO, Ada.Integer_Text_IO;
use Ada.Text_IO, Ada.Integer_Text_IO;

procedure test01_testsiriche is
    test1 : integer;
    test2 : integer;
    test3 : integer;
    test4 : integer;
begin
    test1 := 0;
    if test1 = 0 then 
        test1 := 10;
    end if;
    Put("Resultat Test 1 : ");
    Put(test1);
    New_Line(1);
    test2 := 10;
    if test2 = 0 then 
        test2 := 150;
    elsif test2 = 10 then 
        test2 := 15;
    end if;
    Put("Resultat Test 2 : ");
    Put(test2);
    New_Line(1);
    test3 := 10;
    if test3 = 200 then 
        test3 := 555;
    elsif test3 = 600 then 
        test3 := 666;
    else
        test3 := 20;
        Put("Resultat Test 1 : ");
        Put(test1);
        New_Line(1);
    end if;
    Put("Resultat Test 3 : ");
    Put(test3);
    New_Line(1);
    test3 := 10;
    if test3 = 200 then 
        test3 := 555;
    elsif test3 = 600 then 
        test3 := 666;
    elsif test3 = 10 then 
        test3 := 20;
    elsif test3 = 20 / 2 then 
        test3 := 60;
    else
        test3 := 500;
    end if;
    Put("Resultat Test 3 : ");
    Put(test3);
    New_Line(1);
    test4 := 10;
    if test4 = 300 then 
        test4 := 777;
    else
        test4 := 25;
    end if;
    Put("Resultat Test 4 : ");
    Put(test4);
    New_Line(1);
end test01_testsiriche;