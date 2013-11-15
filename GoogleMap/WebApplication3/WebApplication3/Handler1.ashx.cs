using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Data;
using System.Data.SqlClient;
using System.Collections;
using System.Web.Script.Serialization;

namespace WebApplication3
{
    /// <summary>
    /// Summary description for $codebehindclassname$
    /// </summary>
    [WebService(Namespace = "http://tempuri.org/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    public class Handler1 : IHttpHandler
    {

        public void ProcessRequest(HttpContext context)
        {
            context.Response.ContentType = "text/plain";

            DataTable dt = new DataTable();

            string connStr = "Data Source=124.248.237.50;Initial Catalog=sqlybsp;Persist Security Info=True;User ID=sqlybsp;Password=gezhi";

            SqlConnection conn = new SqlConnection(connStr);

            conn.Open();

            string sql = "select * from MapTable order by Time desc";

            SqlCommand cmd = new SqlCommand(sql, conn);

            SqlDataReader sdr = cmd.ExecuteReader();

            dt.Load(sdr);

            ArrayList eventList = new ArrayList();
            for (int i = 0; i < dt.Rows.Count; i++)
            {
                string strID = dt.Rows[i]["ID"].ToString();
                string strTitle = dt.Rows[i]["Title"].ToString();
                string strTime = dt.Rows[i]["Time"].ToString();
                string strLat = dt.Rows[i]["Lat"].ToString();
                string strLng = dt.Rows[i]["Lng"].ToString();
                string strContent = dt.Rows[i]["EventContent"].ToString();
                strContent = strContent.Replace("#", "<br/>");
                string strVisible = dt.Rows[i]["IsVisible"].ToString();
                string strType = dt.Rows[i]["Type"].ToString();
                string strValid = dt.Rows[i]["IsValid"].ToString();

                if (strValid.Contains("True") && strVisible.Contains("True"))
//                 if (strVisible.Contains("True"))
                {
                    Hashtable ht = new Hashtable();
                    ht.Add("ID", strID);
                    ht.Add("Title", strTitle);
                    ht.Add("Time", strTime);
                    ht.Add("Lat", strLat);
                    ht.Add("Lng", strLng);
                    ht.Add("EventContent", strContent);
                    ht.Add("Type", strType);
                    ht.Add("IsValid", strType);
                    eventList.Add(ht);
                }
            }
            JavaScriptSerializer ser = new JavaScriptSerializer();
            String jsonStr = ser.Serialize(eventList);
            context.Response.Write(jsonStr);

            sdr.Close();

            conn.Close();

            //context.Response.Write("Hello World");
        }

        public bool IsReusable
        {
            get
            {
                return false;
            }
        }
    }
}
