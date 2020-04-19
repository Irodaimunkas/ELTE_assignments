using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace TodoList.Web.ViewModel
{
    public class RegisterViewModel
    {
        [Required]
        [DataType(DataType.Password)]
        public String Password { get; set; }

        [Required]
        public String UserName { get; set; }

        [Required]
        [DataType(DataType.Password)]
        [Compare("Password")]
        public String PasswordConfirm { get; set; }
    }
}
