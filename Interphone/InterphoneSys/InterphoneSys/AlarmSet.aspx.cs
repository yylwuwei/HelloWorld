﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace InterphoneSys
{
    public partial class AlarmSet : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            DropDownList1.Items.Add("基站1");
            DropDownList1.Items.Add("基站2");
            DropDownList1.Items.Add("基站3");
        }
    }
}
