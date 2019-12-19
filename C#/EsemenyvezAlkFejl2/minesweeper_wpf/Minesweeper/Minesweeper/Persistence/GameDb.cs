using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Minesweeper.Persistence
{
    class GameDb
    {
        [Key]
        public String Name { get; set; }
        public Int32 MapSize { get; set; }
        public Player Player { get; set; }
        public DateTime Time { get; set; }
        public ICollection<FieldDb> Fields { get; set; }
        public GameDb()
        {
            Fields = new List<FieldDb>();
            Time = DateTime.Now;
        }
    }
}
