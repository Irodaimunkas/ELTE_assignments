using MaciLaci.Model;
using MaciLaci.Persistence;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MaciLaci
{
    public partial class MaciLaciForm : Form
    {

        private IMapLoad _dataAccess;
        private MaciLaciModel _model;
        private Label[,] _labelGrid;
        private string _gameModePath = "..\\..\\..\\..\\med.txt";
        private Int32 _width = 375;
        private Int32 _height = 440;

        public MaciLaciForm()
        {
            InitializeComponent();
        }
        
        private void GenerateTable()
        {
            _labelGrid = new Label[_model.Table.Size, _model.Table.Size];
            for (Int32 i = 0; i < _model.Table.Size; i++)
                for (Int32 j = 0; j < _model.Table.Size; j++)
                {

                    _labelGrid[i, j] = new Label();
                    _labelGrid[i, j].Location = new Point(5 + 50 * j, 25 + 50 * i); // elhelyezkedés
                    _labelGrid[i, j].Size = new Size(50, 50); // méret
                    _labelGrid[i, j].Enabled = false; // kikapcsolt állapot
                    _labelGrid[i, j].FlatStyle = FlatStyle.Flat; // lapított stípus
                    _labelGrid[i, j].BackColor = Color.White;
                    _labelGrid[i, j].BorderStyle = BorderStyle.FixedSingle;

                    if (_model.Table[i, j] == 2)
                    {
                        _labelGrid[i, j].BackColor = Color.Black;
                    }
                    if (_model.Table[i, j] == 3) _labelGrid[i, j].BackColor = Color.Pink;
                    if (_model.Table[i, j] == 1) _labelGrid[i, j].BackColor = Color.Green;
                    if (_model.Table[i, j] == 9)
                    {
                        _labelGrid[i, j].BackColor = Color.Brown;
                    }

                    Controls.Add(_labelGrid[i, j]);
                    // felevesszük az ablakra a gombot
                }
        }

        //clearing table of labels for new game
        private void ClearTable()
        {
            foreach (Label label in _labelGrid)
            {
                Controls.Remove(label);
            }
        }

        private void MaciLaciForm_Load(object sender, EventArgs e)
        {

            _dataAccess = new MapLoad();
            _model = new MaciLaciModel();

            _dataAccess.LoadMap(_gameModePath, _model.Table);

            GenerateTable();
            _timer.Start();
            _timerLabel.Text = "0";
            this.Width = _width;
            this.Height = _height;

            _model.GameWon += new EventHandler(OnGameWon);
            _model.GameLost += new EventHandler(OnGameLost);
        }

        private void MaciLaciForm_KeyDown(object sender, KeyEventArgs e)
        {
            if (_timer.Enabled)
            {
                Int32 x = _model.Table.Player.GetX;
                Int32 y = _model.Table.Player.GetY;

                _model.OnKeyPressed(x, y, e.KeyData); // player step

                // refreshing fields
                _labelGrid[x, y].BackColor = Color.White;

                _labelGrid[_model.Table.Player.GetX, _model.Table.Player.GetY].BackColor = Color.Brown;

                //setting the down right score counter
                _scoreToolTip.Text = _model.Score.ToString();
            }
        }

        private void _timer_Tick(object sender, EventArgs e)
        {
            Int32 x, y;
            //refreshing the enemies past position
            for (int i = 0; i < _model.Table.EnemyNum; i++)
            {
                x = _model.Table.Enemy(i).GetX;
                y = _model.Table.Enemy(i).GetY;

                _labelGrid[x, y].BackColor = Color.White;

            }

            _model.OnTimer();

            //setting the enemies current position
            for (int i = 0; i < _model.Table.EnemyNum; i++)
            {
                x = _model.Table.Enemy(i).GetX;
                y = _model.Table.Enemy(i).GetY;

                _labelGrid[x, y].BackColor = Color.Black;

            }

            //setting game time
            _timerLabel.Text = _model.GameTime.ToString();
        }

        private void kicsiToolStripMenuItem_Click(object sender, EventArgs e)
        {
            _gameModePath = "..\\..\\..\\..\\small.txt";
            kicsiToolStripMenuItem.Checked = true;
            közepesToolStripMenuItem.Checked = false;
            nagyToolStripMenuItem.Checked = false;
            _width = 275;
            _height = 345;
        }

        private void közepesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            _gameModePath = "..\\..\\..\\..\\med.txt";
            kicsiToolStripMenuItem.Checked = false;
            közepesToolStripMenuItem.Checked = true;
            nagyToolStripMenuItem.Checked = false;
            _width = 375;
            _height = 440;
        }

        private void nagyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            _gameModePath = "..\\..\\..\\..\\big.txt";
            kicsiToolStripMenuItem.Checked = false;
            közepesToolStripMenuItem.Checked = false;
            nagyToolStripMenuItem.Checked = true;
            _width = 475;
            _height = 540;
        }

        private void újJátékToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ClearTable();

            _model.NewGame();

            _dataAccess = new MapLoad();
            _model = new MaciLaciModel();

            _dataAccess.LoadMap(_gameModePath, _model.Table);

            GenerateTable();
            _timer.Start();
            _timerLabel.Text = "0";
            this.Width = _width;
            this.Height = _height;

            _model.GameWon += new EventHandler(OnGameWon);
            _model.GameLost += new EventHandler(OnGameLost);

            szünetToolStripMenuItem.Enabled = true;
            szünetToolStripMenuItem.Visible = true;
        }

        private void szünetToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (_timer.Enabled) _timer.Stop();
            else _timer.Start();
        }

        private void OnGameLost(Object sender, EventArgs e)
        {
            _timer.Stop();

            MessageBox.Show("Sajnos vesztettél...",
                                "MaciLaci",
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Asterisk);
            szünetToolStripMenuItem.Enabled = false;
            szünetToolStripMenuItem.Visible = false;
        }

        private void OnGameWon(Object sender, EventArgs e)
        {
            _timer.Stop();

            MessageBox.Show("Gratulálok, győztél!",
                                "MaciLaci",
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Asterisk);
            szünetToolStripMenuItem.Enabled = false;
            szünetToolStripMenuItem.Visible = false;
        }
    }
}
