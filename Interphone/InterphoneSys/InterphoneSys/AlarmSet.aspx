<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="AlarmSet.aspx.cs" Inherits="InterphoneSys.AlarmSet" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>告警设置</title>
    <style type="text/css">
        #divContent
        {
            margin: 25px 0px 0px 25px;
        }
        #divTitle
        {
        	color:#005831;
        }
        .tableContent
        {
            letter-spacing: 3px;
        }
        #tableSel td
        {
            padding:7px 0px;	
        }
        #btnSave{ font-size:15px; }
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div id="divContent">
        <div id="divTitle">
            <h2>
                告警参数设置</h1>
        </div>
        <hr />
        <br />
        <div>
            <table>
                <tr>
                    <td>
                        请选择基站：
                        <asp:DropDownList ID="DropDownList1" runat="server" Height="22px" Width="160px">
                        </asp:DropDownList>
                    </td>
                    <td>
                    </td>
                </tr>
            </table>
            <br />
            <table id="tableSel" class="tableContent">
                <tr>
                    <td style="width: 200px;">
                        <input id="Checkbox1" type="checkbox" />人生报警
                    </td>
                    <td>
                        <input id="Checkbox2" type="checkbox" />电源报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox4" type="checkbox" />发射报警
                    </td>
                    <td>
                        <input id="Checkbox5" type="checkbox" />接收报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox7" type="checkbox" />电流报警
                    </td>
                    <td>
                        <input id="Checkbox8" type="checkbox" />信号报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox3" type="checkbox" />人生报警
                    </td>
                    <td>
                        <input id="Checkbox6" type="checkbox" />电源报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox9" type="checkbox" />发射报警
                    </td>
                    <td>
                        <input id="Checkbox10" type="checkbox" />接收报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox11" type="checkbox" />电流报警
                    </td>
                    <td>
                        <input id="Checkbox12" type="checkbox" />信号报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox13" type="checkbox" />人生报警
                    </td>
                    <td>
                        <input id="Checkbox14" type="checkbox" />电源报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox15" type="checkbox" />发射报警
                    </td>
                    <td>
                        <input id="Checkbox16" type="checkbox" />接收报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox17" type="checkbox" />电流报警
                    </td>
                    <td>
                        <input id="Checkbox18" type="checkbox" />信号报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox19" type="checkbox" />人生报警
                    </td>
                    <td>
                        <input id="Checkbox20" type="checkbox" />电源报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox21" type="checkbox" />发射报警
                    </td>
                    <td>
                        <input id="Checkbox22" type="checkbox" />接收报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox23" type="checkbox" />电流报警
                    </td>
                    <td>
                        <input id="Checkbox24" type="checkbox" />信号报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox25" type="checkbox" />人生报警
                    </td>
                    <td>
                        <input id="Checkbox26" type="checkbox" />电源报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox27" type="checkbox" />发射报警
                    </td>
                    <td>
                        <input id="Checkbox28" type="checkbox" />接收报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox29" type="checkbox" />电流报警
                    </td>
                    <td>
                        <input id="Checkbox30" type="checkbox" />信号报警
                    </td>
                </tr>
                <tr>
                    <td>
                        &nbsp;
                    </td>
                    <td>
                    </td>
                </tr>
                <tr>
                <table border="0" cellspacing="0" cellpadding="0" width="100%">
                	<tr>
                		<td width="220px"> &nbsp;</td>
                		<td><input type="button" id="btnSave"  value=" 保 存 " onclick="alert('保存成功！');" style="height: 26px; width: 76px" /></td>
                		<!-- <td>&nbsp;</td> -->
                	</tr>
                </table>
                </tr>
            </table>
        </div>
    </div>
    </form>
</body>
</html>
