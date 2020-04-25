using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace Cinema.Models
{
    public class SeatsViewModel
    {
        public const Int32 MAX_COL_NUMBER = 100;
        public const Int32 MAX_ROW_NUMBER = 100;

        [Required]
        public Status[][] Seats { get; set; }

        [DisplayName("Screening")]
        public Int32 ScreeningId { get; set; }

        [DisplayName("Room")]
        public Int32 RoomId { get; set; }

        [MaxLength(30)]
        public String BookerName { get; set; }

        [Display(Name = "Phone")]
        [DataType(DataType.PhoneNumber)]
        public String PhoneNumber { get; set; }

        public SeatsViewModel()
        {
            Seats = new Status[MAX_ROW_NUMBER][];
            for(Int32 i = 0; i < Seats.Length; i++)
            {
                Seats[i] = new Status[MAX_COL_NUMBER];
            }
        }
    }
}
