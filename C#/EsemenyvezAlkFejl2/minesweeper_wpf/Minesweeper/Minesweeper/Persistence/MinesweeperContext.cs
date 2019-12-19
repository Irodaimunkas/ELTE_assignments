using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Minesweeper.Persistence
{
    class MinesweeperContext : DbContext
    {
        public MinesweeperContext(String connection)
            : base(connection)
        {
        }

        public DbSet<GameDb> Games { get; set; }

        public DbSet<FieldDb> Fields { get; set; }
    }
}
