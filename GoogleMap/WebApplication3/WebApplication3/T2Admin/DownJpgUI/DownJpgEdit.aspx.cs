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

namespace WebApplication3.DownJpgUI
{
    public partial class DownJpgEdit : System.Web.UI.Page
    {
        private static string strID = "";
        private string connStr = ConfigurationManager.ConnectionStrings["sqlybspConnectionString"].ConnectionString;

        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session["T2UserName"] == null)
            {
                Response.Redirect("../T2Login.aspx");
            }

            if (!IsPostBack)
            {
                if (Request.QueryString["strID"] == null)
                {
                    lblTitle.Text = "新建一个图片抓取";
                    btnNew.Visible = true;
                    btnSave.Visible = false;
                }
                else
                {
                    lblTitle.Text = "编辑一个图片抓取";
                    this.btnSave.Visible = true;
                    btnNew.Visible = false;
                }

                if (Request.QueryString["strID"] != null)
                {
                    strID = Request.QueryString["strID"].ToString();
                    DataTable dt = new DataTable();
                    SqlConnection conn = new SqlConnection(connStr);
                    conn.Open();
                    string sql = "select * from DownJpgUrlList where ID=" + strID;
                    SqlCommand cmd = new SqlCommand(sql, conn);
                    SqlDataReader sdr = cmd.ExecuteReader();
                    dt.Load(sdr);
                    int iCount = 0;
                    iCount = dt.Rows.Count;
                    if (iCount == 1)
                    {
                        txtUrl.Text = dt.Rows[0]["JpgUrl"].ToString();
                        txtFolderName.Text = dt.Rows[0]["FolderName"].ToString();
                        txtTime.Text = dt.Rows[0]["TimeCycle"].ToString();
                    }
                    sdr.Close();
                    conn.Close();
                }
            }
        }

        private int GetNextID()
        {
            int iCount = 0;
            SqlConnection conn = new SqlConnection(connStr);
            conn.Open();

            DataTable dt = new DataTable();
            string sql = "select * from DownJpgUrlList";
            SqlCommand cmd = new SqlCommand(sql, conn);
            SqlDataReader sdr = cmd.ExecuteReader();
            dt.Load(sdr);
            iCount = dt.Rows.Count;
            sdr.Close();
            conn.Close();

            return iCount;
        }

        private void CheckInput()
        {
            if (txtTime.Text.Trim().Length == 0 ||
                txtUrl.Text.Trim().Length == 0 ||
                txtFolderName.Text.Trim().Length == 0)
            {
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "myscript", "<script>alert('表单必须全部填写完毕才能添加成功！');</script>");
                return;
            }

            float ff = float.Parse(txtTime.Text.Trim());
            if (ff < 0.1 || ff > 48.0)
            {
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "myscript", "<script>alert('时间范围必须在0.1~48小时之间！');</script>");
                return;
            }
        }

        protected void btnSave_Click(object sender, EventArgs e)
        {
            try
            {
                CheckInput();

                SqlConnection conn = new SqlConnection(connStr);
                conn.Open();

                string sql = "update DownJpgUrlList set JpgUrl='" + txtUrl.Text.Trim() + "', FolderName='" + txtFolderName.Text.Trim() + "', TimeCycle=" + txtTime.Text.Trim() + " where ID=" + strID;
                SqlCommand cmd = new SqlCommand(sql, conn);
                int ret = cmd.ExecuteNonQuery();
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "", "<script>alert('恭喜编辑成功！');self.location='DownJpgList.aspx';</script>");
                conn.Close();
            }
            catch (System.Exception ex)
            {
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "myscript", "<script>alert('请检查，您的填写格式有误，请正确填写表单！');</script>");
            }

        }

        protected void btnNew_Click(object sender, EventArgs e)
        {
            try
            {
                CheckInput();

                SqlConnection conn = new SqlConnection(connStr);
                conn.Open();

                int iCount = GetNextID();
                string sql2 = "insert into DownJpgUrlList (ID, JpgUrl, FolderName, TimeCycle, IsValid) values(" +
                    iCount + ",'" + txtUrl.Text.Trim() + "','" + txtFolderName.Text.Trim() + "'," + float.Parse(txtTime.Text.Trim()) + ",'True')";
                SqlCommand cmd2 = new SqlCommand(sql2, conn);
                int ret = cmd2.ExecuteNonQuery();
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "", "<script>alert('恭喜添加成功！');self.location='DownJpgList.aspx';</script>");
                conn.Close();
            }
            catch (System.Exception ex)
            {
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "myscript", "<script>alert('请检查，您的填写格式有误，请正确填写表单！');</script>");
            }

        }
    }
}
