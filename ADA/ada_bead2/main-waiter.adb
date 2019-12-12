separate(main)
task body Waiter is
    Order_Time : Duration;
    Serve_Time : Duration;
begin
    loop
        accept Order(Food : in Pizza_Types; Table : in Integer; Dur : out Duration) do
            Safe_Random.Get_Duration(Order_Time);
            delay Order_Time;
            Safe_Random.Get_Duration(Dur);
            Safe_Random.Get_Duration(Serve_Time);
            delay Serve_Time;
            --plate thingie
            Pizzeria.Waiter_Ready(ID);
        end Order;
    end loop;
end Waiter;