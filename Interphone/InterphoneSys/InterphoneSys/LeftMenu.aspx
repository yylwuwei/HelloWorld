<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="LeftMenu.aspx.cs" Inherits="InterphoneSys.LeftMenu" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <meta http-equiv="Content-Type" content="text/html; charset=gb2312">
    <link href="css/admin.css" type="text/css" rel="stylesheet">
    <style type="text/css">
    td{text-align:left;}
    </style>

    <script language="javascript">
        var totalType = 5;
        
        function LeftInit() {
            for(i = 1; i <= totalType; i++) {
                childObj = document.getElementById("child" + i);
                childObj.style.display = 'block';
            }
        }
        
        function expand(el) {
            childObj = document.getElementById("child" + el);

            if (childObj.style.display == 'none') {
                childObj.style.display = 'block';
            }
            else {
                childObj.style.display = 'none';
            }
            return;
        }
    </script>

</head>
<body onload="LeftInit()">
    <table height="850px" cellspacing="0" cellpadding="0" width="150px" background="images/menu_bg.jpg"
        border="0">
        <tr>
            <td valign="top" align="middle">
                <table cellspacing="0" cellpadding="0" width="100%" border="0">
                    <tr>
                        <td height="10">
                        </td>
                    </tr>
                </table>
                <table cellspacing="0" cellpadding="0" width="150" border="0">
                    <tr height="22">
                        <td style="padding-left: 30px" background="images/menu_bt.jpg" onclick="expand(1)">
                            <a class="menuParent"  href="javascript:void(0);">ϵͳ���</a>
                        </td>
                    </tr>
                    <tr height="4">
                        <td>
                        </td>
                    </tr>
                </table>
                <table id="child1" style="display: none" cellspacing="0" cellpadding="0" width="150"
                    border="0">
                    <tr height="20">
                        <td align="middle" width="30">
                            <img height="9" src="images/menu_icon.gif" width="9">
                        </td>
                        <td>
                            <a class="menuChild" href="MapControl.aspx" target="main">����״̬</a>
                        </td>
                    </tr>
                    <tr height="20">
                        <td align="middle" width="30">
                            <img height="9" src="images/menu_icon.gif" width="9">
                        </td>
                        <td>
                            <a class="menuChild" href="AlarmInfo.aspx" target="main">�澯�鿴</a>
                        </td>
                    </tr>
                    <tr height="20">
                        <td align="middle" width="30">
                            <img height="9" src="images/menu_icon.gif" width="9">
                        </td>
                        <td>
                            <a class="menuChild" href="Building.aspx" target="main">ͨ����Ϣ</a>
                        </td>
                    </tr>
                    <tr height="4">
                        <td colspan="2">
                        </td>
                    </tr>
                </table>
                <table cellspacing="0" cellpadding="0" width="150" border="0">
                    <tr height="22">
                        <td style="padding-left: 30px" background="images/menu_bt.jpg" onclick="expand(2)">
                            <a class="menuParent" href="javascript:void(0);">��վ����</a>
                        </td>
                    </tr>
                    <tr height="4">
                        <td>
                        </td>
                    </tr>
                </table>
                <table id="child2" style="display: none" cellspacing="0" cellpadding="0" width="150"
                    border="0">
                    <tr height="20">
                        <td align="middle" width="30">
                            <img height="9" src="images/menu_icon.gif" width="9">
                        </td>
                        <td>
                            <a class="menuChild" href="BSInfo.aspx" target="main">��վ��Ϣ����</a>
                        </td>
                    </tr>
                    <tr height="20">
                        <td align="middle" width="30">
                            <img height="9" src="images/menu_icon.gif" width="9">
                        </td>
                        <td>
                            <a class="menuChild" href="Building.aspx" target="main">IP��������</a>
                        </td>
                    </tr>
                    <tr height="20">
                        <td align="middle" width="30">
                            <img height="9" src="images/menu_icon.gif" width="9">
                        </td>
                        <td>
                            <a class="menuChild" href="AlarmSet.aspx" target="main">�澯��������</a>
                        </td>
                    </tr>
                    <tr height="20">
                        <td align="middle" width="30">
                            <img height="9" src="images/menu_icon.gif" width="9">
                        </td>
                        <td>
                            <a class="menuChild" href="Building.aspx" target="main">״̬��������</a>
                        </td>
                    </tr>
                    <tr height="4">
                        <td colspan="2">
                        </td>
                    </tr>
                </table>
                <table cellspacing="0" cellpadding="0" width="150" border="0">
                    <tr height="22">
                        <td style="padding-left: 30px" background="images/menu_bt.jpg" onclick="expand(3)">
                            <a class="menuParent" href="javascript:void(0);">ϵͳ����</a>
                        </td>
                    </tr>
                    <tr height="4">
                        <td>
                        </td>
                    </tr>
                </table>
                <table id="child3" style="display: none" cellspacing="0" cellpadding="0" width="150"
                    border="0">
                    <tr height="20">
                        <td align="middle" width="30">
                            <img height="9" src="images/menu_icon.gif" width="9">
                        </td>
                        <td>
                            <a class="menuChild" href="Building.aspx" target="main">ID�����</a>
                        </td>
                    </tr>
                    <tr height="20">
                        <td align="middle" width="30">
                            <img height="9" src="images/menu_icon.gif" width="9">
                        </td>
                        <td>
                            <a class="menuChild" href="Building.aspx" target="main">������������</a>
                        </td>
                    </tr>
                    <tr height="4">
                        <td colspan="2">
                        </td>
                    </tr>
                </table>
                <table cellspacing="0" cellpadding="0" width="150" border="0">
                    <tr height="22">
                        <td style="padding-left: 30px" background="images/menu_bt.jpg" onclick="expand(4)">
                            <a class="menuParent" href="javascript:void(0);">�û�����</a>
                        </td>
                    </tr>
                    <tr height="4">
                        <td>
                        </td>
                    </tr>
                </table>
                <table id="child4" style="display: none" cellspacing="0" cellpadding="0" width="150"
                    border="0">
                    <tr height="20">
                        <td align="middle" width="30">
                            <img height="9" src="images/menu_icon.gif" width="9">
                        </td>
                        <td>
                            <a class="menuChild" href="Building.aspx" target="main">�û���ɾ</a>
                        </td>
                    </tr>
                    <tr height="20">
                        <td align="middle" width="30">
                            <img height="9" src="images/menu_icon.gif" width="9">
                        </td>
                        <td>
                            <a class="menuChild" href="Building.aspx" target="main">�û���ѯ</a>
                        </td>
                    </tr>
                    <tr height="4">
                        <td colspan="2">
                        </td>
                    </tr>
                </table>
                <table cellspacing="0" cellpadding="0" width="150" border="0">
                    <tr height="22">
                        <td style="padding-left: 30px" background="images/menu_bt.jpg" onclick="expand(5)">
                            <a class="menuParent" href="javascript:void(0);">��־����</a>
                        </td>
                    </tr>
                    <tr height="4">
                        <td>
                        </td>
                    </tr>
                </table>
                <table id="child5" style="display: none" cellspacing="0" cellpadding="0" width="150"
                    border="0">
                    <tr height="20">
                        <td align="middle" width="30">
                            <img height="9" src="images/menu_icon.gif" width="9">
                        </td>
                        <td>
                            <a class="menuChild" href="Building.aspx" target="main">ϵͳ��־</a>
                        </td>
                    </tr>
                    <tr height="20">
                        <td align="middle" width="30">
                            <img height="9" src="images/menu_icon.gif" width="9">
                        </td>
                        <td>
                            <a class="menuChild" href="Building.aspx" target="main">ϵͳ����</a>
                        </td>
                    </tr>
                    <tr height="4">
                        <td colspan="2">
                        </td>
                    </tr>
                </table>
                
            </td>
            <td width="1" bgcolor="#d1e6f7">
            </td>
        </tr>
    </table>
    <form id="form1" runat="server">
    <div>
    </div>
    </form>
</body>
</html>
