package body File_System is

    procedure Reverse_Split(Input : in String; Output_One, Output_Two : out Unbounded_String) is
        Counter : Positive := Input'Last;
    begin
        while Input(Counter) /= '/' and Counter /= Input'First loop
            Counter := Counter - 1;
        end loop;

        Output_One := To_Unbounded_String(Input(Input'First .. Counter - 1));
        if(Input(Counter) = '/') then
            Output_Two := To_Unbounded_String(Input(Counter + 1 .. Input'Last));
        else
            Output_Two := To_Unbounded_String(Input(Counter .. Input'Last));
        end if;
    end Reverse_Split;

    procedure Initialize is
    begin
        Paths(Paths'First) := To_Unbounded_String("/");
        Entities(Entities'First) :=  (
                    Entity =>   Directory,
                    Name =>     To_Unbounded_String("/"),
                    Child_Files => (
                        others =>    To_Unbounded_String(" ")
                    ),
                    Child_Directories => (
                        others =>    To_Unbounded_String(" ")
                    )
                );
    end Initialize;

    procedure Mkdir(Input : String) is

        Output_One, Output_Two : Unbounded_String;

    begin
        Reverse_Split(Input, Output_One, Output_Two);
        if Input(Input'First) = '/' then
            for I in 0 .. Current_Path_Number loop
                if Paths(I) = To_Unbounded_String(Input) then
                    Standard_Output("Error: File already exists");
                    return;
                end if;
            end loop;

            Current_Path_Number := Current_Path_Number + 1;

            Paths(Current_Path_Number) := To_Unbounded_String(Input);

            Current_Entity_Number := Current_Entity_Number + 1;
            Entities(Current_Entity_Number) := (
                Entity =>   Directory,
                Name =>     Output_Two,
                Child_Files => (
                    others =>    To_Unbounded_String(" ")
                ),
                Child_Directories => (
                    others =>    To_Unbounded_String(" ")
                )
            );

            for I in 0 .. Current_Path_Number loop
                if Paths(I) = Output_One or Output_One = "" then
                    for J in Entities(I).Child_Directories'Range loop
                        if  Entities(I).Child_Directories(J) = " " then
                            Entities(I).Child_Directories(J) := Entities(Current_Entity_Number).Name;
                            exit;
                        end if;
                    end loop;
                    exit;
                end if;
            end loop;
        else
            for I in 0 .. Current_Path_Number loop
                if Paths(I) = Current_Directory & "/" & To_Unbounded_String(Input) or Paths(I) = Current_Directory & To_Unbounded_String(Input) then
                    Standard_Output("Error: File already exists");
                    return;
                end if;
            end loop;

            Current_Path_Number := Current_Path_Number + 1;

            if Current_Directory = "/" then
                Paths(Current_Path_Number) := Current_Directory & To_Unbounded_String(Input);
            else
                Paths(Current_Path_Number) := Current_Directory & "/" & To_Unbounded_String(Input);
            end if;
            
            Current_Entity_Number := Current_Entity_Number + 1;
            Entities(Current_Entity_Number) := (
                Entity =>   Directory,
                Name =>     Output_Two,
                Child_Files => (
                    others =>    To_Unbounded_String(" ")
                ),
                Child_Directories => (
                    others =>    To_Unbounded_String(" ")
                )
            );

            if Output_One = "" then
                for I in 0 .. Current_Path_Number loop
                    if Paths(I) = Current_Directory then
                        for J in Entities(I).Child_Directories'Range loop
                            if  Entities(I).Child_Directories(J) = " " then
                                Entities(I).Child_Directories(J) := Entities(Current_Entity_Number).Name;
                                exit;
                            end if;
                        end loop;
                        exit;
                    end if;
                end loop;
            else
                for I in 0 .. Current_Path_Number loop
                    if Paths(I) = Current_Directory & To_Unbounded_String("/") & Output_One or Paths(I) = Current_Directory & Output_One then
                        for J in Entities(I).Child_Directories'Range loop
                            if  Entities(I).Child_Directories(J) = " " then
                                Entities(I).Child_Directories(J) := Entities(Current_Entity_Number).Name;
                                exit;
                            end if;
                        end loop;
                        exit;
                    end if;
                end loop;
            end if;
        end if;
    end Mkdir;

    procedure Cd(Input : String) is
        Output_One, Output_Two : Unbounded_String;
    begin
        if Input = ".." then
            Reverse_Split(To_String(Current_Directory), Output_One, Output_Two);
            for I in 1 .. Current_Path_Number loop
                if Paths(I) = Output_One then
                    Current_Directory := Paths(I);
                    return;
                end if;
            end loop;
            Current_Directory := To_Unbounded_String("/");
        else
            if Input(Input'First) = '/' then
                for I in 0 .. Current_Path_Number loop
                    if Paths(I) = To_Unbounded_String(Input) and Entities(I).Entity = Directory then
                        Current_Directory := Paths(I);
                        return;
                    end if;
                end loop;
            else
                for I in 0 .. Current_Path_Number loop
                    if (Paths(I) = To_String(Current_Directory) & "/" & Input or Paths(I) = To_String(Current_Directory) & Input) and Entities(I).Entity = Directory then
                        Current_Directory := Paths(I);
                        return;
                    end if;
                end loop;
            end if;
        end if;
    end Cd;

    procedure Pwd is
    begin
        if Current_Directory = "/" then
            Standard_Output(To_String(Current_Directory));
        else
            Standard_Output(To_String(Current_Directory) & "/");
        end if;
    end Pwd;

    procedure Ls is
    begin
        for I in 0 .. Current_Path_Number loop
            if Paths(I) = Current_Directory then
                for J in Entities(I).Child_Directories'Range loop
                    if  Entities(I).Child_Directories(J) = " " then
                        exit;
                    end if;
                    Standard_Output(To_String(Entities(I).Child_Directories(J)));
                end loop;
                for J in Entities(I).Child_Files'Range loop
                    if  Entities(I).Child_Files(J) = " " then
                        exit;
                    end if;
                    Standard_Output(To_String(Entities(I).Child_Files(J)));
                end loop;
                exit;
            end if;
        end loop;
    end Ls;

    procedure Touch(Input : String) is

    Output_One, Output_Two : Unbounded_String;

    begin
        Reverse_Split(Input, Output_One, Output_Two);
        if Input(Input'First) = '/' then
            for I in 0 .. Current_Path_Number loop
                if Paths(I) = To_Unbounded_String(Input) then
                    Standard_Output("Error: File already exists");
                    return;
                end if;
            end loop;

            Current_Path_Number := Current_Path_Number + 1;

            Paths(Current_Path_Number) := To_Unbounded_String(Input);

            Current_Entity_Number := Current_Entity_Number + 1;
            Entities(Current_Entity_Number) := (
                Entity =>   File,
                Name =>     Output_Two,
                File_Contents => To_Unbounded_String("")
            );

            for I in 0 .. Current_Path_Number loop
                if Paths(I) = Output_One or Output_One = "" then
                    for J in Entities(I).Child_Files'Range loop
                        if  Entities(I).Child_Files(J) = " " then
                            Entities(I).Child_Files(J) := Entities(Current_Entity_Number).Name;
                            exit;
                        end if;
                    end loop;
                    exit;
                end if;
            end loop;
        else
            for I in 0 .. Current_Path_Number loop
                if Paths(I) = Current_Directory & "/" & To_Unbounded_String(Input) or Paths(I) = Current_Directory & To_Unbounded_String(Input) then
                    Standard_Output("Error: File already exists");
                    return;
                end if;
            end loop;

            Current_Path_Number := Current_Path_Number + 1;

            if Current_Directory = "/" then
                Paths(Current_Path_Number) := Current_Directory & To_Unbounded_String(Input);
            else
                Paths(Current_Path_Number) := Current_Directory & "/" & To_Unbounded_String(Input);
            end if;
            
            Current_Entity_Number := Current_Entity_Number + 1;
            Entities(Current_Entity_Number) := (
                Entity =>   File,
                Name =>     Output_Two,
                File_Contents => To_Unbounded_String("")
            );

            if Output_One = "" then
                for I in 0 .. Current_Path_Number loop
                    if Paths(I) = Current_Directory then
                        for J in Entities(I).Child_Files'Range loop
                            if  Entities(I).Child_Files(J) = " " then
                                Entities(I).Child_Files(J) := Entities(Current_Entity_Number).Name;
                                exit;
                            end if;
                        end loop;
                        exit;
                    end if;
                end loop;
            else
                for I in 0 .. Current_Path_Number loop
                    if Paths(I) = Current_Directory & To_Unbounded_String("/") & Output_One or Paths(I) = Current_Directory & Output_One then
                        for J in Entities(I).Child_Files'Range loop
                            if  Entities(I).Child_Files(J) = " " then
                                Entities(I).Child_Files(J) := Entities(Current_Entity_Number).Name;
                                exit;
                            end if;
                        end loop;
                        exit;
                    end if;
                end loop;
            end if;
        end if;
    end Touch;

    procedure Cat(Input : String) is
    begin
        if Input(Input'First) = '/' then
            for I in 0 .. Current_Path_Number loop
                if Paths(I) = To_Unbounded_String(Input) and Entities(I).Entity = File then
                    if  To_String(Entities(I).File_Contents) /= "" then
                        Standard_Output(To_String(Entities(I).File_Contents));
                    end if;
                    exit;
                end if;
            end loop;
        else
            for I in 0 .. Current_Path_Number loop
                if (Paths(I) = Current_Directory & "/" & To_Unbounded_String(Input) or Paths(I) = Current_Directory & To_Unbounded_String(Input)) and Entities(I).Entity = File then
                    if To_String(Entities(I).File_Contents) /= "" then
                        Standard_Output(To_String(Entities(I).File_Contents));
                    end if;
                    exit;
                end if;
            end loop;
        end if;
    end Cat;

    procedure Echo(Input : String) is
        Inputs : Strings(0..2) := (To_Unbounded_String(""), To_Unbounded_String(""), To_Unbounded_String(""));
        Counter : Natural := Input'Last;
        End_Of_Split : Natural := Input'Last;
    begin
        while Counter /= Input'First loop
            if Input(Counter) = ''' then
                exit;
            end if;
            if Input(Counter) = ' ' then
                for I in reverse 0..2 loop
                    if Inputs(I) = To_Unbounded_String("") then
                        Inputs(I) := To_Unbounded_String(Input(Counter + 1 .. End_Of_Split));
                        End_Of_Split := Counter - 1;
                    end if;
                end loop;
            end if;
            Counter := Counter - 1;
        end loop;
        Inputs(0) := To_Unbounded_String(Input(Input'First + 1 .. End_Of_Split - 1));

        if(Inputs(1) = "") then
            Standard_Output(To_String(Inputs(0)));
        elsif(Inputs(1) = ">") then
            if To_String(Inputs(2))(To_String(Inputs(2))'First) = '/' then
                for I in 0 .. Current_Path_Number loop
                    if Paths(I) = Inputs(2) and Entities(I).Entity = File then
                        Entities(I).File_Contents := Inputs(0);
                        exit;
                    end if;
                end loop;
            else
                for I in 0 .. Current_Path_Number loop
                    if (Paths(I) = Current_Directory & "/" & Inputs(2) or Paths(I) = Current_Directory & Inputs(2)) and Entities(I).Entity = File then
                        Entities(I).File_Contents := Inputs(0);
                        exit;
                    end if;
                end loop;
            end if;
        else
            if To_String(Inputs(2))(To_String(Inputs(2))'First) = '/' then
                for I in 0 .. Current_Path_Number loop
                    if Paths(I) = Inputs(2) and Entities(I).Entity = File then
                        Entities(I).File_Contents := Entities(I).File_Contents & LF & Inputs(0);
                        exit;
                    end if;
                end loop;
            else
                for I in 0 .. Current_Path_Number loop
                    if (Paths(I) = Current_Directory & "/" & Inputs(2) or Paths(I) = Current_Directory & Inputs(2)) and Entities(I).Entity = File then
                        Entities(I).File_Contents := Entities(I).File_Contents & LF & Inputs(0);
                        exit;
                    end if;
                end loop;
            end if;
        end if;
    end Echo;

end File_System;