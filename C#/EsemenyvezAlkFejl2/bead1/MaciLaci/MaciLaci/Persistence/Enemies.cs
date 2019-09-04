using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MaciLaci.Persistence
{
    public class Enemies
    {
        private Int32 _x;
        private Int32 _y;
        private Int32 _dir;
        private char _lrup;
        

        public Int32 GetX { get { return _x; } }
        public Int32 GetY { get { return _y; } }
        public Int32 Dir { get { return _dir; } }
        public char LRUP { get { return _lrup; } }


        public void setXY(Int32 x, Int32 y)
        {
            _x = x;
            _y = y;
        }

        public void SetDir(Int32 val) { _dir = val; }

        public void SetLRUP(char c) { _lrup = c; }
        
    }
}
