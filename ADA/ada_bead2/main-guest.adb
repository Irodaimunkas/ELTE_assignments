separate(main)
task body Guest is
    Order : Pizza_Types;
    Dur : Duration;
    Waiter : Waiter_Access;
begin
    Pizzeria.Get_Waiter(Waiter);
    Safe_Random.Generate_Pizza(Order);
    select
        Waiter.Order(Order, Table, Dur);
        Ada.Text_IO.Put_Line(Table'Image & " ordered " & Order'Image);
        select
            accept Serve;
            Ada.Text_IO.Put_Line(Table'Image & " eating");
        or
            delay Dur;
            Ada.Text_IO.Put_Line(Table'Image & " left due to not getting served in the promised time.");
        end select;
    or
        delay Max_Wait_Time;
        Ada.Text_IO.Put_Line(Table'Image & " left due to not getting a table soon enough.");
    end select;
end Guest;