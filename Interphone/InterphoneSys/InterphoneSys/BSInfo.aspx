<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="BSInfo.aspx.cs" Inherits="InterphoneSys.BSInfo" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <style type="text/css" media="screen">
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
    <div>
        <table class="tableborder">
            <tr>
                <td>
                    <table>
                        <tr>
                            <td>
                                <asp:ListBox ID="ListBox1" runat="server" Height="295px" Width="293px">
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
                                 <br /><input id="Button1" type="button" value=" 添 加 " /> 
                                &nbsp; &nbsp; &nbsp;
                                <input id="Button2" type="button" value=" 删 除 " />
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
    </form>
</body>
</html>
