separate(main)
protected body Pizzeria is
    procedure Open is
    begin
        for I in 1..Number_of_Waiters loop
            Waiter_Arr(I) := new Waiter(I);
            Waiter_Availability(I) := True;
        end loop;
    end Open;

    function Get_Guest(Table : Integer) return Guest_Access is
    begin
        return Guest_Arr(Table);
    end Get_Guest;

    procedure Waiter_Ready(ID : Integer) is
    begin
        Waiter_Availability(ID) := True;
        Busy_Waiter := Busy_Waiter - 1;
    end Waiter_Ready;

    entry New_Guest(Input : String)
        when Curr_Guests < Number_of_Guests is
        String_Acc : String_Access := new String(Input'Range);
    begin
        String_Acc.all := Input;
        Curr_Guests := Curr_Guests + 1;
        Guest_Arr(Curr_Guests) := new Guest(String_Acc, Curr_Guests);
    end New_Guest;

    entry Get_Waiter(Waiter_Acc : out Waiter_Access)
        when Busy_Waiter < Number_of_Waiters is
    begin
        Waiter_Acc := Waiter_Arr(Busy_Waiter + 1);
        Waiter_Availability(Busy_Waiter + 1) := False;
        Busy_Waiter := Busy_Waiter + 1;
    end Get_Waiter;
end Pizzeria;