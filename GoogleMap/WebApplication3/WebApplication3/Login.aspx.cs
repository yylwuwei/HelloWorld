using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using System.Data.SqlClient;
using System.Collections;
using System.Configuration;

namespace WebApplication3
{
    public partial class Login : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnLogin_Click(object sender, EventArgs e)
        {
            try
            {
                int iCount = 0;
                string connStr = ConfigurationManager.ConnectionStrings["sqlybspConnectionString"].ConnectionString; ;
                SqlConnection conn = new SqlConnection(connStr);
                conn.Open();

                string sql = "select * from MapUser where ID=1";
                SqlCommand cmd = new SqlCommand(sql, conn);
                SqlDataReader sdr = cmd.ExecuteReader();
                DataTable dt = new DataTable();
                dt.Load(sdr);

                if (dt.Rows[0]["UserName"].ToString() == txtUserName.Text.Trim() && dt.Rows[0]["Pwd"].ToString() == txtPwd.Text.Trim())
                {
                    Session["UserName"] = txtUserName.Text.Trim();
                    Response.Redirect("List.aspx");
                }
                else
                {
                    Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "", "<script>alert('用户名或者密码不正确！');</script>");
                }
            }
            catch (System.Exception ex)
            {
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "", "<script>alert('位置错误！');</script>");            	
            }

        }
    }
}
