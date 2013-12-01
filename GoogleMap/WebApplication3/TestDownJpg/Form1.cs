using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Net;
using System.IO;
using System.Data.SqlClient;
using System.Collections;
using System.Configuration;


namespace TestDownJpg
{
    public partial class Form1 : Form
    {
        private static DownJpgClass downObj = new DownJpgClass();
        private Thread threadObj = new Thread(new ThreadStart(downObj.DownJpg));

        public Form1()
        {
            InitializeComponent();
            label1.Text = "我是服务器程序，自动下载图片，请不要关闭我！";
            threadObj.Start();
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            threadObj.Abort();
        }
    }

    public class JpgUrlStruct{
        public string url;
        public double timeCycle;
        public string folderName;
        public DateTime nextTimeToRun;
    }

    public class DownJpgClass
    {
        private bool bCheckRestart = true;
        private bool bCheckStart = false;
        private string connStr = "Data Source=124.248.237.50;Initial Catalog=sqlybsp;Persist Security Info=True;User ID=sqlybsp;Password=gezhi";

        private bool GetRunState()
        {
            DataTable dt = new DataTable();
            SqlConnection conn = new SqlConnection(connStr);
            conn.Open();
            string sql = "select * from DownJpgCheck where ID = 0";
            SqlCommand cmd = new SqlCommand(sql, conn);
            SqlDataReader sdr = cmd.ExecuteReader();
            dt.Load(sdr);
            bool bRet = Convert.ToBoolean(dt.Rows[0]["IsRun"].ToString());
            sdr.Close();
            conn.Close();
            return bRet;
        }

        public void DownJpg()
        {
            List<JpgUrlStruct> jpgUrlList = new List<JpgUrlStruct>();

            while (true)
            {
                try
                {
                    bCheckStart = GetRunState();

                    if (!bCheckStart)
                    {
                        bCheckRestart = true;
                        Thread.Sleep(1000);
                        continue;
                    }

                    if (bCheckStart && bCheckRestart)
                    {
                        jpgUrlList.Clear();
                        DataTable dt = new DataTable();
                        SqlConnection conn = new SqlConnection(connStr);
                        conn.Open();
                        string sql = "select * from DownJpgUrlList where IsValid = 'True'";
                        SqlCommand cmd = new SqlCommand(sql, conn);
                        SqlDataReader sdr = cmd.ExecuteReader();
                        dt.Load(sdr);
                        for (int j = 0; j < dt.Rows.Count; j++)
                        {
                            JpgUrlStruct jpgUrl = new JpgUrlStruct();
                            jpgUrl.url = dt.Rows[j]["JpgUrl"].ToString();
                            jpgUrl.folderName = dt.Rows[j]["FolderName"].ToString();
                            jpgUrl.timeCycle = Convert.ToDouble(dt.Rows[j]["TimeCycle"].ToString());
                            jpgUrl.nextTimeToRun = DateTime.Now;
                            jpgUrlList.Add(jpgUrl);
                        }
                        bCheckRestart = false;
                        sdr.Close();
                        conn.Close();
                    }

                    if (bCheckStart)
                    {
                        WebClient myWebClient = new WebClient();
                        int i = 0;
                        for (int k = 0; k < jpgUrlList.Count;  )
                        {
                            if (jpgUrlList[i].nextTimeToRun <= DateTime.Now)
                            {
                                string url = jpgUrlList[i].url;
                                string newFileName = DateTime.Now.ToString("yyyyMMddhhmmss");
                                string strRootPath = Environment.CurrentDirectory;
                                string rootFolderPath = @"" + strRootPath;
                                if (!Directory.Exists(rootFolderPath))
                                {
                                    Directory.CreateDirectory(rootFolderPath);
                                }
                                string partPath = @"" + strRootPath + "\\DownJpg\\" + jpgUrlList[i].folderName;
                                if (!Directory.Exists(partPath))
                                {
                                    Directory.CreateDirectory(partPath);
                                }
                                string filePath = partPath + "\\" + newFileName + ".jpg";
                                try
                                {
                                    myWebClient.DownloadFile(url, filePath);
                                }
                                catch (System.Exception ex)
                                {
                                    //MessageBox.Show(ex.ToString());
                                }
                                jpgUrlList[i].nextTimeToRun = jpgUrlList[i].nextTimeToRun.AddHours(jpgUrlList[i].timeCycle);
                            }
                            if (!GetRunState())
                            {
                                k = k + jpgUrlList.Count; //需要结束本次循环
                            }
                            else
                            {
                                k++;
                                i++;
                            }
                        }
                    }
                    Thread.Sleep(1000);
                }
                catch (System.Exception ex)
                {
                    //MessageBox.Show(ex.ToString());
                }
            }
        }
    }
}
