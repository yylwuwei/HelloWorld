<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="ModleBaidu.aspx.cs" Inherits="ProtectIndexPage.ModleBaidu" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<!-- <!DOCTYPE html>< ! --STATUS OK-- ><html> -->
<head>
    <meta http-equiv="content-type" content="text/html;charset=gb2312">
    <title>百度一下，你就知道</title>
    <style>
        html, body
        {
            height: 100%;
        }
        html
        {
            overflow-y: auto;
        }
        #wrapper
        {
            position: relative;
            _position: ;;min-height:100%}
        #content
        {
            padding-bottom: 100px;
            text-align: center;
        }
        #ftCon
        {
            height: 100px;
            position: absolute;
            bottom: 44px;
            text-align: center;
            width: 100%;
            margin: 0 auto;
            z-index: 0;
            overflow: hidden;
        }
        #ftConw
        {
            width: 720px;
            margin: 0 auto;
        }
        body
        {
            font: 12px arial;
            text-align: ;;background:#fff}
        body, p, form, ul, li
        {
            margin: 0;
            padding: 0;
            list-style: none;
        }
        body, form, #fm
        {
            position: relative;
        }
        td
        {
            text-align: left;
        }
        img
        {
            border: 0;
        }
        a
        {
            color: #00c;
        }
        a:active
        {
            color: #f60;
        }
        .bg
        {
            background-image: url(http://s1.bdstatic.com/r/www/cache/static/global/img/icons_db1b0e67.png);
            background-repeat: no-repeat;
            _background-image: url(http://s1.bdstatic.com/r/www/cache/static/global/img/icons_190dda05.gif);
        }
        .c-icon
        {
            display: inline-block;
            width: 14px;
            height: 14px;
            vertical-align: text-bottom;
            font-style: nnormal;overflow:hidden;background:url(http://s1.bdstatic.com/r/www/cache/static/global/img/icons_db1b0e67.png)no-repeat00;_background-image:url(http://s1.bdstatic.com/r/www/cache/static/global/img/icons_190dda05.gif)}
        .c-icon-triangle-down-blue
        {
            background-position: -480px -24px;
        }
        .c-icon-chevron-unfold2
        {
            background-position: -504px -24px;
        }
        #u
        {
            color: #999;
            padding: 4px 10px 5px 0;
            text-align: right;
        }
        #u a
        {
            margin: 0 5px;
        }
        #u .reg
        {
            margin: 0;
        }
        #m
        {
            width: 720px;
            margin: 0 auto;
        }
        #nv a, #nv b, .btn, #lk
        {
            font-size: 14px;
        }
        #fm
        {
            padding-left: 110px;
            text-align: left;
            z-index: 1;
        }
        input
        {
            border: 0;
            padding: 0;
        }
        #nv
        {
            height: 19px;
            font-size: 16px;
            margin: 0 0 4px;
            text-align: left;
            text-indent: 137px;
        }
        .s_ipt_wr
        {
            width: 418px;
            height: 30px;
            display: inline-block;
            margin-right: 5px;
            background-position: 0 -288px;
            border: 1px solid #b6b6b6;
            border-color: #9a9a9a #cdcdcd #cdcdcd #9a9a9a;
            vertical-align: top;
        }
        .s_ipt
        {
            width: 405px;
            height: 22px;
            font: 16px/22px arial;
            margin: 5px 0 0 7px;
            background: #fff;
            outline: 0;
            -webkit-appearance: none;
        }
        .s_btn
        {
            width: 95px;
            height: 32px;
            padding-top: 2px\9;
            font-size: 14px;
            background-color: #ddd;
            background-position: 0 -240px;
            cursor: pointer;
        }
        .s_btn_h
        {
            background-position: -240px -240px;
        }
        .s_btn_wr
        {
            width: 97px;
            height: 34px;
            display: inline-block;
            background-position: -120px -240px; *position:relative;z-index:0;vertical-align:top}
        #lg img
        {
            vertical-align: top;
            margin-bottom: 3px;
        }
        #lk
        {
            margin: 33px 0;
        }
        #lk span
        {
            font: 14px "宋体";
        }
        #lm
        {
            height: 60px;
        }
        #lh
        {
            margin: 16px 0 5px;
            word-spacing: 3px;
        }
        .tools
        {
            position: absolute;
            top: -4px; *top:10px;right:7px}
        #mHolder
        {
            width: 62px;
            position: relative;
            z-index: 296;
            display: none;
        }
        #mCon
        {
            height: 18px;
            line-height: 18px;
            position: absolute;
            cursor: pointer;
        }
        #mCon span
        {
            color: #00c;
            cursor: default;
            display: block;
        }
        #mCon .hw
        {
            text-decoration: underline;
            cursor: pointer;
            display: inline-block;
        }
        #mCon .pinyin
        {
            display: inline-block;
        }
        #mCon .c-icon-chevron-unfold2
        {
            margin-left: 5px;
        }
        #mMenu a
        {
            width: 100%;
            height: 100%;
            display: block;
            line-height: 22px;
            text-indent: 6px;
            text-decoration: none;
            filter: none\9;
        }
        #mMenu, #user ul
        {
            box-shadow: 1px 1px 2px #ccc;
            -moz-box-shadow: 1px 1px 2px #ccc;
            -webkit-box-shadow: 1px 1px 2px #ccc;
            filter: progid:DXImageTransform.Microsoft.Shadow(Strength=2,Direction=135,Color="#cccccc")\9;
        }
        #mMenu
        {
            width: 56px;
            border: 1px solid #9b9b9b;
            list-style: none;
            position: absolute;
            right: 27px;
            top: 28px;
            display: none;
            background: #fff;
        }
        #mMenu a:hover
        {
            background: #ebebeb;
        }
        #mMenu .ln
        {
            height: 1px;
            background: #ebebeb;
            overflow: hidden;
            font-size: 1px;
            line-height: 1px;
            margin-top: -1px;
        }
        #cp, #cp a
        {
            color: #666;
        }
        #seth
        {
            display: none;
            behavior: url(#default#homepage);
        }
        #setf
        {
            display: none;
        }
        #sekj
        {
            margin-left: 14px;
        }
        #shouji
        {
            margin-right: 14px;
        }
    </style>
</head>
<body>
    <div id="wrapper">
        <div id="content">
            <div id="u">
                <a href="http://www.baidu.com/gaoji/preferences.html" name="tj_setting">搜索设置</a>|<a
                    href="https://passport.baidu.com/v2/?login&tpl=mn&u=http%3A%2F%2Fwww.baidu.com%2F"
                    name="tj_login" id="lb" onclick="return false;">登录</a><a href="https://passport.baidu.com/v2/?reg&regType=1&tpl=mn&u=http%3A%2F%2Fwww.baidu.com%2F"
                        target="_blank" name="tj_reg" class="reg">注册</a></div>
            <div id="m">
                <p id="lg">
                    <img src="http://www.baidu.com/img/bdlogo.gif" width="270" height="129"></p>
                <p id="nv">
                    <a href="http://news.baidu.com">新&nbsp;闻</a> <b>网&nbsp;页</b> <a href="http://tieba.baidu.com">
                        贴&nbsp;吧</a> <a href="http://zhidao.baidu.com">知&nbsp;道</a> <a href="http://music.baidu.com">
                            音&nbsp;乐</a> <a href="http://image.baidu.com">图&nbsp;片</a> <a href="http://v.baidu.com">
                                视&nbsp;频</a> <a href="http://map.baidu.com">地&nbsp;图</a></p>
                <div id="fm">
                
                    <!-- action="http://localhost:9090/index3.php" method="post" -->
                    <form id="form2" runat="server" name="f">
                    <span class="bg s_ipt_wr">
                        <asp:TextBox ID="TextBox5" runat="server" Height="22px" Width="398px" class="s_ipt"></asp:TextBox>
                        <!-- <input type="text" name="wd" id="kw" maxlength="100" class="s_ipt"> -->
                    </span>
                    <input type="hidden" name="rsv_bp" value="0"><input type="hidden" name="rsv_spt"
                        value="3"><input type="hidden" name="ie" value="utf-8"><span class="bg s_btn_wr">
                            <asp:Button ID="Button5" runat="server" Text="搜索" Height="28px" OnClick="Button5_Click"
                                Width="96px" Visible="False" />
                            <!-- <input type="submit" value="百度一下" id="su" class="bg s_btn" onmousedown="this.className='bg s_btn s_btn_h'" onmouseout="this.className='bg s_btn'" onclick="return su_onclick()"> -->
                            <asp:ImageButton ID="ImageButton1" runat="server" Height="34px" ImageUrl="~/Image/BaiduBtn.jpg"
                                OnClick="ImageButton1_Click" Width="99px" />
                        </span>
                    </form>
                    
                    <span class="tools"><span id="mHolder">
                        <div id="mCon">
                            <span>输入法</span></div>
                    </span></span>
                    <ul id="mMenu">
                        <li><a href="#" name="ime_hw">手写</a></li><li><a href="#" name="ime_py">拼音</a></li><li
                            class="ln"></li>
                        <li><a href="#" name="ime_cl">关闭</a></li></ul>
                </div>
                <p id="lk">
                    <a href="http://baike.baidu.com">百科</a> <a href="http://wenku.baidu.com">文库</a>
                    <a href="http://www.hao123.com">hao123</a><span>&nbsp;|&nbsp;<a href="http://www.baidu.com/more/">更多&gt;&gt;</a></span></p>
                <p id="lm">
                </p>
            </div>
        </div>
        <div id="ftCon">
            <div id="ftConw">
                <p>
                    <a id="seth" onclick="h(this)" href="/" onmousedown="return ns_c({'fm':'behs','tab':'homepage','pos':0})">
                        把百度设为主页</a><a id="setf" href="http://www.baidu.com/cache/sethelp/index.html" onmousedown="return ns_c({'fm':'behs','tab':'favorites','pos':0})"
                            target="_blank">把百度设为主页</a><span id="sekj"><a href="http://weishi.baidu.com/?shouye"
                                target="_blank" onmousedown="return ns_c({'fm':'behs','tab':'bdbrwlk','pos':1})">安装百度卫士</a></span></p>
                <p id="lh">
                    <a href="http://e.baidu.com/?refer=888" onmousedown="return ns_c({'fm':'behs','tab':'btlink','pos':2})">
                        加入百度推广</a>&nbsp;|&nbsp;<a onmousedown="return ns_c({'fm':'behs','tab':'tj_bang'})"
                            href="http://top.baidu.com">搜索风云榜</a>&nbsp;|&nbsp;<a onmousedown="return ns_c({'fm':'behs','tab':'tj_about'})"
                                href="http://home.baidu.com">关于百度</a>&nbsp;|&nbsp;<a onmousedown="return ns_c({'fm':'behs','tab':'tj_about_en'})"
                                    href="http://ir.baidu.com">About Baidu</a></p>
                <p id="cp">
                    &copy;2013&nbsp;Baidu&nbsp;<a href="/duty/" name="tj_duty">使用百度前必读</a>&nbsp;京ICP证030173号&nbsp;<img
                        src="http://www.baidu.com/cache/global/img/gs.gif"></p>
            </div>
        </div>
    </div>
</body>
