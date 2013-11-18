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
    public partial class UserEdit : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session["UserName"] == null)
            {
                Response.Redirect("Login.aspx");
            }
        }

        protected void btnSave_Click(object sender, EventArgs e)
        {

            if (txtUser.Text.Trim().Length == 0 ||
                txtPwd.Text.Trim().Length == 0 ||
                txtPwd2.Text.Trim().Length == 0)
            {
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "", "<script>alert('信息未填写完整，不能保存');</script>");
                return;
            }

            if (txtPwd.Text.Trim() != txtPwd2.Text.Trim())
            {
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "", "<script>alert('两次输入的密码不一致！');</script>");
                return;
            }

            try
            {
                int iCount = 0;
                string connStr = ConfigurationManager.ConnectionStrings["sqlybspConnectionString"].ConnectionString;
                SqlConnection conn = new SqlConnection(connStr);
                conn.Open();

                string sql = "update MapUser set UserName='" + txtUser.Text.Trim() + "', Pwd='" + txtPwd.Text.Trim() + "' where ID=1";
                SqlCommand cmd = new SqlCommand(sql, conn);
                int ret = cmd.ExecuteNonQuery();
                if (ret == 1)
                {
                    Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "", "<script>alert('恭喜重置用户成功！');self.location='login.aspx';</script>");
                }
            }
            catch (System.Exception ex)
            {
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "", "<script>alert('未知错误，请联系管理员！');</script>");            	
            }

        }
    }
}
