<head>
<meta http-equiv="Content-type" content="text/html;charset=utf-8"/>
</head>
<?

	include ("dblib.php");
	$response = array();
	if (isset($_POST['email'])) {

		$email = $_POST['email'];
		$point = $_POST['point'];
		

		$connect = mysql_connect($host,$user,$pass) or die("SQL server에 연결할 수 없습니다."); 
		mysql_select_db($db,$connect);
		
		
		$result=mysql_query("update user set point=".$point." where BINARY email='".$email."'");
		
		if($result!=NULL)
		{
			echo "Success!";
		}
		
		
	} else {
    
		echo "0:ErrorMessage : value of email is null!<br>";
	}

	echo "<br><a href='admin.php'>관리자페이지로</a>";


	
?>