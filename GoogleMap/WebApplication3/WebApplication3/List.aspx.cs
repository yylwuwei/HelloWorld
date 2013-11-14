using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace WebApplication3
{
    public partial class List : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnNew_Click(object sender, EventArgs e)
        {

        }

        protected void btnEdit_Click(object sender, EventArgs e)
        {
            int iIndex = GridView1.SelectedIndex;
            string id = GridView1.DataKeys[iIndex][0].ToString();
        }

        protected void btnDel_Click(object sender, EventArgs e)
        {
        }

        protected void GridView1_RowCommand(object sender, GridViewCommandEventArgs e)
        {
        }

        protected void GridView1_RowDataBound(object sender, GridViewRowEventArgs e)
        {
        }
    }
}
