using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Net;
using System.IO;
using System.Configuration;
using System.Web.Configuration; 

namespace ProtectIndexPage
{
    //手动构造post数据，提交，此种方式页面跳转，关键在于构造的form的onload事件
    public class RemotePost
    {
        private System.Collections.Specialized.NameValueCollection Inputs = new System.Collections.Specialized.NameValueCollection();

        public string Url = "";
        public string Method = "post";
        public string FormName = "form1";

        public void Add(string name, string value)
        {
            Inputs.Add(name, value);
        }

        public void Post()
        {
            System.Web.HttpContext.Current.Response.Clear();
            System.Web.HttpContext.Current.Response.Write("<html><head>");
            System.Web.HttpContext.Current.Response.Write(string.Format("</head><body onload=\"document.{0}.submit()\">", FormName));
            System.Web.HttpContext.Current.Response.Write(string.Format("<form name=\"{0}\" method=\"{1}\" action=\"{2}\" >",FormName,Method,Url));
            for(int i=0;i< Inputs.Keys.Count;i++)
            {
                System.Web.HttpContext.Current.Response.Write(string.Format("<input name=\"{0}\" type=\"hidden\" value=\"{1}\">",Inputs.Keys[i],Inputs[Inputs.Keys[i]]));
            }
            System.Web.HttpContext.Current.Response.Write("</form>");
            System.Web.HttpContext.Current.Response.Write("</body></html>");
            System.Web.HttpContext.Current.Response.End();
        }
    }

    public partial class ModleBaidu : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            form2.DefaultButton = "ImageButton1";
        }

        protected void Button5_Click(object sender, EventArgs e)
        {
        }

        protected void ImageButton1_Click(object sender, ImageClickEventArgs e)
        {
            //读取Web.Config配置中的值
            Configuration config = WebConfigurationManager.OpenWebConfiguration(Request.ApplicationPath);
            AppSettingsSection appSettings = (AppSettingsSection)config.GetSection("appSettings");
            string strProtectPageUrl = appSettings.Settings["WebProtectPageUrl"].Value;
            string strKeyToProtectPage = appSettings.Settings["WebKeyToProtectPage"].Value;
            //如果匹配Key值，则提交
            if (TextBox5.Text.Trim().Equals(strKeyToProtectPage))
            {
                //手动构造post数据，提交，此种方式页面跳转，关键在于构造的form的onload事件
                RemotePost remotePostObj = new RemotePost();
                remotePostObj.Url = strProtectPageUrl;
                //此处可以添加多个参数来传递
                remotePostObj.Add("KeyToProtectPage", strKeyToProtectPage);
                remotePostObj.Post();
            }
            else //如果不拼配Key值，则转入百度查询
            {
                String str;
                str = "http://www.baidu.com/s?wd=" + TextBox5.Text + "&rsv_bp=0&rsv_spt=3&ie=utf-8&rsv_sug3=7&rsv_sug=0&rsv_sug4=719&rsv_sug1=4&inputT=3435";
                Response.Redirect(str);
            }
        }
    }
}
