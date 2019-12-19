using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Minesweeper.Model;
using Minesweeper.Persistence;
using Moq;
using System.Threading.Tasks;

namespace MinesweeperTest
{
    [TestClass]
    public class MinesweeperTest
    {
        private MinesweeperModel _model;
        Mock<IMinesweeperDataAccess> _mock;
        Field[,] _mockField;

        /* mock field
          1 -1 4 -1 3 1
          2 3 -1 -1 3 -1
          -1 3 3 3 4 2 
          -1 3 1 -1 2 -1 
          -1 2 1 1 2 1 
          1 1 0 0 0 0
         */

        [TestInitialize]
        public void Initialize()
        {
            _mock = new Mock<IMinesweeperDataAccess>();
            _mock.Setup(_mock => _mock.LoadAsync(It.IsAny<string>())).Returns(
                Task.FromResult(new MinesweeperTable(6))
            );
            _mock.Setup(_mock => _mock.SaveAsync(It.IsAny<String>(), new MinesweeperTable(6)));

            _model = new MinesweeperModel(_mock.Object);
            _mockField = new Field[,] {
                {
                    new Field { value = 1, fieldType = FieldType.NOT_BOMB, visible = false, },
                    new Field { value = -1, fieldType = FieldType.BOMB, visible = false, },
                    new Field { value = 4, fieldType = FieldType.NOT_BOMB, visible = false, },
                    new Field { value = -1, fieldType = FieldType.BOMB, visible = false, },
                    new Field { value = 3, fieldType = FieldType.NOT_BOMB, visible = false, },
                    new Field { value = 1, fieldType = FieldType.NOT_BOMB, visible = false, },
                },
                {
                    new Field { value = 2, fieldType = FieldType.NOT_BOMB, visible = false, },
                    new Field { value = 3, fieldType = FieldType.NOT_BOMB, visible = false, },
                    new Field { value = -1, fieldType = FieldType.BOMB, visible = false, },
                    new Field { value = -1, fieldType = FieldType.BOMB, visible = false, },
                    new Field { value = 3, fieldType = FieldType.NOT_BOMB, visible = false, },
                    new Field { value = -1, fieldType = FieldType.BOMB, visible = false, },
                },
                {
                    new Field { value = -1, fieldType = FieldType.BOMB, visible = false, },
                    new Field { value = 3, fieldType = FieldType.NOT_BOMB, visible = false, },
                    new Field { value = 3, fieldType = FieldType.NOT_BOMB, visible = false, },
                    new Field { value = 3, fieldType = FieldType.NOT_BOMB, visible = false, },
                    new Field { value = 4, fieldType = FieldType.NOT_BOMB, visible = false, },
                    new Field { value = 2, fieldType = FieldType.NOT_BOMB, visible = false, },
                },
                {
                    new Field { value = -1, fieldType = FieldType.BOMB, visible = false, },
                    new Field { value = 3, fieldType = FieldType.NOT_BOMB, visible = false, },
                    new Field { value = 1, fieldType = FieldType.NOT_BOMB, visible = false, },
                    new Field { value = -1, fieldType = FieldType.BOMB, visible = false, },
                    new Field { value = 2, fieldType = FieldType.NOT_BOMB, visible = false, },
                    new Field { value = -1, fieldType = FieldType.BOMB, visible = false, },
                },
                {
                    new Field { value = -1, fieldType = FieldType.BOMB, visible = false, },
                    new Field { value = 2, fieldType = FieldType.NOT_BOMB, visible = false, },
                    new Field { value = 1, fieldType = FieldType.NOT_BOMB, visible = false, },
                    new Field { value = 1, fieldType = FieldType.NOT_BOMB, visible = false, },
                    new Field { value = 2, fieldType = FieldType.NOT_BOMB, visible = false, },
                    new Field { value = 1, fieldType = FieldType.NOT_BOMB, visible = false, },
                },
                {
                    new Field { value = 1, fieldType = FieldType.NOT_BOMB, visible = false, },
                    new Field { value = 1, fieldType = FieldType.NOT_BOMB, visible = false, },
                    new Field { value = 0, fieldType = FieldType.NOT_BOMB, visible = false, },
                    new Field { value = 0, fieldType = FieldType.NOT_BOMB, visible = false, },
                    new Field { value = 0, fieldType = FieldType.NOT_BOMB, visible = false, },
                    new Field { value = 0, fieldType = FieldType.NOT_BOMB, visible = false, },
                },
            };
        }
        [TestMethod]
        public void MinesweeperModelNewGameTest()
        {
            _model.NewGame(6);
            Assert.AreEqual(6, _model.Size);
        }

        [TestMethod]
        public void MinesweeperModelStepTest()
        {
            _model.NewGame(6);
            _model.Map = _mockField;
            _model.Step(0, 0);
            Assert.AreEqual(1, _model.Map[0, 0].value);
            for(Int32 i = 0; i < _model.Size; i++)
            {
                for(Int32 j = 0; j < _model.Size; j++)
                {
                    if(i == 0 && j == 0) Assert.AreEqual(true, _model.Map[i, j].visible);
                    else Assert.AreEqual(false, _model.Map[i, j].visible);
                }
            }
        }

        [TestMethod]
        public void MinesweeperModelTurnOverAroundZeroTest()
        {
            _model.NewGame(6);
            _model.Map = _mockField;
            _model.Step(5, 5);
            Assert.AreEqual(0, _model.Map[5, 2].value);
            Assert.AreEqual(true, _model.Map[5, 2].visible);
            Assert.AreEqual(0, _model.Map[5, 3].value);
            Assert.AreEqual(true, _model.Map[5, 3].visible);
            Assert.AreEqual(0, _model.Map[5, 4].value);
            Assert.AreEqual(true, _model.Map[5, 4].visible);
            Assert.AreEqual(0, _model.Map[5, 5].value);
            Assert.AreEqual(true, _model.Map[5, 5].visible);
        }

        [TestMethod]
        public void MinesweeperModelGenerateMapTest()
        {
            _model.NewGame(6);
            Assert.AreEqual(6, _model.Map.GetLength(0));
            Assert.AreEqual(6, _model.Map.GetLength(1));
        }
    }
}
