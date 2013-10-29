基本用户操作：

1、部署ProtectIndexPage到IIS，运行此目录下的ModleBaidu.aspx文件，看到仿百度页面，则运行正常。
继续下一步。

2、在对应目录覆盖index.php页面。

覆盖后，修改Index.php内的 $var_moduleBaiduUrl = "http://localhost:8080/ModleBaidu.aspx";  
修改此网址为仿百度页面的网址。（没有对应安全码的用户，会跳转到此网址，建议设置为仿百度页面的网址。）

修改完成，可以直接从浏览器访问此文件。因为没有安全码，会弹出提示框，点击确定，跳转到仿百度页面。
继续下一步。

3、修改ProtectIndexPage文件夹下的 <add key="WebProtectPageUrl" value="http://localhost:80/index3.php" />
修改此网址为需要保护的index.php的网址，必须全部的地址，不能简写。

截止操作到此步骤，可以试着运行一下，应该具备了全部的功能。在百度搜索框内，输入默认安全码1235，则跳转到index.php，否则进入百度搜索页面。





高级用户操作：

5、没有权限的用户，访问index.php，则会弹出消息框。如果需要修改消息框的内容，可以修改index.php。
$var_alertMsg = "您没有权限登录此网站！请联系管理员齐天大圣解决！邮箱：qtds@163.com";

6、默认安全码为：1235。如需要修改安全码，则需要同时修改ProtectIndexPage文件夹内的Web.config和index.php。
Web.config
<add key="WebKeyToProtectPage" value="1235" />
index.php
$var_keySafe = "1235";
将两个文件内的双引号内的1235，同时替换为新的安全码则可。

