using System;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Net.Sockets;
using System.Threading;
using System.IO;


namespace LoadClient
{

    public partial class LoadTool : Form
    {
        Byte[] data = new Byte[30];

        UInt16 buff_len = 4096;
        private FileStream loadFile;
        private TcpClient client;
        private bool Button_send_enable = true;
        private NetworkStream streamToServer;
        private bool Disconnect_flag = false;
        private bool connect_flag = false;

        CancellationTokenSource cts = new CancellationTokenSource();        //用于终止发送线程

        public LoadTool()
        {
            InitializeComponent();
            CheckForIllegalCrossThreadCalls = false;
        }

        private void FileSystemWatcher1_Changed(object sender, System.IO.FileSystemEventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void Button1_Click(object sender, EventArgs e)
        {

        }
        private void Send_File()      //发送处理线程
        {
            int ret = 0;
            byte[] frmat_id = new byte[2];
            byte[] frmat_len = new byte[4];
            byte[] send_buff = new byte[buff_len];
            UInt32 startAddr = 0;
            UInt32 fpga = 0;
            if (streamToServer != null)
            {
                try
                {
                    startAddr = UInt32.Parse(textBox_startAddr.Text, System.Globalization.NumberStyles.HexNumber);
                    fpga = UInt32.Parse(textBox_fpga.Text, System.Globalization.NumberStyles.HexNumber);
                    Console.WriteLine(startAddr);
                }
                catch
                {
                    label_state.ForeColor = Color.Red;
                    label_state.Text = "Check StartAddress";

                    return;
                }
                if (selectFile.Text == "")
                {
                    label_state.ForeColor = Color.Red;
                    label_state.Text = "not Select File";
                    button_send.ForeColor = Color.Black;

                    this.Button_send_enable = true;
                    return;
                }
                FileInfo fileInfo;
                try
                {
                    fileInfo = new FileInfo(selectFile.Text);
                    loadFile = new FileStream(selectFile.Text, FileMode.Open, FileAccess.Read);
                }
                catch
                {
                    label_state.ForeColor = Color.Red;
                    label_state.Text = "Not Find File";
                    button_send.ForeColor = Color.Black;

                    this.Button_send_enable = true;
                    return;
                }

                data = Encoding.ASCII.GetBytes("fileinfo:");

               
                UInt32 fileLen = (UInt32)fileInfo.Length;
                UInt32 frmat = fileLen / buff_len;
                if ((fileLen % buff_len) > 0)
                {
                    frmat++;
                }
                byte[] startaddr = BitConverter.GetBytes(startAddr);
                byte[] Bytefrmat = BitConverter.GetBytes(fileLen);
                byte[] Bytefpga = BitConverter.GetBytes(fpga);


                byte[] send = new byte[data.Length + startaddr.Length + Bytefrmat.Length + Bytefrmat.Length];
                data.CopyTo(send, 0);
                startaddr.CopyTo(send, data.Length);
                Bytefrmat.CopyTo(send, data.Length + startaddr.Length);
                Bytefpga.CopyTo(send, data.Length + startaddr.Length + Bytefrmat.Length);
                try
                {
                    streamToServer.Write(send, 0, send.Length);
                    streamToServer.Read(data, 0, 8);
                    Console.WriteLine("file info OK " + startAddr + fileLen);
                    //todo 判断接收数据
#if true
                    if ((startAddr != BitConverter.ToUInt32(data, 0))
                   || fileLen != (BitConverter.ToUInt32(data, 4)))    //处理异常
                    {
                        if ((0 == BitConverter.ToUInt32(data, 0)) &&
                        0 == (BitConverter.ToUInt32(data, 4)))
                        {
                            label_state.ForeColor = Color.Red;
                            label_state.Text = "Pin Locked ";


                        }
                        else
                        {
                            label_state.ForeColor = Color.Red;
                            label_state.Text = "Send ERROR ";
                        }
                        button_send.ForeColor = Color.White;
                        this.Button_send_enable = true;
                        return;
                    }
#endif
                    label_state.Text = "Sendding... ";
                    Console.WriteLine("file info >>> " + BitConverter.ToUInt32(data, 0) + BitConverter.ToUInt32(data, 4));
                }
                catch
                {
                    label_state.ForeColor = Color.Red;
                    label_state.Text = "server Closed";
                    streamToServer.Close();
                    loadFile.Close();

                    connect.BackColor = Color.White;
                    connect.ForeColor = Color.White;

                    button_send.ForeColor = Color.Black;
                    this.Button_send_enable = true;
                    return;
                }

                for (UInt16 i = 0; i < frmat; i++)
                {
#if true
                    if (cts.Token.IsCancellationRequested)                  //取消发送
                    {
                        cts = null;
                        data = Encoding.ASCII.GetBytes("!!!!");
                        try
                        {
                            streamToServer.Write(data, 0, 4);
                            streamToServer.Read(data, 0, 4);
                        }
                        catch
                        {
                            label_state.ForeColor = Color.Red;
                            label_state.Text = "server Closed";
                            streamToServer.Close();
                            loadFile.Close();
                            button_send.ForeColor = Color.White;
                            this.Button_send_enable = true;
                            return;
                        }
                        if (0x21212121 == BitConverter.ToUInt32(data, 0))
                        {
                            loadFile.Close();
                            button_send.ForeColor = Color.White;
                            sendprogressBar.Value = 0;
                            label_state.ForeColor = Color.Red;
                            label_state.Text = "Cancel file Loading";
                            
                            this.Button_send_enable = true;
                            return;
                        }
                    }

#endif
                    ret = loadFile.Read(send_buff, 0, buff_len);
                    frmat_id = BitConverter.GetBytes(i);
                    frmat_len = BitConverter.GetBytes(ret );
                    byte[] SendData = new byte[frmat_id.Length + frmat_len.Length + send_buff.Length];
                    //Console.WriteLine("frmat_id "+i+ "frmat_len "+ (UInt16)ret);
                    /****************************************************************************************************************
                                                        数据帧结构
                    byte |  |   |   |   |.................................................|
                         |F_NUM | len   |            data palyload                        |

                    ****************************************************************************************************************/
                    frmat_id.CopyTo(SendData, 0);
                    frmat_len.CopyTo(SendData, frmat_id.Length);
                    send_buff.CopyTo(SendData, frmat_id.Length + frmat_len.Length);
                    try
                    {
                        streamToServer.Write(SendData, 0, ret + frmat_id.Length + frmat_len.Length);
                        streamToServer.Read(data, 0, 6);

                        if (ret != BitConverter.ToUInt32(data, 2))
                        {
                            label_state.ForeColor = Color.Red;
                            label_state.Text = "verify ERROR";
                            button_send.ForeColor = Color.White;
                            this.Button_send_enable = true;

                            return;
                        }

                        
//                        if (i != BitConverter.ToUInt16(data, 0))                   //处理帧出错
//                        {
//                            loadFile.Seek(i * buff_len, SeekOrigin.Begin);
//                        }
                    }
                    catch
                    {
                        loadFile.Close();
                        streamToServer.Close();
                        label_state.ForeColor = Color.Red;
                        label_state.Text = "Send ERROR";
                        button_send.ForeColor = Color.White;
                        this.Button_send_enable = true;

                        return;
                    }

                    sendprogressBar.Value = (int)(100 * i / (frmat * 1.0));
                }
                cts = null;
                loadFile.Close();
                sendprogressBar.Value = 100;
                label_state.ForeColor = Color.SpringGreen;
                label_state.Text = "Send OK";
                button_send.ForeColor = Color.White;
                this.Button_send_enable = true;
            }
            else
            {
                button_send.ForeColor = Color.White;
                this.Button_send_enable = true;
                label_state.ForeColor = Color.Red;
                label_state.Text = "Not Connected";
            }

        }
        private void button2_Click(object sender, EventArgs e)       // send
        {
            if (!this.Button_send_enable)
            {
                return;
            }
            cts = new CancellationTokenSource();
            sendprogressBar.Value = 0;
            ThreadStart childref = new ThreadStart(Send_File);
            Thread childThread = new Thread(childref);
            childThread.Start();

            this.Button_send_enable = false;
            button_send.ForeColor = Color.Gray;
            label_state.ForeColor = Color.SpringGreen;
           
            label_state.Text = "Flash erase... ";


        }

        private void button3_Click(object sender, EventArgs e)       //cancel
        {
            if (this.Button_send_enable == false)
            {
                if (cts != null)
                {
                    cts.Cancel();
                    label_state.ForeColor = Color.Red;
                    label_state.Text = "cancel...";
                    // this.Button_send_enable = false;
                    button_send.ForeColor = Color.White;
                    return;
                }
            }
            else
            {
                label_state.ForeColor = Color.Tomato;
                label_state.Text = "Invalid Operation";
            }


        }

        private void button4_Click(object sender, EventArgs e)                         //open
        {

            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Multiselect = false;//该值确定是否可以选择多个文件
            dialog.Title = "请选择加载文件";
            dialog.Filter = "bin文件|*.bin";
            if (dialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                selectFile.Text = dialog.FileName;

                label_state.ForeColor = Color.SpringGreen;
                label_state.Text = "Open file OK";
            }
            else
            {
                label_state.ForeColor = Color.Red;
                label_state.Text = "Open file Error";
            }

        }

        private void textBox1_TextChanged_1(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void Create_client()            //创建网络连接线程
        {

            client = new TcpClient();
            string ip = textBox_IP.Text;
            string port = textBox_port.Text;

            try
            {
                client.Connect(System.Net.IPAddress.Parse(ip), int.Parse(port));
            }
            catch
            {
                label_state.ForeColor = Color.Red;
                label_state.Text = "Not Find Server";
                connect_flag = false;
                return;
            }

            if (client.Connected)
            {
                Disconnect_flag = true;
                disconnect.ForeColor = Color.White;

                NetworkStream l_streamToServer = client.GetStream();
                byte[] buffer = Encoding.ASCII.GetBytes("getinfo:");

                label_state.ForeColor = Color.SpringGreen;
                label_state.Text = "waitting handshake";
                try
                {

                    l_streamToServer.Write(buffer, 0, buffer.Length);
                    connect.BackColor = Color.Tomato;
                    l_streamToServer.Read(data, 0, 4);                  //等待连接响应
                    buff_len = BitConverter.ToUInt16(data, 0);         //获取send buff大小
                    if ((buff_len > 0xFFFF) || (buff_len < 0x16))
                    {
                        label_state.ForeColor = Color.Red;
                        label_state.Text = "handshake ERROR";

                        l_streamToServer.Close();
                        connect_flag = false;
                        Disconnect_flag = false;
                        disconnect.ForeColor = Color.Gray;
                        connect.BackColor = Color.White;
                        client = null;
                        return;
                    }
                }
                catch
                {
                    l_streamToServer.Close();
                    label_state.ForeColor = Color.Red;
                    label_state.Text = "connect ERROR";
                    connect_flag = false;
                    Disconnect_flag = false;
                    disconnect.ForeColor = Color.Gray;
                    client = null;
                    return;
                }

                buff_len = BitConverter.ToUInt16(data, 0); //获取send buff大小


                connect.BackColor = Color.SpringGreen;
                connect.FlatAppearance.BorderColor = Color.SpringGreen;
                connect.ForeColor = Color.Gray;
                label_state.ForeColor = Color.SpringGreen;
                label_state.Text = "connect OK";

                connect_flag = false;
                streamToServer = l_streamToServer;
            }
        }


        private void Button1_Click_1(object sender, EventArgs e)                         //connect
        {
            if (connect_flag == true)
            {
                return;
            }
            connect_flag = true;

            ThreadStart childref = new ThreadStart(Create_client);
            Thread childThread = new Thread(childref);
            childThread.Start();
        }

        private void TextBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void TextBox4_TextChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click_2(object sender, EventArgs e)         //disconnect
        {
            if (Disconnect_flag == false)
            {
                return;
            }

            if (cts != null)
            {
                cts.Cancel();
            }
            Thread.Sleep(2000);
            if (loadFile != null)
            {
                loadFile.Close();
            }
            if ((client != null) && (client.Connected) && (streamToServer != null))
            {

                streamToServer.Close();

                connect.BackColor = Color.CornflowerBlue;
                streamToServer = null;
                client = null;
            }
            else
            {
                return;
            }
            Disconnect_flag = false;
            connect.BackColor = Color.CornflowerBlue;
            connect.ForeColor = Color.White;
            disconnect.ForeColor = Color.Gainsboro;
            label_state.ForeColor = Color.Red;
            label_state.Text = "disconnect";
        }

        private void sendprogressBar_Click(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void LoadTool_Load(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged_2(object sender, EventArgs e)
        {

        }
    }
}
