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
    public partial class T2Admin : System.Web.UI.Page
    {
        private static string strID = "";
        private static string connStr = ConfigurationManager.ConnectionStrings["sqlybspConnectionString"].ConnectionString;

        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session["T2UserName"] == null)
            {
                Response.Redirect("T2Login.aspx");
            }

            this.GridView1.Visible = false;
            if (!IsPostBack)
            {
                this.RadioButtonList1.Items.Add(new ListItem("新的预告", "1"));
                this.RadioButtonList1.Items.Add(new ListItem("成功预告", "2"));
                this.RadioButtonList1.Items.Add(new ListItem("失败预告", "3"));
                this.RadioButtonList1.Items.Add(new ListItem("同时显示的成功报告", "4"));
                this.RadioButtonList1.Items.Add(new ListItem("Type1", "5"));
                this.RadioButtonList1.Items.Add(new ListItem("Type2", "6"));
                RadioButtonList1.SelectedIndex = 0;
                this.btnSave.Visible = false;
                this.Button1.Visible = false;

                if (Request.QueryString["strID"] == null)
                {
                    lblTitle.Text = "新建";
                    this.Button1.Visible = true;
                }
                else if (Request.QueryString["strID"] != null && Request.QueryString["type"] != null)
                {
                    lblTitle.Text = "另存为";
                    this.Button1.Visible = true;
                }
                else if (Request.QueryString["strID"] != null && Request.QueryString["type"] == null)
                {
                    lblTitle.Text = "编辑";
                    this.btnSave.Visible = true;
                }

                if (Request.QueryString["strID"] != null)
                {
                    strID = Request.QueryString["strID"].ToString();
                    DataTable dt = new DataTable();
                    SqlConnection conn = new SqlConnection(connStr);
                    conn.Open();
                    string sql = "select * from T2_MapTable where ID=" + strID;
                    SqlCommand cmd = new SqlCommand(sql, conn);
                    SqlDataReader sdr = cmd.ExecuteReader();
                    dt.Load(sdr);
                    int iCount = 0;
                    iCount = dt.Rows.Count;
                    if (iCount == 1)
                    {
                        txtTitle.Text = dt.Rows[0]["Title"].ToString();
                        txtTime.Text = dt.Rows[0]["Time"].ToString();
                        txtLat.Text = dt.Rows[0]["Lat"].ToString();
                        txtLng.Text = dt.Rows[0]["Lng"].ToString();
                        txtContent.Text = dt.Rows[0]["EventContent"].ToString();
                        string strType = dt.Rows[0]["Type"].ToString();
                        RadioButtonList1.SelectedIndex = Convert.ToInt32(strType) - 1;
                    }
                    sdr.Close();
                    conn.Close();
                }

            }

        }

        //new
        protected void Button1_Click(object sender, EventArgs e)
        {

            try
            {
                if (txtTitle.Text.Trim().Length == 0 ||
                    txtContent.Text.Trim().Length == 0 ||
                    txtTime.Text.Trim().Length == 0 ||
                    txtLat.Text.Trim().Length == 0 ||
                    txtLng.Text.Trim().Length == 0)
                {
                    Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "myscript", "<script>alert('表单必须全部填写完毕才能添加成功！');</script>");
                    return;
                }

                int iCount = 0;
                SqlConnection conn = new SqlConnection(connStr);
                conn.Open();

                DataTable dt = new DataTable();
                string sql = "select * from T2_MapTable";
                SqlCommand cmd = new SqlCommand(sql, conn);
                SqlDataReader sdr = cmd.ExecuteReader();
                dt.Load(sdr);
                iCount = dt.Rows.Count;
                sdr.Close();
                conn.Close();

                SqlConnection conn2 = new SqlConnection(connStr);
                conn2.Open();
                string sql2 = "insert into T2_MapTable (ID, Title, Time, Lat, Lng, EventContent, IsVisible, Type, IsValid) values(" +
                    iCount + ",'" + txtTitle.Text.Trim() + "','" + txtTime.Text.Trim() + "'," + float.Parse(txtLat.Text.Trim()) + "," +
                    float.Parse(txtLng.Text.Trim()) + ",'" + txtContent.Text.Trim() + "','" + "True" + "'," + int.Parse(RadioButtonList1.SelectedItem.Value) + ",'" + "True" + "')";
                SqlCommand cmd2 = new SqlCommand(sql2, conn2);
                int ret = cmd2.ExecuteNonQuery();
                conn2.Close();
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "", "<script>alert('恭喜添加成功！');self.location='T2List.aspx';</script>");
            }
            catch (System.Exception ex)
            {
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "myscript", "<script>alert('请检查，您的填写格式有误，请正确填写表单！');</script>");
            }
        }

        //save
        protected void btnSave_Click(object sender, EventArgs e)
        {
            try
            {
                if (txtTitle.Text.Trim().Length == 0 ||
                    txtContent.Text.Trim().Length == 0 ||
                    txtTime.Text.Trim().Length == 0 ||
                    txtLat.Text.Trim().Length == 0 ||
                    txtLng.Text.Trim().Length == 0)
                {
                    Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "myscript", "<script>alert('表单必须全部填写完毕才能添加成功！');</script>");
                    return;
                }

                int iCount = 0;
                SqlConnection conn = new SqlConnection(connStr);
                conn.Open();

                string sql = "update T2_MapTable set Title='" + txtTitle.Text.Trim() + "', Time='" + txtTime.Text.Trim() + "', EventContent='" + txtContent.Text.Trim() +
                    "', Lat=" + txtLat.Text.Trim() + ", Lng=" + txtLng.Text.Trim() + ", Type=" + int.Parse(RadioButtonList1.SelectedItem.Value) + " where ID=" + strID;
                SqlCommand cmd = new SqlCommand(sql, conn);
                int ret = cmd.ExecuteNonQuery();
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "", "<script>alert('恭喜编辑成功！');self.location='T2List.aspx';</script>");
            }
            catch (System.Exception ex)
            {
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "myscript", "<script>alert('请检查，您的填写格式有误，请正确填写表单！');</script>");
            }

        }
    }
}
