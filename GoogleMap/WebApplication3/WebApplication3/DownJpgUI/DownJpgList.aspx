<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="DownJpgList.aspx.cs" Inherits="WebApplication3.DownJpgUI.DownJpgList" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    <h1>自动下载列表页面</h1>
    <hr />
    <br />
        <asp:GridView ID="GridView1" runat="server" AutoGenerateColumns="False" 
            BackColor="White" BorderColor="#E7E7FF" BorderStyle="None" BorderWidth="1px" 
            CellPadding="3" DataKeyNames="ID" DataSourceID="SqlDataSource1" 
            GridLines="Horizontal" Width="1195px" AllowPaging="True" 
            AllowSorting="True">
            <RowStyle BackColor="#E7E7FF" ForeColor="#4A3C8C" />
            <Columns>
                <asp:CommandField ShowSelectButton="True" />
                <asp:BoundField DataField="ID" HeaderText="ID" ReadOnly="True" 
                    SortExpression="ID" />
                <asp:BoundField DataField="JpgUrl" HeaderText="JpgUrl" 
                    SortExpression="JpgUrl" />
                <asp:BoundField DataField="FolderName" HeaderText="FolderName" 
                    SortExpression="FolderName" />
                <asp:BoundField DataField="TimeCycle" HeaderText="TimeCycle" 
                    SortExpression="TimeCycle" />
                <asp:CheckBoxField DataField="IsValid" HeaderText="IsValid" 
                    SortExpression="IsValid" />
            </Columns>
            <FooterStyle BackColor="#B5C7DE" ForeColor="#4A3C8C" />
            <PagerStyle BackColor="#E7E7FF" ForeColor="#4A3C8C" HorizontalAlign="Right" />
            <SelectedRowStyle BackColor="#738A9C" Font-Bold="True" ForeColor="#F7F7F7" />
            <HeaderStyle BackColor="#4A3C8C" Font-Bold="True" ForeColor="#F7F7F7" />
            <AlternatingRowStyle BackColor="#F7F7F7" />
        </asp:GridView>
        <asp:SqlDataSource ID="SqlDataSource1" runat="server" 
            ConnectionString="<%$ ConnectionStrings:sqlybspConnectionString %>" 
            SelectCommand="SELECT * FROM [DownJpgUrlList] where IsValid='True'"></asp:SqlDataSource>
            <br />
            <hr />
            <br />
        <asp:Button ID="btnAdd" runat="server" Text=" 新 增 " onclick="btnAdd_Click" /> &nbsp;&nbsp;
        <asp:Button ID="btnEdit" runat="server" Text=" 编 辑 " onclick="btnEdit_Click" /> &nbsp;&nbsp;
        <asp:Button ID="btnDel" runat="server" Text=" 删 除 " onclick="btnDel_Click" /> &nbsp;&nbsp;
        <br />
        <br />
        <hr />
        <br />
<!--         当前开始时间：<asp:Label ID="lblStartTime" runat="server" Text="Label"></asp:Label> -->
<!--         <br/><br/> -->
        <B>当前运行状态：</B><asp:Label ID="lblRunStart" runat="server" Text="Label"></asp:Label>
        <br /><br />
        <asp:Button ID="btnStart" runat="server" Text=" 开 始 抓 图 " 
            onclick="btnStart_Click" /> &nbsp;&nbsp;
        <asp:Button ID="btnStop" runat="server" Text=" 停 止 抓 图 " 
            onclick="btnStop_Click" /> &nbsp;&nbsp;
            
        <br />
        <br />
        <hr />
        <br />
        
        <a href="../List.aspx">点击进入地图列表页面</a>
                       
    </div>
    </form>
</body>
</html>
