using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace ProtectIndexPage
{
    public partial class _Default : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            object obj = Request.Form["TextBox5"];
            if (obj == null)
            {
                Response.Redirect("ErrorPage.aspx");
            }
            else
            {
                String str = Request.Form["TextBox5"].ToString();
                if (!str.Equals("123"))
                {
                    Response.Redirect("ErrorPage.aspx");
                }
            }
        }
    }
}
