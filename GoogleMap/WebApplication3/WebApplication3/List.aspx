<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="List.aspx.cs" Inherits="WebApplication3.List" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    <h1>地图后台管理--告警信息点查询</h1>
    <hr />
        <asp:GridView ID="GridView1" runat="server" AutoGenerateColumns="False" 
            CellPadding="3" DataKeyNames="ID" DataSourceID="SqlDataSource1" AllowPaging="True" 
            AllowSorting="True" Width="80%" BackColor="#DEBA84" 
            BorderColor="#DEBA84" BorderStyle="None" BorderWidth="1px" CellSpacing="2" 
            onrowcommand="GridView1_RowCommand" 
            onrowdatabound="GridView1_RowDataBound">
            <RowStyle BackColor="#FFF7E7" ForeColor="#8C4510" />
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
            <FooterStyle BackColor="#F7DFB5" ForeColor="#8C4510" />
            <PagerStyle ForeColor="#8C4510" HorizontalAlign="Center" />
            <SelectedRowStyle BackColor="#738A9C" Font-Bold="True" ForeColor="White" />
            <HeaderStyle BackColor="#A55129" Font-Bold="True" ForeColor="White" />
        </asp:GridView>
        <asp:SqlDataSource ID="SqlDataSource1" runat="server" 
            ConnectionString="<%$ ConnectionStrings:sqlybspConnectionString %>" 
            SelectCommand="SELECT * FROM [MapTable] where IsValid = 'True' order by Type "></asp:SqlDataSource>
            
            <br/>
            <hr />
            <br />
            
            <table border="0" cellspacing="0" cellpadding="0" width="100%">
        	<tr>
        		<td width="300px"> 
                    <asp:Button ID="btnNew" runat="server" Text=" 新 增 " onclick="btnNew_Click" />&nbsp; &nbsp; 
                    <asp:Button ID="btnEdit" runat="server" Text=" 修 改 " onclick="btnEdit_Click" />&nbsp; &nbsp;
                     <asp:Button ID="btnDel" runat="server" Text=" 删 除 " onclick="btnDel_Click" /></td><td>注：修改和删除告警点，需要先在上表中选中某行！</td>
        	</tr>
        </table>
        
        <br />
        <a href="Map.aspx">点击进入前台地图页</a>
        <br />
        <br />
        <a href="UserEdit.aspx">点击进入用户信息编辑页</a>
        <br />
        <br />
        <a href="GetPos.aspx">点击进入获取经纬度信息页</a>

    </div>
    </form>
</body>
</html>
