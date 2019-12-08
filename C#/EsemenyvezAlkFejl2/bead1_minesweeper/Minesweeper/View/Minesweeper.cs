using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Minesweeper.Model;
using Minesweeper.Persistence;

namespace Minesweeper
{
    public partial class Minesweeper : Form
    {
        private IMinesweeperDataAccess _dataAccess;
        private Int32 _windowSize;
        private MinesweeperModel _model;
        private Button[,] _buttonGrid; // gombrács
        public Minesweeper()
        {
            InitializeComponent();
        }

        private void GenerateTable()
        {
            Size = new System.Drawing.Size(_windowSize - 35, 30 + _windowSize);
            if (_buttonGrid != null)
            {
                foreach (Button label in _buttonGrid)
                {
                    Controls.Remove(label);
                }
            }

            _buttonGrid = new Button[_model.Size, _model.Size];
            for (Int32 i = 0; i < _model.Size; i++)
                for (Int32 j = 0; j < _model.Size; j++)
                {
                    _buttonGrid[i, j] = new Button();
                    _buttonGrid[i, j].Location = new Point(5 + 50 * j, 25 + 50 * i); // elhelyezkedés
                    _buttonGrid[i, j].Size = new Size(50, 50); // méret
                    _buttonGrid[i, j].FlatStyle = FlatStyle.Flat; // lapított stípus
                    _buttonGrid[i, j].BackColor = Color.White;
                    _buttonGrid[i, j].MouseDown += new MouseEventHandler(OnButtonMouseDown);

                    Controls.Add(_buttonGrid[i, j]);
                }
            playerStatusLabel.Text = "Current player: " + _model.CurrPlayer.ToString();
            playerStatusLabel.Visible = true;
        }

        private void UpdateTable()
        {
            for (Int32 i = 0; i < _model.Size; i++)
                for (Int32 j = 0; j < _model.Size; j++)
                {
                    if (_model.Map[i, j].visible)
                    {
                        if (_model.Map[i, j].fieldType == FieldType.BOMB)
                        {
                            _buttonGrid[i, j].BackColor = Color.Black;
                        }
                        else
                        {
                            _buttonGrid[i, j].Text = _model.Map[i, j].value.ToString();
                            _buttonGrid[i, j].TextAlign = ContentAlignment.MiddleCenter;
                            _buttonGrid[i, j].Font = new Font("Arial", 24, FontStyle.Bold);
                        }
                    }
                }
        }

        private void Minesweeper_Load(object sender, EventArgs e)
        {
            _dataAccess = new MinesweeperFileDataAccess();

            _model = new MinesweeperModel(_dataAccess);
            _model.PlayerLost += new EventHandler<MinesweeperEventArgs>(OnPlayerLost);
            _model.Draw += new EventHandler(OnDraw);

            _windowSize = 360;
            _model.NewGame(6);
            GenerateTable();
        }


        private void EasyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            _windowSize = 360;
            _model.NewGame(6);
            GenerateTable();
        }

        private void MediumToolStripMenuItem_Click(object sender, EventArgs e)
        {
            _windowSize = 560;
            _model.NewGame(10);
            GenerateTable();
        }

        private void HardToolStripMenuItem_Click(object sender, EventArgs e)
        {
            _windowSize = 860;
            _model.NewGame(16);
            GenerateTable();
        }

        private void OnButtonMouseDown(object sender, MouseEventArgs e)
        {
            Button btn = (Button)sender;
            // a TabIndex-ből megkapjuk a sort és oszlopot
            Int32 x = (btn.TabIndex - 2) / _model.Size;
            Int32 y = (btn.TabIndex - 2) % _model.Size;

            if(e.Button == MouseButtons.Right)
            {
                if(_buttonGrid[x, y].BackColor != Color.Red)
                {
                    _buttonGrid[x, y].BackColor = Color.Red;
                }
                else
                {
                    _buttonGrid[x, y].BackColor = Color.White;
                }
            }
            else
            {
                _model.Step(x, y);

                UpdateTable();
                playerStatusLabel.Text = "Current player: " + _model.CurrPlayer.ToString();
            }
        }

        private void OnPlayerLost(object sender, MinesweeperEventArgs e)
        {
            UpdateTable();
            MessageBox.Show(e.Player + " won",
                                "Game Over",
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Asterisk);
            _model.NewGame(_model.Size);
            GenerateTable();
        }

        private void OnDraw(object sender, EventArgs e)
        {
            UpdateTable();
            MessageBox.Show("Draw",
                                "Game Over",
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Asterisk);
            _model.NewGame(_model.Size);
            GenerateTable();
        }

        private async void SaveGameToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                await _model.SaveGameAsync(saveFileDialog.FileName);
            }
        }

        private async void LoadGameToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                await _model.LoadGameAsync(openFileDialog.FileName);
                switch (_model.Size)
                {
                    case 6:
                        _windowSize = 360;
                        break;
                    case 10:
                        _windowSize = 560;
                        break;
                    case 16:
                        _windowSize = 860;
                        break;
                }
                GenerateTable();
                UpdateTable();
            }
        }
    }
}
