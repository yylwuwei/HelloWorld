using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using System.Runtime.InteropServices;

namespace WindowsFormsApplication1
{


    public partial class Form1 : Form
    {
        private const int INTERNET_OPTION_END_BROWSER_SESSION = 42;

        public struct Struct_INTERNET_PROXY_INFO
        {
            public int dwAccessType;
            public IntPtr proxy;
            public IntPtr proxyBypass;
        };
        
        [DllImport("wininet.dll", SetLastError = true)]
        private static extern bool InternetSetOption(IntPtr hInternet, int dwOption, IntPtr lpBuffer, int lpdwBufferLength);

        public void ResetSession()
        {
            //Session的选项ID为42
            InternetSetOption(IntPtr.Zero, 42, IntPtr.Zero, 0);
        }

        //清空cookie
        public void ResetCookie()
        {
            if (webBrowser1.Document != null)
            {
                try
                {
                    webBrowser1.Document.Cookie.Remove(0, webBrowser1.Document.Cookie.Count() - 1);
                }
                catch (System.Exception ex)
                {
                	
                }

            }
            string[] theCookies = System.IO.Directory.GetFiles(Environment.GetFolderPath(Environment.SpecialFolder.Cookies));
            foreach (string currentFile in theCookies)
            {
                try
                {
                    System.IO.File.Delete(currentFile);
                }
                catch (Exception ex)
                {
                }
            }
        }

        private void RefreshIESettings(string strProxy)
        {
            const int INTERNET_OPTION_PROXY = 38;
            const int INTERNET_OPEN_TYPE_PROXY = 3;

            Struct_INTERNET_PROXY_INFO struct_IPI;

            // Filling in structure 
            struct_IPI.dwAccessType = INTERNET_OPEN_TYPE_PROXY;
            struct_IPI.proxy = Marshal.StringToHGlobalAnsi(strProxy);
            struct_IPI.proxyBypass = Marshal.StringToHGlobalAnsi("local");

            // Allocating memory 
            IntPtr intptrStruct = Marshal.AllocCoTaskMem(Marshal.SizeOf(struct_IPI));

            // Converting structure to IntPtr 
            Marshal.StructureToPtr(struct_IPI, intptrStruct, true);

            bool iReturn = InternetSetOption(IntPtr.Zero, INTERNET_OPTION_PROXY, intptrStruct, Marshal.SizeOf(struct_IPI));
        }

        private void SomeFunc()
        {
            ResetCookie();
            ResetSession();

            RefreshIESettings(this.textBox1.Text.Trim());

            System.Object nullObject = 0;
            string strTemp = String.Empty;
            System.Object nullObjStr = strTemp;
            webBrowser1.Navigate("http://shop72772786.taobao.com/", null, null, null);

            System.Threading.Thread.Sleep(3000);

            if (this.webBrowser1.Document != null)
            {
                HtmlDocument doca = this.webBrowser1.Document;        //把当前的webBrowser1显示的文档实例化成一个HtmlDocument对象
                for (int i = 0; i < doca.All.Count; i++)          //循环查找这个对象的每一个元素
                {
                    if (doca.All[i].TagName == "A")           //如果这个元素是A
                    {
                        HtmlElement myelement = doca.All[i];       //就把这个元素实例化成一个HtmlElement对象
                        if (myelement.OuterText != null)
                        {
                            if (myelement.GetAttribute("title").Contains("小米"))//  myelement.OuterText.Contains("小米"))       //如果这个元素的文字是“下一页"
                            {
                                myelement.InvokeMember("click");    //对这个元素进行点击
                                return;
                            }
                        }
                    }
                }
            }
        }


        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            SomeFunc();
        }

        private void webBrowser1_NewWindow(object sender, CancelEventArgs e)
        {
            //防止弹窗；
            e.Cancel = true;
            string url = this.webBrowser1.StatusText;
            this.webBrowser1.Url = new Uri(url);
        }

        private void webBrowser1_DocumentCompleted(object sender, WebBrowserDocumentCompletedEventArgs e)
        {

        }
    }
}
