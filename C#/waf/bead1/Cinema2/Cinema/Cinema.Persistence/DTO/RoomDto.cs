using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Text;

namespace Cinema.Persistence.DTO
{
    public class RoomDto
    {
        [Key]
        public Int32 Id { get; set; }

        [Required]
        [MaxLength(15)]
        public String Name { get; set; }

        [Required]
        public Int32 Rows { get; set; }

        [Required]
        public Int32 Columns { get; set; }

        public static explicit operator Room(RoomDto dto) => new Room
        {
            Id = dto.Id,
            Name = dto.Name,
            Rows = dto.Rows,
            Columns = dto.Columns
        };

        public static explicit operator RoomDto(Room i) => new RoomDto
        {
            Id = i.Id,
            Name = i.Name,
            Rows = i.Rows,
            Columns = i.Columns
        };
    }
}
