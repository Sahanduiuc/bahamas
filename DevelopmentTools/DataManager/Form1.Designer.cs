namespace DataManager
{
    partial class Form1
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
            this.tabControl = new System.Windows.Forms.TabControl();
            this.Analyser = new System.Windows.Forms.TabPage();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.button3 = new System.Windows.Forms.Button();
            this.btnLoadCSV = new System.Windows.Forms.Button();
            this.SQL_DB = new System.Windows.Forms.TabPage();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.lblLog = new System.Windows.Forms.TextBox();
            this.tabControl.SuspendLayout();
            this.Analyser.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl
            // 
            this.tabControl.Controls.Add(this.Analyser);
            this.tabControl.Controls.Add(this.SQL_DB);
            this.tabControl.Location = new System.Drawing.Point(5, 5);
            this.tabControl.Name = "tabControl";
            this.tabControl.SelectedIndex = 0;
            this.tabControl.Size = new System.Drawing.Size(799, 737);
            this.tabControl.TabIndex = 0;
            // 
            // Analyser
            // 
            this.Analyser.Controls.Add(this.lblLog);
            this.Analyser.Controls.Add(this.groupBox1);
            this.Analyser.Location = new System.Drawing.Point(4, 22);
            this.Analyser.Name = "Analyser";
            this.Analyser.Padding = new System.Windows.Forms.Padding(3);
            this.Analyser.Size = new System.Drawing.Size(791, 711);
            this.Analyser.TabIndex = 0;
            this.Analyser.Text = "Analyser";
            this.Analyser.UseVisualStyleBackColor = true;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.comboBox1);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.btnLoadCSV);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.textBox1);
            this.groupBox1.Controls.Add(this.button3);
            this.groupBox1.Location = new System.Drawing.Point(6, 6);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(779, 175);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Settings";
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "Zero fill",
            "Interpolate"});
            this.comboBox1.Location = new System.Drawing.Point(116, 24);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(197, 21);
            this.comboBox1.TabIndex = 7;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(7, 27);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(103, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "Empty value handler";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(7, 99);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(111, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Target Header Layout";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(6, 114);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(766, 20);
            this.textBox1.TabIndex = 4;
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(617, 142);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(156, 28);
            this.button3.TabIndex = 3;
            this.button3.Text = "Save";
            this.button3.UseVisualStyleBackColor = true;
            // 
            // btnLoadCSV
            // 
            this.btnLoadCSV.Location = new System.Drawing.Point(10, 51);
            this.btnLoadCSV.Name = "btnLoadCSV";
            this.btnLoadCSV.Size = new System.Drawing.Size(156, 28);
            this.btnLoadCSV.TabIndex = 0;
            this.btnLoadCSV.Text = "Load Raw csv";
            this.btnLoadCSV.UseVisualStyleBackColor = true;
            this.btnLoadCSV.Click += new System.EventHandler(this.button1_Click);
            // 
            // SQL_DB
            // 
            this.SQL_DB.Location = new System.Drawing.Point(4, 22);
            this.SQL_DB.Name = "SQL_DB";
            this.SQL_DB.Padding = new System.Windows.Forms.Padding(3);
            this.SQL_DB.Size = new System.Drawing.Size(791, 711);
            this.SQL_DB.TabIndex = 1;
            this.SQL_DB.Text = "SQL DB";
            this.SQL_DB.UseVisualStyleBackColor = true;
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // lblLog
            // 
            this.lblLog.BackColor = System.Drawing.SystemColors.MenuBar;
            this.lblLog.Font = new System.Drawing.Font("Courier New", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblLog.Location = new System.Drawing.Point(6, 187);
            this.lblLog.Multiline = true;
            this.lblLog.Name = "lblLog";
            this.lblLog.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.lblLog.Size = new System.Drawing.Size(778, 518);
            this.lblLog.TabIndex = 5;
            this.lblLog.Text = "Log";
            // 
            // Form1
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.ClientSize = new System.Drawing.Size(806, 746);
            this.Controls.Add(this.tabControl);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "DataManager x64";
            this.tabControl.ResumeLayout(false);
            this.Analyser.ResumeLayout(false);
            this.Analyser.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl;
        private System.Windows.Forms.TabPage Analyser;
        private System.Windows.Forms.TabPage SQL_DB;
        private System.Windows.Forms.Button btnLoadCSV;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox lblLog;
    }
}

