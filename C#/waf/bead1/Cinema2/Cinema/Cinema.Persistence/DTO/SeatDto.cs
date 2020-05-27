using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Text;

namespace Cinema.Persistence.DTO
{
    public class SeatDto
    {
        [Key]
        public Int32 Id { get; set; }

        [DisplayName("Screening")]
        public Int32? ScreeningId { get; set; }

        [Required]
        [DisplayName("Room")]
        public Int32 RoomId { get; set; }

        [Required]
        public Int32 Row { get; set; }

        [Required]
        public Int32 Column { get; set; }

        [Required]
        public Status Status { get; set; }

        [MaxLength(30)]
        public String BookerName { get; set; }

        [Display(Name = "Phone")]
        [DataType(DataType.PhoneNumber)]
        public String PhoneNumber { get; set; }

        public static explicit operator Seat(SeatDto dto) => new Seat
        {
            Id = dto.Id,
            ScreeningId = dto.ScreeningId,
            RoomId = dto.RoomId,
            Row = dto.Row,
            Column = dto.Column,
            Status = dto.Status,
            BookerName = dto.BookerName,
            PhoneNumber = dto.PhoneNumber
        };

        public static explicit operator SeatDto(Seat i) => new SeatDto
        {
            Id = i.Id,
            ScreeningId = i.ScreeningId,
            RoomId = i.RoomId,
            Row = i.Row,
            Column = i.Column,
            Status = i.Status,
            BookerName = i.BookerName,
            PhoneNumber = i.PhoneNumber
        };
    }
}
