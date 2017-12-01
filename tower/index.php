<html>
<head>
<meta http-equiv="Content-type" content="text/html;charset=utf-8"/>
<title>TowerBattle</title>
</head>
<body>
<font size=20>환영합니다. TOWERBATTLE(Ver1.0) 서버입니다.</font>
<br><br><a href=admin.php>관리자페이지입장</a>
<?
	include ("dblib.php");
	$connect = mysql_connect($host,$user,$pass) or die("SQL server에 연결할 수 없습니다."); 
	mysql_select_db($db,$connect);
	$result = mysql_query("select email from user");
	$equal=1;
	while($row=mysql_fetch_array($result))
	{
		if(strcmp($row['email'],'tower')==0)
			$equal=0;
		
	}
	if($equal==1)
		$result = mysql_query("insert into user values(null,'tower','tower','000-000',0,0)");
	else
		

?>
</body>
</html>
