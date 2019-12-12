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

--random generators

    protected Safe_Random is
        procedure Generate_Pizza(Input : out Pizza_Types);
    end Safe_Random;

    protected body Safe_Random is

        procedure Generate_Pizza(Input : out Pizza_Types) is
            type Rand_Range is range 0..2;
            package Rand_Int is new Ada.Numerics.Discrete_Random(Rand_Range);
            Seed : Rand_Int.Generator;
            Num : Rand_Range;
        begin
            Rand_Int.Reset(Seed);
            Num := Rand_Int.Random(Seed);
            Input := Pizza_Types'Val(Num);
        end Generate_Pizza;

    end Safe_Random;

    protected Random_Duration is
        procedure Get_Duration(Input : out Duration);
    end Random_Duration;

    protected body Random_Duration is
        procedure Get_Duration(Input : out Duration) is
            type Rand_Range is new Float range 0.0..5.0;
            Seed : Ada.Numerics.Float_Random.Generator;
            Num : Rand_Range;
        begin
            Ada.Numerics.Float_Random.Reset(Seed);
            Num := 5.0 * Rand_Range(Ada.Numerics.Float_Random.Random(Seed));
            Input := Duration(Num);
        end Get_Duration;
    end Random_Duration;

--waiters

  --  task type Plate(Table : Integer);
  --  type Plate_Access is access Plate;

    task type Waiter(ID : Integer) is
        entry Order(Food : in Pizza_Types; Table : in Integer; Dur : out Duration);
    end Waiter;

    type Waiter_Access is access Waiter;
    type Waiter_Array is array (1..Number_of_Waiters) of Waiter_Access;

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

--guests
    type String_Access is access String;

    task type Guest(Name : String_Access; Table : Integer) is
        entry Serve;
    end Guest;

    type Guest_Access is access Guest;
    type Guest_Array is array (1..Number_of_Guests) of Guest_Access;

    task body Guest is
        Order : Pizza_Types;
        Dur : Duration;
        Waiter : Waiter_Access;
    begin
        Watier := Pizzeria.Get_Waiter;
        Safe_Random.Generate_Pizza(Order);
        select
            Waiter.Order(Order, Table, Dur);
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


--pizza place

    protected Pizzeria is
        procedure Open;
        entry New_Guest(Input : String);
        entry Get_Waiter(Waiter_Acc : out Waiter_Access);
        function Get_Guest(Table : Integer) return Guest_Access;
        procedure Waiter_Ready(ID : Integer);
    private
        Waiter_Arr : Waiter_Array;
        Waiter_Availability : array(1..Number_of_Waiters) of Boolean;
        Guest_Arr : Guest_Array;
        Curr_Guests : Integer := 0;
    end Pizzeria;

    protected body Pizzeria is
        procedure Open is
        begin
            for I in 1..Number_of_Waiters loop
                Waiter_Arr := new Waiter(I);
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
        end Waiter_Ready;

    begin
        select

        end select;
    end Pizzeria;

begin
    null;
end Main;