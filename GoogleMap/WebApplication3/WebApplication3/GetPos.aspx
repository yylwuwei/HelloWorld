<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="GetPos.aspx.cs" Inherits="WebApplication3.GetPos" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>获取点击经纬度</title>
    <script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.6/jquery.min.js"></script>

    <script type="text/javascript" src="http://maps.google.com/maps/api/js?sensor=false"></script>

    <script type="text/javascript">

        var map;
        var DefaultLat = 23.16667;
        var DefaultLng = 113.23333;
        var DefaultZoom = 3; //默认情况下的zoom

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

            google.maps.event.addListener(map, 'click', function(event) {
                addMarker(event.latLng);
            });
        }

        function addMarker(location) {

             var yyMarker = new google.maps.Marker({
                position: location,
                map: map
            });
            var posInfo = yyMarker.getPosition();
            var yyContentStr = posInfo.lat() + "&nbsp,&nbsp" + posInfo.lng();
            var yyInfowindow = new google.maps.InfoWindow({
                content: yyContentStr
            });
            yyInfowindow.open(map, yyMarker);
        }        

    </script>
</head>
<body onload="MapInit()">
    <div>
        <div id="map" style="width: 80%; height: 700px">
        </div>
    </div>
    <form id="form1" runat="server">
    </form>
</body>
</html>
