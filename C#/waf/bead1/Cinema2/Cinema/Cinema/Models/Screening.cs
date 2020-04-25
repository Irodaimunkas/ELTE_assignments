using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace Cinema.Models
{
    public class Screening
    {
        [Key]
        public Int32 Id { get; set; }

        [Required]
        [DisplayName("Movie")]
        public Int32 MovieId { get; set; }

        public virtual Movie Movie { get; set; }

        [Required]
        [DataType(DataType.Date)]
        public DateTime StartTime { get; set; }

        [Required]
        [DisplayName("Room")]
        public Int32 RoomId { get; set; }

        public virtual Room Room { get; set; }
    }
}
