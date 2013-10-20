<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="AlarmInfo.aspx.cs" Inherits="InterphoneSys.AlarmInfo" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <style type="text/css">
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
        #mytable
        {
            width: 100%;
            padding: 0;
            margin: 0;
        }
        caption
        {
            padding: 0 0 5px 0;
            width: 700px;
            font: italic 11px "Trebuchet MS" , Verdana, Arial, Helvetica, sans-serif;
            text-align: right;
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
        /*---------for IE 5.x bug*/
        html > body td
        {
            font-size: 12px;
        }
        
        #divContainer{margin:0px auto; width:100%;}
        #divTitle{height:70px; margin-left:30px; margin-top:0px; }
        #divContent{height:500px; margin-left:30px; margin-top:0px; }
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div id="divContainer">
     
    <div id="divTitle">
    <h1>告警信息查看</h1>
    <hr />
    </div>
    <div id="divContent">
    
  
            <table id="mytable" cellspacing="0" summary="The technical specifications of the Apple PowerMac G5 series">
            <caption>
            </caption>
            <tr height="35px">
                <th scope="col" abbr="Configurations">
                    基站名称
                </th>
                <th scope="col" abbr="Dual 1.8">
                   告警事件
                </th>
                <th scope="col" abbr="Dual 2">
                    发生时间
                </th>
                <th scope="col" abbr="Dual 2.5">
                    事件备注
                </th>
            </tr>
            <tr>
                <td>
                    lipeng
                </td>
                <td>
                    M9454LL/A
                </td>
                <td>
                    M9455LL/A
                </td>
                <td>
                    M9457LL/A
                </td>
            </tr>
            <tr>
                <td>
                    mapabc
                </td>
                <td>
                    Dual 1.8GHz PowerPC G5
                </td>
                <td>
                    Dual 2GHz PowerPC G5
                </td>
                <td>
                    Dual 2.5GHz PowerPC G5
                </td>
            </tr>
                        <tr>
                <td class="alt">
                    图秀卡
                </td>
                <td class="alt">
                    512K per processor
                </td>
                <td class="alt">
                    512K per processor
                </td>
                <td class="alt">
                    512K per processor
                </td>
            </tr>
            <tr>
                <td>
                    地图名片
                </th>
                <td>
                    900MHz per processor
                </td>
                <td>
                    1GHz per processor
                </td>
                <td>
                    1.25GHz per processor
                </td>
            </tr>


            <tr>
                <td>
                    lipeng
                </td>
                <td>
                    M9454LL/A
                </td>
                <td>
                    M9455LL/A
                </td>
                <td>
                    M9457LL/A
                </td>
            </tr>
            <tr>
                <td>
                    mapabc
                </td>
                <td>
                    Dual 1.8GHz PowerPC G5
                </td>
                <td>
                    Dual 2GHz PowerPC G5
                </td>
                <td>
                    Dual 2.5GHz PowerPC G5
                </td>
            </tr>
                        <tr>
                <td >
                    图秀卡
                </td>
                <td >
                    512K per processor
                </td>
                <td >
                    512K per processor
                </td>
                <td >
                    512K per processor
                </td>
            </tr>
            <tr>
                <td>
                    地图名片
                </th>
                <td>
                    900MHz per processor
                </td>
                <td>
                    1GHz per processor
                </td>
                <td>
                    1.25GHz per processor
                </td>
            </tr>



        </table>

    
    </div>
    
    </div>
    </form>
</body>
</html>
