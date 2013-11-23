<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="AlarmInfo.aspx.cs" Inherits="InterphoneSys.AlarmInfo" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>告警信息查看页</title>
    <style type="text/css">
        #divContent
        {
            margin: 25px 0px 0px 25px;
        }
        #divTitle
        {
            color: #005831;
        }
        td{ text-align:left; }
        #tableSel td
        {
            padding:0px 0px;	
        }
        body
        {
            font: normal 11px auto "Trebuchet MS" , Verdana, Arial, Helvetica, sans-serif;
            color: #4f6b72;
            background: #E6EAE9;
        }
        a
        {
            color: #c75f3e;
        }

        tr
        {
            height:30px;	
        }
        th
        {
            font: bold 20px "Trebuchet MS" , Verdana, Arial, Helvetica, sans-serif;
            color: #4f6b72;
            border-right: 1px solid #C1DAD7;
            border-bottom: 1px solid #C1DAD7;
            border-top: 1px solid #C1DAD7;
            letter-spacing: 2px;
            text-transform: uppercase;
            text-align: left;
            padding: 6px 6px 6px 12px;
            background: #87C4F0 url(images/bg_header.jpg) no-repeat;
        }
        th.nobg
        {
            border-top: 0;
            border-left: 0;
            border-right: 1px solid #C1DAD7;
            background: none;
        }
        td
        {
            border-right: 1px solid #C1DAD7;
            border-bottom: 1px solid #C1DAD7;
            background: #fff;
            font-size: 15px;
            padding: 6px 6px 6px 12px;
            color: #000000;
        }
        td.alt
        {
            background: #F5FAFA;
            color: #797268;
        }
        th.spec
        {
            border-left: 1px solid #C1DAD7;
            border-top: 0;
            background: #fff url(images/bullet1.gif) no-repeat;
            font: bold 15px "Trebuchet MS" , Verdana, Arial, Helvetica, sans-serif;
        }
        th.specalt
        {
            border-left: 1px solid #C1DAD7;
            border-top: 0;
            background: #f5fafa url(images/bullet2.gif) no-repeat;
            font: bold 15px "Trebuchet MS" , Verdana, Arial, Helvetica, sans-serif;
            color: #797268;
        }

    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div id="divContent">
        <div id="divTitle">
            <h1>
                告警信息查看</h1>
        </div>
        <hr />
        <br />
        <div>
            <table id="tableSel" border="1" cellspacing="0" cellpadding="0" width="100%">
            	<tr>
            		<th width="200px">基站名称</th><th width="200px">告警时间</th><th width="400px">告警事件</th>
            	</tr>
            	<tr>
            		<td>广州天河基站</td><td>2011/12/15</td><td>功率过低</td>
            	</tr>
            	<tr>
            		<td>广州天河基站</td><td>2011/12/15</td><td>功率过低</td>
            	</tr>
            	<tr>
            		<td>广州天河基站</td><td>2011/12/15</td><td>功率过低</td>
            	</tr>
            	<tr>
            		<td>广州天河基站</td><td>2011/12/15</td><td>功率过低</td>
            	</tr>
            	<tr>
            		<td>广州天河基站</td><td>2011/12/15</td><td>功率过低</td>
            	</tr>
            	<tr>
            		<td>广州天河基站</td><td>2011/12/15</td><td>功率过低</td>
            	</tr>
            	<tr>
            		<td>广州天河基站</td><td>2011/12/15</td><td>功率过低</td>
            	</tr>
            	<tr>
            		<td>广州天河基站</td><td>2011/12/15</td><td>功率过低</td>
            	</tr>
            	<tr>
            		<td>广州天河基站</td><td>2011/12/15</td><td>功率过低</td>
            	</tr>
            </table>
        </div>
    </div>
    </form>
</body>
</html>
