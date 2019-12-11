with Command_Processor, Ada.Text_IO;

procedure Main is

package My_Command_Processor is new Command_Processor(
    Max_File_Size => 100,
    Max_Directory_Size => 100,
    Standard_Output => Ada.Text_IO.Put_Line,
    Standard_Input => Ada.Text_IO.Get
);

begin
    My_Command_Processor.Run_Terminal;
end Main;