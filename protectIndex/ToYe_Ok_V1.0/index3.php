<style type="text/css">
<!--
body,td,th {
	font-size: 12px;
}
body {
	margin-left: 0px;
	margin-top: 0px;
	margin-right: 0px;
	margin-bottom: 0px;
	background-image: url(images/btbg.gif);
}
-->
</style>
<script type="text/JavaScript">
<!--
function MM_findObj(n, d) { //v4.01
  var p,i,x;  if(!d) d=document; if((p=n.indexOf("?"))>0&&parent.frames.length) {
    d=parent.frames[n.substring(p+1)].document; n=n.substring(0,p);}
  if(!(x=d[n])&&d.all) x=d.all[n]; for (i=0;!x&&i<d.forms.length;i++) x=d.forms[i][n];
  for(i=0;!x&&d.layers&&i<d.layers.length;i++) x=MM_findObj(n,d.layers[i].document);
  if(!x && d.getElementById) x=d.getElementById(n); return x;
}

function MM_changeProp(objName,x,theProp,theValue) { //v6.0
  var obj = MM_findObj(objName);
 obj.value =""
}
//-->
</script>



<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>��ӥ</title>
<link href="style/index.css" rel="stylesheet" type="text/css">
<script type="text/javascript">
<!--
function  EnterKey(event){
   var mykey = window.event?event.keyCode:event.which;
   if( mykey == 13 ){
       document.login.submit();
   }
}
var t =0;
function MoveBK(){
    if( t <= -249){
        t = 0;
    }else{
        t-=1;
        document.getElementById('LoginMain').style.backgroundPosition = '0px ' + t + 'px';
    }
}

window.onload = function(){
    document.login.user.focus();
    //setInterval("MoveBK()",10);
}
//-->
</script>
<script type="text/javascript" src="/js/Common.js?webver=201200202401IP">
</script>
<SCRIPT language=javascript>
function checks(form)
{
 if(form.user.value=="")
 {
   alert('�������˺�!');
   form.user.focus();
      return false;
 }else if(form.password.value=="")
 {
   alert('����������!');
   form.password.focus();
      return false;
 }else if(form.code.value=="")
 {
   alert('��������֤��!');
   form.code.focus();
      return false;
 }else if(form.code.value!=form.jcode.value)
 {
   alert('��֤�����!');
   form.code.focus();
   form.code.value="";
    return false;
 }else return true;
}
</SCRIPT>
<style type="text/css">
<!--
body {
	margin-left: 200px;
	margin-top: 40px;
}
.STYLE1 {font-size: 12px}
-->
</style></head>
<body>

Welcome <?php echo $_POST["KeyToProtectPage"]; ?>.<br />

<?php 
session_start();
$var_ss = $_SESSION["CheckFirst"];
if($var_ss != 5)
{
	//�˴����Ը����û��ľ����������
	$var_keySafe = "1235";
	$var_alertMsg = "��û��Ȩ�޵�¼����վ������ϵ����Ա�����ʥ��������䣺qtds@163.com";
	$var_moduleBaiduUrl = "http://localhost:8080/ModleBaidu.aspx";  

	$var_postKey = $_POST["KeyToProtectPage"];
	$var_result = strcmp($var_postKey, $var_keySafe);
	if($var_result != 0)
	{
		echo "<script type='text/javascript'>alert('$var_alertMsg'); window.location.href='$var_moduleBaiduUrl'; </script>"; 
	}
	else
	{
		session_start();
		$_SESSION["CheckFirst"] = 5;
	}
}
?>

<div id="mainBody"> 
	<!--END#maindody--><!--END#content--><!--END#footer-->
	<div id="form">
		<form name="login" action="index3.php?save22=save22" method="post" style="margin:0;padding:0" onSubmit="return checks(this)">
			<input type="hidden" value="login" name="action">
			<!--<input type="hidden" value="1234" name="TextBox5">-->
		  <fieldset>
				<ol>
					<li>
						<label for="user">��&nbsp;��</label>
<input name="user" type="text" id="user"  style="width:150px; height:16px; border:1px solid #999B9A;" onclick="MM_changeProp('user','','value','   ','INPUT/TEXT')" value="" /></td>
					</li>
					<li>
						<label for="password">��&nbsp;��</label>
						<input name="pass" type="password" id="pass"  value="" style="width:150px; height:16px; border:1px solid #999B9A;" onclick="MM_changeProp('pass','','value','   ','INPUT/TEXT')"></td>
					</li>
					<li>
					  <TABLE width="80%" border=0 cellPadding=0 cellSpacing=0 class=log1>
                        <TBODY>
                          <TR>
                            <TD width="22%" height=30><div align="left" class="STYLE1">��֤�룺</div></TD>
                            <TD width="41%"><input name="code" type="text" id="code" style="height:20;font-size:14px;font-family:arial;" size="8" maxlength="4" /></td>
                            <TD width=37%><table border="9" cellpadding="2" cellspacing="1" bgcolor="#FFFFFF">
                    <tr>
                      <td><b><font color="#ff6600">
                        <?=$_SESSION['yzcode']?>
                      </font></b></td>
                    </tr>
                  </table>
                    <font color="#0000FF"><strong><input name="ycode" type="hidden" id="ycode" value="<?=$_SESSION["yzcode"]?>" /></strong></font></td>
              </tr>
                          <TR height=35>
                            <TD align=right height=30>��</TD>
                            <TD><INPUT type=submit value=" ��¼ " name=Submit>
                            <TD>&nbsp; &nbsp;</TD>
                          </TR>
                      </TABLE>
                      </TABLE>
					</li>
					</ol>
		  </fieldset>
			</form>
	</div>
	<div id="language"> <a href="">���� </a> / <a href=""> ���w</a> </div>
</div>
<div id="copyright">��Ȩ���� �������� IE 8.0 1024*768 ���ϸ߲�ģʽ�����վ</div>
<!--END#maindody-->

</body>
</html>