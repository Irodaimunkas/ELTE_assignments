using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MaciLaci.Persistence
{
    public class Player
    {
        private Int32 _x;
        private Int32 _y;


        public Int32 GetX { get { return _x; } }
        public Int32 GetY { get { return _y; } }


        public Player()
        {
            _x = 0;
            _y = 0;
        }

        public void setXY(Int32 x, Int32 y)
        {
            _x = x;
            _y = y;
        }
    }
}
