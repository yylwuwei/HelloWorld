<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="DownJpgEdit.aspx.cs" Inherits="WebApplication3.DownJpgUI.DownJpgEdit" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>自动下载图片信息编辑页面</title>
    <style type="text/css">
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    <h1>
        <asp:Label ID="lblTitle" runat="server"></asp:Label></h1>
        <hr />
        <br />
        <table id="myTable" border="0" cellspacing="0" cellpadding="0" width="100%">
        	<tr>
        		<td style="width:200px; " >请输入需要的图片网址：</td><td><asp:TextBox ID="txtUrl" 
                    runat="server" Width="533px"></asp:TextBox></td>
        	</tr>
        	<tr>
        		<td >图片自动下载时间周期：</td><td>
                    <asp:TextBox ID="txtTime" runat="server" Width="200px"></asp:TextBox>&nbsp;(h)&nbsp;示例：3.5，以小时为单位，范围是（0.1~48）</td>
        	</tr>
        	<tr>
        		<td >存放图片的文件夹名称：</td><td>
                    <asp:TextBox ID="txtFolderName" runat="server" Width="200px"></asp:TextBox>&nbsp;示例：nanmei</td>
        	</tr>
        	<tr>
           		<td>&nbsp;</td><td></td>
        	</tr>        	        	
        	<tr>
        		<td>
                    </td><td><asp:Button ID="btnSave" runat="server" Text=" 保 存 " 
                        onclick="btnSave_Click" />
                    <asp:Button ID="btnNew" runat="server" onclick="btnNew_Click" Text=" 新 建 " />
                </td>
        	</tr>        	        	
        </table>
        <br />
        <hr />
        <br />
        <a href="DownJpgList.aspx">返回图片列表页面</a>
    </div>
    </form>
</body>
</html>
