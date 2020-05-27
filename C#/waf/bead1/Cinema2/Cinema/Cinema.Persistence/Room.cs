using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace Cinema.Persistence
{
    public class Room
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
    }
}
