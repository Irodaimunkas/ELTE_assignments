using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace Cinema.Models
{
    public enum Status { Sold, Free, Booked }
    public class Seat
    {
        [Key]
        public Int32 Id { get; set; }

        [DisplayName("Screening")]
        public Int32? ScreeningId { get; set; }

        public virtual Screening Screening { get; set; }

        [Required]
        [DisplayName("Room")]
        public Int32 RoomId { get; set; }

        public virtual Room Room { get; set; }

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
    }
}
