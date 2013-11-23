<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="BSInfo.aspx.cs" Inherits="InterphoneSys.BSInfo" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <style type="text/css" media="screen">
                #divContent
        {
            margin: 25px 0px 0px 25px;
        }
        #divTitle
        {
            color: #005831;
        }
        td{ text-align:left; }
        #tableSel td
        {
            padding:0px 0px;	
        }
        body
        {
            font: normal 11px auto "Trebuchet MS" , Verdana, Arial, Helvetica, sans-serif;
            color: #4f6b72;
            background: #E6EAE9;
        }

        table td
        {
            border: #000000 1px solid;
        }
        .tableborder
        {
            border: 1px ridge #000000;
            border-color: #000000 #000000 #000000 #000000;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server">
        <div id="divContent">
        <div id="divTitle">
            <h1>
                基站信息管理</h1>
        </div>
        <hr />
        <br />
        <div>
        <table class="tableborder">
            <tr>
                <td>
                    <table>
                        <tr>
                            <td>
                                <asp:ListBox ID="ListBox2" runat="server" Height="295px" Width="293px">
                                    <asp:ListItem>基站1</asp:ListItem>
                                    <asp:ListItem>基站2</asp:ListItem>
                                    <asp:ListItem>基站3</asp:ListItem>
                                    <asp:ListItem>基站4</asp:ListItem>
                                    <asp:ListItem>基站5</asp:ListItem>
                                    <asp:ListItem>基站6</asp:ListItem>
                                    <asp:ListItem>基站7</asp:ListItem>
                                    <asp:ListItem>基站8</asp:ListItem>
                                </asp:ListBox>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                 <br /><input id="Button3" type="button" value=" 添 加 " onclick="alert('此功能暂未添加！');" /> 
                                &nbsp; &nbsp; &nbsp;
                                <input id="Button4" type="button" value=" 删 除 " onclick="alert('此功能暂未添加！');"/>
                               <br /><br /><br /><br /><br /><br /><br /><br /><br /><br />
                            </td>
                        </tr>
                    </table>
                </td>
                <td>
                    <table>
                        <tr>
                            <td>
                                <img src="images/station1.jpg" />
                            </td>
                        </tr>
                        <tr>
                            <td>
                            <br />
                            <div>
                            当前基站为天河区基站，基站的ID是0005，目前运行正常！
                            </div>
                            <br />
                            </td>
                        </tr>
                    </table>
                </td>
            </tr>
        </table>
        </div>
    </div>
    </form>
</body>
</html>
