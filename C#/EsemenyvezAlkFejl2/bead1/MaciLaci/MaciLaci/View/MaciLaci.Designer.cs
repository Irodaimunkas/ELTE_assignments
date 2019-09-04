namespace MaciLaci
{
    partial class MaciLaciForm
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
            this.components = new System.ComponentModel.Container();
            this._menuStrip = new System.Windows.Forms.MenuStrip();
            this.újJátékToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pályaMéreteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.kicsiToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.közepesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.nagyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.szünetToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this._statusStrip = new System.Windows.Forms.StatusStrip();
            this._timerLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel2 = new System.Windows.Forms.ToolStripStatusLabel();
            this._scoreLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this._scoreToolTip = new System.Windows.Forms.ToolStripStatusLabel();
            this._timer = new System.Windows.Forms.Timer(this.components);
            this._menuStrip.SuspendLayout();
            this._statusStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // _menuStrip
            // 
            this._menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.újJátékToolStripMenuItem,
            this.pályaMéreteToolStripMenuItem,
            this.szünetToolStripMenuItem});
            this._menuStrip.Location = new System.Drawing.Point(0, 0);
            this._menuStrip.Name = "_menuStrip";
            this._menuStrip.Size = new System.Drawing.Size(339, 24);
            this._menuStrip.TabIndex = 0;
            this._menuStrip.Text = "menuStrip1";
            // 
            // újJátékToolStripMenuItem
            // 
            this.újJátékToolStripMenuItem.Name = "újJátékToolStripMenuItem";
            this.újJátékToolStripMenuItem.Size = new System.Drawing.Size(59, 20);
            this.újJátékToolStripMenuItem.Text = "Új Játék";
            this.újJátékToolStripMenuItem.Click += new System.EventHandler(this.újJátékToolStripMenuItem_Click);
            // 
            // pályaMéreteToolStripMenuItem
            // 
            this.pályaMéreteToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.kicsiToolStripMenuItem,
            this.közepesToolStripMenuItem,
            this.nagyToolStripMenuItem});
            this.pályaMéreteToolStripMenuItem.Name = "pályaMéreteToolStripMenuItem";
            this.pályaMéreteToolStripMenuItem.Size = new System.Drawing.Size(87, 20);
            this.pályaMéreteToolStripMenuItem.Text = "Pálya mérete";
            // 
            // kicsiToolStripMenuItem
            // 
            this.kicsiToolStripMenuItem.Name = "kicsiToolStripMenuItem";
            this.kicsiToolStripMenuItem.Size = new System.Drawing.Size(117, 22);
            this.kicsiToolStripMenuItem.Text = "Kicsi";
            this.kicsiToolStripMenuItem.Click += new System.EventHandler(this.kicsiToolStripMenuItem_Click);
            // 
            // közepesToolStripMenuItem
            // 
            this.közepesToolStripMenuItem.Checked = true;
            this.közepesToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked;
            this.közepesToolStripMenuItem.Name = "közepesToolStripMenuItem";
            this.közepesToolStripMenuItem.Size = new System.Drawing.Size(117, 22);
            this.közepesToolStripMenuItem.Text = "Közepes";
            this.közepesToolStripMenuItem.Click += new System.EventHandler(this.közepesToolStripMenuItem_Click);
            // 
            // nagyToolStripMenuItem
            // 
            this.nagyToolStripMenuItem.Name = "nagyToolStripMenuItem";
            this.nagyToolStripMenuItem.Size = new System.Drawing.Size(117, 22);
            this.nagyToolStripMenuItem.Text = "Nagy";
            this.nagyToolStripMenuItem.Click += new System.EventHandler(this.nagyToolStripMenuItem_Click);
            // 
            // szünetToolStripMenuItem
            // 
            this.szünetToolStripMenuItem.Name = "szünetToolStripMenuItem";
            this.szünetToolStripMenuItem.Size = new System.Drawing.Size(54, 20);
            this.szünetToolStripMenuItem.Text = "Szünet";
            this.szünetToolStripMenuItem.Click += new System.EventHandler(this.szünetToolStripMenuItem_Click);
            // 
            // _statusStrip
            // 
            this._statusStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this._timerLabel,
            this.toolStripStatusLabel2,
            this._scoreLabel,
            this._scoreToolTip});
            this._statusStrip.Location = new System.Drawing.Point(0, 337);
            this._statusStrip.Name = "_statusStrip";
            this._statusStrip.Size = new System.Drawing.Size(339, 24);
            this._statusStrip.TabIndex = 1;
            this._statusStrip.Text = "statusStrip1";
            // 
            // _timerLabel
            // 
            this._timerLabel.BorderSides = ((System.Windows.Forms.ToolStripStatusLabelBorderSides)((((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left | System.Windows.Forms.ToolStripStatusLabelBorderSides.Top) 
            | System.Windows.Forms.ToolStripStatusLabelBorderSides.Right) 
            | System.Windows.Forms.ToolStripStatusLabelBorderSides.Bottom)));
            this._timerLabel.Name = "_timerLabel";
            this._timerLabel.Size = new System.Drawing.Size(47, 19);
            this._timerLabel.Text = "1:00:00";
            // 
            // toolStripStatusLabel2
            // 
            this.toolStripStatusLabel2.Name = "toolStripStatusLabel2";
            this.toolStripStatusLabel2.Size = new System.Drawing.Size(173, 19);
            this.toolStripStatusLabel2.Spring = true;
            // 
            // _scoreLabel
            // 
            this._scoreLabel.Name = "_scoreLabel";
            this._scoreLabel.Size = new System.Drawing.Size(91, 19);
            this._scoreLabel.Text = "Felvett kosarak: ";
            // 
            // _scoreToolTip
            // 
            this._scoreToolTip.Name = "_scoreToolTip";
            this._scoreToolTip.Size = new System.Drawing.Size(13, 19);
            this._scoreToolTip.Text = "0";
            // 
            // _timer
            // 
            this._timer.Interval = 1000;
            this._timer.Tick += new System.EventHandler(this._timer_Tick);
            // 
            // MaciLaciForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(339, 361);
            this.Controls.Add(this._statusStrip);
            this.Controls.Add(this._menuStrip);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MainMenuStrip = this._menuStrip;
            this.Name = "MaciLaciForm";
            this.Text = "MaciLaci";
            this.Load += new System.EventHandler(this.MaciLaciForm_Load);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.MaciLaciForm_KeyDown);
            this._menuStrip.ResumeLayout(false);
            this._menuStrip.PerformLayout();
            this._statusStrip.ResumeLayout(false);
            this._statusStrip.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip _menuStrip;
        private System.Windows.Forms.ToolStripMenuItem újJátékToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem pályaMéreteToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem kicsiToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem közepesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem nagyToolStripMenuItem;
        private System.Windows.Forms.StatusStrip _statusStrip;
        private System.Windows.Forms.ToolStripStatusLabel _timerLabel;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel2;
        private System.Windows.Forms.ToolStripStatusLabel _scoreLabel;
        private System.Windows.Forms.ToolStripStatusLabel _scoreToolTip;
        private System.Windows.Forms.Timer _timer;
        private System.Windows.Forms.ToolStripMenuItem szünetToolStripMenuItem;
    }
}

