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

        [TestInitialize]
        public void Initialize()
        {
            _mock = new Mock<IMinesweeperDataAccess>();
            _mock.Setup(_mock => _mock.LoadAsync(It.IsAny<string>())).Returns(
                Task.FromResult(new MinesweeperTable(6))
            );
            _mock.Setup(_mock => _mock.SaveAsync(It.IsAny<String>(), new MinesweeperTable(6)));

            _model = new MinesweeperModel(_mock.Object);
        }
    }
}
