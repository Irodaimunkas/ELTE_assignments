using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Minesweeper.Persistence;

namespace Minesweeper.Model
{
    public class MinesweeperEventArgs : EventArgs
    {
        private Player _player;
        public Player Player { get { return _player;  } }
        public MinesweeperEventArgs(Player player)
        {
            _player = player;
        }
    }
}
