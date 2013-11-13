<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Map.aspx.cs" Inherits="WebApplication3.Map" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>地质异常监测组</title>
    <meta charset="UTF-8">
    <meta name="Generator" content="EditPlus">
    <meta name="Keywords" content="">
    <meta name="Description" content="">
    <!--[if lt ie 9]><script type="text/javascript" src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script><![endif]-->

    <script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.6/jquery.min.js"></script>

    <script type="text/javascript" src="http://maps.google.com/maps/api/js?sensor=false"></script>

    <link href="css/index.css" type="text/css" rel="stylesheet" media="all" />

    <script type="text/javascript">

        var yyDataJson; //可以改为局部变量，通过参数传递的形式
        var yyMarkerArray = new Array();
        var yyNewMarkerArray = new Array();
        var yySucMarkerArray = new Array();
        var yyFailMarkerArray = new Array();
        var yyCurType = "nono";
        
        
        var yyPosArray = new Array(); //可以删掉
        var yyContentArray = new Array();
        


        var newIcon = { anchor: new google.maps.Point(0, 0), origin: new google.maps.Point(0, 0), size: new google.maps.Size(50, 74), url: "http://news.ceic.ac.cn/images/star.gif" };
        var sucIcon = "Image/huangse.png";
        var failIcon = "Image/huise.png";
        
        
        var yyIcon = "http://so.redocn.com/images/redocn/zhuce2.jpg";
        var yyContentStr = "hello,MM";
        var yyInfowindow = new google.maps.InfoWindow({
            content: yyContentStr
        });

        var bFirst = 1;
        var bFirInit = 1;

        var newCount = 0;
        var sucCount = 0;
        var failCount = 0;

        var map;
        var polyline;
        var polylinesArray = [];
        //距离标记数组
        var lenArray = [];

        var DefaultLat = 23.16667;
        var DefaultLng = 113.23333;
        var DefaultZoom = 3; //默认情况下的zoom

        //地图初始化
        function MapInit() {

            
            
            var singapoerCenter = new google.maps.LatLng(DefaultLat, DefaultLng); //设置中心位置
            var myOptions = {
                zoom: DefaultZoom,
                center: singapoerCenter,
                navigationControl: true,
                scaleControl: true,
                streetViewControl: true,
                mapTypeId: google.maps.MapTypeId.ROADMAP

            };
            map = new google.maps.Map(document.getElementById("map"), myOptions);

            //为地图的缩放事件提供
            google.maps.event.addListener(map, 'zoom_changed', function() {
                if (this.getZoom() <= 1) {
                    CreateMarker(DefaultLat, DefaultLng, 1);
                }
            });

            getDistance();

            $.ajax({
                type: "get",
                url: "Handler1.ashx",
                dataType: "json",
                data: "name=yyl&pwd=123",
                success: function(dataJson) {
                    yyDataJson = dataJson;
                    AutoAddMarker();
                    if (bFirInit == 1) {
                        bFirInit = 2;
                        for (var i in dataJson) {
                            //alert(dataJson[i].Title);
                            AddLi(dataJson[i].Type, dataJson[i].Title, dataJson[i].Time, dataJson[i].ID);
                            yyContentArray[i] = dataJson[i].EventContent;
                        }
                    }
                },
                error: function(err) {
                    alert(err);
                }
            });
        }

        function AddLi(type, title, time, id) {
            var ulID;
            var showLiID;
            if (type == "1") {
                ulID = "ulIDTest1";
                newCount++;
                showLiID = newCount;
            }
            else if (type == "2") {
                ulID = "ulIDTest2";
                sucCount++;        
                showLiID = sucCount;
            }
            else if(type == "3") {
                ulID = "ulIDTest3";
                failCount++;
                showLiID = failCount;
            }
            var s = document.getElementById(ulID);
            var li = document.createElement("li");
            li.id = id;
            li.onclick = function () {
                $("div[@id=testDivID1] li ul li").each(function() {
                    this.className = "";
                });
                li.className = "selected";
                var iIndex = li.id;

                yyContentStr = yyContentArray[iIndex];
                yyInfowindow.setContent(yyContentStr);
                yyInfowindow.open(map, yyMarkerArray[iIndex]);
            }  
            li.innerHTML = "<span class='number'>"+showLiID+"</span> <span class='time'>"+time+"</span><span class='title'>"+title+"</span>";
            s.appendChild(li);
        }

        function AutoAddMarker() {
        
            yyMarkerArray = [];
            yyNewMarkerArray = [];
            yySucMarkerArray = [];
            yyFailMarkerArray = [];
            yyPosArray = [];
            
            for (var i in yyDataJson) {
                var yyLatlng = new google.maps.LatLng(yyDataJson[i].Lat, yyDataJson[i].Lng);
                var yyMarker = new google.maps.Marker({
                    position: yyLatlng,
                    title: yyDataJson[i].Title,
                    id: i
                });
                if (yyDataJson[i].Type == "1") {
                    yyMarker.setIcon(newIcon);
                    yyMarker.setDraggable(true);
                    if (yyCurType == "nono" || yyCurType == "newLi") {
                        yyMarker.setMap(map);
                    }
                    yyNewMarkerArray.push(yyMarker);
                }
                else if (yyDataJson[i].Type == "2") {
                    yyMarker.setIcon(sucIcon);
                    yyMarker.setMap(null);
                    if (yyCurType == "sucLi") {
                        yyMarker.setMap(map);
                    }
                    yySucMarkerArray.push(yyMarker);
                }
                else if (yyDataJson[i].Type == "3") {
                    yyMarker.setIcon(failIcon);
                    yyMarker.setMap(null);
                    if (yyCurType == "failLi") {
                        yyMarker.setMap(map);
                    }
                    yyFailMarkerArray.push(yyMarker);
                }
                yyMarkerArray[i] = yyMarker;
                google.maps.event.addListener(yyMarker, 'click', function() {
                    $("div[@id=testDivID1] li ul li").each(function() {
                        this.className = "";
                    });
                    document.getElementById(this.id).className = "selected";

                    yyInfowindow.setContent(this.title);
                    yyInfowindow.open(map, this);
                });
            }
        }

        function CreateMarker(lat, lng, MyGoToCommunityZoom) {

            var singapoerCenter = new google.maps.LatLng(lat, lng);
            var myOptions = {
                zoom: MyGoToCommunityZoom,
                center: singapoerCenter,
                navigationControl: true,
                scaleControl: true,
                streetViewControl: true,
                mapTypeId: google.maps.MapTypeId.ROADMAP
            }
            map.setOptions(myOptions);
        }

        //距离
        function getDistance() {
            google.maps.event.addListener(map, "click", function(event) {
                addMarker(event.latLng);
            });
        }

        //添加新标记
        function addMarker(location) {
            if (lenArray.length == 0) {
                var icon = "http://b259.photo.store.qq.com/psb?/V12hQgmW13ePD6/Z8f42qJ1d4Eu9Wsgc6Facsirxp2FqpqRJP69*4ZzgV0!/b/dGXbZJrELgAA&bo=GAAoAAAAAAADABU!&rf=photoDetail";
            } else {

                if (lenArray.length >= 2) {
                    marker.setMap(null);
                }
                var icon = "http://b259.photo.store.qq.com/psb?/V12hQgmW13ePD6/Z8f42qJ1d4Eu9Wsgc6Facsirxp2FqpqRJP69*4ZzgV0!/b/dGXbZJrELgAA&bo=GAAoAAAAAAADABU!&rf=photoDetail";
            }
            //标记选项
            var myOptions = {
                position: location,
                draggable: true,
                map: map,
                icon: icon
            };

            marker = new google.maps.Marker(myOptions);

            //双击
            google.maps.event.addListener(marker, 'click', function() {
                lenArray.push(marker);
                drawOverlay(marker);
            });

            //拖动结束事件
            google.maps.event.addListener(marker, 'dragend', function() {
                lenArray.push(marker);
                drawOverlay(marker);

            });

            lenArray.push(marker);
            drawOverlay(marker);

        }
        //画出路径覆盖层
        function drawOverlay(marker) {
            //路线数组
            var flightPlanCoordinates = [];
            //
            //将坐标压入路线数组
            if (lenArray) {
                for (i in lenArray) {
                    flightPlanCoordinates.push(lenArray[i].getPosition());
                }
            }
            //路径选项
            var myOptions = {
                path: flightPlanCoordinates,
                map: map,
                strokeColor: "#FF0000",
                strokeOpacity: 1.0,
                strokeWeight: 2
            };
            polyline = new google.maps.Polyline(myOptions);
            //清除原有折线路径
            if (polylinesArray) {
                for (i in polylinesArray) {
                    polylinesArray[i].setMap(null);
                }
                polylinesArray = [];
            }
            polyline.setMap(map);

            // document.getElementById("sRes").innerHTML =(polyline.getLength()/1000).toFixed(3);

            if (bFirst != 1) {
                var contentString2 = (polyline.getLength() / 1000).toFixed(3) + ' km';
                var infowindow2 = new google.maps.InfoWindow({
                    content: contentString2
                });
                infowindow2.open(map, marker);

                google.maps.event.addListener(infowindow2, "closeclick", function() {
                    deleteOverlays();
                });
            }

            bFirst++;

            polylinesArray.push(polyline);
        }


        google.maps.LatLng.prototype.distanceFrom = function(latlng) {
            var lat = [this.lat(), latlng.lat()]
            var lng = [this.lng(), latlng.lng()] //var R = 6371; // km (change this constant to get miles)
            var R = 6378137; // In meters
            var dLat = (lat[1] - lat[0]) * Math.PI / 180;
            var dLng = (lng[1] - lng[0]) * Math.PI / 180;
            var a = Math.sin(dLat / 2) * Math.sin(dLat / 2) + Math.cos(lat[0] * Math.PI / 180) * Math.cos(lat[1] * Math.PI / 180) * Math.sin(dLng / 2) * Math.sin(dLng / 2);
            var c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));
            var d = R * c;
            return Math.round(d);
        }

        google.maps.Marker.prototype.distanceFrom = function(marker) {
            return this.getPosition().distanceFrom(marker.getPosition());
        }

        google.maps.Polyline.prototype.getLength = function() {
            var d = 0;
            var path = this.getPath();
            var latlng;
            for (var i = 0; i < path.getLength() - 1; i++) {
                latlng = [path.getAt(i), path.getAt(i + 1)];
                d += latlng[0].distanceFrom(latlng[1]);
            }
            return d;
        }

        // 删除所有叠加物 
        function deleteOverlays() {
            bFirst = 1;
            if (lenArray) {
                for (i in lenArray) {
                    lenArray[i].setMap(null);
                }
                lenArray.length = 0;
            }

            //清除原有折线路径
            if (polylinesArray) {
                for (i in polylinesArray) {
                    polylinesArray[i].setMap(null);
                }
                polylinesArray = [];
            }
        }


    </script>

    <script type="text/javascript">

        $(document).ready(function() {

            var accordion_head = $('.accordion > li > a'),
				accordion_body = $('.accordion li > .sub-menu');
            accordion_head.first().addClass('active').next().slideDown('normal');
            accordion_head.live('click', function(event) {
                //event.preventDefault();
                if ($(this).attr('class') != 'active') {
                    accordion_body.slideUp('normal');
                    $(this).next().stop(true, true).slideToggle('normal');
                    accordion_head.removeClass('active');
                    $(this).addClass('active');
                    var itemID = $(this).attr('id');
                    yyCurType = itemID;
                    for (i in yyMarkerArray) {
                        yyMarkerArray[i].setMap(null);
                    }
                    if (itemID == 'newLi') {
                        for (i in yyNewMarkerArray) {
                            yyNewMarkerArray[i].setMap(map);
                        }
                    }
                    else if (itemID == 'sucLi') {
                    for (i in yySucMarkerArray) {
                        yySucMarkerArray[i].setMap(map);
                    }
                }
                    else if (itemID == 'failLi') {
                    for (i in yyFailMarkerArray) {
                        yyFailMarkerArray[i].setMap(map);
                    }
                }
                }
            });

            $("li ul li").click(function() {
                $("div[@id=testDivID1] li ul li").each(function() {
                    //alert(this.id)
                    this.className = "";
                });
                this.className = "selected";
            });

            $(".about_btn").click(function() {
                $('.about_us').show();
            });
            $(".close").click(function() {
                $('.about_us').hide();
            });
            $(".full").click(function() {
                $('.map_info').hide();
                $('#map').css("margin-left", "0");
                $('.panelarrow').show();
                MapInit();
            });
            $(".panelarrow").click(function() {
                $('.map_info').show();
                $('#map').css("margin-left", "335px");
            });
            $(".sub-menu li:odd").addClass('color');
            $('a').bind("focus", function() {
                $(this).blur();
            })
            $("#map").css("height", $(document).height());
        });
    </script>

