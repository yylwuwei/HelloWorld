<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="AlarmSet.aspx.cs" Inherits="InterphoneSys.AlarmSet" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    <table>
    <tr>
    <td>请选择基站：</td>
    <td>
        <asp:DropDownList ID="DropDownList1" runat="server">
        </asp:DropDownList>
    </td>
    </tr>
    <tr>
    <td>
        <input id="Checkbox1" type="checkbox" />风扇报警</td>
    <td>
        <input id="Checkbox2" type="checkbox" />电源报警</td>
    <td>
        <input id="Checkbox3" type="checkbox" />电源报警</td>
    </tr>
    <tr>
    <td>
        <input id="Checkbox4" type="checkbox" />发射报警</td>
    <td>
        <input id="Checkbox5" type="checkbox" />接收报警</td>
    <td>
        <input id="Checkbox6" type="checkbox" />电压报警</td>
    </tr>
    <tr>
    <td>
        <input id="Checkbox7" type="checkbox" />电流报警</td>
    <td>
        <input id="Checkbox8" type="checkbox" />信号报警</td>
    <td>
        <input id="Checkbox9" type="checkbox" />圆形报警</td>
    </tr>
    <tr>
    <td>
    <input type="button" value=" 保 存 " />
    </td>
    </tr>
    </table>
    </div>
    </form>
</body>
</html>
