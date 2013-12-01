using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;
using System.Collections;
using System.Configuration;
using System.Net;
using System.IO;
using System.Data.SqlClient;
using System.Collections;
using System.Configuration;
using System.Data;

namespace WebApplication3.DownJpgUI
{
    public partial class DownJpgList : System.Web.UI.Page
    {
        private string connStr = ConfigurationManager.ConnectionStrings["sqlybspConnectionString"].ConnectionString;

        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session["UserName"] == null)
            {
                Response.Redirect("../Login.aspx");
            }

            if (GetRunState())
            {
                lblRunStart.Text = "已经开始，正在抓图";
            }
            else
            {
                lblRunStart.Text = "已经结束，停止抓图";
            }
        }

        protected void btnAdd_Click(object sender, EventArgs e)
        {
            Response.Redirect("DownJpgEdit.aspx");
        }

        protected void btnEdit_Click(object sender, EventArgs e)
        {
            string strID = "";
            int iIndex = GridView1.SelectedIndex;
            if (iIndex != -1)
            {
                strID = GridView1.DataKeys[iIndex][0].ToString();
                Response.Redirect("DownJpgEdit.aspx?strID=" + strID);
            }
            else
            {
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "myscript", "<script>alert('您必须先在上表中选择某行！');</script>");
            }
        }

        protected void btnDel_Click(object sender, EventArgs e)
        {
            string strID = "";
            int iIndex = GridView1.SelectedIndex;
            if (iIndex != -1)
            {
                strID = GridView1.DataKeys[iIndex][0].ToString();
                SqlConnection conn = new SqlConnection(connStr);
                conn.Open();

                string sql = "update DownJpgUrlList set IsValid='False' where ID=" + strID;
                SqlCommand cmd = new SqlCommand(sql, conn);
                int ret = cmd.ExecuteNonQuery();
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "", "<script>alert('恭喜删除成功！');self.location='DownJpgList.aspx';</script>");
            }
            else
            {
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "myscript", "<script>alert('您必须先在上表中选择某行！');</script>");
            }
        }

        private bool GetRunState()
        {
            DataTable dt = new DataTable();
            SqlConnection conn = new SqlConnection(connStr);
            conn.Open();
            string sql = "select * from DownJpgCheck where ID = 0";
            SqlCommand cmd = new SqlCommand(sql, conn);
            SqlDataReader sdr = cmd.ExecuteReader();
            dt.Load(sdr);
            return Convert.ToBoolean(dt.Rows[0]["IsRun"].ToString());
        }

        private bool SetRunState(bool bRun)
        {
            SqlConnection conn = new SqlConnection(connStr);
            conn.Open();
            string sql;
            if (bRun)
            {
                sql = "update DownJpgCheck set IsRun= 'True', StartTime='" + DateTime.Now.ToString() +"' where ID = 0";
            }
            else
            {
                sql = "update DownJpgCheck set IsRun= 'False'where ID = 0";
            }
            SqlCommand cmd = new SqlCommand(sql, conn);
            int ret = cmd.ExecuteNonQuery();
            if (ret == 1)
            {
                return true;
            }
            return false;
        }

        protected void btnStart_Click(object sender, EventArgs e)
        {
            if (GetRunState())
            {
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "myscript", "<script>alert('您已经处于开始状态，不需要重复点击！');</script>");
                return;
            }
            if (SetRunState(true))
            {
                lblRunStart.Text = "已经开始，正在抓图";
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "myscript", "<script>alert('成功开始抓图！');</script>");
            }
        }

        protected void btnStop_Click(object sender, EventArgs e)
        {
            if (!GetRunState())
            {
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "myscript", "<script>alert('您已经处于停止抓图状态，不需要重复点击！');</script>");
                return;
            }
            if (SetRunState(false))
            {
                lblRunStart.Text = "已经结束，停止抓图";
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "myscript", "<script>alert('成功停止抓图！');</script>");
            }
        }
    }
}