</head>
<body onload="MapInit()">
    <div id="page">
        <div class="fanhui">
            <a href="javascript:void(0)" class="panelarrow" style="display: none"></a>
        </div>
        <div id="map">
        </div>
        <div class="map_info">
            <div class="head">
                <h1>
                    <img src="image/logo.png"></h1>
            </div>
            <div class="top_btn">
                <div class="about_us_link">
                    <a href="javascript:void(0)" class="map_btn about_btn">关于本站</a>
                </div>
                <div class="large">
                    <a href="javascript:void(0)" class="map_btn full">全屏</a>
                </div>
                <div class="large_ico">
                    <a href="javascript:void(0)" class="full"></a>
                </div>
            </div>
            <div class="about_us" style="display: none">
                <a href="javascript:void(0)" class="close"></a>
                <p>
                    习近平总书记深刻指出，我们党领导人民进行社会主义建设，有改革开放前和改革开放后两个历史时期，这是两个相互联系又有重大区别的时期，但本质上都是我们党领导人民进行社会主义建设的实践探索。他强调，对改革开放前的历史时期要正确评价，不能用改革开放后的历史时期否定改革开放前的历史时期，也不能用改革开放前的历史时期否定改革开放后的历史时期（以下简称“两个不能否定”）。习近平总书记的这一重要论述，集中体现了我们党对于这一重大问题的根本立场和鲜明态度。学习习近平总书记的重要论述，对于我们从宏观上正确认识和把握改革开放前后两个历史时期乃至整个党的历史，进一步在坚定党的历史自信中坚定中国特色社会主义道路自信、理论自信、制度自信，坚定不移地把中国特色社会主义伟大事业继续推向前进，具有重要指导意义。
                </p>
            </div>
            <div class="forecas">
                <div id="testDivID1" class="forecas_tlist">
                    <ul class="accordion">
                        <li ><a id="newLi" href="javascript:void(0)">最新预报</a>
                            <ul id="ulIDTest1" class="sub-menu">
<!--                                 <li ><span class="number">1</span> <span class="time">2013-05-07 11:27</span> -->
<!--                                     <span class="title">我是广州没有地震</span> </li> -->
                            </ul>
                        </li>
                        <li ><a id="sucLi" href="javascript:void(0)">成功预报</a>
                            <ul id="ulIDTest2" class="sub-menu">
<!--                                 <li><span class="number">1</span> <span class="time">2013-05-07 11:27</span> <span -->
<!--                                     class="title">台湾花莲7.2级地震</span> </li> -->
                            </ul>
                        </li>
                        <li ><a id="failLi" href="javascript:void(0)">失败预报</a>
                            <ul id="ulIDTest3" class="sub-menu">
<!--                                 <li><span class="number">5</span> <span class="time">2013-05-07 11:27</span> <span -->
<!--                                     class="title">台湾花莲7.2级地震</span> </li> -->
                            </ul>
                        </li>
                    </ul>
                </div>
            </div>
            <div class="foot">
                <p>
                    © 2013 地质异常监测组 版权所有</p>
            </div>
        </div>
    </div>
    <form id="form1" runat="server">
    </form>
</body>
</html>
