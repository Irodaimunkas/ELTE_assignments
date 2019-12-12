separate(main)
task body Waiter is
    Order_Time : Duration;
    Serve_Time : Duration;
    Plate_To_Serve : Plate_Access;
begin
    loop
        select
            accept Order(Food : in Pizza_Types; Table : in Integer; Dur : out Duration);
            Safe_Random.Get_Duration(Order_Time);
            delay Order_Time;
            Safe_Random.Get_Duration(Dur);
            Safe_Random.Get_Duration(Serve_Time);
            delay Serve_Time;
            Ada.Text_IO.Put_Line(Serve_Time'Image);
            Plate_To_Serve := new Plate(Table);
            Pizzeria.Waiter_Ready(ID);
        end select;
    end loop;
end Waiter;