namespace Minesweeper
{
    partial class Minesweeper
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Minesweeper));
            this._menuStrip = new System.Windows.Forms.MenuStrip();
            this._newGameToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this._easyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this._mediumToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this._hardToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this._saveGameToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this._loadGameToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this._statusStrip = new System.Windows.Forms.StatusStrip();
            this._playerStatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this._saveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this._openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this._menuStrip.SuspendLayout();
            this._statusStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // _menuStrip
            // 
            this._menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this._newGameToolStripMenuItem,
            this._saveGameToolStripMenuItem,
            this._loadGameToolStripMenuItem});
            this._menuStrip.Location = new System.Drawing.Point(0, 0);
            this._menuStrip.Name = "_menuStrip";
            this._menuStrip.Size = new System.Drawing.Size(344, 24);
            this._menuStrip.TabIndex = 0;
            this._menuStrip.Text = "menuStrip1";
            // 
            // _newGameToolStripMenuItem
            // 
            this._newGameToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this._easyToolStripMenuItem,
            this._mediumToolStripMenuItem,
            this._hardToolStripMenuItem});
            this._newGameToolStripMenuItem.Name = "_newGameToolStripMenuItem";
            this._newGameToolStripMenuItem.Size = new System.Drawing.Size(77, 20);
            this._newGameToolStripMenuItem.Text = "New Game";
            // 
            // _easyToolStripMenuItem
            // 
            this._easyToolStripMenuItem.Name = "_easyToolStripMenuItem";
            this._easyToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this._easyToolStripMenuItem.Text = "Easy";
            this._easyToolStripMenuItem.Click += new System.EventHandler(this.EasyToolStripMenuItem_Click);
            // 
            // _mediumToolStripMenuItem
            // 
            this._mediumToolStripMenuItem.Name = "_mediumToolStripMenuItem";
            this._mediumToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this._mediumToolStripMenuItem.Text = "Medium";
            this._mediumToolStripMenuItem.Click += new System.EventHandler(this.MediumToolStripMenuItem_Click);
            // 
            // _hardToolStripMenuItem
            // 
            this._hardToolStripMenuItem.Name = "_hardToolStripMenuItem";
            this._hardToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this._hardToolStripMenuItem.Text = "Hard";
            this._hardToolStripMenuItem.Click += new System.EventHandler(this.HardToolStripMenuItem_Click);
            // 
            // _saveGameToolStripMenuItem
            // 
            this._saveGameToolStripMenuItem.Name = "_saveGameToolStripMenuItem";
            this._saveGameToolStripMenuItem.Size = new System.Drawing.Size(77, 20);
            this._saveGameToolStripMenuItem.Text = "Save Game";
            this._saveGameToolStripMenuItem.Click += new System.EventHandler(this.SaveGameToolStripMenuItem_Click);
            // 
            // _loadGameToolStripMenuItem
            // 
            this._loadGameToolStripMenuItem.Name = "_loadGameToolStripMenuItem";
            this._loadGameToolStripMenuItem.Size = new System.Drawing.Size(79, 20);
            this._loadGameToolStripMenuItem.Text = "Load Game";
            this._loadGameToolStripMenuItem.Click += new System.EventHandler(this.LoadGameToolStripMenuItem_Click);
            // 
            // _statusStrip
            // 
            this._statusStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this._playerStatusLabel});
            this._statusStrip.Location = new System.Drawing.Point(0, 299);
            this._statusStrip.Name = "_statusStrip";
            this._statusStrip.Size = new System.Drawing.Size(344, 22);
            this._statusStrip.TabIndex = 1;
            this._statusStrip.Text = "statusStrip1";
            // 
            // _playerStatusLabel
            // 
            this._playerStatusLabel.Name = "_playerStatusLabel";
            this._playerStatusLabel.Size = new System.Drawing.Size(118, 17);
            this._playerStatusLabel.Text = "toolStripStatusLabel1";
            this._playerStatusLabel.Visible = false;
            // 
            // _saveFileDialog
            // 
            this._saveFileDialog.Filter = "Saved Game (*.save)|*.save";
            this._saveFileDialog.Title = "Save Game";
            // 
            // _openFileDialog
            // 
            this._openFileDialog.Filter = "Saved Game (*.save)|*.save";
            this._openFileDialog.Title = "Load Game";
            // 
            // Minesweeper
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(344, 321);
            this.Controls.Add(this._statusStrip);
            this.Controls.Add(this._menuStrip);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this._menuStrip;
            this.Name = "Minesweeper";
            this.Text = "Minesweeper";
            this.Load += new System.EventHandler(this.Minesweeper_Load);
            this._menuStrip.ResumeLayout(false);
            this._menuStrip.PerformLayout();
            this._statusStrip.ResumeLayout(false);
            this._statusStrip.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip _menuStrip;
        private System.Windows.Forms.ToolStripMenuItem _newGameToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem _easyToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem _mediumToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem _hardToolStripMenuItem;
        private System.Windows.Forms.StatusStrip _statusStrip;
        private System.Windows.Forms.ToolStripStatusLabel _playerStatusLabel;
        private System.Windows.Forms.ToolStripMenuItem _saveGameToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem _loadGameToolStripMenuItem;
        private System.Windows.Forms.SaveFileDialog _saveFileDialog;
        private System.Windows.Forms.OpenFileDialog _openFileDialog;
    }
}

