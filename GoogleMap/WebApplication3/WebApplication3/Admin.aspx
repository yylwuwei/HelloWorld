<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Admin.aspx.cs" Inherits="WebApplication3.Admin" validateRequest="false" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title></title>
    <style type="text/css">
    #GridView1 TD{word-break:break-all; width:100px;}
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    <h1>地图后台管理--告警信息点查询</h1>
    <hr />
        <asp:GridView ID="GridView1" runat="server" AutoGenerateColumns="False" 
            CellPadding="4" DataKeyNames="ID" DataSourceID="SqlDataSource1" 
            ForeColor="#333333" GridLines="None" AllowPaging="True" 
            AllowSorting="True" PageSize="8" Width="80%">
            <RowStyle BackColor="#EFF3FB" />
            <Columns>
                <asp:CommandField ShowSelectButton="True" />
                <asp:BoundField DataField="ID" HeaderText="ID" ReadOnly="True" 
                    SortExpression="ID" />
                <asp:BoundField DataField="Title" HeaderText="Title" SortExpression="Title" />
                <asp:BoundField DataField="Time" HeaderText="Time" SortExpression="Time" />
                <asp:BoundField DataField="Lat" HeaderText="Lat" SortExpression="Lat" />
                <asp:BoundField DataField="Lng" HeaderText="Lng" SortExpression="Lng" />
                <asp:BoundField DataField="EventContent" HeaderText="EventContent" 
                    SortExpression="EventContent" />
                <asp:CheckBoxField DataField="IsVisible" HeaderText="IsVisible" 
                    SortExpression="IsVisible" />
                <asp:BoundField DataField="Type" HeaderText="Type" SortExpression="Type" />
                <asp:CheckBoxField DataField="IsValid" HeaderText="IsValid" 
                    SortExpression="IsValid" />
            </Columns>
            <FooterStyle BackColor="#507CD1" Font-Bold="True" ForeColor="White" />
            <PagerStyle BackColor="#2461BF" ForeColor="White" HorizontalAlign="Center" />
            <SelectedRowStyle BackColor="#D1DDF1" Font-Bold="True" ForeColor="#333333" />
            <HeaderStyle BackColor="#507CD1" Font-Bold="True" ForeColor="White" />
            <EditRowStyle BackColor="#2461BF" />
            <AlternatingRowStyle BackColor="White" />
        </asp:GridView>
        <asp:SqlDataSource ID="SqlDataSource1" runat="server" 
            ConnectionString="<%$ ConnectionStrings:sqlybspConnectionString %>" 
            SelectCommand="SELECT * FROM [MapTable] order by Type"></asp:SqlDataSource>
        <br />
        <h1>地图后台管理--告警信息点增加</h1>
        <hr />
        <table border="0" cellspacing="0" cellpadding="0" width="100%">
        	<tr>
        		<td width="100px">标题：</td><td>
                    <asp:TextBox ID="txtTitle" runat="server" Width="366px"></asp:TextBox>&nbsp;&nbsp;此标题用于显示在左边栏</td>
        	</tr>
        	<tr>
        		<td>时间：</td><td>
                    <asp:TextBox ID="txtTime" runat="server" Width="366px"></asp:TextBox>&nbsp;&nbsp;格式示例：2012/12/18 09:08:20<td>
        	</tr>
        	<tr>
        		<td>内容：</td><td>
                <asp:TextBox ID="txtContent" runat="server" Height="101px" 
                    Width="366px" TextMode="MultiLine"></asp:TextBox>&nbsp;&nbsp;点击地图上的告警标志，会显示此内容<td>
        	</tr>
        	<tr>
        		<td>类型：</td><td>
                    <asp:RadioButtonList ID="RadioButtonList1" runat="server" RepeatDirection="Horizontal">
                    </asp:RadioButtonList>
                    <td>
        	</tr>
        	<tr>
        		<td>纬度：</td><td><asp:TextBox ID="txtLat" runat="server" Width="366px"></asp:TextBox>&nbsp;&nbsp;示例：31.820587<td>
        	</tr>
        	<tr>
        		<td>经度：</td><td>
                    <asp:TextBox ID="txtLng" runat="server" Width="366px"></asp:TextBox>&nbsp;&nbsp;示例：117.227239<td>
        	</tr>
        	<tr>
        		<td></td><td> 
                    <asp:Button ID="Button1" runat="server" Text="点击增加" onclick="Button1_Click" /> &nbsp;  ps: 所有项必须正确填写，否则提交失败。         <td>
        	</tr>
        </table>
            
    </div>
    </form>
</body>
</html>
