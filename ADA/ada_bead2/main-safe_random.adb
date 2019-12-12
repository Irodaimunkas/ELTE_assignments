separate(main)
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