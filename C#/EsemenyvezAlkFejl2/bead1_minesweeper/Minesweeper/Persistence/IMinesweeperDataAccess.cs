using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Minesweeper.Model;

namespace Minesweeper.Persistence
{
    public interface IMinesweeperDataAccess
    {
        /*
        private Player _currPlayer = Player.PLAYER_ONE;
        private Field[,] _map;
        private Int32 _size;
        */
        Task<MinesweeperTable> LoadAsync(String path);
        Task SaveAsync(String path, MinesweeperTable gameTable);
    }
}
