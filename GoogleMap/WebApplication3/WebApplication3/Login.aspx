<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Login.aspx.cs" Inherits="WebApplication3.Login" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
                <table border="0" cellspacing="0" cellpadding="0" width="100%">
        	<tr>
        		<td width="300px">&nbsp;</td><td></td>
        	</tr>
        	<tr>
        		<td>&nbsp;</td><td></td>
        	</tr>
        	<tr>
        		<td>&nbsp;</td><td></td>
        	</tr>
        	<tr>
        		<td>&nbsp;</td><td>用户：&nbsp;<asp:TextBox ID="txtUserName" runat="server"></asp:TextBox></td>
        	</tr>
        	<tr>
        		<td>&nbsp;</td><td>密码：&nbsp;<asp:TextBox ID="txtPwd" runat="server" 
                    TextMode="Password"></asp:TextBox></td>
        	</tr>
        	<tr>
        		<td>&nbsp;</td><td><asp:Button ID="btnLogin" runat="server" Text="登  录" 
                    onclick="btnLogin_Click" /></td>
        	</tr>
        	<tr>
        		<td></td><td></td>
        	</tr>

    </div>
    </form>
</body>
</html>
