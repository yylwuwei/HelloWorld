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
            color: #005831;
        }
        .tableContent
        {
            letter-spacing: 3px;
        }
        #tableSel td
        {
            padding:4px 0px;
            font-size: 14px;
            font: SimSun;
            color: Black;
        }
        #btnSave{ font-size:15px; }
        
        #divSelTitle 
        {
        	font-size: 15px;
        	color: Black;
        	}
        
        #divBtnSave
        {
        	margin-left:210px;
        	}
        
        body
        {
            font: normal 11px auto "Trebuchet MS" , Verdana, Arial, Helvetica, sans-serif;
            color: #4f6b72;
            background: #E6EAE9;
        }

    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div id="divContent">
        <div id="divTitle">
            <h1>
                告警参数设置</h1>
        </div>
        <hr />
        <br />
        <div>
        <div id="divSelTitle">请选择基站：
                        <asp:DropDownList ID="DropDownList1" runat="server" Height="23px" Width="160px">
                        </asp:DropDownList></div>
                        <br />
            <table id="tableSel" class="tableContent">
                <tr>
                    <td style="width: 200px;">
                        <input id="Checkbox31" type="checkbox" />人生报警
                    </td>
                    <td>
                        <input id="Checkbox32" type="checkbox" />电源报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox33" type="checkbox" />发射报警
                    </td>
                    <td>
                        <input id="Checkbox34" type="checkbox" />接收报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox35" type="checkbox" />电流报警
                    </td>
                    <td>
                        <input id="Checkbox36" type="checkbox" />信号报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox37" type="checkbox" />人生报警
                    </td>
                    <td>
                        <input id="Checkbox38" type="checkbox" />电源报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox39" type="checkbox" />发射报警
                    </td>
                    <td>
                        <input id="Checkbox40" type="checkbox" />接收报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox41" type="checkbox" />电流报警
                    </td>
                    <td>
                        <input id="Checkbox42" type="checkbox" />信号报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox43" type="checkbox" />人生报警
                    </td>
                    <td>
                        <input id="Checkbox44" type="checkbox" />电源报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox45" type="checkbox" />发射报警
                    </td>
                    <td>
                        <input id="Checkbox46" type="checkbox" />接收报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox47" type="checkbox" />电流报警
                    </td>
                    <td>
                        <input id="Checkbox48" type="checkbox" />信号报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox49" type="checkbox" />人生报警
                    </td>
                    <td>
                        <input id="Checkbox50" type="checkbox" />电源报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox51" type="checkbox" />发射报警
                    </td>
                    <td>
                        <input id="Checkbox52" type="checkbox" />接收报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox53" type="checkbox" />电流报警
                    </td>
                    <td>
                        <input id="Checkbox54" type="checkbox" />信号报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox55" type="checkbox" />人生报警
                    </td>
                    <td>
                        <input id="Checkbox56" type="checkbox" />电源报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox57" type="checkbox" />发射报警
                    </td>
                    <td>
                        <input id="Checkbox58" type="checkbox" />接收报警
                    </td>
                </tr>
                <tr>
                    <td>
                        <input id="Checkbox59" type="checkbox" />电流报警
                    </td>
                    <td>
                        <input id="Checkbox60" type="checkbox" />信号报警
                    </td>
                </tr>
            </table>
            <br />
            <div id="divBtnSave">
            <input type="button" id="Button1"  value=" 保 存 " onclick="alert('保存成功！');" style="height: 26px; width: 76px" />
            </div>
        </div>
    </div>
    </form>
</body>
</html>
