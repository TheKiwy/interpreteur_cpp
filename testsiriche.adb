procedure testsiriche is
    test1 : integer;
    test2 : integer;
    test3 : integer;
    test4 : integer;
begin
    test1 := 0;
    if test1 = 0 then 
        test1 := 10;
    end if;
    test2 := 10;
    if test2 = 0 then 
        test2 := 150;
    elsif test2 = 10 then 
        test2 := 15;
    end if;
    test3 := 10;
    if test3 = 200 then 
        test3 := 555;
    elsif test3 = 600 then 
        test3 := 666;
    else
        test3 := 20;
    end if;
    test4 := 10;
    if test4 = 300 then 
        test4 := 777;
    else
        test4 := 25;
    end if;
end testsiriche;