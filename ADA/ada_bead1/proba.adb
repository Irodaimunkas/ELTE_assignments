Reverse_Split(Input, Output_One, Output_Two);

        Current_Path_Number := Current_Path_Number + 1;

        if Input(Input'First) = '/' then
            for I in 1 .. Current_Path_Number loop
                if Paths(I) = To_Unbounded_String(Input) then
                    Standard_Output("Error: File already exists");
                    return;
                end if;
            end loop;

            Paths(Current_Path_Number) := To_Unbounded_String("/") & To_Unbounded_String(Input);
        else    
            for I in 1 .. Current_Path_Number loop
                if Paths(I) = Current_Directory & To_Unbounded_String(Input) then
                    Standard_Output("Error: File already exists");
                    return;
                end if;
            end loop;

            if Current_Directory = "/" then
                Paths(Current_Path_Number) := Current_Directory & To_Unbounded_String(Input);
            else
                if Input(Input'First) /= "/" then
                    Paths(Current_Path_Number) := Current_Directory & "/" & To_Unbounded_String(Input);
                else
                    Paths(Current_Path_Number) := To_Unbounded_String(Input);
                end if;
            end if;
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
        if Input(Input'First) = '/' then
            for I in 1 .. Current_Path_Number loop
                if Paths(I) = Output_One then
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
            for I in 1 .. Current_Path_Number loop
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
        end if;