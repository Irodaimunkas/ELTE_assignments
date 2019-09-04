using MaciLaci.Persistence;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MaciLaci.Model
{
    public class MaciLaciModel
    {
        private FieldTable _table;
        private Int32 _score;
        private Double _gameTime = 0;

        //properties
        public Double GameTime { get { return _gameTime; } }
        public Int32 Score { get { return _score; } }
        public FieldTable Table { get { return _table; } }

        //events
        public event EventHandler GameWon;
        public event EventHandler GameLost;


        public MaciLaciModel()
        {
            _table = new FieldTable();
        }

        public void NewGame()
        {
            _table = new FieldTable();
            _gameTime = 0;
        }
        
        public void OnKeyPressed(Int32 x, Int32 y, System.Windows.Forms.Keys key)
        {
            // 1 represents obstacles
            if (key == System.Windows.Forms.Keys.Up)
            {
                if (x - 1 != -1 && _table[x - 1, y] != 1) _table.Player.setXY(x - 1, y);
            }
            else if (key == System.Windows.Forms.Keys.Down)
            {
                if (x + 1 < _table.Size && _table[x + 1, y] != 1) _table.Player.setXY(x + 1, y);
            }
            else if (key == System.Windows.Forms.Keys.Left)
            {
                if (y - 1 != -1 && _table[x, y - 1] != 1) _table.Player.setXY(x, y - 1);
            }
            else if (key == System.Windows.Forms.Keys.Right)
            {
                if (y + 1 < _table.Size && _table[x, y + 1] != 1) _table.Player.setXY(x, y + 1);
            }

            //3 represents baskets
            if (_table[_table.Player.GetX, _table.Player.GetY] == 3) _score++;

            //if game is won, emitting game won signal
            if (_score == _table.MaxScore)
            {
                EventArgs e;
                e = new EventArgs();
                GameWon(this, e);
            }

            for (int i = 0; i < _table.EnemyNum; i++)
            {
                Int32 e_x = _table.Enemy(i).GetX;
                Int32 e_y = _table.Enemy(i).GetY;

                Int32 p_x = _table.Player.GetX;
                Int32 p_y = _table.Player.GetY;

                //if players coordinate is around one of the enemies coordinates,
                //emitting game lost signal
                if (p_x == e_x + 1 && p_y == e_y + 1 ||
                    p_x == e_x + 1 && p_y == e_y - 1 ||
                    p_x == e_x - 1 && p_y == e_y - 1 ||
                    p_x == e_x - 1 && p_y == e_y + 1 ||
                    p_x == e_x + 1 && p_y == e_y ||
                    p_x == e_x - 1 && p_y == e_y ||
                    p_x == e_x && p_y == e_y + 1 ||
                    p_x == e_x && p_y == e_y - 1
                    )
                {
                    EventArgs e;
                    e = new EventArgs();
                    GameLost(this, e);
                    return;
                }
            }
        }

        public void OnTimer()
        {
            Int32 x, y;
            for (int i = 0; i < _table.EnemyNum; i++)
            {
                x = _table.Enemy(i).GetX;
                y = _table.Enemy(i).GetY;
                
                //7 represents horizontal movement
                if (_table.Enemy(i).Dir == 7)
                {
                    if (_table.Enemy(i).LRUP == 'r')
                    {
                        if (y + 1 < _table.Size && _table[x, y + 1] != 1) _table.Enemy(i).setXY(x, y + 1);
                        //if enemy reached a wall or obstacle,
                        //set its movement to reverse
                        else
                        {
                            _table.Enemy(i).setXY(x, y - 1);
                            _table.Enemy(i).SetLRUP('l');
                        }
                    }
                    else
                    {
                        if (y - 1 >= 0 && _table[x, y - 1] != 1) _table.Enemy(i).setXY(x, y - 1);
                        //if enemy reached a wall or obstacle,
                        //set its movement to reverse
                        else
                        {
                            _table.Enemy(i).setXY(x, y + 1);
                            _table.Enemy(i).SetLRUP('r');
                        }
                    }
                }
                //8 would represent vertical movement
                else
                {
                    if (_table.Enemy(i).LRUP == 'u')
                    {
                        if (x - 1 >= 0 && _table[x - 1, y] != 1) _table.Enemy(i).setXY(x - 1, y);
                        //if enemy reached a wall or obstacle,
                        //set its movement to reverse
                        else
                        {
                            _table.Enemy(i).setXY(x + 1, y);
                            _table.Enemy(i).SetLRUP('d');
                        }
                    }
                    else
                    {
                        if (x + 1 < _table.Size && _table[x + 1, y] != 1) _table.Enemy(i).setXY(x + 1, y);
                        //if enemy reached a wall or obstacle,
                        //set its movement to reverse
                        else
                        {
                            _table.Enemy(i).setXY(x - 1, y);
                            _table.Enemy(i).SetLRUP('u');
                        }
                    }
                }
            }
            //adding 1 to the game time
            _gameTime++;


            //checking if an enemy got too close (radious 1) to the player,
            //if one of the enemies did, emitting game lost signal
            for (int i = 0; i < _table.EnemyNum; i++)
            {
                Int32 e_x = _table.Enemy(i).GetX;
                Int32 e_y = _table.Enemy(i).GetY;

                Int32 p_x = _table.Player.GetX;
                Int32 p_y = _table.Player.GetY;

                if (p_x == e_x + 1 && p_y == e_y + 1 ||
                    p_x == e_x + 1 && p_y == e_y - 1 ||
                    p_x == e_x - 1 && p_y == e_y - 1 ||
                    p_x == e_x - 1 && p_y == e_y + 1 ||
                    p_x == e_x + 1 && p_y == e_y ||
                    p_x == e_x - 1 && p_y == e_y ||
                    p_x == e_x && p_y == e_y + 1 ||
                    p_x == e_x && p_y == e_y - 1
                    )
                {
                    EventArgs e;
                    e = new EventArgs();
                    GameLost(this, e);
                    return;
                }
            }
        }

    }
}
