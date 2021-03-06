with Ada.Text_IO, Ada.Numerics.Discrete_Random, Ada.Numerics.Float_Random;

procedure Main is
    Min_Wait_Time : constant Duration := 1.0;
    Max_Wait_Time : constant Duration := 5.0;
    Min_Serve_Time : constant Duration := 2.0;
    Max_Serve_Time : constant Duration := 5.0;
    Min_Order_Time : constant Duration := 1.0;
    Max_Order_Time : constant Duration := 3.0;
    Number_of_Waiters : constant Integer := 2;
    Number_of_Guests : constant Integer := 5;

    type Pizza_Types is (Hawaii, Pepperoni, Vegan);

    protected Safe_Random is
        procedure Generate_Pizza(Input : out Pizza_Types);
        procedure Get_Duration(Input : out Duration);
    end Safe_Random;

    protected body Safe_Random is separate;

    task type Waiter(ID : Integer) is
        entry Order(Food : in Pizza_Types; Table : in Integer; Dur : out Duration);
    end Waiter;
    type Waiter_Boolean_Array is array(1..Number_of_Waiters) of Boolean;
    type Waiter_Access is access Waiter;
    type Waiter_Array is array (1..Number_of_Waiters) of Waiter_Access;

    type String_Access is access String;

    task type Guest(Name : String_Access; Table : Integer) is
        entry Serve;
    end Guest;
    type Guest_Access is access Guest;
    type Guest_Array is array (1..Number_of_Guests) of Guest_Access;

    task type Plate(Table : Integer);
    type Plate_Access is access Plate;

    protected Pizzeria is
        procedure Open;
        entry New_Guest(Input : String);
        entry Get_Waiter(Waiter_Acc : out Waiter_Access);
        function Get_Guest(Table : Integer) return Guest_Access;
        procedure Waiter_Ready(ID : Integer);
    private
        Waiter_Arr : Waiter_Array;
        Waiter_Availability : Waiter_Boolean_Array;
        Guest_Arr : Guest_Array;
        Busy_Waiter : Integer := 0;
        Curr_Guests : Integer := 0;
    end Pizzeria;

    protected body Pizzeria is separate;

    task body Guest is separate;

    task body Waiter is separate;

    task body Plate is separate;
begin
    Pizzeria.Open;
    for I in 1..Number_of_Guests loop
        Pizzeria.New_Guest(I'Image);
    end loop;
end Main;