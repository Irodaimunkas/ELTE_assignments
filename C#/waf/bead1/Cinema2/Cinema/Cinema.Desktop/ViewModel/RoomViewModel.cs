using Cinema.Persistence.DTO;
using System;

namespace Cinema.Desktop.ViewModel
{
    public class RoomViewModel : ViewModelBase
    {
        public Int32 Id { get; set; }

        public String Name { get; set; }

        public static explicit operator RoomViewModel(RoomDto dto) => new RoomViewModel
        {
            Id = dto.Id,
            Name = dto.Name
        };

        public static explicit operator RoomDto(RoomViewModel i) => new RoomDto
        {
            Id = i.Id,
            Name = i.Name
        };
    }
}