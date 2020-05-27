using Microsoft.AspNetCore.Identity;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace Cinema.Persistence
{
    public class Employee : IdentityUser
    {
        [DisplayName("Real Name")]
        [Required]
        public String RealName { get; set; }
    }
}
