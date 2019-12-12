separate(main)
task body Waiter is
    Order_Time : Duration;
    Serve_Time : Duration;
begin
    loop
        accept Order(Food : in Pizza_Types; Table : in Integer; Dur : out Duration) do
            Random_Duration.Get_Duration(Order_Time);
            delay Order_Time;
            Random_Duration.Get_Duration(Dur);
            Random_Duration.Get_Duration(Serve_Time);
        end Order;
    end loop;
end Waiter;