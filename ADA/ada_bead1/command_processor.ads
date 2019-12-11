with File_System, Ada.Text_IO, Ada.Strings.Unbounded, Ada.Strings.Fixed;
use Ada.Text_IO, Ada.Strings.Unbounded, Ada.Strings.Fixed;

generic

    Max_File_Size : Integer;
    Max_Directory_Size : Integer;

    with procedure Standard_Output(Output : in String);
    with procedure Standard_Input(Input : out String);

package Command_Processor is

    procedure Process_Command (Full_Command : String); 
    procedure Run_Terminal;
    procedure Split(Input : in String; Output_One, Output_Two : out Unbounded_String);

    package My_File_System is new File_System(
        File_Size => Max_File_Size,
        Directory_Size => Max_Directory_Size,
        Standard_Output => Ada.Text_IO.Put_Line,
        Standard_Input => Ada.Text_IO.Get
    );

    private

    type Commands is ( Mkdir, Cd, Pwd, Ls, Touch, Cat, Echo, Exit_Cmd);

    procedure Command_Mkdir (Arguments: String);
    procedure Command_Cd (Arguments: String);
    procedure Command_Pwd;
    procedure Command_Ls;
    procedure Command_Touch (Arguments: String);
    procedure Command_Cat (Arguments: String);
    procedure Command_Echo (Arguments: String);

end Command_Processor;