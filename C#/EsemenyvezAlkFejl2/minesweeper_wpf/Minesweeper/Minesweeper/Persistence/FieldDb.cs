using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Minesweeper.Persistence
{
    class FieldDb
    {
        [Key]
        public Int32 Id { get; set; }
        public Int32 X { get; set; }
        public Int32 Y { get; set; }
        public Int32 Value { get; set; }
        public Boolean Visibility { get; set; }
        public FieldType FieldType { get; set; }
    }
}
