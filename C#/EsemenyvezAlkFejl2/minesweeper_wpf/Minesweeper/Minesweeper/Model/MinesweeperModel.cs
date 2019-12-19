using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Minesweeper.Persistence;

namespace Minesweeper.Model
{

    public class MinesweeperModel
    {
        private IMinesweeperDataAccess _dataAccess;
        private MinesweeperTable _gameTable;

        public Int32 Size { get => _gameTable.Size; set => _gameTable.Size = value; }
        public Player CurrPlayer { get => _gameTable.CurrPlayer; set => _gameTable.CurrPlayer = value; }
        public Field[,] Map { get => _gameTable.Map; set => _gameTable.Map = value; }


        public event EventHandler<MinesweeperEventArgs> PlayerLost;
        public event EventHandler Draw;

        public MinesweeperModel(IMinesweeperDataAccess dataAccess)
        {
            _dataAccess = dataAccess;
        }

        public void NewGame(Int32 size)
        {
            _gameTable = new MinesweeperTable(size);
            GenerateMap();
        }

        public void Step(Int32 x, Int32 y)
        {
            if (!_gameTable.Map[x, y].visible)
            {
                if ( _gameTable.CurrPlayer == Player.PLAYER_ONE)
                {
                    _gameTable.CurrPlayer = Player.PLAYER_TWO;
                }
                else
                {
                    _gameTable.CurrPlayer = Player.PLAYER_ONE;
                }
                _gameTable.Map[x, y].visible = true;
                if (_gameTable.Map[x, y].fieldType == FieldType.BOMB)
                {
                    PlayerLost(this, new MinesweeperEventArgs(_gameTable.CurrPlayer));
                } else if(_gameTable.Map[x,y].value == 0)
                {
                    TurnOverAroundZero(x, y);
                }

                Boolean draw = true;
                Int32 i, j;
                i = j = 0;
                while(i < _gameTable.Size && draw)
                {
                    j = 0;
                    while(j < _gameTable.Size && draw)
                    {
                        if (!_gameTable.Map[i, j].visible && _gameTable.Map[i, j].fieldType != FieldType.BOMB)
                        {
                            draw = false;
                        }
                        j++;
                    }
                    i++;
                }
                if (draw)
                {
                    Draw(this, new EventArgs());
                }
            }
        }
        public async Task LoadGameAsync(String path)
        {
            _gameTable = await _dataAccess.LoadAsync(path);
        }

        public async Task SaveGameAsync(String path)
        {
            await _dataAccess.SaveAsync(path, _gameTable);
        }

        private void TurnOverAroundZero(int i, int j)
        {
            for(int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    if (i + x >= 0 && i + x < _gameTable.Size && j + y >= 0 && j + y < _gameTable.Size && _gameTable.Map[i + x, j + y].value != 0)
                    {
                        _gameTable.Map[i + x, j + y].visible = true;
                    }
                    else if (i + x >= 0 && i + x < _gameTable.Size && j + y >= 0 && j + y < _gameTable.Size && !_gameTable.Map[i + x, j + y].visible)
                    {
                        _gameTable.Map[i + x, j + y].visible = true;
                        TurnOverAroundZero(i + x, j + y);
                    }
                }
            }
        }

        private void GenerateMap()
        {
            Int32 counter = 0;
            switch (_gameTable.Size)
            {
                case 6:
                    counter = 10;
                    break;
                case 10:
                    counter = 40;
                    break;
                case 16:
                    counter = 99;
                    break;
            }
            //counter = 2;
            Random rnd = new Random();
            for (Int32 i = 0; i < _gameTable.Size; i++)
            {
                for (Int32 j = 0; j < _gameTable.Size; j++)
                {
                    _gameTable.Map[i, j].visible = false;
                    _gameTable.Map[i, j].value = rnd.Next(-1, 2);
                    if(_gameTable.Map[i, j].value == -1 && counter > 0)
                    {
                        _gameTable.Map[i, j].fieldType = FieldType.BOMB;
                        counter--;
                    }
                    else
                    {
                        _gameTable.Map[i, j].fieldType = FieldType.NOT_BOMB;
                    }
                }
            }
            for (Int32 i = 0; i < _gameTable.Size; i++)
            {
                for (Int32 j = 0; j < _gameTable.Size; j++)
                {
                    if (_gameTable.Map[i, j].fieldType != FieldType.BOMB)
                    {
                        _gameTable.Map[i, j].value = 0;

                        for (int x = -1; x < 2; x++)
                        {
                            for (int y = -1; y < 2; y++)
                            {
                                if (i + x >= 0 && i + x < _gameTable.Size && j + y >= 0 && j + y < _gameTable.Size && _gameTable.Map[i + x, j + y].fieldType == FieldType.BOMB)
                                {
                                    _gameTable.Map[i, j].value++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
