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

namespace WebApplication3.T2Admin
{
    public partial class T2List : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session["T2UserName"] == null)
            {
                Response.Redirect("T2Login.aspx");
            }
        }

        protected void btnNew_Click(object sender, EventArgs e)
        {
            Response.Redirect("T2Admin.aspx");
        }

        protected void btnEdit_Click(object sender, EventArgs e)
        {
            string strID = "";
            int iIndex = GridView1.SelectedIndex;
            if (iIndex != -1)
            {
                strID = GridView1.DataKeys[iIndex][0].ToString();
                Response.Redirect("T2Admin.aspx?strID=" + strID);
            }
            else
            {
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "myscript", "<script>alert('您必须先在上表中选择某个告警项！');</script>");
            }
        }

        protected void btnDel_Click(object sender, EventArgs e)
        {
            string strID = "";
            int iIndex = GridView1.SelectedIndex;
            if (iIndex != -1)
            {
                strID = GridView1.DataKeys[iIndex][0].ToString();
                //Response.Redirect("Admin.aspx?strID=" + strID);
                string connStr = ConfigurationManager.ConnectionStrings["sqlybspConnectionString"].ConnectionString;
                SqlConnection conn = new SqlConnection(connStr);
                conn.Open();

                string sql = "update T2_MapTable set IsValid='False' where ID=" + strID;
                SqlCommand cmd = new SqlCommand(sql, conn);
                int ret = cmd.ExecuteNonQuery();
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "", "<script>alert('恭喜删除成功！');self.location='T2List.aspx';</script>");
            }
            else
            {
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "myscript", "<script>alert('您必须先在上表中选择某个告警项！');</script>");
            }
        }

        protected void GridView1_RowCommand(object sender, GridViewCommandEventArgs e)
        {
        }

        protected void GridView1_RowDataBound(object sender, GridViewRowEventArgs e)
        {
        }

        protected void btnSaveEx_Click(object sender, EventArgs e)
        {
            string strID = "";
            int iIndex = GridView1.SelectedIndex;
            if (iIndex != -1)
            {
                strID = GridView1.DataKeys[iIndex][0].ToString();
                Response.Redirect("T2Admin.aspx?type=saveEx&strID=" + strID);
            }
            else
            {
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "myscript", "<script>alert('您必须先在上表中选择某个告警项！');</script>");
            }
        }
    }
}
