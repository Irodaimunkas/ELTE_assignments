using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace Cinema.Models
{
    public class Movie
    {
        [Key]
        public Int32 Id { get; set; }

        [Required]
        public String Name { get; set; }

        [Required]
        public String Director { get; set; }

        [DataType(DataType.MultilineText)]
        public String Synopsis { get; set; }

        [Required]
        [DisplayName("Length")]
        public Int32 LengthInMinutes { get; set; }

        public byte[] Image { get; set; }

        [Required]
        [DataType(DataType.Date)]
        public DateTime PostTime { get; set; }
    }
}
