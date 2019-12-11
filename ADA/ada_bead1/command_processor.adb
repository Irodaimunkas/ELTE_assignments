package body Command_Processor is

    procedure Split(Input : in String; Output_One, Output_Two : out Unbounded_String) is
        Counter : Integer := 1;
    begin
        while Input(Counter) /= ' ' and Counter /= Input'Last loop
            Counter := Counter + 1;
        end loop;

        if(Counter = Input'Last) then
            Output_One := To_Unbounded_String(Input(Input'First .. Counter));
            return;
        end if;

        Output_One := To_Unbounded_String(Input(Input'First .. Counter - 1));
        Output_Two := To_Unbounded_String(Input(Counter + 1 .. Input'Last));
    end Split;

    procedure Process_Command (Full_Command : String) is
        Output_One, Output_Two : Unbounded_String;
        Command : Commands := Exit_Cmd;
    begin
        Split(Full_Command, Output_One, Output_Two);

        if(To_String(Output_One) = "mkdir") then
            Command := Mkdir;
        elsif(To_String(Output_One) = "cd") then
            Command := Cd;
        elsif(To_String(Output_One) = "pwd") then
            Command := Pwd;
        elsif(To_String(Output_One) = "ls") then
            Command := Ls;
        elsif(To_String(Output_One) = "touch") then
            Command := Touch;
        elsif(To_String(Output_One) = "cat") then
            Command := Cat;
        elsif(To_String(Output_One) = "echo") then
            Command := Echo;
        elsif(To_String(Output_One) = "exit") then
            Command := Exit_Cmd;
        end if;

        Case Command is
            When Mkdir =>   Command_Mkdir(To_String(Output_Two));
            When Cd =>      Command_Cd(To_String(Output_Two));
            When Pwd =>     Command_Pwd;
            When Ls =>      Command_Ls;
            When Touch =>   Command_Touch(To_String(Output_Two));
            When Cat =>     Command_Cat(To_String(Output_Two));
            When Echo =>    Command_Echo(To_String(Output_Two));
            When Exit_Cmd =>null;
        end Case;
    end Process_Command;

    procedure Run_Terminal is 
        Input : Unbounded_String;
    begin
        My_File_System.Initialize;
        loop
            Input := To_Unbounded_String(Get_Line);

            Process_Command(To_String(Input));

            exit when To_String(Input) = "exit";
        end loop;
    end Run_Terminal;

    procedure Command_Mkdir (Arguments: String) is

    begin
        My_File_System.Mkdir(Arguments);
    end Command_Mkdir;

    procedure Command_Cd (Arguments: String) is

    begin
        My_File_System.Cd(Arguments);
    end Command_Cd;

    procedure Command_Pwd is

    begin
        My_File_System.Pwd;
    end Command_Pwd;

    procedure Command_Ls is

    begin
        My_File_System.Ls;
    end Command_Ls;

    procedure Command_Touch (Arguments: String) is

    begin
       My_File_System.Touch(Arguments);
    end Command_Touch;

    procedure Command_Cat (Arguments: String) is 

    begin
        My_File_System.Cat(Arguments);
    end Command_Cat;

    procedure Command_Echo (Arguments: String) is

    begin
        My_File_System.Echo(Arguments);
    end Command_Echo;

end Command_Processor;