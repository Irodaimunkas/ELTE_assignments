with Ada.Text_IO, Ada.Strings.Unbounded, Ada.Characters.Latin_1;
use  Ada.Text_IO, Ada.Strings.Unbounded, Ada.Characters.Latin_1;

generic

    File_Size : Integer;
    Directory_Size : Integer;
    with procedure Standard_Output(Output : in String);
    with procedure Standard_Input(Input : out String);

package File_System is

    procedure Initialize;
    procedure Mkdir(Input : String);
    procedure Cd(Input : String);
    procedure Pwd;
    procedure Ls;
    procedure Touch(Input : String);
    procedure Cat(Input : String);
    procedure Echo(Input : String);

private

    procedure Reverse_Split(Input : in String; Output_One, Output_Two : out Unbounded_String);

    type Entity_Type is ( Directory, File );
    type Strings is array (Natural range <>) of Unbounded_String;

    type File_Entity(Entity : Entity_Type := Directory) is record
        Name : Unbounded_String;
        Case Entity is
            When Directory =>   Child_Files : Strings(1..Directory_Size);
                                Child_Directories : Strings(1..Directory_Size);
            When File =>        File_Contents : Unbounded_String;
        end Case;
    end record;

    type Entities_Array is array(Natural range <>) of File_Entity;

    Entities : Entities_Array(0 .. File_Size + Directory_Size);
    Paths : Strings(0 .. File_Size + Directory_Size);

    Current_Path_Number : Natural := 0;
    Current_Entity_Number : Natural := 0;

    Current_Directory : Unbounded_String := To_Unbounded_String("/");

end File_System;