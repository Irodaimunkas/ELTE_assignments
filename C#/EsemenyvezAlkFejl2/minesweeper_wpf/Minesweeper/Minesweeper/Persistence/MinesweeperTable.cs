using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Minesweeper.Persistence
{
    public enum Player { PLAYER_ONE, PLAYER_TWO };
    public enum FieldType { BOMB, NOT_BOMB };
    public struct Field
    {
        public Int32 value;
        public FieldType fieldType;
        public Boolean visible;
    }

    public class MinesweeperTable
    {
        private Player _currPlayer = Player.PLAYER_ONE;
        private Field[,] _map;
        private Int32 _size;

        public Player CurrPlayer { get => _currPlayer; set => _currPlayer = value; }
        public Field[,] Map { get => _map; set => _map = value; }
        public int Size { get => _size; set => _size = value; }

        public MinesweeperTable(Int32 size)
        {
            _size = size;
            _map = new Field[_size, _size];
        }
    }
}
