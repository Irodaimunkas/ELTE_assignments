using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Text;

namespace Cinema.Persistence.DTO
{
    public class ScreeningDto
    {
        [Key]
        public Int32 Id { get; set; }

        [Required]
        [DisplayName("Movie")]
        public Int32 MovieId { get; set; }

        [Required]
        [DataType(DataType.Date)]
        public DateTime StartTime { get; set; }

        [Required]
        [DisplayName("Room")]
        public Int32 RoomId { get; set; }

        public String RoomName { get; set; }

        public String MovieName { get; set; }

        public static explicit operator Screening(ScreeningDto dto) => new Screening
        {
            Id = dto.Id,
            MovieId = dto.MovieId,
            StartTime = dto.StartTime,
            RoomId = dto.RoomId
        };

        public static explicit operator ScreeningDto(Screening i) => new ScreeningDto
        {
            Id = i.Id,
            MovieId = i.MovieId,
            StartTime = i.StartTime,
            RoomId = i.RoomId
        };
    }
}
