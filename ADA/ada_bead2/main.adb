with Ada.Text_IO, Ada.Numerics.Discrete_Random, Ada.Numerics.Float_Random;

procedure Main is
    Min_Wait_Time : constant Float := 1.0;
    Max_Wait_Time : constant Float := 5.0;
    Min_Serve_Time : constant Float := 2.0;
    Max_Serve_Time : constant Float := 5.0;
    Min_Order_Time : constant Float := 1.0;
    Max_Order_Time : constant Float := 3.0;
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

--pizza place

    

--waiters

    task type Waiter(ID : Integer) is
        entry Order(Food : in Pizza_Types; Table : in Integer; Dur : out Duration);
    end Waiter;

    type Waiter_Access is access Waiter;
    type Waiter_Array is array (1..Number_of_Waiters) of Waiter_Access;

    task body Waiter is
        Order_Time : Duration;
    begin
        loop
            accept Order(Food : in Pizza_Types; Table : in Integer; Dur : out Duration) do
                Random_Duration.Get_Duration(Order_Time);
                delay Order_Time;
                Random_Duration.Get_Duration(Dur);
            end Order;
        end loop;
    end Waiter;

--guests




    Aasd : Pizza_Types;
    Asd : Duration;
begin
    Safe_Random.Generate_Pizza(Aasd);
    Random_Duration.Get_Duration(Asd);
end Main;