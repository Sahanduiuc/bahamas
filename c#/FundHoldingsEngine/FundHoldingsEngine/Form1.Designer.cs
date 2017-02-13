namespace FundHoldingsEngine
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
            this.label1 = new System.Windows.Forms.Label();
            this.idTxt = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.lblStatus = new System.Windows.Forms.Label();
            this.cmdLoad = new System.Windows.Forms.Button();
            this.cmdProcess = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(45, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Fund ID";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // idTxt
            // 
            this.idTxt.Location = new System.Drawing.Point(54, 6);
            this.idTxt.Name = "idTxt";
            this.idTxt.Size = new System.Drawing.Size(200, 20);
            this.idTxt.TabIndex = 1;
            this.idTxt.Text = "vac13f";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 296);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(37, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Status";
            // 
            // lblStatus
            // 
            this.lblStatus.BackColor = System.Drawing.SystemColors.ControlText;
            this.lblStatus.ForeColor = System.Drawing.Color.Lime;
            this.lblStatus.Location = new System.Drawing.Point(6, 313);
            this.lblStatus.Name = "lblStatus";
            this.lblStatus.Size = new System.Drawing.Size(443, 28);
            this.lblStatus.TabIndex = 3;
            this.lblStatus.Text = "Ready";
            // 
            // cmdLoad
            // 
            this.cmdLoad.Location = new System.Drawing.Point(374, 9);
            this.cmdLoad.Name = "cmdLoad";
            this.cmdLoad.Size = new System.Drawing.Size(75, 23);
            this.cmdLoad.TabIndex = 4;
            this.cmdLoad.Text = "Load";
            this.cmdLoad.UseVisualStyleBackColor = true;
            this.cmdLoad.Click += new System.EventHandler(this.cmdLoad_Click);
            // 
            // cmdProcess
            // 
            this.cmdProcess.Location = new System.Drawing.Point(374, 39);
            this.cmdProcess.Name = "cmdProcess";
            this.cmdProcess.Size = new System.Drawing.Size(75, 23);
            this.cmdProcess.TabIndex = 5;
            this.cmdProcess.Text = "Output";
            this.cmdProcess.UseVisualStyleBackColor = true;
            this.cmdProcess.Click += new System.EventHandler(this.cmdProcess_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Window;
            this.ClientSize = new System.Drawing.Size(461, 350);
            this.Controls.Add(this.cmdProcess);
            this.Controls.Add(this.cmdLoad);
            this.Controls.Add(this.lblStatus);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.idTxt);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Fund Holdings Engine ";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox idTxt;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label lblStatus;
        private System.Windows.Forms.Button cmdLoad;
        private System.Windows.Forms.Button cmdProcess;
    }
}

