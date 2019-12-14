separate(main)
task body Plate is
begin
    Pizzeria.Get_Guest(Table).Serve;
    Ada.Text_IO.Put_Line("Serving: " & Table'Image);
    exception
        when Tasking_Error =>
            Ada.Text_IO.Put_Line("Serving: " & Table'Image & " already left.");
end Plate;