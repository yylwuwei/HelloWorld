<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="IPSet.aspx.cs" Inherits="InterphoneSys.IPSet" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>IP参数配置</title>
    <style type="text/css">
        #divContent
        {
            margin: 25px 0px 0px 25px;
        }
        #divTitle
        {
            font: normal 11px auto "Trebuchet MS" , Verdana, Arial, Helvetica, sans-serif;
            color: #005831;
        }
        #divIPSet
        {
            width: 702px;
        }
        #divIPLeft
        {
            float: left;
            width: 200px;
            height: 460px;
            background: #FFFFFF;
        }
        #divIPMiddle
        {
            float: left;
            width: 2px;
            height: 460px;
            background: #FFFFFF;
        }
        #divIPRight
        {
            float: left;
            width: 500px;
            height: 460px;
            background: #FFFFFF;
        }
        #divIPLeftTop
        {
            margin: 15px 0 0 15px;
        }
        #tableIPSet td
        {
            padding: 5px 0px 5px 0px;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div id="divContent">
        <div id="divTitle">
            <h1>
                基站IP参数配置</h1>
        </div>
        <hr />
        <br />
        <table border="1" cellspacing="0" cellpadding="0" width="702px">
        	<tr>
        		<td>
        <div id="divIPSet">
            <div id="divIPLeft">
                <div id="divIPLeftTop">
                    <asp:ListBox ID="ListBox1" runat="server" Height="352px" Width="175px">
                        <asp:ListItem>基 站 1</asp:ListItem>
                        <asp:ListItem>基 站 2</asp:ListItem>
                        <asp:ListItem>基 站 3</asp:ListItem>
                        <asp:ListItem>基 站 4</asp:ListItem>
                        <asp:ListItem>基 站 5</asp:ListItem>
                        <asp:ListItem>基 站 6</asp:ListItem>
                    </asp:ListBox>
                </div>
                <div id="divIPLeftBottom">
                    <br />
                    &nbsp;&nbsp;
                    <input type="button" value=" 确 定 " />&nbsp;&nbsp;
                    <input type="button" value=" 重 置 " />
                </div>
            </div>
            <div id="divIPMiddle">
                <table border="1" cellspacing="0" cellpadding="0" width="1px" height="460px">
                </table>
            </div>
            <div id="divIPRight">
                <br />
                <table id="tableIPSet" border="0" cellspacing="0" cellpadding="0" width="100%" >
                    <tr>
                        <td style="text-align: right; width: 150px;">
                            系统类型：
                        </td>
                        <td>
                            <input type="text" value="IP站点连接" style="width: 250px" />
                        </td>
                    </tr>
                    <tr>
                        <td style="text-align: right;">
                            基站ID：
                        </td>
                        <td>
                            <input type="text" style="width: 250px" />
                        </td>
                    </tr>
                    <tr>
                        <td style="text-align: right;">
                            基站IP地址：
                        </td>
                        <td>
                            <input type="text" value="192.168.27.159" style="width: 250px" />
                        </td>
                    </tr>
                    <tr>
                        <td style="text-align: right;">
                            IP地址类型：
                        </td>
                        <td>
                            <input type="text" style="width: 250px; height: 70px;" />
                        </td>
                    </tr>
                    <tr>
                        <td style="text-align: right;">
                            系统类型：
                        </td>
                        <td>
                            <input type="text" style="width: 250px" />
                        </td>
                    </tr>
                    <tr>
                        <td style="text-align: right;">
                            基站ID：
                        </td>
                        <td>
                            <input type="text" style="width: 250px" />
                        </td>
                    </tr>
                    <tr>
                        <td style="text-align: right;">
                            基站IP地址：
                        </td>
                        <td>
                            <input type="text" style="width: 250px" />
                        </td>
                    </tr>
                    <tr>
                        <td style="text-align: right;">
                            IP地址类型：
                        </td>
                        <td>
                            <input type="text" style="width: 250px; height: 70px;" />
                        </td>
                    </tr>
                </table>
            </div>
        </div>
        </td>
        	</tr>
        </table>
    </div>
    </form>
</body>
</html>
