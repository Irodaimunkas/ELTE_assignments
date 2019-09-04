using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using MaciLaci.Model;
using MaciLaci.Persistence;
namespace MaciLaciTest
{
    [TestClass]
    public class MaciLaciModelTest
    {
        private MaciLaciModel _model;
        private IMapLoad _dataAccess;

        [TestInitialize]
        public void Initialize()
        {
            _dataAccess = new MapLoad();
            _model = new MaciLaciModel();

            _dataAccess.LoadMap("..\\..\\..\\..\\med.txt", _model.Table);
        }

        [TestMethod]
        public void _timer_TickTest()
        {
            Int32[] x_b, y_b, x_a, y_a;
            x_b = new Int32[_model.Table.EnemyNum];
            y_b = new Int32[_model.Table.EnemyNum];
            x_a = new Int32[_model.Table.EnemyNum];
            y_a = new Int32[_model.Table.EnemyNum];

            for (int i = 0; i < _model.Table.EnemyNum; i++)
            {
                x_b[i] = _model.Table.Enemy(i).GetX;
                y_b[i] = _model.Table.Enemy(i).GetY;
            }

            _model.OnTimer();

            //added one to the game timer
            Assert.AreNotEqual(_model.GameTime, 0);

            for (int i = 0; i < _model.Table.EnemyNum; i++)
            {
                x_a[i] = _model.Table.Enemy(i).GetX;
                y_a[i] = _model.Table.Enemy(i).GetY;
            }

            //on a medium map, the first enemy moves down first,
            //and the second and third moves to the right
            Assert.AreNotEqual(x_a[0], x_b[0]);
            Assert.AreNotEqual(y_a[1], y_b[1]);
            Assert.AreNotEqual(y_a[2], y_b[2]);
        }

        [TestMethod]
        public void KeyDownEvent()
        {
            _model.OnTimer();

            Int32 x1 = _model.Table.Player.GetX;
            Int32 y1 = _model.Table.Player.GetY;

            _model.OnKeyPressed(x1, y1, System.Windows.Forms.Keys.Right);

            Int32 x2 = _model.Table.Player.GetX;
            Int32 y2 = _model.Table.Player.GetY;

            Assert.AreNotEqual(y1, y2);

            _model.OnKeyPressed(x2, y2, System.Windows.Forms.Keys.Left);

            x2 = _model.Table.Player.GetX;
            y2 = _model.Table.Player.GetY;

            _model.OnKeyPressed(x2, y2, System.Windows.Forms.Keys.Down);

            x2 = _model.Table.Player.GetX;
            y2 = _model.Table.Player.GetY;

            Assert.AreNotEqual(x1, x2);
        }
    }
}
