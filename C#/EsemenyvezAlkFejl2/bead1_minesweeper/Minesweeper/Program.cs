using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Minesweeper
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Minesweeper _minesweeper;
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            _minesweeper = new Minesweeper();
            _minesweeper.FormBorderStyle = FormBorderStyle.FixedDialog;
            _minesweeper.MaximizeBox = false;
            _minesweeper.MinimizeBox = false;
            _minesweeper.Size = new System.Drawing.Size(360 - 35, 30 + 360);
            _minesweeper.StartPosition = FormStartPosition.CenterScreen;
            Application.Run(_minesweeper);
        }
    }
}
