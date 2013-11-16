﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using System.Data.SqlClient;
using System.Collections;

namespace WebApplication3
{
    public partial class List : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session["UserName"] == null)
            {
                Response.Redirect("Login.aspx");
            }
        }

        protected void btnNew_Click(object sender, EventArgs e)
        {
            Response.Redirect("Admin.aspx");
        }

        protected void btnEdit_Click(object sender, EventArgs e)
        {
            string strID = "";
            int iIndex = GridView1.SelectedIndex;
            if (iIndex != -1)
            {
                strID = GridView1.DataKeys[iIndex][0].ToString();
                Response.Redirect("Admin.aspx?strID=" + strID);
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
                string connStr = "Data Source=124.248.237.50;Initial Catalog=sqlybsp;Persist Security Info=True;User ID=sqlybsp;Password=gezhi";
                SqlConnection conn = new SqlConnection(connStr);
                conn.Open();

                string sql = "update MapTable set IsValid='False' where ID=" + strID;
                SqlCommand cmd = new SqlCommand(sql, conn);
                int ret = cmd.ExecuteNonQuery();
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "", "<script>alert('恭喜删除成功！');self.location='list.aspx';</script>");
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
    }
}
