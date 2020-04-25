using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace Cinema.Models
{
    public class Employee
    {
        [Key] 
        public Int32 Id { get; set; }

        [DisplayName("Real Name")]
        [Required]
        public String RealName { get; set; }

        [DisplayName("Username")]
        [Required]
        public String UserName { get; set; }

        [Required]
        [DisplayName("Password")]
        [DataType(DataType.Password)]
        public String Password { get; set; }
    }
}
