separate(main)
task body Waiter is
    Order_Time : Duration;
    Serve_Time : Duration;
    Plate_To_Serve_Acc : Plate_Access;
    Plate_To_Serve_Int :  Integer;
begin
    loop
        select
            accept Order(Food : in Pizza_Types; Table : in Integer; Dur : out Duration) do
                Plate_To_Serve_Int := Table;
                Safe_Random.Get_Duration(Order_Time);
                delay Order_Time;
                Safe_Random.Get_Duration(Dur);
            end Order;
        end select;
        Safe_Random.Get_Duration(Serve_Time);
        delay Serve_Time;
        Plate_To_Serve_Acc := new Plate(Plate_To_Serve_Int);
        Pizzeria.Waiter_Ready(ID);
    end loop;
end Waiter;