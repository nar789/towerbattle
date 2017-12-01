<head>
<meta http-equiv="Content-type" content="text/html;charset=utf-8"/>
</head>
<?

	include ("dblib.php");
	
	


	$connect = mysql_connect($host,$user,$pass) or die("SQL server에 연결할 수 없습니다."); 
	
	//$result = mysql_query("create database ".$db);
	
	mysql_select_db($db,$connect);
	
	$result = mysql_query("create table user(no int(11) primary key auto_increment,email varchar(50),password varchar(50),account varchar(50),point int(30),cash int(10))");
	
	$result = mysql_query("insert into user(null,'tower','tower','1234',0,0)");
	
	
	echo "설치가 완료됐습니다.!!";
	echo "<br><a href='index.php'>홈으로</a>";



	
?>