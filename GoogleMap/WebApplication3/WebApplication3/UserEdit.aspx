﻿<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="UserEdit.aspx.cs" Inherits="WebApplication3.UserEdit" %>

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
        		<td>&nbsp;</td><td>请输入重置的用户名和密码：</td>
        	</tr>
        	<tr>
        		<td>&nbsp;</td><td>重置用户：&nbsp;<asp:TextBox ID="txtUser" runat="server"></asp:TextBox></td>
        	</tr>
        	<tr>
        		<td>&nbsp;</td><td>新的密码：&nbsp;<asp:TextBox ID="txtPwd" runat="server" 
                    TextMode="Password"></asp:TextBox></td>
        	</tr>
        	<tr>
        		<td>&nbsp;</td><td>重复密码：&nbsp;<asp:TextBox ID="txtPwd2" runat="server" 
                    TextMode="Password"></asp:TextBox></td>
        	</tr>
        	<tr>
        		<td>&nbsp;</td><td>
                <asp:Button ID="btnSave" runat="server" Text=" 保 存 " onclick="btnSave_Click" />
                </td>
        	</tr>
        	<tr>
        		<td></td><td></td>
        	</tr>

    </div>
    </form>
</body>
</html>
