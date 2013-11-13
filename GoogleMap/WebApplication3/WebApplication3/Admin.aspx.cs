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
            if (!IsPostBack)
            {
                this.RadioButtonList1.Items.Add(new ListItem("新的报告", "1"));
                this.RadioButtonList1.Items.Add(new ListItem("成功报告", "2"));
                this.RadioButtonList1.Items.Add(new ListItem("失败报告", "3"));
            }
        }

        protected void Button1_Click(object sender, EventArgs e)
        {
            DataTable dt = new DataTable();

            string connStr = "Data Source=124.248.237.50;Initial Catalog=sqlybsp;Persist Security Info=True;User ID=sqlybsp;Password=gezhi";

            SqlConnection conn = new SqlConnection(connStr);

            conn.Open();

            string sql = "select * from MapTable";

            SqlCommand cmd = new SqlCommand(sql, conn);

            SqlDataReader sdr = cmd.ExecuteReader();

            dt.Load(sdr);

            //dt.Rows.Count

            //string sqlInsert = "insert "



            string strSql = "insert into MapTable (ID, Title, Time, Lat, Lng, EventContent, IsVisible, Type, IsValid) values(" +
                dt.Rows.Count + ",'" + txtTitle.Text.Trim() + "'," + DateTime.Parse(txtTime.Text.Trim()) + "," + float.Parse(txtLat.Text.Trim()) + "," +
                float.Parse(txtLng.Text.Trim()) + ",'" + "True" + "'," + int.Parse(RadioButtonList1.SelectedItem.Value) +",'"+ "True" + "')";

            SqlCommand cmd2 = new SqlCommand(strSql, conn);
            int ret = cmd.ExecuteNonQuery();

            sdr.Close();

            conn.Close();

        }
    }
}
