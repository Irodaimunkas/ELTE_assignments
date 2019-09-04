using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MaciLaci.Persistence
{
    public class FieldTable
    {
        private Int32 _tableSize;
        private Int32[,] _tableValues;
        private Enemies[] _enemyCoord;
        private Player _player;
        private Int32 _enemyNum;
        private Int32 _maxScore = 0;


        public Int32 MaxScore { get { return _maxScore; } }
        public Int32 EnemyNum { get { return _enemyNum; } }
        public Player Player { get { return _player; } }
        public Int32 Size { get { return _tableSize; } }
        public Int32 this[Int32 x, Int32 y] { get { return _tableValues[x, y]; } }


        public FieldTable() { _player = new Player(); }

        public void SetTableSize(Int32 val)
        {
            _tableSize = val;
            _tableValues = new Int32[_tableSize, _tableSize];
        }

        public void SetMaxScore(Int32 val) { _maxScore = val; }


        public void SetEnemiesSize(Int32 val)
        {
            _enemyCoord = new Enemies[val];
            _enemyNum = val;
            for (int i = 0; i < val; i++)
            {
                _enemyCoord[i] = new Enemies();
            }
        }

        public Enemies Enemy(Int32 val) { return _enemyCoord[val]; }

        public void SetValue(Int32 x, Int32 y, Int32 val)
        {
            _tableValues[x, y] = val;
        }
    }
}
