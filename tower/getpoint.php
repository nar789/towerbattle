<head>
<meta http-equiv="Content-type" content="text/html;charset=utf-8"/>
</head>
<?
	include ("dblib.php");

	$response = array();
	if (isset($_POST['email'])) {

		$email = $_POST['email'];
		

		$connect = mysql_connect($host,$user,$pass) or die("SQL server에 연결할 수 없습니다."); 
		mysql_select_db($db,$connect);
		
		
		$result=mysql_query("select point from user where BINARY email='".$email."'");
		
		if($response=mysql_fetch_array($result))
		{
			echo $response['point']."]<br>";
		}
		
		
	} else {
    
		echo "0:ErrorMessage : value of email is null!<br>";
	}

	echo "<br><a href='admin.php'>관리자페이지로</a>";


	
?>