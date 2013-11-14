using System;
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
    public partial class Admin : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            this.GridView1.Visible = false;
            if (!IsPostBack)
            {
                this.RadioButtonList1.Items.Add(new ListItem("新的报告", "1"));
                this.RadioButtonList1.Items.Add(new ListItem("成功报告", "2"));
                this.RadioButtonList1.Items.Add(new ListItem("失败报告", "3"));
                RadioButtonList1.SelectedIndex = 0;
            }
        }

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
                string connStr = "Data Source=124.248.237.50;Initial Catalog=sqlybsp;Persist Security Info=True;User ID=sqlybsp;Password=gezhi";

                DataTable dt = new DataTable();
                SqlConnection conn = new SqlConnection(connStr);
                conn.Open();
                string sql = "select * from MapTable";
                SqlCommand cmd = new SqlCommand(sql, conn);
                SqlDataReader sdr = cmd.ExecuteReader();
                dt.Load(sdr);
                iCount = dt.Rows.Count;
                sdr.Close();
                conn.Close();

                SqlConnection conn2 = new SqlConnection(connStr);
                conn2.Open();
                string sql2 = "insert into MapTable (ID, Title, Time, Lat, Lng, EventContent, IsVisible, Type, IsValid) values(" +
                    iCount + ",'" + txtTitle.Text.Trim() + "','" + txtTime.Text.Trim() + "'," + float.Parse(txtLat.Text.Trim()) + "," +
                    float.Parse(txtLng.Text.Trim()) + ",'" + txtContent.Text.Trim() + "','" + "True" + "'," + int.Parse(RadioButtonList1.SelectedItem.Value) + ",'" + "True" + "')";
                SqlCommand cmd2 = new SqlCommand(sql2, conn2);
                int ret = cmd2.ExecuteNonQuery();
                conn2.Close();

                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "", "<script>alert('恭喜添加成功！'); location=location;</script>");
                //Response.Redirect("Admin.aspx");
            }
            catch (System.Exception ex)
            {
                Page.ClientScript.RegisterStartupScript(ClientScript.GetType(), "myscript", "<script>alert('请检查，您的填写格式有误，请正确填写表单！');</script>");
            }


        }
    }
}
