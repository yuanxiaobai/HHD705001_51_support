namespace LoadClient
{
    partial class LoadTool
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(LoadTool));
            this.textBox_IP = new System.Windows.Forms.TextBox();
            this.textBox_port = new System.Windows.Forms.TextBox();
            this.selectFile = new System.Windows.Forms.TextBox();
            this.textBox_startAddr = new System.Windows.Forms.TextBox();
            this.button_send = new System.Windows.Forms.Button();
            this.cancel = new System.Windows.Forms.Button();
            this.sendprogressBar = new System.Windows.Forms.ProgressBar();
            this.open = new System.Windows.Forms.Button();
            this.connect = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.disconnect = new System.Windows.Forms.Button();
            this.label_state = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.textBox_fpga = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // textBox_IP
            // 
            resources.ApplyResources(this.textBox_IP, "textBox_IP");
            this.textBox_IP.BackColor = System.Drawing.Color.White;
            this.textBox_IP.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox_IP.ForeColor = System.Drawing.SystemColors.AppWorkspace;
            this.textBox_IP.Name = "textBox_IP";
            this.textBox_IP.TextChanged += new System.EventHandler(this.textBox1_TextChanged_1);
            // 
            // textBox_port
            // 
            resources.ApplyResources(this.textBox_port, "textBox_port");
            this.textBox_port.BackColor = System.Drawing.Color.White;
            this.textBox_port.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox_port.CausesValidation = false;
            this.textBox_port.ForeColor = System.Drawing.SystemColors.AppWorkspace;
            this.textBox_port.Name = "textBox_port";
            this.textBox_port.TextChanged += new System.EventHandler(this.TextBox2_TextChanged);
            // 
            // selectFile
            // 
            resources.ApplyResources(this.selectFile, "selectFile");
            this.selectFile.AllowDrop = true;
            this.selectFile.BackColor = System.Drawing.SystemColors.Control;
            this.selectFile.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.selectFile.ForeColor = System.Drawing.SystemColors.ControlDarkDark;
            this.selectFile.Name = "selectFile";
            // 
            // textBox_startAddr
            // 
            resources.ApplyResources(this.textBox_startAddr, "textBox_startAddr");
            this.textBox_startAddr.BackColor = System.Drawing.SystemColors.Window;
            this.textBox_startAddr.ForeColor = System.Drawing.SystemColors.AppWorkspace;
            this.textBox_startAddr.Name = "textBox_startAddr";
            this.textBox_startAddr.TextChanged += new System.EventHandler(this.TextBox4_TextChanged);
            // 
            // button_send
            // 
            resources.ApplyResources(this.button_send, "button_send");
            this.button_send.BackColor = System.Drawing.Color.CornflowerBlue;
            this.button_send.FlatAppearance.BorderColor = System.Drawing.Color.DodgerBlue;
            this.button_send.FlatAppearance.MouseDownBackColor = System.Drawing.Color.CornflowerBlue;
            this.button_send.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.button_send.Name = "button_send";
            this.button_send.UseVisualStyleBackColor = false;
            this.button_send.Click += new System.EventHandler(this.button2_Click);
            // 
            // cancel
            // 
            resources.ApplyResources(this.cancel, "cancel");
            this.cancel.BackColor = System.Drawing.Color.CornflowerBlue;
            this.cancel.FlatAppearance.BorderColor = System.Drawing.Color.DodgerBlue;
            this.cancel.FlatAppearance.MouseDownBackColor = System.Drawing.Color.CornflowerBlue;
            this.cancel.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.cancel.Name = "cancel";
            this.cancel.UseVisualStyleBackColor = false;
            this.cancel.Click += new System.EventHandler(this.button3_Click);
            // 
            // sendprogressBar
            // 
            resources.ApplyResources(this.sendprogressBar, "sendprogressBar");
            this.sendprogressBar.BackColor = System.Drawing.Color.SpringGreen;
            this.sendprogressBar.Cursor = System.Windows.Forms.Cursors.No;
            this.sendprogressBar.Name = "sendprogressBar";
            this.sendprogressBar.Click += new System.EventHandler(this.sendprogressBar_Click);
            // 
            // open
            // 
            resources.ApplyResources(this.open, "open");
            this.open.BackColor = System.Drawing.Color.CornflowerBlue;
            this.open.FlatAppearance.BorderColor = System.Drawing.Color.CornflowerBlue;
            this.open.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.open.Name = "open";
            this.open.UseVisualStyleBackColor = false;
            this.open.Click += new System.EventHandler(this.button4_Click);
            // 
            // connect
            // 
            resources.ApplyResources(this.connect, "connect");
            this.connect.BackColor = System.Drawing.Color.CornflowerBlue;
            this.connect.FlatAppearance.BorderColor = System.Drawing.Color.DodgerBlue;
            this.connect.FlatAppearance.MouseDownBackColor = System.Drawing.Color.CornflowerBlue;
            this.connect.ForeColor = System.Drawing.Color.White;
            this.connect.Name = "connect";
            this.connect.UseVisualStyleBackColor = false;
            this.connect.Click += new System.EventHandler(this.Button1_Click_1);
            // 
            // label1
            // 
            resources.ApplyResources(this.label1, "label1");
            this.label1.BackColor = System.Drawing.Color.DodgerBlue;
            this.label1.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.label1.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label1.Name = "label1";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // label2
            // 
            resources.ApplyResources(this.label2, "label2");
            this.label2.BackColor = System.Drawing.Color.DodgerBlue;
            this.label2.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label2.Name = "label2";
            // 
            // label3
            // 
            resources.ApplyResources(this.label3, "label3");
            this.label3.BackColor = System.Drawing.Color.DodgerBlue;
            this.label3.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label3.Name = "label3";
            this.label3.Click += new System.EventHandler(this.label3_Click);
            // 
            // label4
            // 
            resources.ApplyResources(this.label4, "label4");
            this.label4.BackColor = System.Drawing.Color.DodgerBlue;
            this.label4.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label4.Name = "label4";
            this.label4.Click += new System.EventHandler(this.label4_Click);
            // 
            // disconnect
            // 
            resources.ApplyResources(this.disconnect, "disconnect");
            this.disconnect.BackColor = System.Drawing.Color.CornflowerBlue;
            this.disconnect.FlatAppearance.BorderColor = System.Drawing.Color.DodgerBlue;
            this.disconnect.FlatAppearance.MouseDownBackColor = System.Drawing.Color.CornflowerBlue;
            this.disconnect.ForeColor = System.Drawing.Color.White;
            this.disconnect.Name = "disconnect";
            this.disconnect.UseVisualStyleBackColor = false;
            this.disconnect.Click += new System.EventHandler(this.button1_Click_2);
            // 
            // label_state
            // 
            resources.ApplyResources(this.label_state, "label_state");
            this.label_state.BackColor = System.Drawing.SystemColors.ControlDark;
            this.label_state.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label_state.Name = "label_state";
            this.label_state.Click += new System.EventHandler(this.label5_Click);
            // 
            // label5
            // 
            resources.ApplyResources(this.label5, "label5");
            this.label5.BackColor = System.Drawing.Color.DodgerBlue;
            this.label5.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label5.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label5.Name = "label5";
            // 
            // textBox_fpga
            // 
            resources.ApplyResources(this.textBox_fpga, "textBox_fpga");
            this.textBox_fpga.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox_fpga.ForeColor = System.Drawing.SystemColors.AppWorkspace;
            this.textBox_fpga.Name = "textBox_fpga";
            this.textBox_fpga.TextChanged += new System.EventHandler(this.textBox1_TextChanged_2);
            // 
            // LoadTool
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDark;
            this.Controls.Add(this.textBox_fpga);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label_state);
            this.Controls.Add(this.disconnect);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.connect);
            this.Controls.Add(this.open);
            this.Controls.Add(this.sendprogressBar);
            this.Controls.Add(this.cancel);
            this.Controls.Add(this.button_send);
            this.Controls.Add(this.textBox_startAddr);
            this.Controls.Add(this.selectFile);
            this.Controls.Add(this.textBox_port);
            this.Controls.Add(this.textBox_IP);
            this.ForeColor = System.Drawing.SystemColors.ControlDarkDark;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.KeyPreview = true;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "LoadTool";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.Load += new System.EventHandler(this.LoadTool_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox_IP;
        private System.Windows.Forms.TextBox textBox_port;
        private System.Windows.Forms.TextBox selectFile;
        private System.Windows.Forms.TextBox textBox_startAddr;
        private System.Windows.Forms.Button button_send;
        private System.Windows.Forms.Button cancel;
        private System.Windows.Forms.ProgressBar sendprogressBar;
        private System.Windows.Forms.Button open;
        private System.Windows.Forms.Button connect;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button disconnect;
        private System.Windows.Forms.Label label_state;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBox_fpga;
    }
}

