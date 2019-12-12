with Ada.Text_IO, Ada.Numerics.Float_Random, Ada.Numerics.Discrete_Random;
use Ada.Numerics.Float_Random;

procedure Main is
	
	type Door_Range is range 1..5;

	protected Printer is
		procedure Put (S : String);
	end Printer;

	protected body Printer is
		procedure Put (S : String) is 
		begin
			Ada.Text_IO.Put_Line (S);
		end Put;
	end Printer;
	
	protected Safe_Random is
		procedure Generate (D : out Duration);
	private
		G : Generator;
		Initialised : Boolean := False;
	end Safe_Random;
	
	protected body Safe_Random is
		procedure Generate (D : out Duration) is
		begin
			if not Initialised  then
				Initialised := True;
				Reset (G);
			end if;
			D := Duration(Random (G) * 4.0);
		end Generate;
	end Safe_Random;
	
	
	task type Door (ID: Door_Range) is
		entry Open;
		entry Close;
		entry Set_Trap;
	end Door;
	type Door_Access is access Door;
	type Door_Array is array (Door_Range) of Door_Access;
	
	package Door_Random is new Ada.Numerics.Discrete_Random (Door_Range);
	
	task Burgler is
		entry Hit;
	end Burgler;
	
	task type Trap;
	type Trap_Access is access Trap;
	
	task Kevin is
		entry Catch;
	end Kevin;
	
	protected House is
		procedure Init;
		procedure Get_Door (D : out Door_Access);
		function Get_Door (Door_ID : Door_Range) return Door_Access;
	private
		Doors : Door_Array;
		G : Door_Random.Generator;
		Initialised : Boolean;
	end House;
	
	protected body House is
		procedure Init is
		begin
			for I in Door_Range loop
				Doors (I) := new Door (I);
			end loop;
			Printer.Put ("House is ready‍");
		end Init;
		
		procedure Get_Door (D : out Door_Access) is
		begin
			if not Initialised then
				Door_Random.Reset (G);
				Initialised := True;
			end if;
			D := Doors (Door_Random.Random (G));
		end Get_Door;
		
		function Get_Door (Door_ID : Door_Range) return Door_Access is 
		begin
			return Doors (Door_ID);
		end Get_Door;
	end House;
	
	task body Trap is
		Wait_Time : Duration;
	begin
		Safe_Random.Generate (Wait_Time);
		Printer.Put ("Trap fired in: " & Duration'Image(Wait_Time));
		delay Wait_Time;
		Burgler.Hit;
	exception
		when Tasking_Error => Printer.Put ("Burgler escaped");
	end Trap;
	
	task body Door is
		Is_Open : Boolean := False;
		Door_Trap : Trap_Access;
		Has_Trap : Boolean := False;
	begin
		loop
			select
				when not Is_Open => 
					accept Open;
					Is_Open := True;
					if Has_Trap then
						Door_Trap := new Trap;
					end if;
			or
				when Is_Open => 
					accept Close;
					Is_Open := False;
			or
				accept Set_Trap;
				Has_Trap := True;
			or
				terminate;
			end select;
		end loop;
	end Door;

	task body Burgler is
		My_Door : Door_Access;
	begin
		delay 3.5;
		House.Get_Door (My_Door);
		Printer.Put ("Burgler going for door #" & Door_Range'Image (My_Door.ID));
		My_Door.Open;
		Printer.Put ("Burgler inside");
		select
			accept Hit;
			Printer.Put ("Burgler hit");
		or
			delay 3.0;
			Kevin.Catch;
			My_Door.Close;
			Printer.Put ("Burgler outside with Kevin!!!");
		end select;
	end Burgler;
	
	task body Kevin is
		Is_Free : Boolean := True;
	begin
		for I in Door_Range loop
			select
				accept Catch;
				Printer.Put ("Got caught :(");
				Is_Free := False;
				exit;
			or
				delay 1.0;
			end select;
			House.Get_Door(I).Set_Trap;
			Printer.Put ("Kevin: Trap set for Door#" & Door_Range'Image (I));
		end loop;
		if Is_Free then
			select
				accept Catch;
				Printer.Put ("Got caught :(");
			or
				terminate;
			end select;
		end if;
	end Kevin;
begin
	House.Init;
end Main;